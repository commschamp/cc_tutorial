#include "Tutorial1ClientSession.h"

#include <iostream>
#include <cassert>

#include "comms/process.h"
#include "comms/iterator.h"

namespace cc_tutorial
{

void Tutorial1ClientSession::handle(Msg1& msg)
{
    // The report below uses NON-polymorphic name and ID retrievals
    std::cout << "Received " << msg.doName() << " with ID=" << msg.doGetId() << std::endl;

    if (m_currentStage != CommsStage_Msg1) {
        std::cerr << "ERROR: Unexpected message received: " << std::endl;
        return;
    }

    doNextStage();
}

void Tutorial1ClientSession::handle(Msg2& msg)
{
    // The report below uses NON-polymorphic name and ID retrievals
    std::cout << "Received " << msg.doName() << " with ID=" << msg.doGetId() << std::endl;

    if (m_currentStage != CommsStage_Msg2) {
        std::cerr << "ERROR: Unexpected message received" << std::endl;
        return;
    }

    doNextStage();
}

void Tutorial1ClientSession::handle(Message& msg)
{
    // The statement below uses polymorphic message name and ID retrievals.
    std::cout << "ERROR: Received unexpected message \"" << msg.name() << "\" with ID=" <<
                 msg.getId() << std::endl;
}

bool Tutorial1ClientSession::startImpl()
{
    doNextStage();
    return true;
}

std::size_t Tutorial1ClientSession::processInputImpl(const std::uint8_t* buf, std::size_t bufLen)
{
    // Process reported input, create relevant message objects and
    // dispatch all the created messages
    // to this object for handling (appropriate handle() member function will be called)
    return comms::processAllWithDispatch(buf, bufLen, m_frame, *this);
}

void Tutorial1ClientSession::sendMessage(const Message& msg)
{
    // The statement below uses polymorphic message name and ID retrievals.
    std::cout << "Sending message \"" << msg.name() << "\" with ID=" << msg.getId() << std::endl;

    std::vector<std::uint8_t> output;

    // Use polymorphic serialization length calculation to reserve
    // needed capacity
    output.reserve(m_frame.length(msg));

    // Serialize message into the buffer (including framing)
    // The serialization uses polymorphic write functionality.
    auto writeIter = std::back_inserter(output);

    auto es = m_frame.write(msg, writeIter, output.max_size());
    if (es != comms::ErrorStatus::Success) {
        assert(!"Write operation failed unexpectedly");
        return;
    }

    // Send serialized message back
    sendOutput(&output[0], output.size());
}

void Tutorial1ClientSession::doNextStage()
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
        static const std::size_t MaxCycles = 3U;
        if (MaxCycles <= m_completedCycles) {
            // Client execution is complete
            getIoService().stop();
            return;
        }

        // Start new cycle
        m_currentStage = static_cast<decltype(m_currentStage)>(0);
    } while (false);

    using NextSendFunc = void (Tutorial1ClientSession::*)();
    static const NextSendFunc Map[] = {
        /* CommsStage_Msg1 */ &Tutorial1ClientSession::sendMsg1,
        /* CommsStage_Msg2 */ &Tutorial1ClientSession::sendMsg2
    };
    static const std::size_t MapSize = std::extent<decltype(Map)>::value;
    static_assert(MapSize == CommsStage_NumOfValues, "Invalid Map");

    auto func = Map[m_currentStage];
    (this->*func)(); // Call appropriate sending function
}

void Tutorial1ClientSession::sendMsg1()
{
    Msg1 msg;
    sendMessage(msg);
}

void Tutorial1ClientSession::sendMsg2()
{
    Msg2 msg;
    sendMessage(msg);
}


SessionPtr Session::createClient(boost::asio::io_service& io)
{
    return SessionPtr(new Tutorial1ClientSession(io));
}

} // namespace cc_tutorial
