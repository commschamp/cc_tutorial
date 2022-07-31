#include "ClientSession.h"

#include <cassert>
#include <iterator>

#include "comms/cast.h"
#include "comms/iterator.h"
#include "comms/process.h"

namespace cc_tutorial
{

void ClientSession::handle(Msg1& msg)
{
    std::cout << "Received \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << '\n' <<
        '\t' << msg.field_f1().name() << " = " << msg.field_f1().value() << '\n' <<
        '\t' << msg.field_f2().name() << " = " << msg.field_f2().value() << '\n' <<
        std::endl;


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

    msg.field_f1().setS1();
    msg.field_f2().value() = "hello";

    sendMessage(msg);
}

SessionPtr Session::createClient(boost_wrap::io& io)
{
    return SessionPtr(new ClientSession(io));
}

} // namespace cc_tutorial
