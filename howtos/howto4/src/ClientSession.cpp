#include "ClientSession.h"

#include <cassert>
#include <iterator>
#include <iomanip>

#include "comms/process.h"
#include "comms/iterator.h"

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

void ClientSession::handle(Msg& msg)
{
    std::cout << "Received message \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << '\n';
    
    auto& propsVec = msg.field_props().value();
    std::cout << '\t' << msg.field_props().name() << " (" << propsVec.size() << " elements)\n";
    for (auto idx = 0U; idx < propsVec.size(); ++idx) {
        const auto& elem = propsVec[idx]; // access to the variant element
        elem.currFieldExec(PropDispatchHelper(*this));
    }

    std::cout << std::endl;
    doNextStage();    
}

void ClientSession::handle(Message& msg)
{
    static_cast<void>(msg);
    std::cerr << "ERROR: Received unexpected message, should not happen" << std::endl;
    assert(!"Should not happen");
}

bool ClientSession::startImpl()
{
    doNextStage();
    return true;
}

void ClientSession::handleProp(const Prop1& prop)
{
    std::cout << "\t\t" << prop.name() << ":\n" <<
        "\t\t\t" << prop.field_key().name() << " = " << (unsigned)prop.field_key().value() << '\n' <<
        "\t\t\t" << prop.field_length().name() << " = " << (unsigned)prop.field_length().value() << '\n' <<
        "\t\t\t" << prop.field_val().name() << " = " << prop.field_val().value() << '\n';
}

void ClientSession::handleProp(const Prop2& prop)
{
    std::cout << "\t\t" << prop.name() << ":\n" <<
        "\t\t\t" << prop.field_key().name() << " = " << (unsigned)prop.field_key().value() << '\n' <<
        "\t\t\t" << prop.field_length().name() << " = " << (unsigned)prop.field_length().value() << '\n' <<
        "\t\t\t" << prop.field_val().name() << " = " << prop.field_val().value() << '\n';
}

void ClientSession::handleProp(const Prop3& prop)
{
    auto& val = prop.field_val().value();
    std::cout << "\t\t" << prop.name() << ":\n" <<
        "\t\t\t" << prop.field_key().name() << " = " << (unsigned)prop.field_key().value() << '\n' <<
        "\t\t\t" << prop.field_length().name() << " = " << (unsigned)prop.field_length().value() << '\n' <<
        "\t\t\t" << prop.field_val().name() << " = " << std::string(val.begin(), val.end()) << '\n';
}

void ClientSession::handleProp(const AnyProp& prop)
{
    std::cout << "\t\t" << prop.name() << ":\n" <<
        "\t\t\t" << prop.field_key().name() << " = " << (unsigned)prop.field_key().value() << '\n' <<
        "\t\t\t" << prop.field_length().name() << " = " << (unsigned)prop.field_length().value() << '\n' <<
        "\t\t\t" << prop.field_val().name() << " = " << std::hex;

    std::copy(prop.field_val().value().begin(), prop.field_val().value().end(), std::ostream_iterator<unsigned>(std::cout, " "));
    std::cout << std::dec << '\n';
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
        /* CommsStage_Msg */ &ClientSession::sendMsg,
    };
    static const std::size_t MapSize = std::extent<decltype(Map)>::value;
    static_assert(MapSize == CommsStage_NumOfValues, "Invalid Map");

    auto func = Map[m_currentStage];
    (this->*func)(); // Call appropriate sending function
}

void ClientSession::sendMsg()
{
    Msg msg;
    auto& propsVec = msg.field_props().value();
    propsVec.resize(3);
    propsVec[0].initField_prop1().field_val().value() = 0x12345678;
    propsVec[1].initField_prop2().field_val().value() = 1.23;
    propsVec[2].initField_prop3().field_val().value() = "hello";
    
    msg.doRefresh(); // Update the length fields.

    std::vector<std::uint8_t> output;
    output.reserve(m_frame.length(msg));
    auto writeIter = std::back_inserter(output);
    auto es = m_frame.write(msg, writeIter, output.max_size());
    if (es == comms::ErrorStatus::UpdateRequired) {
        auto updateIter = &output[0];
        es = m_frame.update(updateIter, output.size());
    }
    assert(es == comms::ErrorStatus::Success);
    sendOutput(&output[0], output.size());
}

SessionPtr Session::createClient(boost_wrap::io& io)
{
    return SessionPtr(new ClientSession(io));
}

} // namespace cc_tutorial
