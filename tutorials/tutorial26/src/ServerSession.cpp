#include "ServerSession.h"

#include <cassert>
#include <iterator>
#include <memory>

#include "comms/process.h"
#include "comms/iterator.h"

namespace cc_tutorial
{

void ServerSession::handle(Msg1& msg)
{
    std::cout << "Received message \"" << msg.doName() << "\"" << std::endl;
    sendMessage(msg);
    m_msg.reset(new Msg2);
}

void ServerSession::handle(Msg2& msg)
{
    std::cout << "Received message \"" << msg.doName() << "\"" << std::endl;
    sendMessage(msg);
    m_msg.reset(new Msg3);
}

void ServerSession::handle(Msg3& msg)
{
    std::cout << "Received message \"" << msg.doName() << "\"" << std::endl;
    sendMessage(msg);
    m_msg.reset(new Msg1);
}

void ServerSession::handle(Message& msg)
{
    std::cerr << "ERROR: Failed to properly dispatch message: " << msg.name() << std::endl;
}

bool ServerSession::startImpl()
{
    m_msg.reset(new Msg1);
    return true;
}

std::size_t ServerSession::processInputImpl(const std::uint8_t* buf, std::size_t bufLen)
{
    std::cout << "Processing input: " << std::hex;
    std::copy_n(buf, bufLen, std::ostream_iterator<unsigned>(std::cout, " "));
    std::cout << std::dec << std::endl;

    assert(m_msg);
    auto* prev = buf;
    std::size_t consumed = 0U;
    while (consumed < bufLen) {
        auto es = comms::processSingleWithDispatch(buf, bufLen, m_frame, *m_msg, *this);
        if (es != comms::ErrorStatus::Success) {
            std::cerr << "ERROR: unexpected protocol sequence" << std::endl;
            return consumed;
        }

        consumed += static_cast<std::size_t>(std::distance(prev, buf));
    }
    return consumed;
}

void ServerSession::sendMessage(const Message& msg)
{
    std::cout << "Sending message \"" << msg.name() << "\" with ID=" << (unsigned)msg.getId() << std::endl;

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
