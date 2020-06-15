#pragma once

#include "tutorial10/Message.h"
#include "tutorial10/frame/Frame.h"
#include "tutorial10/input/ServerInputMessages.h"
#include "tutorial10/options/ServerDefaultOptions.h"

#include "Session.h"

namespace cc_tutorial
{

class ServerSession : public Session
{
    using Base = Session;
public:
    using Base::Base; // Inherit constructors

    // Common interface class for all the messages
    using Message =
        tutorial10::Message<
            comms::option::app::ReadIterator<const std::uint8_t*>, // Polymorphic read
            comms::option::app::WriteIterator<std::uint8_t*>, // Polymorphic write
            comms::option::app::LengthInfoInterface, // Polymorphic length calculation
            comms::option::app::IdInfoInterface, // Polymorphic message ID retrieval
            comms::option::app::NameInterface, // Polymorphic message name retrieval
            comms::option::app::Handler<ServerSession> // Polymorphic message dispatch
        >;

    // Protocol configuration options suitable for server
    using ServerOptions = tutorial10::options::ServerDefaultOptions;

    // Definition of messages
    using Msg1 = tutorial10::message::Msg1<Message, ServerOptions>;
    using Msg2 = tutorial10::message::Msg2<Message, ServerOptions>;
    using Msg3 = tutorial10::message::Msg3<Message, ServerOptions>;
    using Msg4 = tutorial10::message::Msg4<Message, ServerOptions>;
    using Msg5 = tutorial10::message::Msg5<Message, ServerOptions>;

    // Handlers for input messages
    void handle(Msg1& msg);
    void handle(Message& msg);

protected:
    virtual std::size_t processInputImpl(const std::uint8_t* buf, std::size_t bufLen) override final;

private:
    // Definition of the frame
    using Frame =
        tutorial10::frame::Frame<
            Message,
            tutorial10::input::ServerInputMessages<Message, ServerOptions>,
            ServerOptions
        >;

    void sendMessage(const Message& msg);

    Frame m_frame;
};

} // namespace cc_tutorial
