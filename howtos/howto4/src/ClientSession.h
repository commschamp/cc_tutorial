#pragma once

#include <iterator>
#include <vector>

#include "howto4/Message.h"
#include "howto4/frame/Frame.h"
#include "howto4/input/ClientInputMessages.h"
#include "howto4/options/ClientDefaultOptions.h"
#include "howto4/options/DataViewDefaultOptions.h"

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
        howto4::Message<>;

    // Protocol options for client
    using ClientProtocolOptions = 
        howto4::options::DataViewDefaultOptionsT<
            howto4::options::ClientDefaultOptions
        >;
        
    // Definition of all the used message classes
    using Msg = howto4::message::Msg<Message, ClientProtocolOptions>;
    
    // Handling functions for all the dispatched message objects
    void handle(Msg& msg);
    void handle(Message& msg);

    // Handling functions for the properties
    using Prop1 = Msg::Field_props::ValueType::value_type::Field_prop1;
    using Prop2 = Msg::Field_props::ValueType::value_type::Field_prop2;
    using Prop3 = Msg::Field_props::ValueType::value_type::Field_prop3;
    using AnyProp = Msg::Field_props::ValueType::value_type::Field_any;

    void handleProp(const Prop1& prop);
    void handleProp(const Prop2& prop);
    void handleProp(const Prop3& prop);
    void handleProp(const AnyProp& prop);

protected:
    virtual bool startImpl() override final;
    virtual std::size_t processInputImpl(const std::uint8_t* buf, std::size_t bufLen) override final;

private:
    enum CommsStage
    {
        CommsStage_Msg,
        CommsStage_NumOfValues
    };

    using OutputBuf = std::vector<std::uint8_t>;

    void doNextStage();
    void sendMsg();

    // Client specific frame 
    using Frame = 
        howto4::frame::Frame<
            Message,
            howto4::input::ClientInputMessages<Message, ClientProtocolOptions>,
            ClientProtocolOptions
        >;

    Frame m_frame;
    CommsStage m_currentStage = CommsStage_NumOfValues;
};

} // namespace cc_tutorial
