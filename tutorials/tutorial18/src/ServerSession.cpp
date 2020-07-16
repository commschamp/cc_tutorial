#include "ServerSession.h"

#include <iostream>
#include <cassert>

#include "comms/process.h"
#include "comms/iterator.h"

namespace cc_tutorial
{

void ServerSession::handle(Message& msg)
{
    std::cerr << "ERROR: Failed to properly dispatch message: " << msg.name() << std::endl;
}

std::size_t ServerSession::processInputImpl(const std::uint8_t* buf, std::size_t bufLen)
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

        tutorial18::MsgId msgId = tutorial18::MsgId_ValuesLimit;
        std::size_t msgIdx = std::numeric_limits<std::size_t>::max();
        auto es = 
            m_frame.read(
                msg, 
                iter, 
                remLen, 
                comms::protocol::msgId(msgId),
                comms::protocol::msgIndex(msgIdx));

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

            std::cout << "Detected message: ID=" << (unsigned)msgId << "; idx=" << msgIdx << std::endl; 

            // Dispatch using id + index to map to real type
            comms::dispatchMsg<ServerInputMessages>(msgId, msgIdx, *msg, *this);
        }

        // Iterator has been advanced, updated consumed counter
        consumed += static_cast<std::size_t>(std::distance(begIter, iter));
    }

    return consumed;
}

void ServerSession::sendMessage(const Message& msg)
{
    std::vector<std::uint8_t> output;

    // Use polymorphic serialization length calculation to create
    // buffer of the requires size
    output.resize(m_frame.length(msg));

    // Serialize message into the buffer (including framing)
    // The serialization uses polymorphic write functionality.
    auto writeIter = &output[0];
    auto es = m_frame.write(msg, writeIter, output.size());
    if (es != comms::ErrorStatus::Success) {
        assert(!"Write operation failed unexpectedly");
        return;
    }

    // writeIter has been advanced, check that it reached end of the allocated buffer.
    assert(output.size() == static_cast<std::size_t>(std::distance(&output[0], writeIter)));

    // Send (re)serialized message back
    sendOutput(&output[0], output.size());
}

SessionPtr Session::createServer(boost_wrap::io& io)
{
    return SessionPtr(new ServerSession(io));
}

} // namespace cc_tutorial
