#include "ServerSession.h"

#include <cassert>

#include "comms/process.h"
#include "comms/iterator.h"

namespace cc_tutorial
{

void ServerSession::handle(Prot1PseudoMsg& msg)
{
    std::cout << "Received message \"" << msg.doName() << '\n';

    MsgBuf prot2ProcessBuf;
    dropEscapes(msg.field_data().value().data(), msg.field_data().value().size(), prot2ProcessBuf);

    std::cout << "post-processed input: " << std::hex;
    std::copy(prot2ProcessBuf.begin(), prot2ProcessBuf.end(), std::ostream_iterator<unsigned>(std::cout, " "));
    std::cout << std::dec << std::endl;

    comms::processAllWithDispatch(prot2ProcessBuf.data(), prot2ProcessBuf.size(), m_prot2Frame, *this);
}

void ServerSession::handle(Prot1Interface& msg)
{
    std::cerr << "ERROR: Received unexpected PROT1 message \"" << msg.name() << " with ID=" << (unsigned)msg.getId() << std::endl;
}

void ServerSession::handle(Prot2Interface& msg)
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

    return comms::processAllWithDispatch(buf, bufLen, m_prot1Frame, *this);
}

void ServerSession::sendMessage(const Prot2Interface& msg)
{
    std::cout << "Sending message \"" << msg.name() << "\" with ID=" << (unsigned)msg.getId() << std::endl;
    MsgBuf output;

    // Use polymorphic serialization length calculation to create
    // buffer of the requires size
    output.resize(m_prot2Frame.length(msg));

    // Serialize message into the buffer (including framing)
    // The serialization uses polymorphic write functionality.
    auto writeIter = &output[0];
    auto es = m_prot2Frame.write(msg, writeIter, output.size());
    if (es != comms::ErrorStatus::Success) {
        assert(!"Write operation failed unexpectedly");
        return;
    }

    // writeIter has been advanced, check that it reached end of the allocated buffer.
    assert(output.size() == static_cast<std::size_t>(std::distance(&output[0], writeIter)));

    // Introduce special characters
    addEscapes(output);

    Prot1PseudoMsg pseudoMsg;
    comms::util::assign(pseudoMsg.field_data().value(), output.begin(), output.end());

    MsgBuf finalOutput;
    finalOutput.resize(m_prot1Frame.length(pseudoMsg));

    auto finalWriteIter = &finalOutput[0];
    es = m_prot1Frame.write(pseudoMsg, finalWriteIter, finalOutput.size());
    if (es != comms::ErrorStatus::Success) {
        assert(!"Write operation failed unexpectedly");
        return;
    }    

    // Send (re)serialized message back
    sendOutput(&finalOutput[0], finalOutput.size());
}

SessionPtr Session::createServer(boost_wrap::io& io)
{
    return SessionPtr(new ServerSession(io));
}

} // namespace cc_tutorial
