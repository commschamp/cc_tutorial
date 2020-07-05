#pragma once

#include <iterator>
#include <vector>
#include <iostream>

#include "tutorial15/Message.h"
#include "tutorial15/frame/Frame.h"
#include "tutorial15/input/ClientInputMessages.h"
#include "tutorial15/options/ClientDefaultOptions.h"

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
        tutorial15::Message<
            comms::option::app::ReadIterator<const std::uint8_t*>, // Polymorphic read
            comms::option::app::WriteIterator<std::back_insert_iterator<std::vector<std::uint8_t> > >, // Polymorphic write
            comms::option::app::LengthInfoInterface, // Polymorphic length calculation
            comms::option::app::IdInfoInterface, // Polymorphic message ID retrieval
            comms::option::app::NameInterface, // Polymorphic name retrieval
            comms::option::app::Handler<ClientSession> // Polymorphic dispatch        
        >;

    // Protocol options for client
    using ClientProtocolOptions = tutorial15::options::ClientDefaultOptions;
        
    // Definition of all the used message classes
    using Msg1 = tutorial15::message::Msg1<Message, ClientProtocolOptions>;
    using Msg2 = tutorial15::message::Msg2<Message, ClientProtocolOptions>;
    using Msg3 = tutorial15::message::Msg3<Message, ClientProtocolOptions>;
    
    // Handling functions for all the dispatched message objects
    void handle(Msg2& msg);
    void handle(Msg3& msg);
    void handle(Message& msg);

protected:
    virtual bool startImpl() override final;
    virtual std::size_t processInputImpl(const std::uint8_t* buf, std::size_t bufLen) override final;

private:
    enum CommsStage
    {
        CommsStage_Msg1Msg2,
        CommsStage_Msg3,
        CommsStage_NumOfValues
    };

    void sendMessage(const Message& msg);
    void doNextStage();
    void sendMsg1Msg2();
    void sendMsg3();

    // Client specific frame 
    using Frame = 
        tutorial15::frame::Frame<
            Message,
            tutorial15::input::ClientInputMessages<Message, ClientProtocolOptions>,
            ClientProtocolOptions
        >;

    Frame m_frame;
    CommsStage m_currentStage = CommsStage_NumOfValues;
    unsigned m_completedCycles = 0;
};

} // namespace cc_tutorial
