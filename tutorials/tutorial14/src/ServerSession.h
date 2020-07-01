#pragma once

#include "tutorial14/Message.h"
#include "tutorial14/frame/Frame.h"
#include "tutorial14/input/ServerInputMessages.h"
#include "tutorial14/options/ServerDefaultOptions.h"

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
        tutorial14::Message<
            comms::option::app::ReadIterator<const std::uint8_t*>, // Polymorphic read
            comms::option::app::WriteIterator<std::uint8_t*>, // Polymorphic write
            comms::option::app::LengthInfoInterface, // Polymorphic length calculation
            comms::option::app::IdInfoInterface, // Polymorphic message ID retrieval
            comms::option::app::NameInterface, // Polymorphic name retrieval
            comms::option::app::Handler<ServerSession> // Polymorphic dispatch
        >;

    // Protocol options for server
    using ServerProtocolOptions = tutorial14::options::ServerDefaultOptions;
        
    // Handle all the received messages in a single function
    void handle(Message& msg);

protected:
    virtual std::size_t processInputImpl(const std::uint8_t* buf, std::size_t bufLen) override final;

private:
    // Server specific frame 
    using Frame = 
        tutorial14::frame::Frame<
            Message,
            tutorial14::input::ServerInputMessages<Message, ServerProtocolOptions>,
            ServerProtocolOptions
        >;

    Frame m_frame;
};

} // namespace cc_tutorial
