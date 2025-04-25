#include "ClientSession.h"

#include <cassert>
#include <iterator>

#include "comms/process.h"
#include "comms/iterator.h"

namespace cc_tutorial
{

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

    using ProcFunc = std::size_t (ClientSession::*)(const std::uint8_t* buf, std::size_t bufLen);
    static const ProcFunc ProcMap[] = {
        /* CommsStage_Msg1 */ &ClientSession::processInputSub1,
        /* CommsStage_Msg2 */ &ClientSession::processInputSub1,
        /* CommsStage_Msg3 */ &ClientSession::processInputSub1,
        /* CommsStage_Msg4 */ &ClientSession::processInputSub2,
        /* CommsStage_Msg5 */ &ClientSession::processInputSub2,
        /* CommsStage_Msg6 */ &ClientSession::processInputSub2,
    };
    static const std::size_t ProcMapSize = std::extent<decltype(ProcMap)>::value;
    static_assert(ProcMapSize == CommsStage_NumOfValues, "Invalid map");

    auto idx = static_cast<unsigned>(m_currentStage);
    assert(idx < ProcMapSize);

    auto func = ProcMap[idx];
    return (this->*func)(buf, bufLen);    
}


std::size_t ClientSession::processInputSub1(const std::uint8_t* buf, std::size_t bufLen)
{
    assert(m_sub1Msg);
    auto* prev = buf;
    auto consumed = 0U;
    while (consumed < bufLen) {
        auto es = comms::processSingleWithDispatch(buf, bufLen, m_sub1Frame, *m_sub1Msg, *this);
        if (es != comms::ErrorStatus::Success) {
            std::cerr << "ERROR: unexpected protocol sequence" << std::endl;
            return consumed;
        }

        consumed += static_cast<std::size_t>(std::distance(prev, buf));
    }

    return consumed;
}

std::size_t ClientSession::processInputSub2(const std::uint8_t* buf, std::size_t bufLen)
{
    return comms::processAllWithDispatch(buf, bufLen, m_sub2Frame, *this);
}

void ClientSession::sendMessage(const Message& msg)
{
    std::cout << "Sending message \"" << msg.name() << "\" with ID=" << (unsigned)msg.getId() << std::endl;

    // The statement below uses polymorphic message name and ID retrievals.
    std::vector<std::uint8_t> output;

    // Serialize message into the buffer (including framing)
    // The serialization uses polymorphic write functionality.
    auto writeIter = std::back_inserter(output);

    using WriteFunc = comms::ErrorStatus (ClientSession::*)(const Message& msg, WriteIter& iter, std::size_t bufLen);
    static const WriteFunc WriteMap[] = {
        /* CommsStage_Msg1 */ &ClientSession::writeMessageSub1,
        /* CommsStage_Msg2 */ &ClientSession::writeMessageSub1,
        /* CommsStage_Msg3 */ &ClientSession::writeMessageSub1,
        /* CommsStage_Msg4 */ &ClientSession::writeMessageSub2,
        /* CommsStage_Msg5 */ &ClientSession::writeMessageSub2,
        /* CommsStage_Msg6 */ &ClientSession::writeMessageSub2,
    };
    static const std::size_t WriteMapSize = std::extent<decltype(WriteMap)>::value;
    static_assert(WriteMapSize == CommsStage_NumOfValues, "Invalid map");

    auto idx = static_cast<unsigned>(m_currentStage);
    assert(idx < WriteMapSize);

    auto func = WriteMap[idx];
    auto es = (this->*func)(msg, writeIter, output.max_size());

    if (es != comms::ErrorStatus::Success) {
        assert(!"Write operation failed unexpectedly");
        return;
    }       

    // Send serialized message back
    sendOutput(&output[0], output.size());
}

comms::ErrorStatus ClientSession::writeMessageSub1(const Message& msg, WriteIter& iter, std::size_t bufLen)
{
    return m_sub1Frame.write(msg, iter, bufLen);
}

comms::ErrorStatus ClientSession::writeMessageSub2(const Message& msg, WriteIter& iter, std::size_t bufLen)
{
    return m_sub2Frame.write(msg, iter, bufLen);
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
        /* CommsStage_Msg4 */ &ClientSession::sendMsg4,
        /* CommsStage_Msg5 */ &ClientSession::sendMsg5,
        /* CommsStage_Msg6 */ &ClientSession::sendMsg6,
    };
    static const std::size_t MapSize = std::extent<decltype(Map)>::value;
    static_assert(MapSize == CommsStage_NumOfValues, "Invalid Map");

    auto func = Map[m_currentStage];
    (this->*func)(); // Call appropriate sending function
}

void ClientSession::sendMsg1()
{
    m_sub1Msg.reset(new Msg1);
    sendMessage(*m_sub1Msg);
}

void ClientSession::sendMsg2()
{
    m_sub1Msg.reset(new Msg2);
    sendMessage(*m_sub1Msg);
}

void ClientSession::sendMsg3()
{
    m_sub1Msg.reset(new Msg3);
    sendMessage(*m_sub1Msg);
}

void ClientSession::sendMsg4()
{
    m_sub1Msg.reset(); // No need to pre-allocated next message any more
    Msg4 msg;
    sendMessage(msg);
}

void ClientSession::sendMsg5()
{
    Msg5 msg;
    sendMessage(msg);
}

void ClientSession::sendMsg6()
{
    Msg6 msg;
    sendMessage(msg);
}

SessionPtr Session::createClient(boost_wrap::io& io)
{
    return SessionPtr(new ClientSession(io));
}

} // namespace cc_tutorial
