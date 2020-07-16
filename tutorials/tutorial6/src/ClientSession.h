#pragma once

#include <iterator>
#include <vector>
#include <iostream>

#include "tutorial6/Message.h"
#include "tutorial6/frame/Frame.h"

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
        tutorial6::Message<
            comms::option::app::ReadIterator<const std::uint8_t*>, // Polymorphic read
            comms::option::app::WriteIterator<std::back_insert_iterator<std::vector<std::uint8_t> > >, // Polymorphic write
            comms::option::app::LengthInfoInterface, // Polymorphic length calculation
            comms::option::app::IdInfoInterface, // Polymorphic message ID retrieval
            comms::option::app::NameInterface // Polymorphic message name retrieval
        >;
        
    // Definition of all the used message classes
    using Msg1 = tutorial6::message::Msg1<Message>;
    using Msg2 = tutorial6::message::Msg2<Message>;
    using Msg3 = tutorial6::message::Msg3<Message>;

    // Handling functions for all the dispatched message objects
    template <typename TMsg>
    void handle(TMsg& msg)
    {
        std::cout << "Received \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << '\n';
        doNextStage();
    }

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
        CommsStage_NumOfValues
    };

    void sendMessage(const Message& msg);
    void doNextStage();
    void sendMsg1();
    void sendMsg2();
    void sendMsg3();

    using Frame = tutorial6::frame::Frame<Message>;

    Frame m_frame;
    CommsStage m_currentStage = CommsStage_NumOfValues;
};

} // namespace cc_tutorial
