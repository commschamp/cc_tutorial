#pragma once

#include <iterator>
#include <vector>

#include "tutorial1/Message.h"
#include "tutorial1/frame/Frame.h"

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
        tutorial1::Message<
            comms::option::ReadIterator<const std::uint8_t*>, // Polymorphic read
            comms::option::WriteIterator<std::back_insert_iterator<std::vector<std::uint8_t> > >, // Polymorphic write
            comms::option::LengthInfoInterface, // Polymorphic length calculation
            comms::option::IdInfoInterface, // Polymorphic message ID retrieval
            comms::option::NameInterface, // Polymorphic message name retrieval
            comms::option::Handler<ClientSession> // Polymorphic dispatch
        >;

    // Definition of all the used message classes
    using Msg1 = tutorial1::message::Msg1<Message>;
    using Msg2 = tutorial1::message::Msg2<Message>;

    // Handling functions for all the dispatched message objects
    void handle(Msg1& msg);
    void handle(Msg2& msg);
    void handle(Message& msg);

protected:
    virtual bool startImpl() override final;
    virtual std::size_t processInputImpl(const std::uint8_t* buf, std::size_t bufLen) override final;

private:
    enum CommsStage
    {
        CommsStage_Msg1,
        CommsStage_Msg2,
        CommsStage_NumOfValues
    };

    void sendMessage(const Message& msg);
    void doNextStage();
    void sendMsg1();
    void sendMsg2();

    using Frame = tutorial1::frame::Frame<Message>;
    Frame m_frame;
    CommsStage m_currentStage = CommsStage_NumOfValues;
    unsigned m_completedCycles = 0;
};

} // namespace cc_tutorial
