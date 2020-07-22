#pragma once

#include "comms/GenericMessage.h"

#include "tutorial20/Interface.h"
#include "tutorial20/frame/Frame.h"
#include "tutorial20/input/ServerInputMessages.h"
#include "tutorial20/options/ServerDefaultOptions.h"
#include "tutorial20/options/DataViewDefaultOptions.h"
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
        tutorial20::Interface<
            comms::option::app::ReadIterator<const std::uint8_t*>, // Polymorphic read
            comms::option::app::WriteIterator<std::uint8_t*>, // Polymorphic write
            comms::option::app::LengthInfoInterface, // Polymorphic length calculation
            comms::option::app::IdInfoInterface, // Polymorphic message ID retrieval
            comms::option::app::NameInterface, // Polymorphic name retrieval
            comms::option::app::Handler<ServerSession> // Polymorphic dispatch
        >;

    using ServerProtocolOptions = 
        tutorial20::options::DataViewDefaultOptionsT<
            tutorial20::options::ServerDefaultOptions
        >;

    using ConnectMsg = tutorial20::message::Connect<Message, ServerProtocolOptions>;

    // Handle the Connect message
    void handle(ConnectMsg& msg);

    // Handle all the other received messages
    template <typename TMsg>
    void handle(TMsg& msg)
    {
        std::cout << "Received message \"" << msg.doName() << 
            "\" with ID=" << (unsigned)msg.getId() << 
            " and version=" << (unsigned)msg.version() << std::endl;
        sendMessage(msg);
    }

    void handle(Message& msg);

protected:
    virtual std::size_t processInputImpl(const std::uint8_t* buf, std::size_t bufLen) override final;

private:
    // Server specific frame 
    using Frame = 
        tutorial20::frame::Frame<
            Message,
            tutorial20::input::ServerInputMessages<Message, ServerProtocolOptions>,
            ServerProtocolOptions
        >;

    void sendMessage(const Message& msg);

    Frame m_frame;
};

} // namespace cc_tutorial
