#pragma once

#include "tutorial5/Message.h"
#include "tutorial5/frame/ServerToClientFrame.h"
#include "tutorial5/frame/ClientToServerFrame.h"

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
        tutorial5::Message<
            comms::option::app::ReadIterator<const std::uint8_t*>, // Polymorphic read
            comms::option::app::WriteIterator<std::uint8_t*>, // Polymorphic write
            comms::option::app::LengthInfoInterface, // Polymorphic length calculation
            comms::option::app::IdInfoInterface, // Polymorphic message ID retrieval
            comms::option::app::NameInterface // Polymorphic message name retrieval
        >;
        
    // Handle all the received messages in a single function
    void handle(Message& msg);

protected:
    virtual std::size_t processInputImpl(const std::uint8_t* buf, std::size_t bufLen) override final;

private:

    using ServerToClientFrame = tutorial5::frame::ServerToClientFrame<Message>;
    using ClientToServerFrame = tutorial5::frame::ClientToServerFrame<Message>;

    ServerToClientFrame m_serverToClientFrame;
    ClientToServerFrame m_clientToServerFrame;
};

} // namespace cc_tutorial
