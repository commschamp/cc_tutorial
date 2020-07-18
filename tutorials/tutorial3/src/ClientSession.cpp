#include "ClientSession.h"

#include <cassert>
#include <iterator>
#include <iomanip>

#include "comms/process.h"
#include "comms/iterator.h"
#include "comms/units.h"

namespace cc_tutorial
{

void ClientSession::handle(Msg1& msg)
{
    std::cout << "Received \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << '\n' <<
        '\t' << msg.field_f1().name() << " = " << std::fixed << msg.field_f1().getScaled<float>() <<
            " (orig = " << msg.field_f1().value() << ")\n" <<
        '\t' << msg.field_f2().name() << " = " << std::fixed << msg.field_f2().getScaled<double>() <<
            " (orig = " << msg.field_f2().value() << ")\n" <<
        std::endl;

    doNextStage();
}

void ClientSession::handle(Msg2& msg)
{
    // Compile time checks could be used before third party units conversions (like Boost.Units)
    static_assert(comms::units::isSeconds<Msg2::Field_f1>(), "Unexpected units");
    static_assert(comms::units::isMillimeters<Msg2::Field_f2>(), "Unexpected units");

    std::cout << "Received \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << '\n' <<
        '\t' << msg.field_f1().name() << " = " << msg.field_f1().value() << '\n' <<
            "\t\t= " << comms::units::getMicroseconds<std::uintmax_t>(msg.field_f1()) << " us\n" <<
            "\t\t= " << comms::units::getMilliseconds<unsigned>(msg.field_f1()) << " ms\n" <<
            "\t\t= " << comms::units::getSeconds<unsigned>(msg.field_f1()) << " s\n" <<
            "\t\t= " << std::fixed << comms::units::getMinutes<float>(msg.field_f1()) << " min\n" <<
            "\t\t= " << std::fixed << comms::units::getHours<double>(msg.field_f1()) << " h\n" <<
        '\t' << msg.field_f2().name() << " = " << std::fixed << msg.field_f2().value() << '\n' <<
            "\t\t= " << std::fixed << comms::units::getMicrometers<double>(msg.field_f2()) << " um\n" <<
            "\t\t= " << std::fixed << comms::units::getMillimeters<double>(msg.field_f2()) << " mm\n" <<
            "\t\t= " << std::fixed << comms::units::getMeters<double>(msg.field_f2()) << " m\n" <<
        std::endl;

    if (m_currentStage != CommsStage_Msg2) {
        std::cerr << "ERROR: Unexpected message received" << std::endl;
        return;
    }

    doNextStage();
}

void ClientSession::handle(Msg3& msg)
{
    std::cout << "Received \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << '\n' <<
        '\t' << msg.field_f1().name() << " = " << msg.field_f1().value() << '\n' <<
               "\t\t= " << std::fixed << comms::units::getMicrometers<double>(msg.field_f1()) << " um\n" <<
               "\t\t= " << std::fixed << comms::units::getMillimeters<double>(msg.field_f1()) << " mm\n" <<
               "\t\t= " << std::fixed << comms::units::getCentimeters<double>(msg.field_f1()) << " cm\n" <<
               "\t\t= " << std::fixed << comms::units::getMeters<double>(msg.field_f1()) << " m\n" <<
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
                 (unsigned)msg.getId() << std::endl;
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

    msg.field_f1().setScaled(1.234f);
    assert(msg.field_f1().value() == 1234);

    msg.field_f2().setScaled(12.345678);
    assert(msg.field_f2().value() == 12345678);

    sendMessage(msg);
}

void ClientSession::sendMsg2()
{
    Msg2 msg;

    comms::units::setMinutes(msg.field_f1(), 1.5);
    comms::units::setMeters(msg.field_f2(), 1.2);

    sendMessage(msg);
}

void ClientSession::sendMsg3()
{
    Msg3 msg;

    comms::units::setMillimeters(msg.field_f1(), 123.45678);

    sendMessage(msg);
}

SessionPtr Session::createClient(boost_wrap::io& io)
{
    return SessionPtr(new ClientSession(io));
}

} // namespace cc_tutorial
