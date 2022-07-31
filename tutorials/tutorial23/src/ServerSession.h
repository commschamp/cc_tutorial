#pragma once

#include "comms/GenericMessage.h"

#include "tutorial23/Message.h"
#include "tutorial23/frame/Frame.h"
#include "tutorial23/input/ServerInputMessages.h"
#include "t23_ext/options/ServerDefaultOptions.h"
#include "tutorial23/options/ServerDefaultOptions.h"
#include "t23_ext/options/DataViewDefaultOptions.h"
#include "tutorial23/options/DataViewDefaultOptions.h"
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
        tutorial23::Message<
            comms::option::app::ReadIterator<const std::uint8_t*>, // Polymorphic read
            comms::option::app::WriteIterator<std::uint8_t*>, // Polymorphic write
            comms::option::app::LengthInfoInterface, // Polymorphic length calculation
            comms::option::app::IdInfoInterface, // Polymorphic message ID retrieval
            comms::option::app::NameInterface, // Polymorphic name retrieval
            comms::option::app::Handler<ServerSession> // Polymorphic dispatch
        >;

    using ExtProtocolOptions = 
        t23_ext::options::DataViewDefaultOptionsT<
            t23_ext::options::ServerDefaultOptions
        >;

    using ServerProtocolOptions = 
        tutorial23::options::DataViewDefaultOptionsT<
            tutorial23::options::ServerDefaultOptionsT<
                tutorial23::options::DefaultOptionsT<
                    ExtProtocolOptions
                >   
            >
        >;


    void handle(Message& msg);

protected:
    virtual std::size_t processInputImpl(const std::uint8_t* buf, std::size_t bufLen) override final;

private:
    // Server specific frame 
    using Frame = 
        tutorial23::frame::Frame<
            Message,
            tutorial23::input::ServerInputMessages<Message, ServerProtocolOptions>,
            ServerProtocolOptions
        >;

    void sendMessage(const Message& msg);

    Frame m_frame;
};

} // namespace cc_tutorial
