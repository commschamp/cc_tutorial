#pragma once

#include <iostream>
#include <vector>

#include "comms/GenericHandler.h"

#include "tutorial8/Message.h"
#include "tutorial8/frame/Frame.h"

#include "Session.h"

namespace cc_tutorial
{

class ClientSession : public Session
{
    using Base = Session;
public:

    using Base::Base;

    // Return type of handle() member functions
    using RetType = bool;

    // Common interface class for all the messages
    using Message =
        tutorial8::Message<
            comms::option::app::ReadIterator<const std::uint8_t*>, // Polymorphic read
            comms::option::app::WriteIterator<std::back_insert_iterator<std::vector<std::uint8_t> > >, // Polymorphic write
            comms::option::app::LengthInfoInterface, // Polymorphic length calculation
            comms::option::app::IdInfoInterface, // Polymorphic message ID retrieval
            comms::option::app::NameInterface, // Polymorphic message name retrieval
            comms::option::app::Handler<ClientSession> // Polymorphic dispatch
        >;


    // Definition of all the used message classes
    using Msg1 = tutorial8::message::Msg1<Message>;
    using Msg2 = tutorial8::message::Msg2<Message>;
    using Msg3 = tutorial8::message::Msg3<Message>;

    bool handle(Msg1& msg);
    bool handle(Msg2& msg);
    bool handle(Message& msg);

protected:
    virtual bool startImpl() override final;
    virtual std::size_t processInputImpl(const std::uint8_t* buf, std::size_t bufLen) override final;

private:
    using Frame = tutorial8::frame::Frame<Message>;

    enum CommsStage
    {
        CommsStage_Msg1,
        CommsStage_Msg2,
        CommsStage_Msg3,
        CommsStage_NumOfValues
    };

    template<typename TMsg>
    bool handleInternal(TMsg& msg)
    {
        std::cout << "Received message \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << std::endl;
        return true;
    }

    void sendMessage(const Message& msg);
    void doNextStage();
    void sendMsg1();
    void sendMsg2();
    void sendMsg3();

    Frame m_frame;
    CommsStage m_currentStage = CommsStage_NumOfValues;
};

} // namespace cc_tutorial
