#pragma once

#include "comms/GenericMessage.h"

#include "tutorial26/Message.h"
#include "tutorial26/frame/Frame.h"
#include "tutorial26/input/ServerInputMessages.h"
#include "tutorial26/options/ServerDefaultOptions.h"
#include "tutorial26/options/ServerInputMessagesDynMemMsgFactoryDefaultOptions.h"
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
        tutorial26::Message<
            comms::option::app::ReadIterator<const std::uint8_t*>, // Polymorphic read
            comms::option::app::WriteIterator<std::uint8_t*>, // Polymorphic write
            comms::option::app::LengthInfoInterface, // Polymorphic length calculation
            comms::option::app::IdInfoInterface, // Polymorphic message ID retrieval
            comms::option::app::NameInterface, // Polymorphic name retrieval
            comms::option::app::Handler<ServerSession> // Polymorphic dispatch
        >;

    using ServerProtocolOptions = tutorial26::options::ServerDefaultOptions;

    // Definition of all the used message classes
    TUTORIAL26_ALIASES_FOR_ALL_MESSAGES(,,Message,ServerProtocolOptions);

    // Handle all the received messages
    void handle(Msg1& msg);
    void handle(Msg2& msg);
    void handle(Msg3& msg);
    void handle(Message& msg);

protected:
    virtual bool startImpl() override final;
    virtual std::size_t processInputImpl(const std::uint8_t* buf, std::size_t bufLen) override final;

private:
    // Server specific frame
    using Frame =
        tutorial26::frame::Frame<
            Message,
            tutorial26::input::ServerInputMessages<Message, ServerProtocolOptions>,
            ServerProtocolOptions
        >;

    void sendMessage(const Message& msg);

    Frame m_frame;
    Frame::MsgPtr m_msg;
};

} // namespace cc_tutorial
