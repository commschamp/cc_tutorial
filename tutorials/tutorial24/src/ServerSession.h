#pragma once

#include "comms/GenericMessage.h"

#include "tutorial24/Message.h"
#include "tutorial24/frame/Frame.h"
#include "tutorial24/input/ServerInputMessages.h"
#include "tutorial24/options/ServerDefaultOptions.h"
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
        tutorial24::Message<
            comms::option::app::ReadIterator<const std::uint8_t*>, // Polymorphic read
            comms::option::app::WriteIterator<std::uint8_t*>, // Polymorphic write
            comms::option::app::LengthInfoInterface, // Polymorphic length calculation
            comms::option::app::IdInfoInterface, // Polymorphic message ID retrieval
            comms::option::app::NameInterface, // Polymorphic name retrieval
            comms::option::app::Handler<ServerSession> // Polymorphic dispatch
        >;

    using ServerProtocolOptions = tutorial24::options::ServerDefaultOptions;

    // Handle all the received messages
    void handle(Message& msg);

protected:
    virtual std::size_t processInputImpl(const std::uint8_t* buf, std::size_t bufLen) override final;

private:
    // Server specific frame 
    using Frame = 
        tutorial24::frame::Frame<
            Message,
            tutorial24::input::ServerInputMessages<Message, ServerProtocolOptions>,
            ServerProtocolOptions
        >;

    void sendMessage(const Message& msg);

    Frame m_frame;
};

} // namespace cc_tutorial
