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
            comms::option::app::ReadIterator<const std::uint8_t*>, // Polymorphic read
            comms::option::app::WriteIterator<std::back_insert_iterator<std::vector<std::uint8_t> > >, // Polymorphic write
            comms::option::app::LengthInfoInterface, // Polymorphic length calculation
            comms::option::app::IdInfoInterface, // Polymorphic message ID retrieval
            comms::option::app::NameInterface, // Polymorphic message name retrieval
            comms::option::app::Handler<ClientSession> // Polymorphic dispatch
        >;
        
    // Verify presence of polymorphic functionality
    static_assert(Message::hasRead(), "Missing polymorphic read");
    static_assert(Message::hasWrite(), "Missing polymorphic write");
    static_assert(Message::hasLength(), "Missing polymorphic length");
    static_assert(Message::hasGetId(), "Missing polymorphic getId");
    static_assert(Message::hasName(), "Missing polymorphic name");
    static_assert(Message::hasDispatch(), "Missing polymorphic dispatch");
        
        
    // Verify that destructor is virtual
    static_assert(std::has_virtual_destructor<Message>::value, "Destructor is not virtual");
        

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
