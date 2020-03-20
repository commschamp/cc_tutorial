#include "ClientSession.h"

#include <iostream>
#include <cassert>
#include <iterator>
#include <iomanip>

#include "comms/process.h"
#include "comms/iterator.h"
#include "comms/cast.h"

namespace cc_tutorial
{

namespace
{

template <typename TField>
void printSetField(const TField& field, const std::string& prefix = std::string())
{
    std::cout << '\t' << prefix << field.name() << " = 0x" <<
        std::setfill('0') << std::setw(field.length() * 2) <<
        std::hex << (std::uintmax_t)field.value() << std::dec << '\n';

   for (auto idx = 0U; idx < field.length() * 8; ++idx) {
        auto bitIdx = static_cast<typename TField::BitIdx>(idx);
        const char* bitName = field.bitName(bitIdx);
        if (bitName == nullptr) {
            continue;
        }

        std::cout << "\t\t" << bitName << ": " << std::boolalpha << field.getBitValue(bitIdx) << '\n';
    }
}

template <typename TField>
void printDataField(const TField& field, const std::string& prefix = std::string())
{
    std::cout << '\t' << prefix << field.name() << " = " << std::hex;
    for (auto byte : field.value()) {
        std::cout << std::setfill('0') << std::setw(2) << static_cast<unsigned>(byte) << ' ';
    }
    std::cout << std::dec << '\n';
}

} // namespace

void ClientSession::handle(Msg1& msg)
{
    std::cout << "Received \"" << msg.doName() << "\" with ID=" << msg.doGetId() << '\n' <<
        '\t' << msg.field_f1().name() << " = " << (unsigned)msg.field_f1().value() << '\n' <<
        '\t' << msg.field_f2().name() << " = " << msg.field_f2().value() << '\n' << std::endl;

    if (m_currentStage != CommsStage_Msg1) {
        std::cerr << "ERROR: Unexpected message received: " << std::endl;
        return;
    }

    doNextStage();
}

void ClientSession::handle(Msg2& msg)
{
    std::cout << "Received \"" << msg.doName() << "\" with ID=" << msg.doGetId() << '\n' <<
        '\t' << msg.field_f1().name() << " = " << (unsigned)msg.field_f1().value() << " (" << msg.field_f1().valueName()  << ")\n" <<
        '\t' << msg.field_f2().name() << " = " << (unsigned)msg.field_f2().value() << " (" << msg.field_f2().valueName()  << ")\n" <<
        '\t' << msg.field_f3().name() << " = " << " (" << msg.field_f3().valueName()  << ")\n" <<
        '\t' << msg.field_f4().name() << " = " << (unsigned)msg.field_f4().value() << " (" << msg.field_f4().valueName()  << ")\n" <<
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
        '\t' << msg.field_f1().name() << " = " << msg.field_f1().value() << '\n' <<
        '\t' << msg.field_f2().name() << " = " << msg.field_f2().value() << '\n' <<
        '\t' << msg.field_f3().name() << " = " << msg.field_f3().value() << '\n' <<
        '\t' << msg.field_f4().name() << " = " << (unsigned)msg.field_f4().value() << '\n' <<
        '\t' << msg.field_f5().name() << " = " << msg.field_f5().value() << '\n' <<
        std::endl;

    if (m_currentStage != CommsStage_Msg3) {
        std::cerr << "ERROR: Unexpected message received: " << std::endl;
        return;
    }

    doNextStage();
}

void ClientSession::handle(Msg4& msg)
{
    std::cout << "Received \"" << msg.doName() << "\" with ID=" << msg.doGetId() << '\n';
    printSetField(msg.field_f1());
    printSetField(msg.field_f2());
    printSetField(msg.field_f3());
    std::cout << std::endl;

    if (m_currentStage != CommsStage_Msg4) {
        std::cerr << "ERROR: Unexpected message received" << std::endl;
        return;
    }

    doNextStage();
}

void ClientSession::handle(Msg5& msg)
{
    std::cout << "Received \"" << msg.doName() << "\" with ID=" << msg.doGetId() << '\n' <<
        '\t' << msg.field_f1().name() << " = " << msg.field_f1().value() << '\n' <<
        '\t' << msg.field_f2().name() << " = " << msg.field_f2().value() << '\n' <<
        std::endl;

    if (m_currentStage != CommsStage_Msg5) {
        std::cerr << "ERROR: Unexpected message received" << std::endl;
        return;
    }

    doNextStage();
}

void ClientSession::handle(Msg6& msg)
{
    std::cout << "Received \"" << msg.doName() << "\" with ID=" << msg.doGetId() << '\n' <<
        '\t' << msg.field_f1().name() << " = " << msg.field_f1().value() << '\n' <<
        '\t' << msg.field_f2().name() << " = " << msg.field_f2().value() << '\n' <<
        '\t' << msg.field_f3().name() << " = " << msg.field_f3().value() << '\n' <<
        '\t' << msg.field_f4().name() << " = " << msg.field_f4().value() << '\n' <<
        '\t' << msg.field_f5().name() << " = " << msg.field_f5().value() << '\n' <<
        std::endl;

    if (m_currentStage != CommsStage_Msg6) {
        std::cerr << "ERROR: Unexpected message received" << std::endl;
        return;
    }

    doNextStage();
}

void ClientSession::handle(Msg7& msg)
{
    std::cout << "Received \"" << msg.doName() << "\" with ID=" << msg.doGetId() << '\n';
    printDataField(msg.field_f1());
    printDataField(msg.field_f2());
    printDataField(msg.field_f3());
    std::cout << std::endl;

    if (m_currentStage != CommsStage_Msg7) {
        std::cerr << "ERROR: Unexpected message received" << std::endl;
        return;
    }

    doNextStage();
}

void ClientSession::handle(Msg8& msg)
{
    auto* f1Name = msg.field_f1().name();
    auto* f2Name = msg.field_f2().name();
    std::cout << "Received \"" << msg.doName() << "\" with ID=" << msg.doGetId() << '\n' <<
        '\t' << f1Name << '.' << msg.field_f1().field_m1().name() << " = " <<
            msg.field_f1().field_m1().value() << '\n' <<
        '\t' << f1Name << '.' << msg.field_f1().field_m2().name() << " = " <<
            (unsigned)msg.field_f1().field_m2().value() << " (" << msg.field_f1().field_m2().valueName()  << ")\n" <<
        '\t' << f1Name << '.' << msg.field_f1().field_m3().name() << " = " <<
            msg.field_f1().field_m3().value() << '\n' <<
        '\t' << f2Name << '.' << msg.field_f2().field_m1().name() << " = " <<
            msg.field_f2().field_m1().value() << '\n';
    printSetField(msg.field_f2().field_m2(), std::string(f2Name) + '.');
    printDataField(msg.field_f2().field_m3(), std::string(f2Name) + '.');
    std::cout << std::endl;

    if (m_currentStage != CommsStage_Msg8) {
        std::cerr << "ERROR: Unexpected message received" << std::endl;
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
        static const std::size_t MaxCycles = 1U;
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
        /* CommsStage_Msg4 */ &ClientSession::sendMsg4,
        /* CommsStage_Msg5 */ &ClientSession::sendMsg5,
        /* CommsStage_Msg6 */ &ClientSession::sendMsg6,
        /* CommsStage_Msg7 */ &ClientSession::sendMsg7,
        /* CommsStage_Msg8 */ &ClientSession::sendMsg8,
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

void ClientSession::sendMsg4()
{
    Msg4 msg;
    msg.field_f1().setBitValue_B0(false);
    msg.field_f1().setBitValue_B2(true);
    assert(msg.field_f1().valid());

    msg.field_f2().setBitValue_B15(false);

    msg.field_f3().value() = 0xff;
    assert(msg.field_f3().length() == 3U);
    static_assert(Msg4::Field_f3::minLength() == 3U, "Invalid assumption");
    static_assert(Msg4::Field_f3::maxLength() == 3U, "Invalid assumption");
    assert(!msg.field_f3().valid());
    sendMessage(msg);
}

void ClientSession::sendMsg5()
{
    Msg5 msg;
    msg.field_f1().value() = 1.2345;

    assert(msg.field_f2().isS1());
    msg.field_f2().setS3();
    sendMessage(msg);
}

void ClientSession::sendMsg6()
{
    Msg6 msg;

    std::string& f1Str = msg.field_f1().value();
    assert(f1Str.empty()); // Empty string on construction
    assert(msg.field_f1().length() == 5U); // but the reported length is as expected
    f1Str = "abc";
    assert(msg.field_f1().length() == 5U);

    assert(msg.field_f2().value() == "hello");
    assert(msg.field_f2().length() == 6U);
    msg.field_f2().value() = "bye";
    assert(msg.field_f2().length() == 4U);

    msg.field_f3().value() = "deadbeef";

    assert(msg.field_f4().length() == 1U);
    msg.field_f4().value() = "blablabla";
    assert(msg.field_f4().length() == 10U);

    msg.field_f5().value() = "foobar";

    sendMessage(msg);
}

void ClientSession::sendMsg7()
{
    Msg7 msg;

    std::vector<std::uint8_t>& f1Vec = msg.field_f1().value();
    assert(f1Vec.empty()); // Empty vector on construction
    assert(msg.field_f1().length() == 5U); // but the reported length is as expected
    f1Vec = {0xde, 0xad, 0xbe, 0xef};
    assert(msg.field_f1().length() == 5U);

    // msg.field_f2().value() is unchanged
    assert(msg.field_f2().value().size() == 6U); // The vector has 6 bytes
    assert(msg.field_f2().length() == 7U); // The total serialization length is 7

    msg.field_f3().value() = {0xaa, 0xbb};
    assert(msg.field_f3().length() == 2U);

    sendMessage(msg);
}

void ClientSession::sendMsg8()
{
    Msg8 msg;

    auto& f1 = msg.field_f1();
    f1.field_m1().value() = 1234;
    f1.field_m2().value() = Msg8::Field_f1::Field_m2::ValueType::V1;
    f1.field_m3().value() = "hello";

    auto& f2 = msg.field_f2();
    f2.field_m1().value() = 1.25;
    f2.field_m2().setBitValue_SomeBit(true);
    f2.field_m3().value() = {0xab, 0xcd};

    sendMessage(msg);
}

SessionPtr Session::createClient(boost::asio::io_service& io)
{
    return SessionPtr(new ClientSession(io));
}

} // namespace cc_tutorial
