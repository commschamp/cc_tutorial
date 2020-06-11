#pragma once

#include "tutorial9/Message.h"
#include "tutorial9/frame/Frame.h"
#include "tutorial9/input/ServerInputMessages.h"

#include "Session.h"

namespace cc_tutorial
{

class ServerSession : public Session
{
    using Base = Session;
public:
    using Base::Base; // Inherit constructors

    // Common interface class for input messages
    using InMessage =
        tutorial9::Message<
            comms::option::app::ReadIterator<const std::uint8_t*>, // Polymorphic read
            comms::option::app::Handler<ServerSession> // Polymorphic message dispatch
        >;

    // Declaration of input messages
    using InMsg1 = tutorial9::message::Msg1<InMessage>;
    using InMsg3 = tutorial9::message::Msg3<InMessage>;

    // Handlers for input messages
    void handle(InMsg1& msg);
    void handle(InMsg3& msg);
    void handle(InMessage& msg);

protected:
    virtual std::size_t processInputImpl(const std::uint8_t* buf, std::size_t bufLen) override final;

private:

    // Common interface class for output messages
    using OutMessage =
        tutorial9::Message<
            comms::option::app::WriteIterator<std::uint8_t*>, // Polymorphic write
            comms::option::app::LengthInfoInterface, // Polymorphic length calculation
            comms::option::app::IdInfoInterface, // Polymorphic message ID retrieval
            comms::option::app::NameInterface // Polymorphic message name retrieval
        >;

    // Declaration of output messages
    using OutMsg2 = tutorial9::message::Msg2<OutMessage>;
    using OutMsg4 = tutorial9::message::Msg4<OutMessage>;

    using Frame =
        tutorial9::frame::Frame<
            InMessage,
            tutorial9::input::ServerInputMessages<InMessage>
        >;

    void sendMessage(const OutMessage& msg);

    Frame m_frame;
};

} // namespace cc_tutorial
