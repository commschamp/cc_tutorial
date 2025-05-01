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

template <typename TMsg, typename TFrame>
void writePropInternal(const TMsg& prop, TFrame& frame, std::vector<std::uint8_t>& output)
{
    output.reserve(output.size() + frame.length(prop));
    auto writeIter = std::back_inserter(output);

    auto es = frame.write(prop, writeIter, output.max_size());
    if (es != comms::ErrorStatus::Success) {
        assert(!"Write operation failed unexpectedly");
        return;
    }
}

void writeVar1Prop(const ClientSession::Var1Interface& prop, ClientSession::KeyValuePropFrame& frame, std::vector<std::uint8_t>& output)
{
    writePropInternal(prop, frame, output);
}

void writeVar2Prop(const ClientSession::Var2Interface& prop, ClientSession::TlvPropFrame& frame, std::vector<std::uint8_t>& output)
{
    writePropInternal(prop, frame, output);
}

} // namespace 
    

void ClientSession::handle(Msg1& msg)
{
    std::cout << "Received \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << '\n';

    KeyValuePropFrame keyValueFrame;
    auto& keyValuePropsData = msg.field_keyValueProps().value();
    auto readIter = keyValuePropsData.begin();

    for (auto idx = 0U; idx < msg.field_count().value(); ++idx) {
        KeyValuePropFrame::MsgPtr propPtr;
        auto es = comms::processSingleWithDispatch(readIter, keyValuePropsData.size(), keyValueFrame, propPtr, *this);
        if (es != comms::ErrorStatus::Success) {
            std::cerr << "ERROR: encountered unexpected property" << std::endl;
        }
    }    

    std::cout << std::endl;

    if (m_currentStage != CommsStage_Msg1) {
        std::cerr << "ERROR: Unexpected message received" << std::endl;
        return;
    }    

    doNextStage();
}

void ClientSession::handle(Msg2& msg)
{
    std::cout << "Received \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << '\n';

    TlvPropFrame tlvFrame;
    auto& tlvPropsData = msg.field_tlvProps().value();
    auto readIter = tlvPropsData.begin();

    comms::processAllWithDispatch(readIter, tlvPropsData.size(), tlvFrame, *this);
    std::cout << std::endl;

    if (m_currentStage != CommsStage_Msg2) {
        std::cerr << "ERROR: Unexpected message received" << std::endl;
        return;
    }

    doNextStage();
}

void ClientSession::handle(ProtMessage& msg)
{
    // The statement below uses polymorphic message name and ID retrievals.
    std::cout << "ERROR: Received unexpected message \"" << msg.name() << "\" with ID=" <<
                 (unsigned)msg.getId() << std::endl;
}

void ClientSession::handle(Prop1& prop)
{
    std::cout << "\t\t" << prop.doName() << ":\n" <<
        "\t\t\t" << prop.field_val().name() << " = " << prop.field_val().value() << '\n';
}

void ClientSession::handle(Prop2& prop)
{
    std::cout << "\t\t" << prop.doName() << ":\n" <<
        "\t\t\t" << prop.field_val().name() << " = " << prop.field_val().value() << '\n';
}

void ClientSession::handle(Prop3& prop)
{
    std::cout << "\t\t" << prop.doName() << ":\n" <<
        "\t\t\t" << prop.field_val().name() << " = " << prop.field_val().value() << '\n';
}

void ClientSession::handle(Prop4& prop)
{
    std::cout << "\t\t" << prop.doName() << ":\n" <<
        "\t\t\t" << prop.field_val().name() << " = " << prop.field_val().value() << '\n';
}

void ClientSession::handle(Prop5& prop)
{
    std::cout << "\t\t" << prop.doName() << ":\n" <<
        "\t\t\t" << prop.field_val().name() << " = " << prop.field_val().value() << '\n';
}

void ClientSession::handle(Prop6& prop)
{
    std::cout << "\t\t" << prop.doName() << ":\n" <<
        "\t\t\t" << prop.field_val().name() << " = " << prop.field_val().value() << '\n';
}

void ClientSession::handle(Prop7& prop)
{
    std::cout << "\t\t" << prop.doName() << ":\n" <<
        "\t\t\t" << prop.field_val().name() << " = " << prop.field_val().value() << '\n';
}

void ClientSession::handle(Var1Interface& prop)
{
    std::cout << "\t\t" << prop.name() << ": (unexpected)\n";
}

void ClientSession::handle(Var2Interface& prop)
{
    std::cout << "\t\t" << prop.name() << ": (unexpected)\n";
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

void ClientSession::sendMessage(const ProtMessage& msg)
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
    };
    static const std::size_t MapSize = std::extent<decltype(Map)>::value;
    static_assert(MapSize == CommsStage_NumOfValues, "Invalid Map");

    auto func = Map[m_currentStage];
    (this->*func)(); // Call appropriate sending function
}

void ClientSession::sendMsg1()
{
    std::vector<std::uint8_t> propsData;
    KeyValuePropFrame keyValueFrame;

    Prop1 prop1;
    prop1.field_val().value() = 0xabcd;
    writeVar1Prop(prop1, keyValueFrame, propsData);

    Prop3 prop3;
    prop3.field_val().value() = "hello";
    writeVar1Prop(prop3, keyValueFrame, propsData);

    Prop2 prop2;
    prop2.field_val().value() = std::numeric_limits<Prop2::Field_val::ValueType>::infinity();
    writeVar1Prop(prop2, keyValueFrame, propsData);

    Msg1 msg;
    msg.field_count().value() = 3U;
    comms::util::assign(msg.field_keyValueProps().value(), propsData.begin(), propsData.end());

    sendMessage(msg);
}

void ClientSession::sendMsg2()
{
    std::vector<std::uint8_t> propsData;
    TlvPropFrame tlvFrame;

    Prop4 prop4;
    prop4.field_val().value() = 0xdeadbeef;
    writeVar2Prop(prop4, tlvFrame, propsData);

    Prop6 prop6;
    prop6.field_val().value() = "blabla";
    writeVar2Prop(prop6, tlvFrame, propsData);

    Prop5 prop5;
    prop5.field_val().value() = 1.234;
    writeVar2Prop(prop5, tlvFrame, propsData);

    Prop7 prop7;
    prop7.field_val().value() = 100;
    writeVar2Prop(prop7, tlvFrame, propsData);

    Msg2 msg;
    comms::util::assign(msg.field_tlvProps().value(), propsData.begin(), propsData.end());
    sendMessage(msg);
}

SessionPtr Session::createClient(boost_wrap::io& io)
{
    return SessionPtr(new ClientSession(io));
}

} // namespace cc_tutorial
