#pragma once

#include <iostream>

#include "tutorial11/Message.h"
#include "tutorial11/frame/Frame.h"
#include "tutorial11/input/ServerInputMessages.h"
#include "tutorial11/options/ServerDefaultOptions.h"

#include "Session.h"
#include "ProtocolOptions.h"

namespace cc_tutorial
{

class ServerSession : public Session
{
    using Base = Session;
public:
    using Base::Base; // Inherit constructors

    // Common interface class for all the messages
    using Message =
        tutorial11::Message<>;

    // Protocol options for server
    using ServerProtocolOptions = 
        ProtocolOptionsT<
            tutorial11::options::ServerDefaultOptions
        >;
        
    // Handle all the received messages in a common generic fuctnion
    template <typename TMsg>
    void handle(TMsg& msg)
    {
        std::cout << "Received message \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << std::endl;
        sendMessage(msg);
    }

    void handle(Message& msg);

protected:
    virtual std::size_t processInputImpl(const std::uint8_t* buf, std::size_t bufLen) override final;

private:
    template <typename TMsg>
    void sendMessage(TMsg& msg)
    {
        std::vector<std::uint8_t> output;

        // Use polymorphic serialization length calculation to create
        // buffer of the requires size
        output.resize(m_frame.length(msg));

        // Serialize message into the buffer (including framing)
        // The serialization uses polymorphic write functionality.
        auto writeIter = &output[0];
        auto es = m_frame.write(msg, writeIter, output.size());
        if (es != comms::ErrorStatus::Success) {
            assert(!"Write operation failed unexpectedly");
            return;
        }

        // writeIter has been advanced, check that it reached end of the allocated buffer.
        assert(output.size() == static_cast<std::size_t>(std::distance(&output[0], writeIter)));

        // Send (re)serialized message back
        sendOutput(&output[0], output.size());        
    }

    using Frame = 
        tutorial11::frame::Frame<
            Message,
            tutorial11::input::ServerInputMessages<Message, ServerProtocolOptions>,
            ServerProtocolOptions
        >;

    Frame m_frame;
};

} // namespace cc_tutorial
