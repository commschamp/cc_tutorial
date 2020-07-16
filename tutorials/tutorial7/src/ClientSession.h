#pragma once

#include <vector>

#include "comms/GenericHandler.h"

#include "tutorial7/Message.h"
#include "tutorial7/frame/Frame.h"

#include "Session.h"

namespace cc_tutorial
{

class ClientSession : public Session
{
    using Base = Session;
public:

    explicit ClientSession(boost_wrap::io& io);

    // Forward declaration
    class HandlerBase;

    // Common interface class for all the messages
    using Message =
        tutorial7::Message<
            comms::option::app::ReadIterator<const std::uint8_t*>, // Polymorphic read
            comms::option::app::WriteIterator<std::back_insert_iterator<std::vector<std::uint8_t> > >, // Polymorphic write
            comms::option::app::LengthInfoInterface, // Polymorphic length calculation
            comms::option::app::IdInfoInterface, // Polymorphic message ID retrieval
            comms::option::app::NameInterface, // Polymorphic message name retrieval
            comms::option::app::Handler<HandlerBase> // Polymorphic dispatch
        >;

    using Frame = tutorial7::frame::Frame<Message>;

    class HandlerBase : public
        comms::GenericHandler<
            Message,
            Frame::AllMessages
        >
    {
    public:
        virtual ~HandlerBase() = default;
    };

    using HandlerPtr = std::unique_ptr<HandlerBase>;
        
    // Definition of all the used message classes
    using Msg1 = tutorial7::message::Msg1<Message>;
    using Msg2 = tutorial7::message::Msg2<Message>;
    using Msg3 = tutorial7::message::Msg3<Message>;


    class Handler1 : public HandlerBase
    {
    public:
        using HandlerBase::handle; // to avoid "hiding" warning

        virtual void handle(Msg1& msg) override;
        virtual void handle(Message& msg) override;
    };

    class Handler2 : public HandlerBase
    {
    public:
        using HandlerBase::handle; // to avoid "hiding" warning

        virtual void handle(Msg2& msg) override;
        virtual void handle(Message& msg) override;
    };

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

    Frame m_frame;
    CommsStage m_currentStage = CommsStage_NumOfValues;
    std::vector<HandlerPtr> m_handlers;
};

} // namespace cc_tutorial
