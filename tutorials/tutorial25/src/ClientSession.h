#pragma once

#include <iterator>
#include <iostream>
#include <vector>

#include "tutorial25/Message.h"
#include "tutorial25/frame/Frame.h"
#include "tutorial25/input/ClientInputMessages.h"
#include "tutorial25/options/ClientInputMessagesDynMemMsgFactoryDefaultOptions.h"
#include "tutorial25/options/ClientDefaultOptions.h"

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
        tutorial25::Message<
            comms::option::app::ReadIterator<const std::uint8_t*>, // Polymorphic read
            comms::option::app::WriteIterator<std::back_insert_iterator<std::vector<std::uint8_t> > >, // Polymorphic write
            comms::option::app::LengthInfoInterface, // Polymorphic length calculation
            comms::option::app::IdInfoInterface, // Polymorphic message ID retrieval
            comms::option::app::NameInterface, // Polymorphic name retrieval
            comms::option::app::Handler<ClientSession> // Polymorphic dispatch        
        >;

    // Protocol options for client
    using ClientProtocolOptions = 
        tutorial25::options::ClientInputMessagesDynMemMsgFactoryDefaultOptionsT<
            tutorial25::options::ClientDefaultOptions
        >;
        
    // Definition of all the used message classes
    TUTORIAL25_ALIASES_FOR_ALL_MESSAGES(,,Message,ClientProtocolOptions);
    
    // Handling functions for all the dispatched message objects
    template <typename TMsg>
    void handle(TMsg& msg)
    {
        std::cout << "Received message \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << std::endl;
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
        CommsStage_Msg4,
        CommsStage_Msg5,
        CommsStage_Msg6,
        CommsStage_Msg7,
        CommsStage_Msg8,
        CommsStage_Msg9,
        CommsStage_Msg10,
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

    // Client specific frame 
    using Frame = 
        tutorial25::frame::Frame<
            Message,
            tutorial25::input::ClientInputMessages<Message, ClientProtocolOptions>,
            ClientProtocolOptions
        >;

    Frame m_frame;
    CommsStage m_currentStage = CommsStage_NumOfValues;
};

} // namespace cc_tutorial
