#pragma once

#include "tutorial1/Message.h"
#include "tutorial1/frame/Frame.h"

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
        tutorial1::Message<
            comms::option::ReadIterator<const std::uint8_t*>, // Polymorphic read
            comms::option::WriteIterator<std::uint8_t*>, // Polymorphic write
            comms::option::LengthInfoInterface, // Polymorphic length calculation
            comms::option::IdInfoInterface, // Polymorphic message ID retrieval
            comms::option::NameInterface // Polymorphic message name retrieval
        >;
        
    // Verify presence of polymorphic functionality
    static_assert(Message::hasRead(), "Missing polymorphic read");
    static_assert(Message::hasWrite(), "Missing polymorphic write");
    static_assert(Message::hasLength(), "Missing polymorphic length");
    static_assert(Message::hasGetId(), "Missing polymorphic getId");
    static_assert(Message::hasName(), "Missing polymorphic name");
        
    // Verify that destructor is virtual
    static_assert(std::has_virtual_destructor<Message>::value, "Destructor is not virtual");

    // Handle all the received messages in a single function
    void handle(Message& msg);

protected:
    virtual std::size_t processInputImpl(const std::uint8_t* buf, std::size_t bufLen) override final;

private:

    using Frame = tutorial1::frame::Frame<Message>;

    Frame m_frame;
};

} // namespace cc_tutorial
