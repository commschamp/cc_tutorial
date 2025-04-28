#include "ServerSession.h"

#include <cassert>
#include <iterator>
#include <memory>

#include "comms/process.h"
#include "comms/iterator.h"

#include "tutorial27/sub1/dispatch/DispatchServerInputMessage.h"
#include "tutorial27/sub2/dispatch/DispatchServerInputMessage.h"

namespace cc_tutorial
{

void ServerSession::handle(Msg1& msg)
{
    std::cout << "Received message \"" << msg.doName() << "\"" << std::endl;
    assert(m_protStage == ProtStage_sub1);
    sendMessage(msg);
    m_sub1Msg.reset(new Msg2);
}

void ServerSession::handle(Msg2& msg)
{
    std::cout << "Received message \"" << msg.doName() << "\"" << std::endl;
    assert(m_protStage == ProtStage_sub1);
    sendMessage(msg);    
    m_sub1Msg.reset(new Msg3);
}

void ServerSession::handle(Msg3& msg)
{
    std::cout << "Received message \"" << msg.doName() << "\"" << std::endl;
    assert(m_protStage == ProtStage_sub1);
    sendMessage(msg);    
    m_sub1Msg.reset();
    m_protStage = ProtStage_sub2;
}

void ServerSession::handle(Msg4& msg)
{
    std::cout << "Received message \"" << msg.doName() << "\"" << std::endl;
    assert(m_protStage == ProtStage_sub2);
    sendMessage(msg);
}

void ServerSession::handle(Msg5& msg)
{
    std::cout << "Received message \"" << msg.doName() << "\"" << std::endl;
    assert(m_protStage == ProtStage_sub2);
    sendMessage(msg);    
}

void ServerSession::handle(Msg6& msg)
{
    std::cout << "Received message \"" << msg.doName() << "\"" << std::endl;
    assert(m_protStage == ProtStage_sub2);
    sendMessage(msg);    
}

void ServerSession::handle(Message& msg)
{
    std::cerr << "ERROR: Failed to properly dispatch message: " << msg.name() << std::endl;
}

bool ServerSession::startImpl()
{
    m_sub1Msg.reset(new Msg1);
    return true;
}

std::size_t ServerSession::processInputImpl(const std::uint8_t* buf, std::size_t bufLen)
{
    std::cout << "Processing input: " << std::hex;
    std::copy_n(buf, bufLen, std::ostream_iterator<unsigned>(std::cout, " "));
    std::cout << std::dec << std::endl;

    using ProcFunc = std::size_t (ServerSession::*)(const std::uint8_t* buf, std::size_t bufLen);
    static const ProcFunc ProcMap[] = {
        /* ProtStage_sub1 */ &ServerSession::processInputSub1,
        /* ProtStage_sub2 */ &ServerSession::processInputSub2,
    };
    static const std::size_t ProcMapSize = std::extent<decltype(ProcMap)>::value;
    static_assert(ProcMapSize == ProtStage_numOfValues, "Invalid map");

    auto idx = static_cast<unsigned>(m_protStage);
    assert(idx < ProcMapSize);

    auto func = ProcMap[idx];
    return (this->*func)(buf, bufLen);
}

void ServerSession::sendMessage(const Message& msg)
{
    std::cout << "Sending message \"" << msg.name() << "\"" << std::endl;

    std::vector<std::uint8_t> output;

    // Serialize message into the buffer (including framing)
    // The serialization uses polymorphic write functionality.
    auto writeIter = std::back_inserter(output);

    using WriteFunc = comms::ErrorStatus (ServerSession::*)(const Message& msg, WriteIter& iter, std::size_t bufLen);
    static const WriteFunc WriteMap[] = {
        /* ProtStage_sub1 */ &ServerSession::writeMessageSub1,
        /* ProtStage_sub2 */ &ServerSession::writeMessageSub2,
    };
    static const std::size_t WriteMapSize = std::extent<decltype(WriteMap)>::value;
    static_assert(WriteMapSize == ProtStage_numOfValues, "Invalid map");

    auto idx = static_cast<unsigned>(m_protStage);
    assert(idx < WriteMapSize);

    auto func = WriteMap[idx];
    auto es = (this->*func)(msg, writeIter, output.max_size());
    if (es != comms::ErrorStatus::Success) {
        assert(!"Write operation failed unexpectedly");
        return;
    }    

    // Send (re)serialized message back
    sendOutput(&output[0], output.size());
}

std::size_t ServerSession::processInputSub1(const std::uint8_t* buf, std::size_t bufLen)
{
    assert(m_sub1Msg);
    auto* prev = buf;
    std::size_t consumed = 0U;
    while ((consumed < bufLen) && (m_protStage == ProtStage_sub1)) {
        auto es = comms::processSingleWithDispatch(buf, bufLen, m_sub1Frame, *m_sub1Msg, *this);
        if (es != comms::ErrorStatus::Success) {
            std::cerr << "ERROR: unexpected protocol sequence" << std::endl;
            return consumed;
        }

        consumed += static_cast<std::size_t>(std::distance(prev, buf));
    }

    return consumed;
}

std::size_t ServerSession::processInputSub2(const std::uint8_t* buf, std::size_t bufLen)
{
    return comms::processAllWithDispatch(buf, bufLen, m_sub2Frame, *this);
}

comms::ErrorStatus ServerSession::writeMessageSub1(const Message& msg, WriteIter& iter, std::size_t bufLen)
{
    return m_sub1Frame.write(msg, iter, bufLen);
}

comms::ErrorStatus ServerSession::writeMessageSub2(const Message& msg, WriteIter& iter, std::size_t bufLen)
{
    return m_sub2Frame.write(msg, iter, bufLen);
}

SessionPtr Session::createServer(boost_wrap::io& io)
{
    return SessionPtr(new ServerSession(io));
}

} // namespace cc_tutorial
