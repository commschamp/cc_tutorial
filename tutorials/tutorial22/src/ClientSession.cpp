#include "ClientSession.h"

#include <cassert>
#include <iterator>

#include "comms/cast.h"
#include "comms/iterator.h"
#include "comms/process.h"

namespace cc_tutorial
{

namespace
{

class PropDispatchHelper
{
public:
    explicit PropDispatchHelper(ClientSession& session)
      : m_session(session)
    {
    }

    template <std::size_t TIdx, typename TField>
    void operator()(const TField& field)
    {
        m_session.handleProp(field);
    }

private:
    ClientSession& m_session;
};

} // namespace    

void ClientSession::handle(Msg1& msg)
{
    std::cout << "Received message \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << std::endl;

    auto& f1Vec = msg.field_f1().value();
    std::cout << '\t' << msg.field_f1().name() << " (" << f1Vec.size() << " elements)\n";
    for (auto idx = 0U; idx < f1Vec.size(); ++idx) {
        auto& elem = f1Vec[idx]; // access to the variant element
        elem.currentFieldExec(PropDispatchHelper(*this));
    }

    std::cout << std::endl;    

    if (m_currentStage != CommsStage_Msg1) {
        std::cerr << "ERROR: Unexpected stage" << std::endl;
        return;
    }

    doNextStage();
}

void ClientSession::handle(Message& msg)
{
    std::cerr << "ERROR: Received unexpected message \"" << msg.name() << " with ID=" << (unsigned)msg.getId() << std::endl;
}


void ClientSession::handleProp(const Prop1& prop)
{
    std::cout << "\t\t" << prop.name() << ":\n" <<
        "\t\t\t" << prop.field_key().name() << " = " << (unsigned)prop.field_key().value() << '\n' <<
        "\t\t\t" << prop.field_length().name() << " = " << (unsigned)prop.field_length().getValue() << '\n' <<
        "\t\t\t" << prop.field_val().name() << " = " << prop.field_val().value() << '\n';
}

void ClientSession::handleProp(const Prop2& prop)
{
    std::cout << "\t\t" << prop.name() << ":\n" <<
        "\t\t\t" << prop.field_key().name() << " = " << (unsigned)prop.field_key().value() << '\n' <<
        "\t\t\t" << prop.field_length().name() << " = " << (unsigned)prop.field_length().getValue() << '\n' <<
        "\t\t\t" << prop.field_val().name() << " = " << prop.field_val().value() << '\n';
}

void ClientSession::handleProp(const AnyProp& prop)
{
    std::cout << "\t\t" << prop.name() << ":\n" <<
        "\t\t\t" << prop.field_key().name() << " = " << (unsigned)prop.field_key().value() << '\n' <<
        "\t\t\t" << prop.field_length().name() << " = " << (unsigned)prop.field_length().getValue() << '\n' <<
        "\t\t\t" << prop.field_val().name() << " = " << std::hex;

    std::copy(prop.field_val().value().begin(), prop.field_val().value().end(), std::ostream_iterator<unsigned>(std::cout, " "));
    std::cout << std::dec << '\n';
}


bool ClientSession::startImpl()
{
    doNextStage();
    return true;
}

std::size_t ClientSession::processInputImpl(const std::uint8_t* buf, std::size_t bufLen)
{
    std::cout << "Processing input: " << std::hex;
    std::copy_n(buf, bufLen, std::ostream_iterator<unsigned>(std::cout, " "));
    std::cout << std::dec << std::endl;

    // Process reported input, create relevant message objects and
    // dispatch all the created messages
    // to this object for handling (appropriate handle() member function will be called)
    return comms::processAllWithDispatch(buf, bufLen, m_frame, *this);
}

void ClientSession::sendMessage(Message& msg)
{
    std::cout << "Sending message \"" << msg.name() << "\" with ID=" << (unsigned)msg.getId() << std::endl;

    // The statement below uses polymorphic message name and ID retrievals.
    std::vector<std::uint8_t> output;

    // Use polymorphic serialization length calculation to reserve
    // needed capacity
    output.reserve(m_frame.length(msg));

    // Serialize message into the buffer (including framing)
    // The serialization uses polymorphic write functionality.
    auto writeIter = std::back_inserter(output);

    // The frame will use polymorphic message ID retrieval to
    // prefix message payload with message ID
    auto es = m_frame.write(msg, writeIter, output.max_size());
    if (es == comms::ErrorStatus::UpdateRequired) {
        auto updateIter = &output[0];
        es = m_frame.update(updateIter, output.size());
    }

    if (es != comms::ErrorStatus::Success) {
        assert(!"Write operation failed unexpectedly");
        return;
    }

    // Send serialized message back
    sendOutput(&output[0], output.size());
}

void ClientSession::doNextStage()
{
    do {
        if (CommsStage_NumOfValues <= m_currentStage) {
            // Happens in first cycle
            m_currentStage = static_cast<decltype(m_currentStage)>(0);
            break;
        }

        m_currentStage =
            static_cast<decltype(m_currentStage)>(
                static_cast<unsigned>(m_currentStage) + 1);

        if (m_currentStage < CommsStage_NumOfValues) {
            break;
        }

        // Client execution is complete
        getIo().stop();
        return;
    } while (false);

    using NextSendFunc = void (ClientSession::*)();
    static const NextSendFunc Map[] = {
        /* CommsStage_Msg1 */ &ClientSession::sendMsg1,
    };
    static const std::size_t MapSize = std::extent<decltype(Map)>::value;
    static_assert(MapSize == CommsStage_NumOfValues, "Invalid Map");

    auto func = Map[m_currentStage];
    (this->*func)(); // Call appropriate sending function
}

void ClientSession::sendMsg1()
{
    Msg1 msg;

    auto& listOfProps = msg.field_f1().value(); // vector of variant fields
    listOfProps.resize(2);
    assert(msg.doLength() == 0U);
    assert(!listOfProps[0].valid());
    assert(!listOfProps[1].valid());

    listOfProps[0].initField_prop1().field_val().value() = 0x12;
    listOfProps[1].initField_prop2().field_val().value().assign(300, 'a'); // Force long length form.

    msg.doRefresh(); // Bring message to a consistent state    
    sendMessage(msg);
}

SessionPtr Session::createClient(boost_wrap::io& io)
{
    return SessionPtr(new ClientSession(io));
}

} // namespace cc_tutorial
