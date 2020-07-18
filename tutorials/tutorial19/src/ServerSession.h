#pragma once

#include "comms/GenericMessage.h"

#include "tutorial19/Interface.h"
#include "tutorial19/frame/Frame.h"
#include "tutorial19/input/ServerInputMessages.h"
#include "tutorial19/options/ServerDefaultOptions.h"
#include "tutorial19/options/DataViewDefaultOptions.h"
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
        tutorial19::Interface<
            comms::option::app::ReadIterator<const std::uint8_t*>, // Polymorphic read
            comms::option::app::WriteIterator<std::uint8_t*>, // Polymorphic write
            comms::option::app::LengthInfoInterface, // Polymorphic length calculation
            comms::option::app::IdInfoInterface, // Polymorphic message ID retrieval
            comms::option::app::NameInterface, // Polymorphic name retrieval
            comms::option::app::Handler<ServerSession> // Polymorphic dispatch
        >;

    using ServerProtocolOptions = 
        tutorial19::options::DataViewDefaultOptionsT<
            tutorial19::options::ServerDefaultOptions
        >;

    // Handle all the received messages
    void handle(Message& msg);

protected:
    virtual std::size_t processInputImpl(const std::uint8_t* buf, std::size_t bufLen) override final;

private:
    // Server specific frame 
    using Frame = 
        tutorial19::frame::Frame<
            Message,
            tutorial19::input::ServerInputMessages<Message, ServerProtocolOptions>,
            ServerProtocolOptions
        >;

    void sendMessage(const Message& msg);

    Frame m_frame;
};

} // namespace cc_tutorial
