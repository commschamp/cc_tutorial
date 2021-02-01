#include "ServerSession.h"

#include <cassert>

#include "comms/process.h"
#include "comms/iterator.h"

namespace cc_tutorial
{

void ServerSession::handle(Message& msg)
{
    // The statement below uses polymorphic message name and ID retrievals.
    std::cout << "Received message \"" << msg.name() << "\" with ID=" << (unsigned)msg.getId() << std::endl;
    sendMessage(msg);
}

std::size_t ServerSession::processInputImpl(const std::uint8_t* buf, std::size_t bufLen)
{
    std::cout << "Processing input: " << std::hex;
    std::copy_n(buf, bufLen, std::ostream_iterator<unsigned>(std::cout, " "));
    std::cout << std::dec << std::endl;

    // Process reported input, create relevant message objects and
    // dispatch all the created messages
    // to this object for handling (handle() member function will be called)
    MsgBuf msgBuf;
    auto consumed = preProcessInput(buf, bufLen, msgBuf);

    if (!msgBuf.empty()) {
        comms::processAllWithDispatch(&msgBuf[0], msgBuf.size(), m_frame, *this);
    }

    return consumed;
}

void ServerSession::sendMessage(const Message& msg)
{
    MsgBuf output;

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

    // Introduce special characters
    postProcessOutput(output);

    // Send (re)serialized message back
    sendOutput(&output[0], output.size());

    std::cout << "Sending message \"" << msg.name() << "\" with ID=" << (unsigned)msg.getId() << ": " << std::hex;
    std::copy(output.begin(), output.end(), std::ostream_iterator<unsigned>(std::cout, " "));
    std::cout << std::dec << std::endl;    
}

SessionPtr Session::createServer(boost_wrap::io& io)
{
    return SessionPtr(new ServerSession(io));
}

} // namespace cc_tutorial
