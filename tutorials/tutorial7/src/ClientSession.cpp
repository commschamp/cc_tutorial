#include "ClientSession.h"

#include <cassert>
#include <iterator>
#include <iomanip>

#include "comms/process.h"
#include "comms/iterator.h"

namespace cc_tutorial
{

ClientSession::ClientSession(boost_wrap::io& io)
  : Base(io)
{
    m_handlers.emplace_back(new Handler1);
    m_handlers.emplace_back(new Handler2);
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

            // Dispatch to all the handlers
            std::cout << "-----------------------------\n";
            for (auto& h : m_handlers) {
                msg->dispatch(*h);
            }

            std::cout << std::endl;
            doNextStage();
        }

        // Iterator has been advanced, updated consumed counter
        consumed += static_cast<std::size_t>(std::distance(begIter, iter));
    }
    return  consumed;
}

void ClientSession::sendMessage(const Message& msg)
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
        /* CommsStage_Msg2 */ &ClientSession::sendMsg2,
        /* CommsStage_Msg3 */ &ClientSession::sendMsg3,
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

void ClientSession::sendMsg3()
{
    Msg3 msg;
    sendMessage(msg);
}

void ClientSession::Handler1::handle(Msg1& msg)
{
    std::cout << "Handler1: Received " << msg.doName() << std::endl;
}

void ClientSession::Handler1::handle(Message& msg)
{
    std::cout << "Handler1: Common handling of message with ID=" << (unsigned)msg.getId() << std::endl;
}

void ClientSession::Handler2::handle(Msg2& msg)
{
    std::cout << "Handler2: Received " << msg.doName() << std::endl;
}

void ClientSession::Handler2::handle(Message& msg)
{
    std::cout << "Handler2: Common handling of message with ID=" << (unsigned)msg.getId() << std::endl;
}

SessionPtr Session::createClient(boost_wrap::io& io)
{
    return SessionPtr(new ClientSession(io));
}


} // namespace cc_tutorial
