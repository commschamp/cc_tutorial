#pragma once

#include "comms/GenericMessage.h"

#include "tutorial15/Message.h"
#include "tutorial15/frame/Frame.h"
#include "tutorial15/input/ServerInputMessages.h"
#include "tutorial15/options/ServerDefaultOptions.h"
#include "tutorial15/options/DataViewDefaultOptions.h"

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
        tutorial15::Message<
            comms::option::app::ReadIterator<const std::uint8_t*>, // Polymorphic read
            comms::option::app::WriteIterator<std::uint8_t*>, // Polymorphic write
            comms::option::app::LengthInfoInterface, // Polymorphic length calculation
            comms::option::app::IdInfoInterface, // Polymorphic message ID retrieval
            comms::option::app::NameInterface, // Polymorphic name retrieval
            comms::option::app::Handler<ServerSession> // Polymorphic dispatch
        >;

    // Generic message
    using GenericMessage = 
        comms::GenericMessage<
            Message,
            comms::option::app::OrigDataView // Passed to raw data storage field
        >;

    using ServerProtocolOptionsBase = 
        tutorial15::options::DataViewDefaultOptionsT<
            tutorial15::options::ServerDefaultOptions
        >;

    // Protocol options for server
    class ServerProtocolOptions : public ServerProtocolOptionsBase
    {
        using Base = ServerProtocolOptionsBase;
    public:
        struct frame : public Base::frame
        {
            struct FrameLayers : public Base::frame::FrameLayers
            {
                // Extra options for tutorial15::frame::FrameLayers::Id layer.
                using Id = 
                    std::tuple<
                        comms::option::app::SupportGenericMessage<GenericMessage>,
                        Base::frame::FrameLayers::Id
                    >;
            }; // struct FrameLayers
        }; // struct Frame
    };

    // Definition of relevant messages
    using Msg1 = tutorial15::message::Msg1<Message, ServerProtocolOptions>;

    // Relevant input messages
    using InputMessages = 
        std::tuple<
            Msg1
        >;
        
    // Handle all the received messages
    void handle(Msg1& msg);
    void handle(GenericMessage& msg);
    void handle(Message& msg);

protected:
    virtual std::size_t processInputImpl(const std::uint8_t* buf, std::size_t bufLen) override final;

private:
    // Server specific frame 
    using Frame = 
        tutorial15::frame::Frame<
            Message,
            InputMessages,
            ServerProtocolOptions
        >;

    void sendMessage(const Message& msg);

    Frame m_frame;
};

} // namespace cc_tutorial
