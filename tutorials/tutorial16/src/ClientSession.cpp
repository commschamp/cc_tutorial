#include "ClientSession.h"

#include <cassert>
#include <iterator>

#include "comms/process.h"
#include "comms/iterator.h"

namespace cc_tutorial
{

void ClientSession::handle(Msg1& msg)
{
    std::cout << "Received message \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << '\n';
    printIntField(msg.field_f1());
    printIntField(msg.field_f2());
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
    std::cout << "Received message \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << '\n';
    printString(msg.field_f1());
    if (printOptionalField(msg.field_f2())) {
        printIntField(msg.field_f2().field(), "\t");
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
    std::cout << "Received message \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << '\n';
    printIntField(msg.field_f1());
    std::cout << std::endl;

    if (m_currentStage != CommsStage_Msg3) {
        std::cerr << "ERROR: Unexpected stage" << std::endl;
        return;
    }

    doNextStage();
}

void ClientSession::handle(Msg4& msg)
{
    std::cout << "Received message \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << '\n';
    printIntField(msg.field_f1());
    std::cout << std::endl;

    if (m_currentStage != CommsStage_Msg4) {
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
    };
    static const std::size_t MapSize = std::extent<decltype(Map)>::value;
    static_assert(MapSize == CommsStage_NumOfValues, "Invalid Map");

    auto func = Map[m_currentStage];
    (this->*func)(); // Call appropriate sending function
}

void ClientSession::sendMsg1()
{
    Msg1 msg;
    assert(msg.field_f3().isMissing()); // F3 is missing when default constructed

    msg.field_f1().value() = 1111;
    msg.field_f2().value() = 2222;
    msg.field_f3().field().value() = 1234;
    msg.transportField_flags().setBitValue_B0(true);

    msg.doRefresh(); // Bring everything into consistent state
    assert(msg.field_f3().doesExist()); // F3 must exist after refresh
    
    sendMessage(msg);
}

void ClientSession::sendMsg2()
{
    Msg2 msg;
    assert(msg.field_f2().isMissing()); // F2 is missing when default constructed

    msg.field_f1().value() = "hello";
    msg.field_f2().field().value() = 4321;
    msg.transportField_flags().setBitValue_B1(true);

    msg.doRefresh(); // Bring everything into consistent state
    assert(msg.field_f2().doesExist()); // F2 must exist after refresh    
    sendMessage(msg);
}

void ClientSession::sendMsg3()
{
    Msg3 msg;
    assert(msg.transportField_flags().getBitValue_B2()); // Check the constructor sets bit's value

    msg.field_f1().value() = 1111;
    sendMessage(msg);
}

void ClientSession::sendMsg4()
{
    Msg4 msg;
    assert(msg.transportField_flags().getBitValue_B2()); // Check the constructor sets bit's value
    assert(msg.transportField_flags().getBitValue_B3()); // Check the constructor sets bit's value

    msg.field_f1().value() = 2222;
    sendMessage(msg);
}

SessionPtr Session::createClient(boost_wrap::io& io)
{
    return SessionPtr(new ClientSession(io));
}

} // namespace cc_tutorial
