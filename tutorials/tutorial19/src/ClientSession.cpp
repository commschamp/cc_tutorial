#include "ClientSession.h"

#include <iostream>
#include <cassert>
#include <iterator>
#include <iomanip>

#include "comms/process.h"
#include "comms/iterator.h"

namespace cc_tutorial
{

namespace
{

template <typename TField>
void printIntField(const TField& field, const std::string& prefix = std::string())
{
    std::cout << '\t' << prefix << field.name() << " = " << field.value() << '\n';
}

template <typename TField>
bool printOptionalField(const TField& field, const std::string& prefix = std::string())
{
    std::cout << '\t' << prefix << field.name();

    static const std::string ModeMap[] = {
        /* comms::field::OptionalMode::Tentative */ "tentative",
        /* comms::field::OptionalMode::Exists */ "exists",
        /* comms::field::OptionalMode::Missing */ "missing",
    };
    static const std::size_t ModeMapSize = std::extent<decltype(ModeMap)>::value;
    static_assert(ModeMapSize == (unsigned)comms::field::OptionalMode::NumOfModes, "Invalid Map");

    auto mapIdx = static_cast<unsigned>(field.getMode());
    if (ModeMapSize <= mapIdx) {
        assert(!"Unexpected mode value, should not happen");
        std::cout << " (unknown)" << std::endl;
        return false;
    }

    std::cout << " (" << ModeMap[mapIdx] << ")" << std::endl;
    return field.doesExist(); // Print the rest only if field is present
}

template <typename TField>
void printEnumField(const TField& field, const std::string& prefix = std::string())
{
    std::cout << '\t' << prefix << field.name() << " = " << (unsigned)field.value() << 
        " (" << field.valueName() << ")\n";
}

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

} // namespace

void ClientSession::handle(Msg1& msg)
{
    std::cout << "Received message \"" << msg.doName() << "\" with ID=" << 
        (unsigned)msg.doGetId() << " and version=" << msg.version() << '\n';
    printIntField(msg.field_f1());
    if (printOptionalField(msg.field_f2())) {
        printIntField(msg.field_f2().field(), "\t");
    }    
    if (printOptionalField(msg.field_f3())) {
        printIntField(msg.field_f3().field(), "\t");
    }
    std::cout << std::endl;

    if (m_currentStage != CommsStage_Msg1) {
        std::cerr << "ERROR: Unexpected stage" << std::endl;
        return;
    }

    doNextStage();
}

void ClientSession::handle(Msg2& msg)
{
    std::cout << "Received message \"" << msg.doName() << "\" with ID=" << 
        (unsigned)msg.doGetId() << " and version=" << msg.version() << '\n';

    if (printOptionalField(msg.field_f1())) {
        printEnumField(msg.field_f1().field(), "\t");
    }         
    if (printOptionalField(msg.field_f2())) {
        printEnumField(msg.field_f2().field(), "\t");
    }    
    std::cout << std::endl;

    if (m_currentStage != CommsStage_Msg2) {
        std::cerr << "ERROR: Unexpected stage" << std::endl;
        return;
    }

    doNextStage();
}

void ClientSession::handle(Msg3& msg)
{
    std::cout << "Received message \"" << msg.doName() << "\" with ID=" << 
        (unsigned)msg.doGetId() << " and version=" << msg.version() << '\n';

    printSetField(msg.field_f1());
    if (printOptionalField(msg.field_f2())) {
        printIntField(msg.field_f2().field(), "\t");
    }
    if (printOptionalField(msg.field_f3())) {
        printIntField(msg.field_f3().field(), "\t");
    }    
    if (printOptionalField(msg.field_f4())) {
        printIntField(msg.field_f4().field(), "\t");
    }    
    std::cout << std::endl;

    if (m_currentStage != CommsStage_Msg3) {
        std::cerr << "ERROR: Unexpected stage" << std::endl;
        return;
    }

    doNextStage();
}

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
    if (es == comms::ErrorStatus::UpdateRequired) {
        auto updateIter = &output[0];
        es = m_frame.update(updateIter, output.size());
    }

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
    assert(msg.version() == 5U); // Schema version by default

    // The version based optional fields must exist by default
    assert(msg.field_f2().doesExist());
    assert(msg.field_f3().doesExist());
    
    msg.field_f1().value() = 1111;
    msg.field_f2().field().value() = 2222;
    msg.field_f3().field().value() = 3333;

    msg.version() = 3U;
    msg.doRefresh(); // Update version fields;

    assert(msg.field_f2().doesExist());
    assert(msg.field_f3().isMissing()); // Does not exist for version 3    
    
    sendMessage(msg);
}

void ClientSession::sendMsg2()
{
    Msg2 msg;
    assert(msg.version() == 5U); // Schema version by default

    // The version based optional fields must exist by default
    assert(msg.field_f1().doesExist());
    assert(msg.field_f2().doesExist());
    
    msg.field_f1().field().value() = Msg2::Field_f1::Field::ValueType::V1;
    msg.field_f2().field().value() = Msg2::Field_f2::Field::ValueType::V2;

    msg.version() = 2U;
    msg.doRefresh(); // Update version fields;

    assert(msg.field_f1().doesExist());
    assert(msg.field_f2().isMissing()); // Does not exist for version 2       
    sendMessage(msg);
}

void ClientSession::sendMsg3()
{
    Msg3 msg;
    assert(msg.version() == 5U); // Schema version by default

    msg.field_f2().field().value() = 1111;
    msg.field_f3().field().value() = 2222;
    msg.field_f4().field().value() = 3333;
    msg.field_f1().setBitValue_B0(true);

    msg.doRefresh(); // Update version fields;

    assert(msg.field_f2().doesExist());
    assert(msg.field_f3().isMissing()); 
    assert(msg.field_f4().doesExist()); // Exists for versison 5
    sendMessage(msg);
}

SessionPtr Session::createClient(boost_wrap::io& io)
{
    return SessionPtr(new ClientSession(io));
}

} // namespace cc_tutorial
