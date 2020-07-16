#pragma once

#include <iostream>

#include "tutorial18/Message.h"
#include "tutorial18/frame/Frame.h"
#include "tutorial18/input/ServerInputMessages.h"
#include "tutorial18/options/ServerDefaultOptions.h"
#include "tutorial18/options/DataViewDefaultOptions.h"

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
        tutorial18::Message<
            comms::option::app::ReadIterator<const std::uint8_t*>, // Polymorphic read
            comms::option::app::WriteIterator<std::uint8_t*>, // Polymorphic write
            comms::option::app::LengthInfoInterface, // Polymorphic length calculation
            comms::option::app::IdInfoInterface, // Polymorphic message ID retrieval
            comms::option::app::NameInterface // Polymorphic name retrieval
        >;

    // Protocol options for server
    using ServerProtocolOptions = 
        tutorial18::options::DataViewDefaultOptionsT<
            tutorial18::options::ServerDefaultOptions
        >;
        
    // Handle all the received messages in a single function
    template <typename TMsg>
    void handle(TMsg& msg)
    {
        // The statement below uses non-polymorphic message name and ID retrievals.
        std::cout << "Received message \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << std::endl;
        sendMessage(msg);
    }

    void handle(Message& msg);

protected:
    virtual std::size_t processInputImpl(const std::uint8_t* buf, std::size_t bufLen) override final;

private:
    // Server input messages
    using ServerInputMessages = 
        tutorial18::input::ServerInputMessages<Message, ServerProtocolOptions>;

    // Server specific frame 
    using Frame = 
        tutorial18::frame::Frame<
            Message,
            ServerInputMessages,
            ServerProtocolOptions
        >;

    void sendMessage(const Message& msg);

    Frame m_frame;
};

} // namespace cc_tutorial
