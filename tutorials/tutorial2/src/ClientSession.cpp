#include "ClientSession.h"

#include <cassert>
#include <iterator>

#include "comms/process.h"
#include "comms/iterator.h"
#include "comms/cast.h"

namespace cc_tutorial
{

void ClientSession::handle(Msg1& msg)
{
    std::cout << "Received \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << '\n' <<
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
    std::cout << "Received \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << '\n' <<
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
    std::cout << "Received \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << '\n' <<
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
    std::cout << "Received \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << '\n';
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
    std::cout << "Received \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << '\n' <<
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
    std::cout << "Received \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << '\n' <<
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
    std::cout << "Received \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << '\n';
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
    std::cout << "Received \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << '\n' <<
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

void ClientSession::handle(Msg9& msg)
{
    auto* f1Name = msg.field_f1().name();
    auto* f2Name = msg.field_f2().name();
    std::cout << "Received \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << '\n' <<
        '\t' << f1Name << '.' << msg.field_f1().field_m1().name() << " = " <<
            msg.field_f1().field_m1().value() << '\n' <<
        '\t' << f1Name << '.' << msg.field_f1().field_m2().name() << " = " <<
            (unsigned)msg.field_f1().field_m2().value() << " (" << msg.field_f1().field_m2().valueName()  << ")\n";
    printSetField(msg.field_f1().field_m3(), std::string(f1Name) + '.');
    std::cout <<
        '\t' << f2Name << '.' << msg.field_f2().field_m1().name() << " = " <<
            msg.field_f2().field_m1().value() << '\n' <<
        '\t' << f2Name << '.' << msg.field_f2().field_m2().name() << " = " <<
            (unsigned)msg.field_f2().field_m2().value() << " (" << msg.field_f2().field_m2().valueName()  << ")\n";
    printSetField(msg.field_f2().field_m3(), std::string(f2Name) + '.');
    std::cout << std::endl;

    if (m_currentStage != CommsStage_Msg9) {
        std::cerr << "ERROR: Unexpected message received" << std::endl;
        return;
    }

    doNextStage();
}

void ClientSession::handle(Msg10& msg)
{
    std::cout << "Received \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << '\n';

    auto& f1Vec = msg.field_f1().value();
    std::cout << '\t' << msg.field_f1().name() << " (" << f1Vec.size() << " elements)\n";
    for (auto idx = 0U; idx < f1Vec.size(); ++idx) {
        auto& elem = f1Vec[idx];
        std::cout << "\t\t" << elem.name() << ' ' << idx << " = " << elem.value() << '\n';
    }

    auto& f2Vec = msg.field_f2().value();
    std::cout << '\t' << msg.field_f2().name() << " (" << f2Vec.size() << " elements)\n";
    for (auto idx = 0U; idx < f2Vec.size(); ++idx) {
        auto& elem = f2Vec[idx];
        std::cout << "\t\t" << elem.name() << ' ' << idx << " = " << elem.value() << '\n';
    }

    auto& f3Vec = msg.field_f3().value();
    std::cout << '\t' << msg.field_f3().name() << " (" << f3Vec.size() << " elements)\n";
    for (auto idx = 0U; idx < f3Vec.size(); ++idx) {
        auto& elem = f3Vec[idx];
        std::cout << "\t\t" << elem.name() << ' ' << idx << '\n' <<
            "\t\t\t" << elem.field_m1().name() << " = " << (unsigned)elem.field_m1().value() << '\n' <<
            "\t\t\t" << elem.field_m2().name() << " = " << elem.field_m2().value() << '\n';
    }

    auto& f4Vec = msg.field_f4().value();
    std::cout << '\t' << msg.field_f4().name() << " (" << f4Vec.size() << " elements)\n";
    for (auto idx = 0U; idx < f4Vec.size(); ++idx) {
        auto& elem = f4Vec[idx];
        std::cout << "\t\t" << elem.name() << ' ' << idx << '\n' <<
            "\t\t\t" << elem.field_m1().name() << " = " << (unsigned)elem.field_m1().value() << '\n' <<
            "\t\t\t" << elem.field_m2().name() << " = " << (unsigned)elem.field_m2().value() <<
                     " (" << elem.field_m2().valueName() << ")\n" <<
            "\t\t\t" << elem.field_m3().name() << " = " << elem.field_m3().value() << '\n';
    }
    std::cout << std::endl;

    if (m_currentStage != CommsStage_Msg10) {
        std::cerr << "ERROR: Unexpected message received" << std::endl;
        return;
    }

    doNextStage();
}

void ClientSession::handle(Msg11& msg)
{
    std::cout << "Received \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << '\n' <<
        '\t' << msg.field_f11_1().name() << " = " << (unsigned)msg.field_f11_1().value() << '\n' <<
        '\t' << msg.field_f2().name() << " = " <<
            (unsigned)msg.field_f2().value() << " (" << msg.field_f2().valueName()  << ")\n" <<
        '\t' << msg.field_f3().name() << '.' << msg.field_f3().field_m1().name() << " = " <<
            (unsigned)msg.field_f3().field_m1().value() << '\n' <<
        '\t' << msg.field_f3().name() << '.' << msg.field_f3().field_m2().name() << " = " <<
            (unsigned)msg.field_f3().field_m2().value() << " (" << msg.field_f3().field_m2().valueName()  << ")\n" <<
        std::endl;

    doNextStage();        
}

void ClientSession::handle(Msg12& msg)
{
    std::cout << "Received \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << '\n';
    if (printOptionalField(msg.field_f1())) {
        std::cout << "\t\t" << msg.field_f1().field().name() << " = " << msg.field_f1().field().value() << '\n';
    }
    std::cout << std::endl;

    doNextStage();        
}

void ClientSession::handle(Msg13& msg)
{
    std::cout << "Received \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << '\n';
    printSetField(msg.field_flags());
    if (printOptionalField(msg.field_f2())) {
        std::cout << "\t\t" << msg.field_f2().field().name() << " = " << msg.field_f2().field().value() << '\n';
    }

    if (printOptionalField(msg.field_f3())) {
        std::cout << "\t\t" << msg.field_f3().field().name() << " = " << (unsigned)msg.field_f3().field().value() << '\n';
    }    
    std::cout << std::endl;

    doNextStage();        
}

void ClientSession::handle(Msg14& msg)
{
    std::cout << "Received \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << '\n' <<
         '\t' << msg.field_f1().name() << " = " << (int)msg.field_f1().value() << '\n' <<
         '\t' << msg.field_f2().name() << " = " << (int)msg.field_f2().value() << '\n';

    if (printOptionalField(msg.field_f3())) {
        std::cout << "\t\t" << msg.field_f3().field().name() << " = " << msg.field_f3().field().value() << '\n';
    }

    std::cout << std::endl;

    doNextStage();
}

void ClientSession::handle(Msg15& msg)
{
    std::cout << "Received \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << '\n' <<
        '\t' << msg.field_f1().name() << " = " << (unsigned)msg.field_f1().value() << '\n' <<
        '\t' << msg.field_f2().name() << " = " << msg.field_f2().value() << '\n' <<
        '\t' << msg.field_f3().name() << " = " << (unsigned)msg.field_f3().value() << '\n' <<
        std::endl;

    if (m_currentStage != CommsStage_Msg15) {
        std::cerr << "ERROR: Unexpected message received: " << std::endl;
        return;
    }

    doNextStage();
}

void ClientSession::handle(Msg16& msg)
{
    std::cout << "Received \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << '\n' <<
        '\t' << msg.field_f1().name() << " = " << (unsigned)msg.field_f1().value() << '\n' <<
        '\t' << msg.field_f2().name() << " = " << (unsigned)msg.field_f2().value() << '\n' <<
        '\t' << msg.field_f3().name() << " = " << (unsigned)msg.field_f3().value() << '\n' <<
        std::endl;

    if (m_currentStage != CommsStage_Msg16) {
        std::cerr << "ERROR: Unexpected message received: " << std::endl;
        return;
    }

    doNextStage();
}

void ClientSession::handle(Msg17& msg)
{
    auto* f2Name = msg.field_f2().name();
    std::cout << "Received \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << '\n' <<
        '\t' << msg.field_f1().name() << " = " <<
            msg.field_f1().value() << '\n' <<
        '\t' << f2Name << '.' << msg.field_f2().field_m1().name() << " = " <<
            msg.field_f2().field_m1().value() << '\n' <<
        '\t' << f2Name << '.' << msg.field_f2().field_m2().name() << " = " <<
            msg.field_f2().field_m2().value() << '\n' <<
        '\t' << f2Name << '.' << msg.field_f2().field_m3().name() << " = " <<
            msg.field_f2().field_m3().value() << '\n';            
    std::cout << std::endl;

    if (m_currentStage != CommsStage_Msg17) {
        std::cerr << "ERROR: Unexpected message received: " << std::endl;
        return;
    }

    doNextStage();
}

void ClientSession::handle(Msg18& msg)
{
    std::cout << "Received \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << '\n' <<
        '\t' << msg.field_f1().name() << " = " << msg.field_f1().value() << '\n';
    if (printOptionalField(msg.field_f2())) {
        std::cout << "\t\t" << msg.field_f2().field().name() << " = " << msg.field_f2().field().value() << '\n';
    }

    if (printOptionalField(msg.field_f3())) {
        std::cout << "\t\t" << msg.field_f3().field().name() << " = " << (unsigned)msg.field_f3().field().value() << '\n';
    }    
    std::cout << std::endl;

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
    std::cout << "Sending message \"" << msg.name() << "\" with ID=" << (unsigned)msg.getId() << std::endl;
    
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
        /* CommsStage_Msg7 */ &ClientSession::sendMsg7,
        /* CommsStage_Msg8 */ &ClientSession::sendMsg8,
        /* CommsStage_Msg9 */ &ClientSession::sendMsg9,
        /* CommsStage_Msg10 */ &ClientSession::sendMsg10,
        /* CommsStage_Msg11 */ &ClientSession::sendMsg11,
        /* CommsStage_Msg12 */ &ClientSession::sendMsg12,
        /* CommsStage_Msg13 */ &ClientSession::sendMsg13,
        /* CommsStage_Msg14 */ &ClientSession::sendMsg14,
        /* CommsStage_Msg15 */ &ClientSession::sendMsg15,
        /* CommsStage_Msg16 */ &ClientSession::sendMsg16,
        /* CommsStage_Msg17 */ &ClientSession::sendMsg17,
        /* CommsStage_Msg18 */ &ClientSession::sendMsg18,
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
    msg.field_f1().value() = 1.2345f;

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

    auto& f1 = msg.field_f1(); // Access to f1 field

    // Assign values to f1 members
    f1.field_m1().value() = 1234;
    f1.field_m2().value() = Msg8::Field_f1::Field_m2::ValueType::V1;
    f1.field_m3().value() = "hello";

    auto& f2 = msg.field_f2(); // Access to f2 field

    // Assign values to f2 members
    f2.field_m1().value() = 1.25;
    f2.field_m2().setBitValue_SomeBit(true);
    f2.field_m3().value() = {0xab, 0xcd};

    sendMessage(msg);
}

void ClientSession::sendMsg9()
{
    Msg9 msg;

    static_assert(Msg9::Field_f1::minLength() == 2U, "Invalid length of F1");
    static_assert(Msg9::Field_f2::minLength() == 3U, "Invalid length of F2");

    // Assign values to f1 members
    msg.field_f1().field_m1().value() = 55;
    msg.field_f1().field_m2().value() = Msg9::Field_f1::Field_m2::ValueType::V2;
    msg.field_f1().field_m3().setBitValue_B5(true);
    assert(msg.field_f1().length() == 2U); // Runtime verification of serialization length

    // Keeping values of f2 as default constructed

    assert(msg.doLength() == 5U); // Verification of message serialization length (non-polymorphic).
    sendMessage(msg);
}

void ClientSession::sendMsg10()
{
    Msg10 msg;

    auto& f1Vec = msg.field_f1().value(); // Access to F1 storage vector
    assert(f1Vec.empty()); // The default constructed vector is empty
    f1Vec.resize(3); // Resizing to lesser than required size on purpose
    f1Vec[0].value() = 12345;
    f1Vec[1].value() = 54321;
    f1Vec[2].value() = 33333;

    auto& f2Vec = msg.field_f2().value(); // Access to F2 storage vector
    assert(f2Vec.empty()); // The default constructed vector is empty
    f2Vec.resize(2);
    f2Vec[0].value() = -125;
    f2Vec[1].value() = 123;

    auto& f3Vec = msg.field_f3().value(); // Access to F3 storage vector
    assert(f3Vec.empty()); // The default constructed vector is empty
    f3Vec.resize(2);
    f3Vec[0].field_m1().value() = 125;
    f3Vec[0].field_m2().value() = "abcd"; // Last character is expected to be truncated
    f3Vec[1].field_m1().value() = 111;
    f3Vec[1].field_m2().value() = "aa";

    auto& f4Vec = msg.field_f4().value(); // Access to F4 storage vector
    assert(f4Vec.empty()); // The default constructed vector is empty
    f4Vec.resize(1);
    f4Vec[0].field_m1().value() = 99;
    f4Vec[0].field_m2().value() = Msg10::Field_f4::ValueType::value_type::Field_m2::ValueType::V2;
    f4Vec[0].field_m3().value() = "hello"; 
    sendMessage(msg);
}

void ClientSession::sendMsg11()
{
    Msg11 msg;

    msg.field_f11_1().value() = 0xff;
    msg.field_f2().value() = Msg11::Field_f2::ValueType::V1;
    msg.field_f3().field_m1().value() = 0x11;
    msg.field_f3().field_m2().value() = Msg11::Field_f3::Field_m2::ValueType::V2;
    sendMessage(msg);
}

void ClientSession::sendMsg12()
{
    Msg12 msg;

    assert(msg.field_f1().isTentative());
    assert(msg.field_f1().length() == 0U); // Tentative mode does not produce any output

    msg.field_f1().field().value() = 0xabcd;
    msg.field_f1().setExists();

    assert(msg.field_f1().length() == 2U); // Now when exists, the output is expected

    sendMessage(msg);
}

void ClientSession::sendMsg13()
{
    Msg13 msg;

    assert(msg.field_f2().isMissing());
    assert(msg.field_f3().doesExist());

    msg.field_f2().field().value() = 0xabcd;
    msg.field_flags().setBitValue_F2Present(true);
    msg.field_flags().setBitValue_F3Missing(true);

    msg.doRefresh(); // Bring message contents into consistent state
    assert(msg.field_f2().doesExist());
    assert(msg.field_f3().isMissing());

    sendMessage(msg);
}

void ClientSession::sendMsg14()
{
    Msg14 msg;

    assert(msg.field_f3().isMissing());

    msg.field_f1().value() = 5;
    msg.field_f2().value() = -5;
    msg.field_f3().field().value() = 0xaaaa;

    msg.doRefresh(); // Bring message contents into consistent state
    assert(msg.field_f3().doesExist());

    sendMessage(msg);
}

void ClientSession::sendMsg15()
{
    Msg15 msg;
    msg.field_f1().value() = 5;
    msg.field_f2().value() = 100;
    msg.field_f3().value() = 20;
    sendMessage(msg);
}

void ClientSession::sendMsg16()
{
    Msg16 msg;
    msg.field_f1().value() = 1;
    msg.field_f2().value() = 2;
    msg.field_f3().value() = 3;
    sendMessage(msg);
}


void ClientSession::sendMsg17()
{
    Msg17 msg;

    auto& f2 = msg.field_f2(); // Access to f2 field
    // Assign values to f2 members
    f2.field_m1().value() = 0x1234;
    f2.field_m2().value() = 0x5678;
    f2.field_m2().value() = 0xdead;

    sendMessage(msg);
}

void ClientSession::sendMsg18()
{
    Msg18 msg;

    assert(msg.field_f2().isMissing());
    assert(msg.field_f3().doesExist());

    msg.field_f1().value() = "hello";
    msg.field_f2().field().value() = 0xabcd;

    msg.doRefresh(); // Bring message contents into consistent state
    assert(msg.field_f2().doesExist());
    assert(msg.field_f3().isMissing());

    sendMessage(msg);
}

SessionPtr Session::createClient(boost_wrap::io& io)
{
    return SessionPtr(new ClientSession(io));
}

} // namespace cc_tutorial
