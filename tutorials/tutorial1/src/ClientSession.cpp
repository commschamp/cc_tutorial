#include "ClientSession.h"

#include <cassert>
#include <iterator>

#include "comms/process.h"
#include "comms/iterator.h"

namespace cc_tutorial
{

void ClientSession::handle(Msg1& msg)
{
    // The report below uses NON-polymorphic name and ID retrievals
    std::cout << "Received " << msg.doName() << " with ID=" << (unsigned)msg.doGetId() << std::endl;

    if (m_currentStage != CommsStage_Msg1) {
        std::cerr << "ERROR: Unexpected message received: " << std::endl;
        return;
    }

    doNextStage();
}

void ClientSession::handle(Msg2& msg)
{
    // The report below uses NON-polymorphic name and ID retrievals
    std::cout << "Received " << msg.doName() << " with ID=" << (unsigned)msg.doGetId() << std::endl;

    if (m_currentStage != CommsStage_Msg2) {
        std::cerr << "ERROR: Unexpected message received" << std::endl;
        return;
    }

    doNextStage();
}

void ClientSession::handle(Message& msg)
{
    // The statement below uses polymorphic message name and ID retrievals.
    std::cout << "ERROR: Received unexpected message \"" << msg.name() << "\" with ID=" <<
                 (unsigned)msg.getId() << std::endl;
}

bool ClientSession::startImpl()
{
    doNextStage();
    return true;
}

std::size_t ClientSession::processInputImpl(const std::uint8_t* buf, std::size_t bufLen)
{
    // Similar to server's code comms::processAllWithDispatch can also be
    // called with the same effect. The code below is there for
    // the demonstration purposes of what comms::processAllWithDispatch()
    // is actually doing.
    // return comms::processAllWithDispatch(buf, bufLen, m_frame, *this);

    std::size_t consumed = 0U;
    while (consumed < bufLen) {
        auto begIter = buf + consumed;
        auto remLen = bufLen - consumed;
        auto iter = begIter;

        // Frame class defines smart pointer (std::unique_ptr) to
        // dynamically allocated message object.
        Frame::MsgPtr msg;

        auto es = m_frame.read(msg, iter, remLen);
        if (es == comms::ErrorStatus::NotEnoughData) {
            // Some more data needs to be received
            break;
        }

        if (es == comms::ErrorStatus::ProtocolError) {
            // Framing is wrong, skip one byte and try again
            ++consumed;
            continue;
        }

        if (es == comms::ErrorStatus::Success) {
            assert(msg); // Message object must be allocated

            msg->dispatch(*this); // Uses polymorphic dispatch, appropriate
                                  // handle() member function will be called.
        }

        // Iterator has been advanced, updated consumed counter
        consumed += static_cast<std::size_t>(std::distance(begIter, iter));
    }

    return consumed;
}

void ClientSession::sendMessage(const Message& msg)
{
    // The statement below uses polymorphic message name and ID retrievals.
    std::cout << "Sending message \"" << msg.name() << "\" with ID=" << (unsigned)msg.getId() << std::endl;

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
        /* CommsStage_Msg2 */ &ClientSession::sendMsg2
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
}

void ClientSession::sendMsg2()
{
    Msg2 msg;
    sendMessage(msg);
}


SessionPtr Session::createClient(boost_wrap::io& io)
{
    return SessionPtr(new ClientSession(io));
}

} // namespace cc_tutorial
