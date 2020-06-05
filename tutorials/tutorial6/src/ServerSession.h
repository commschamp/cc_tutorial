#pragma once

#include <iostream>

#include "tutorial6/Message.h"
#include "tutorial6/frame/Frame.h"

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
        tutorial6::Message<
            comms::option::app::ReadIterator<const std::uint8_t*>, // Polymorphic read
            comms::option::app::WriteIterator<std::uint8_t*>, // Polymorphic write
            comms::option::app::LengthInfoInterface, // Polymorphic length calculation
            comms::option::app::IdInfoInterface // Polymorphic message ID retrieval
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
    void sendMessage(Message& msg);

    using Frame = tutorial6::frame::Frame<Message>;

    Frame m_frame;
};

} // namespace cc_tutorial
