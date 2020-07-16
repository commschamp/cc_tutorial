#include "ClientSession.h"

#include <iostream>
#include <cassert>
#include <iterator>
#include <iomanip>

#include "comms/process.h"
#include "comms/iterator.h"

#include "tutorial11/dispatch/DispatchClientInputMessage.h"

namespace cc_tutorial
{

void ClientSession::handle(Message& msg)
{
    static_cast<void>(msg);
    std::cerr << "Received unexpected message" << std::endl;
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

    // Force switch statement based dispatch
    using Dispatcher =
        tutorial11::dispatch::ClientInputMsgDispatcher<ClientProtocolOptions>;    

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

SessionPtr Session::createClient(boost_wrap::io& io)
{
    return SessionPtr(new ClientSession(io));
}

} // namespace cc_tutorial
