#pragma once

#include <iterator>
#include <vector>

#include "tutorial13/Message.h"
#include "tutorial13/frame/Frame.h"
#include "tutorial13/input/ClientInputMessages.h"
#include "tutorial13/options/ClientDefaultOptions.h"

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
        tutorial13::Message<
            comms::option::app::ReadIterator<const std::uint8_t*>, // Polymorphic read
            comms::option::app::WriteIterator<std::back_insert_iterator<std::vector<std::uint8_t> > >, // Polymorphic write
            comms::option::app::LengthInfoInterface, // Polymorphic length calculation
            comms::option::app::IdInfoInterface, // Polymorphic message ID retrieval
            comms::option::app::NameInterface, // Polymorphic name retrieval
            comms::option::app::Handler<ClientSession> // Polymorphic dispatch        
        >;

    // Protocol options for client
    using ClientProtocolOptions = tutorial13::options::ClientDefaultOptions;
        
    // Definition of all the used message classes
    using Msg1_1 = tutorial13::message::Msg1_1<Message, ClientProtocolOptions>;
    using Msg1_2 = tutorial13::message::Msg1_2<Message, ClientProtocolOptions>;
    using Msg1_3 = tutorial13::message::Msg1_3<Message, ClientProtocolOptions>;
    using Msg2_1 = tutorial13::message::Msg2_1<Message, ClientProtocolOptions>;
    using Msg2_2 = tutorial13::message::Msg2_2<Message, ClientProtocolOptions>;
    using Msg2_3 = tutorial13::message::Msg2_3<Message, ClientProtocolOptions>;
    
    // Handling functions for all the dispatched message objects
    void handle(Msg1_1& msg);
    void handle(Msg1_2& msg);
    void handle(Msg1_3& msg);
    void handle(Msg2_1& msg);
    void handle(Msg2_2& msg);
    void handle(Msg2_3& msg);
    void handle(Message& msg);

protected:
    virtual bool startImpl() override final;
    virtual std::size_t processInputImpl(const std::uint8_t* buf, std::size_t bufLen) override final;

private:
    enum CommsStage
    {
        CommsStage_Msg1_1,
        CommsStage_Msg1_2,
        CommsStage_Msg1_3,
        CommsStage_Msg2_1,
        CommsStage_Msg2_2,
        CommsStage_Msg2_3,
        CommsStage_NumOfValues
    };

    void sendMessage(const Message& msg);
    void doNextStage();
    void sendMsg1_1();
    void sendMsg1_2();
    void sendMsg1_3();
    void sendMsg2_1();
    void sendMsg2_2();
    void sendMsg2_3();

    // Client specific frame 
    using Frame = 
        tutorial13::frame::Frame<
            Message,
            tutorial13::input::ClientInputMessages<Message, ClientProtocolOptions>,
            ClientProtocolOptions
        >;

    Frame m_frame;
    CommsStage m_currentStage = CommsStage_NumOfValues;
};

} // namespace cc_tutorial
