#pragma once

#include <iterator>
#include <vector>

#include "tutorial22/Message.h"
#include "tutorial22/frame/Frame.h"
#include "tutorial22/input/ClientInputMessages.h"
#include "tutorial22/options/ClientDefaultOptions.h"

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
        tutorial22::Message<
            comms::option::app::ReadIterator<const std::uint8_t*>, // Polymorphic read
            comms::option::app::WriteIterator<std::back_insert_iterator<std::vector<std::uint8_t> > >, // Polymorphic write
            comms::option::app::LengthInfoInterface, // Polymorphic length calculation
            comms::option::app::IdInfoInterface, // Polymorphic message ID retrieval
            comms::option::app::NameInterface, // Polymorphic name retrieval
            comms::option::app::Handler<ClientSession>, // Polymorphic dispatch        
            comms::option::app::RefreshInterface // Polymorphic refresh        
        >;

    // Protocol options for client
    using ClientProtocolOptions = tutorial22::options::ClientDefaultOptions;
        
    // Definition of all the used message classes
    using Msg1 = tutorial22::message::Msg1<Message, ClientProtocolOptions>;
    
    // Handling functions for all the dispatched message objects
    void handle(Msg1& msg);
    void handle(Message& msg);

    using Prop1 = Msg1::Field_f1::ValueType::value_type::Field_prop1;
    using Prop2 = Msg1::Field_f1::ValueType::value_type::Field_prop2;
    using AnyProp = Msg1::Field_f1::ValueType::value_type::Field_any;    

    void handleProp(const Prop1& prop);
    void handleProp(const Prop2& prop);
    void handleProp(const AnyProp& prop);    

protected:
    virtual bool startImpl() override final;
    virtual std::size_t processInputImpl(const std::uint8_t* buf, std::size_t bufLen) override final;

private:
    enum CommsStage
    {
        CommsStage_Msg1,
        CommsStage_NumOfValues
    };

    void sendMessage(Message& msg);
    void doNextStage();
    void sendMsg1();

    // Client specific frame 
    using Frame = 
        tutorial22::frame::Frame<
            Message,
            tutorial22::input::ClientInputMessages<Message, ClientProtocolOptions>,
            ClientProtocolOptions
        >;

    Frame m_frame;
    CommsStage m_currentStage = CommsStage_NumOfValues;
};

} // namespace cc_tutorial
