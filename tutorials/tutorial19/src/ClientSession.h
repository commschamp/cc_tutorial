#pragma once

#include <iterator>
#include <vector>

#include "tutorial19/Interface.h"
#include "tutorial19/frame/Frame.h"
#include "tutorial19/input/ClientInputMessages.h"
#include "tutorial19/options/ClientDefaultOptions.h"
#include "tutorial19/options/DataViewDefaultOptions.h"

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
        tutorial19::Interface<
            comms::option::app::ReadIterator<const std::uint8_t*>, // Polymorphic read
            comms::option::app::WriteIterator<std::back_insert_iterator<std::vector<std::uint8_t> > >, // Polymorphic write
            comms::option::app::LengthInfoInterface, // Polymorphic length calculation
            comms::option::app::IdInfoInterface, // Polymorphic message ID retrieval
            comms::option::app::NameInterface, // Polymorphic name retrieval
            comms::option::app::Handler<ClientSession> // Polymorphic dispatch        
        >;

    // Protocol options for client
    using ClientProtocolOptions = 
        tutorial19::options::DataViewDefaultOptionsT<
            tutorial19::options::ClientDefaultOptions
        >;
        
    // Definition of all the used message classes
    using Msg1 = tutorial19::message::Msg1<Message, ClientProtocolOptions>;
    using Msg2 = tutorial19::message::Msg2<Message, ClientProtocolOptions>;
    using Msg3 = tutorial19::message::Msg3<Message, ClientProtocolOptions>;
    
    // Handling functions for all the dispatched message objects
    void handle(Msg1& msg);
    void handle(Msg2& msg);
    void handle(Msg3& msg);
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

    // Client specific frame 
    using Frame = 
        tutorial19::frame::Frame<
            Message,
            tutorial19::input::ClientInputMessages<Message, ClientProtocolOptions>,
            ClientProtocolOptions
        >;

    Frame m_frame;
    CommsStage m_currentStage = CommsStage_NumOfValues;
};

} // namespace cc_tutorial
