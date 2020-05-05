#pragma once

#include <iterator>
#include <vector>

#include "tutorial2/Message.h"
#include "tutorial2/frame/Frame.h"

#include "Session.h"

namespace cc_tutorial
{

class ClientSession : public Session
{
    using Base = Session;
public:
    using Base::Base; // Inherit constructors

    // Common interface class for all the messages
    using Message =
        tutorial2::Message<
            comms::option::ReadIterator<const std::uint8_t*>, // Polymorphic read
            comms::option::WriteIterator<std::back_insert_iterator<std::vector<std::uint8_t> > >, // Polymorphic write
            comms::option::LengthInfoInterface, // Polymorphic length calculation
            comms::option::IdInfoInterface, // Polymorphic message ID retrieval
            comms::option::NameInterface, // Polymorphic message name retrieval
            comms::option::Handler<ClientSession> // Polymorphic dispatch
        >;
        
    // Definition of all the used message classes
    using Msg1 = tutorial2::message::Msg1<Message>;
    using Msg2 = tutorial2::message::Msg2<Message>;
    using Msg3 = tutorial2::message::Msg3<Message>;
    using Msg4 = tutorial2::message::Msg4<Message>;
    using Msg5 = tutorial2::message::Msg5<Message>;
    using Msg6 = tutorial2::message::Msg6<Message>;
    using Msg7 = tutorial2::message::Msg7<Message>;
    using Msg8 = tutorial2::message::Msg8<Message>;
    using Msg9 = tutorial2::message::Msg9<Message>;
    using Msg10 = tutorial2::message::Msg10<Message>;
    using Msg11 = tutorial2::message::Msg11<Message>;

    // Handling functions for all the dispatched message objects
    void handle(Msg1& msg);
    void handle(Msg2& msg);
    void handle(Msg3& msg);
    void handle(Msg4& msg);
    void handle(Msg5& msg);
    void handle(Msg6& msg);
    void handle(Msg7& msg);
    void handle(Msg8& msg);
    void handle(Msg9& msg);
    void handle(Msg10& msg);
    void handle(Msg11& msg);
    void handle(Message& msg);

protected:
    virtual bool startImpl() override final;
    virtual std::size_t processInputImpl(const std::uint8_t* buf, std::size_t bufLen) override final;

private:
    enum CommsStage
    {
        CommsStage_Msg1,
        CommsStage_Msg2,
        CommsStage_Msg3,
        CommsStage_Msg4,
        CommsStage_Msg5,
        CommsStage_Msg6,
        CommsStage_Msg7,
        CommsStage_Msg8,
        CommsStage_Msg9,
        CommsStage_Msg10,
        CommsStage_Msg11,
        CommsStage_NumOfValues
    };

    void sendMessage(const Message& msg);
    void doNextStage();
    void sendMsg1();
    void sendMsg2();
    void sendMsg3();
    void sendMsg4();
    void sendMsg5();
    void sendMsg6();
    void sendMsg7();
    void sendMsg8();
    void sendMsg9();
    void sendMsg10();
    void sendMsg11();

    using Frame = tutorial2::frame::Frame<Message>;
    Frame m_frame;
    CommsStage m_currentStage = CommsStage_NumOfValues;
    unsigned m_completedCycles = 0;
};

} // namespace cc_tutorial
