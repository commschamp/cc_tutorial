
#include "ClientSession.h"

#include <cassert>
#include <iterator>
#include <iomanip>

#include "comms/process.h"
#include "comms/iterator.h"

namespace cc_tutorial
{

void ClientSession::handle(Prot1PseudoMsg& msg)
{
    std::cout << "Received message \"" << msg.doName() << '\n';

    MsgBuf prot2ProcessBuf;
    dropEscapes(msg.field_data().value().data(), msg.field_data().value().size(), prot2ProcessBuf);

    std::cout << "post-processed input: " << std::hex;
    std::copy(prot2ProcessBuf.begin(), prot2ProcessBuf.end(), std::ostream_iterator<unsigned>(std::cout, " "));
    std::cout << std::dec << std::endl;

    comms::processAllWithDispatch(prot2ProcessBuf.data(), prot2ProcessBuf.size(), m_prot2Frame, *this);
}

void ClientSession::handle(Prot1Interface& msg)
{
    std::cerr << "ERROR: Received unexpected PROT1 message \"" << msg.name() << " with ID=" << (unsigned)msg.getId() << std::endl;
}

void ClientSession::handle(Prot2Msg1& msg)
{
    std::cout << "Received message \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << '\n';
    printString(msg.field_f1());
    doNextStage();
}

void ClientSession::handle(Prot2Msg2& msg)
{
    std::cout << "Received message \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << '\n';
    printDataField(msg.field_f1());
}

void ClientSession::handle(Prot2Msg3& msg)
{
    std::cout << "Received message \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << '\n';
    printIntField(msg.field_f1());
    doNextStage();
}

void ClientSession::handle(Prot2Interface& msg)
{
    std::cerr << "ERROR: Received unexpected PROT2 message \"" << msg.name() << " with ID=" << (unsigned)msg.getId() << std::endl;
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

    return comms::processAllWithDispatch(buf, bufLen, m_prot1Frame, *this);
}

void ClientSession::writeMessage(const Prot2Interface& msg, MsgBuf& output)
{
    MsgBuf outputTmp;

    // Serialize message into the buffer (including framing)
    // The serialization uses polymorphic write functionality.
    auto writeIter = std::back_inserter(outputTmp);

    // The frame will use polymorphic message ID retrieval to
    // prot1fix message payload with message ID
    auto es = m_prot2Frame.write(msg, writeIter, outputTmp.max_size());
    if (es == comms::ErrorStatus::UpdateRequired) {
        auto updateIter = &outputTmp[0];
        es = m_prot2Frame.update(msg, updateIter, outputTmp.size());
    }

    if (es != comms::ErrorStatus::Success) {
        assert(!"Write operation failed unexpectedly");
        return;
    }    

    // Introduce special characters
    addEscapes(outputTmp);

    Prot1PseudoMsg pseudoMsg;
    comms::util::assign(pseudoMsg.field_data().value(), outputTmp.begin(), outputTmp.end());

    auto finalWriteIter = std::back_inserter(output);

    auto sizeBeforeWrite = output.size();
    es = m_prot1Frame.write(pseudoMsg, finalWriteIter, output.max_size());
    if (es == comms::ErrorStatus::UpdateRequired) {
        auto updateIter = &output[sizeBeforeWrite];
        es = m_prot1Frame.update(pseudoMsg, updateIter, output.size() - sizeBeforeWrite);
    }

    if (es != comms::ErrorStatus::Success) {
        assert(!"Write operation failed unexpectedly");
        return;
    }       
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
        /* CommsStage_Msg2 */ &ClientSession::sendMsg2Msg3,
    };
    static const std::size_t MapSize = std::extent<decltype(Map)>::value;
    static_assert(MapSize == CommsStage_NumOfValues, "Invalid Map");

    auto func = Map[m_currentStage];
    (this->*func)(); // Call appropriate sending function
}

void ClientSession::sendMsg1()
{
    MsgBuf output;
    Prot2Msg1 msg1;
    msg1.field_f1().value() = "hello";
    writeMessage(msg1, output);
    sendOutput(output.data(), output.size());
}

void ClientSession::sendMsg2Msg3()
{
    static const std::uint8_t Buf[] = {
        0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x10, 0x11, 0x12,
    };

    MsgBuf output;
    Prot2Msg2 msg2;
    comms::util::assign(msg2.field_f1().value(), std::begin(Buf), std::end(Buf));
    writeMessage(msg2, output);

    Prot2Msg3 msg3;
    msg3.field_f1().value() = 0xabcd;
    writeMessage(msg3, output);

    // Send serialized messages
    sendOutput(&output[0], output.size());
}

SessionPtr Session::createClient(boost_wrap::io& io)
{
    return SessionPtr(new ClientSession(io));
}

} // namespace cc_tutorial
