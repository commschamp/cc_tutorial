#include "ClientSession.h"

#include <cassert>
#include <iterator>
#include <iomanip>
#include <iostream>

#include "comms/process.h"
#include "comms/iterator.h"

namespace cc_tutorial
{

void ClientSession::handle(Msg2& msg)
{
    std::cout << "Received message \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << std::endl;

    if (m_currentStage != CommsStage_Msg1) {
        std::cerr << "ERROR: Unexpected message received: " << std::endl;
        return;
    }

    doNextStage();
}

void ClientSession::handle(Msg3& msg)
{
    std::cout << "Received message \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << std::endl;

    if (m_currentStage != CommsStage_Msg3) {
        std::cerr << "ERROR: Unexpected message received: " << std::endl;
        return;
    }

    doNextStage();
}

void ClientSession::handle(Msg4& msg)
{
    std::cout << "Received message \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << std::endl;

    if (m_currentStage != CommsStage_Msg4) {
        std::cerr << "ERROR: Unexpected message received: " << std::endl;
        return;
    }

    doNextStage();
}

void ClientSession::handle(Msg5& msg)
{
    std::cout << "Received message \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << std::endl;

    if (m_currentStage != CommsStage_Msg5) {
        std::cerr << "ERROR: Unexpected message received: " << std::endl;
        return;
    }

    doNextStage();
}

void ClientSession::handle(Message& msg)
{
    static_cast<void>(msg);
    std::cout << "ERROR: Received unexpected message \"" << msg.name() << "\" with ID=" << (unsigned)msg.getId() << std::endl;
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
    // to this object for handling (handle() member function will be called)
    return comms::processAllWithDispatch(buf, bufLen, m_frame, *this);
}

void ClientSession::sendMessage(const Message& msg)
{
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
    if (es != comms::ErrorStatus::Success) {
        std::cerr << "ERROR: Write operation failed with status: " << (unsigned)es << std::endl;
        return;
    }

    // Send serialized message back
    sendOutput(&output[0], output.size());

    std::cout << "Sending message \"" << msg.name() << "\" with ID=" << (unsigned)msg.getId() << ": " << std::hex;
    std::copy(output.begin(), output.end(), std::ostream_iterator<unsigned>(std::cout, " "));
    std::cout << std::dec << std::endl;
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
        /* CommsStage_Msg3 */ &ClientSession::sendMsg3,
        /* CommsStage_Msg4 */ &ClientSession::sendMsg4,
        /* CommsStage_Msg5 */ &ClientSession::sendMsg5,
    };
    static const std::size_t MapSize = std::extent<decltype(Map)>::value;
    static_assert(MapSize == CommsStage_NumOfValues, "Invalid Map");

    auto func = Map[m_currentStage];
    (this->*func)(); // Call appropriate sending function
}

void ClientSession::sendMsg1()
{
    Msg1 msg;
    sendMessage(msg);

    // try to send Msg2, expected to fail
    Msg2 msg2;
    sendMessage(msg2);
}

void ClientSession::sendMsg3()
{
    Msg3 msg;
    sendMessage(msg);
}

void ClientSession::sendMsg4()
{
    Msg4 msg;
    sendMessage(msg);
}

void ClientSession::sendMsg5()
{
    Msg5 msg;
    sendMessage(msg);
}

SessionPtr Session::createClient(boost_wrap::io& io)
{
    return SessionPtr(new ClientSession(io));
}


} // namespace cc_tutorial
