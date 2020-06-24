#include "ClientSession.h"

#include <iostream>
#include <cassert>
#include <iterator>
#include <iomanip>

#include "comms/process.h"
#include "comms/iterator.h"
#include "comms/util/assign.h"

#include "tutorial12/dispatch/DispatchClientInputMessage.h"

namespace cc_tutorial
{

namespace
{

template <typename TField>
void printString(const TField& field)
{
    std::cout << '\t' << field.name() << " = " << std::string(field.value().begin(), field.value().end()) << '\n';
}

template <typename TField>
void printData(const TField& field)
{
    std::cout << '\t' << field.name() << " = " << std::hex;
    std::copy(field.value().begin(), field.value().end(), std::ostream_iterator<unsigned>(std::cout, " "));
    std::cout << std::dec << '\n';
}

template <typename TField>
void printList(const TField& field)
{
    std::cout << '\t' << field.name() << " = ";
    for (auto& f : field.value()) {
        std::cout << f.value() << " ";
    }
    std::cout << '\n';
}

} // namespace

void ClientSession::handle(Msg1& msg)
{
    std::cout << "Received message \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << '\n';
    printString(msg.field_f1());
    printString(msg.field_f2());
    std::cout << std::endl;

    if (m_currentStage != CommsStage_Msg1) {
        std::cerr << "ERROR: Unexpected stage" << std::endl;
        return;
    }

    doNextStage();
}

void ClientSession::handle(Msg2& msg)
{
    std::cout << "Received message \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << '\n';
    printData(msg.field_f1());
    printData(msg.field_f2());
    std::cout << std::endl;

    if (m_currentStage != CommsStage_Msg2) {
        std::cerr << "ERROR: Unexpected stage" << std::endl;
        return;
    }

    doNextStage();
}

void ClientSession::handle(Msg3& msg)
{
    std::cout << "Received message \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << '\n';
    printList(msg.field_f1());
    printList(msg.field_f2());
    std::cout << std::endl;

    if (m_currentStage != CommsStage_Msg3) {
        std::cerr << "ERROR: Unexpected stage" << std::endl;
        return;
    }

    doNextStage();
}

void ClientSession::handle(Message& msg)
{
    static_cast<void>(msg);
    std::cerr << "ERROR: Received unexpected message" << std::endl;
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

    // Force switch statement based
    using Dispatcher =
        tutorial12::dispatch::ClientInputMsgDispatcher<ClientProtocolOptions>; 

    // Process reported input, create relevant message objects and
    // dispatch all the created messages
    // to this object for handling (appropriate handle() member function will be called)
    return comms::processAllWithDispatchViaDispatcher<Dispatcher>(buf, bufLen, m_frame, *this);
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

        ++m_completedCycles;
        static const std::size_t MaxCycles = 1U;
        if (MaxCycles <= m_completedCycles) {
            // Client execution is complete
            getIo().stop();
            return;
        }

        // Start new cycle
        m_currentStage = static_cast<decltype(m_currentStage)>(0);
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
    msg.field_f1().value() = "abcdef";
    msg.field_f2().value() = "blabla";
    sendMessage(msg);
}

void ClientSession::sendMsg2()
{
    static const std::uint8_t Data1[] = {0xaa, 0xbb, 0xcc, 0xdd};
    static const std::uint8_t Data2[] = {0x12, 0x34, 0x58, 0x78};
    Msg2 msg;
    comms::util::assign(msg.field_f1().value(), std::begin(Data1), std::end(Data1));
    msg.field_f2().value() = Data2;
    sendMessage(msg);
}

void ClientSession::sendMsg3()
{
    Msg3 msg;
    auto& f1Vec = msg.field_f1().value();
    f1Vec.resize(4);
    f1Vec[0].value() = 1234;
    f1Vec[1].value() = 1235;
    f1Vec[2].value() = 1236;
    f1Vec[3].value() = 1237;

    auto& f2Vec = msg.field_f2().value();
    f2Vec.resize(3);
    f2Vec[0].value() = 500;
    f2Vec[1].value() = 501;
    f2Vec[2].value() = 502;
    sendMessage(msg);
}

SessionPtr Session::createClient(boost_wrap::io& io)
{
    return SessionPtr(new ClientSession(io));
}

} // namespace cc_tutorial
