#include "ClientSession.h"

#include <iostream>
#include <cassert>
#include <iterator>

#include "comms/process.h"
#include "comms/iterator.h"
#include "comms/cast.h"

namespace cc_tutorial
{

void ClientSession::handle(Msg1& msg)
{
    std::cout << "Received \"" << msg.doName() << "\" with ID=" << msg.doGetId() << '\n' <<
        "\tf1 = " << (unsigned)msg.field_f1().value() << '\n' <<
        "\tf2 = " << msg.field_f2().value() << '\n' << std::endl;

    if (m_currentStage != CommsStage_Msg1) {
        std::cerr << "ERROR: Unexpected message received: " << std::endl;
        return;
    }

    doNextStage();
}

void ClientSession::handle(Msg2& msg)
{
    std::cout << "Received \"" << msg.doName() << "\" with ID=" << msg.doGetId() << '\n' <<
        "\tf1 = " << (unsigned)msg.field_f1().value() << " (" << msg.field_f1().valueName()  << ")\n" <<
        "\tf2 = " << (unsigned)msg.field_f2().value() << " (" << msg.field_f2().valueName()  << ")\n" <<
        "\tf3 = " << (int)msg.field_f3().value() << " (" << msg.field_f3().valueName()  << ")\n" <<
        "\tf4 = " << (unsigned)msg.field_f4().value() << " (" << msg.field_f4().valueName()  << ")\n" <<
        std::endl;

    if (m_currentStage != CommsStage_Msg2) {
        std::cerr << "ERROR: Unexpected message received" << std::endl;
        return;
    }

    doNextStage();
}

void ClientSession::handle(Msg3& msg)
{
    std::cout << "Received \"" << msg.doName() << "\" with ID=" << msg.doGetId() << '\n' <<
        "\tf1 = " << msg.field_f1().value() << '\n' <<
        "\tf2 = " << msg.field_f2().value() << '\n' <<
        "\tf3 = " << msg.field_f3().value() << '\n' <<
        "\tf4 = " << (unsigned)msg.field_f4().value() << '\n' <<
        "\tf5 = " << msg.field_f5().value() << '\n' <<
        std::endl;

    if (m_currentStage != CommsStage_Msg3) {
        std::cerr << "ERROR: Unexpected message received: " << std::endl;
        return;
    }

    doNextStage();
}

void ClientSession::handle(Message& msg)
{
    // The statement below uses polymorphic message name and ID retrievals.
    std::cout << "ERROR: Received unexpected message \"" << msg.name() << "\" with ID=" <<
                 msg.getId() << std::endl;
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
    auto result = comms::processAllWithDispatch(buf, bufLen, m_frame, *this);
    if (result < bufLen) {
        std::cout << "Processed only " << result << " bytes." << std::endl;
    }
    return result;
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

    std::cout << "Sending message \"" << msg.name() << "\" with ID=" << msg.getId() << ": " << std::hex;
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
    msg.field_f1().value() = 1;
    msg.field_f2().value() = 100;
    sendMessage(msg);
}

void ClientSession::sendMsg2()
{
    Msg2 msg;
    msg.field_f1().value() = tutorial2::field::E2_1Val::V2;
    msg.field_f2().value() = tutorial2::field::E2_2Common::ValueType::V3;
    msg.field_f3().value() = Msg2::Field_f3::ValueType::V1;
    comms::cast_assign(msg.field_f4().value()) = 0xff;
    sendMessage(msg);
}

void ClientSession::sendMsg3()
{
    Msg3 msg;
    assert(msg.field_f1().value() == 10); // Keep default value of f1

    msg.field_f2().value() = 0xabcdef;
    assert(msg.field_f2().length() == 3U); // the f2 has fixed length of 3 bytes
    static_assert(Msg3::Field_f2::minLength() == 3U, "Invalid assumption");
    static_assert(Msg3::Field_f2::maxLength() == 3U, "Invalid assumption");

    assert(msg.field_f3().length() == 1U); // It takes 1 byte to serialize default value 0
    msg.field_f3().value() = 128;
    assert(msg.field_f3().length() == 2U); // the f3 is encoded with base-128
    static_assert(Msg3::Field_f3::minLength() == 1U, "Invalid assumption");
    static_assert(Msg3::Field_f3::maxLength() == 4U, "Invalid assumption");

    assert(msg.field_f4().isS1()); // Check default value
    msg.field_f4().setS2();

    assert(msg.field_f5().value() == 2020); // Check default value
    msg.field_f5().value() = 2021;
    assert(msg.field_f5().length() == 1U); // the f5 has fixed length of 1 bytes
    static_assert(Msg3::Field_f5::minLength() == 1U, "Invalid assumption");
    static_assert(Msg3::Field_f5::maxLength() == 1U, "Invalid assumption");

    sendMessage(msg);
}

SessionPtr Session::createClient(boost::asio::io_service& io)
{
    return SessionPtr(new ClientSession(io));
}

} // namespace cc_tutorial
