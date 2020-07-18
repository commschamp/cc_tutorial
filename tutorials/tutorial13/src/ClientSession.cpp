#include "ClientSession.h"

#include <cassert>
#include <iterator>
#include <iomanip>

#include "comms/process.h"
#include "comms/iterator.h"

namespace cc_tutorial
{

namespace
{

} // namespace

void ClientSession::handle(Msg1_1& msg)
{
    std::cout << "Received message \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << '\n' <<
        "\t" << msg.field_f1().name() << " = " << msg.field_f1().value() << '\n' <<
        std::endl;

    if (m_currentStage != CommsStage_Msg1_1) {
        std::cerr << "ERROR: Unexpected stage" << std::endl;
        return;
    }

    doNextStage();
}

void ClientSession::handle(Msg1_2& msg)
{
    std::cout << "Received message \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << '\n' <<
        "\t" << msg.field_f1().name() << " = " << msg.field_f1().value() << '\n' <<
        std::endl;

    if (m_currentStage != CommsStage_Msg1_2) {
        std::cerr << "ERROR: Unexpected stage" << std::endl;
        return;
    }

    doNextStage();
}

void ClientSession::handle(Msg1_3& msg)
{
    std::cout << "Received message \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << '\n' <<
        "\t" << msg.field_f1().name() << " = " << msg.field_f1().value() << '\n' <<
        std::endl;

    if (m_currentStage != CommsStage_Msg1_3) {
        std::cerr << "ERROR: Unexpected stage" << std::endl;
        return;
    }

    doNextStage();
}

void ClientSession::handle(Msg2_1& msg)
{
    std::cout << "Received message \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << '\n' <<
        "\t" << msg.field_type().name() << " = " << (unsigned)msg.field_type().value() << '\n' <<
        "\t" << msg.field_f1().name() << " = " << msg.field_f1().value() << '\n' <<
        std::endl;

    if (m_currentStage != CommsStage_Msg2_1) {
        std::cerr << "ERROR: Unexpected stage" << std::endl;
        return;
    }

    doNextStage();
}

void ClientSession::handle(Msg2_2& msg)
{
    std::cout << "Received message \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << '\n' <<
        "\t" << msg.field_type().name() << " = " << (unsigned)msg.field_type().value() << '\n' <<
        "\t" << msg.field_f1().name() << " = " << msg.field_f1().value() << '\n' <<
        std::endl;

    if (m_currentStage != CommsStage_Msg2_2) {
        std::cerr << "ERROR: Unexpected stage" << std::endl;
        return;
    }

    doNextStage();
}

void ClientSession::handle(Msg2_3& msg)
{
    std::cout << "Received message \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << '\n' <<
        "\t" << msg.field_type().name() << " = " << (unsigned)msg.field_type().value() << '\n' <<
        "\t" << msg.field_f1().name() << " = " << msg.field_f1().value() << '\n' <<
        std::endl;

    if (m_currentStage != CommsStage_Msg2_3) {
        std::cerr << "ERROR: Unexpected stage" << std::endl;
        return;
    }

    doNextStage();
}

void ClientSession::handle(Message& msg)
{
    std::cerr << "ERROR: Received unexpected message \"" << msg.name() << " with ID=" << (unsigned)msg.getId() << std::endl;
    doNextStage();
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

    // Process reported input, create relevant message objects and
    // dispatch all the created messages
    // to this object for handling (appropriate handle() member function will be called)
    return comms::processAllWithDispatch(buf, bufLen, m_frame, *this);
}

void ClientSession::sendMessage(const Message& msg)
{
    // The statement below uses polymorphic message name and ID retrievals.
    std::vector<std::uint8_t> output;

    // Use polymorphic serialization length calculation to reserve
    // needed capacity
    output.reserve(m_frame.length(msg));

    // Serialize message into the buffer (including framing)
    // The serialization uses polymorphic write functionality.
    auto writeIter = std::back_inserter(output);

    // The frame will use polymorphic message ID retrieval to
    // prefix message payload with message ID
    auto es = m_frame.write(msg, writeIter, output.max_size());
    if (es != comms::ErrorStatus::Success) {
        assert(!"Write operation failed unexpectedly");
        return;
    }

    // Send serialized message back
    sendOutput(&output[0], output.size());

    std::cout << "Sending message \"" << msg.name() << "\" with ID=" << (unsigned)msg.getId() << ": " << std::hex;
    std::copy(output.begin(), output.end(), std::ostream_iterator<unsigned>(std::cout, " "));
    std::cout << std::dec << std::endl;
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
        /* CommsStage_Msg1_1 */ &ClientSession::sendMsg1_1,
        /* CommsStage_Msg1_2 */ &ClientSession::sendMsg1_2,
        /* CommsStage_Msg1_3 */ &ClientSession::sendMsg1_3,
        /* CommsStage_Msg2_1 */ &ClientSession::sendMsg2_1,
        /* CommsStage_Msg2_2 */ &ClientSession::sendMsg2_2,
        /* CommsStage_Msg2_3 */ &ClientSession::sendMsg2_3,
    };
    static const std::size_t MapSize = std::extent<decltype(Map)>::value;
    static_assert(MapSize == CommsStage_NumOfValues, "Invalid Map");

    auto func = Map[m_currentStage];
    (this->*func)(); // Call appropriate sending function
}

void ClientSession::sendMsg1_1()
{
    Msg1_1 msg;
    msg.field_f1().value() = 123456789012ULL;
    sendMessage(msg);
}

void ClientSession::sendMsg1_2()
{
    Msg1_2 msg;
    msg.field_f1().value() = 123456;
    sendMessage(msg);
}

void ClientSession::sendMsg1_3()
{
    Msg1_3 msg;
    msg.field_f1().value() = 1024;
    sendMessage(msg);
}

void ClientSession::sendMsg2_1()
{
    Msg2_1 msg;
    msg.field_f1().value() = 1024;
    sendMessage(msg);
}

void ClientSession::sendMsg2_2()
{
    Msg2_2 msg;
    msg.field_f1().value() = 123456;
    sendMessage(msg);
}

void ClientSession::sendMsg2_3()
{
    Msg2_3 msg;
    msg.field_f1().value() = 123456789012ULL;
    sendMessage(msg);
}

SessionPtr Session::createClient(boost_wrap::io& io)
{
    return SessionPtr(new ClientSession(io));
}

} // namespace cc_tutorial
