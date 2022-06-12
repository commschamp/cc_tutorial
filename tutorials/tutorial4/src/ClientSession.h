#pragma once

#include <iterator>
#include <vector>

#include "tutorial4/Message.h"
#include "tutorial4/frame/Frame.h"

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
        tutorial4::Message<
            comms::option::app::ReadIterator<const std::uint8_t*>, // Polymorphic read
            comms::option::app::WriteIterator<std::back_insert_iterator<std::vector<std::uint8_t> > >, // Polymorphic write
            comms::option::app::LengthInfoInterface, // Polymorphic length calculation
            comms::option::app::IdInfoInterface, // Polymorphic message ID retrieval
            comms::option::app::NameInterface, // Polymorphic message name retrieval
            comms::option::app::Handler<ClientSession> // Polymorphic dispatch
        >;
        
    // Definition of all the used message classes
    using Msg1 = tutorial4::message::Msg1<Message>;
    using Msg2 = tutorial4::message::Msg2<Message>;

    // Handling functions for all the dispatched message objects
    void handle(Msg1& msg);
    void handle(Msg2& msg);
    void handle(Message& msg);

    using Prop1 = Msg1::Field_f1::ValueType::value_type::Field_prop1;
    using Prop2 = Msg1::Field_f1::ValueType::value_type::Field_prop2;
    using Prop3 = Msg1::Field_f1::ValueType::value_type::Field_prop3;
    using Prop4 = Msg2::Field_f1::ValueType::value_type::Field_prop4;
    using Prop5 = Msg2::Field_f1::ValueType::value_type::Field_prop5;
    using Prop6 = Msg2::Field_f1::ValueType::value_type::Field_prop6;
    using Prop7 = Msg2::Field_f1::ValueType::value_type::Field_prop7;
    using AnyProp = Msg2::Field_f1::ValueType::value_type::Field_any;

    void handleProp(const Prop1& prop);
    void handleProp(const Prop2& prop);
    void handleProp(const Prop3& prop);
    void handleProp(const Prop4& prop);
    void handleProp(const Prop5& prop);
    void handleProp(const Prop6& prop);
    void handleProp(const Prop7& prop);
    void handleProp(const AnyProp& prop);

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

    using Frame = tutorial4::frame::Frame<Message>;
    Frame m_frame;
    CommsStage m_currentStage = CommsStage_NumOfValues;
};

} // namespace cc_tutorial
