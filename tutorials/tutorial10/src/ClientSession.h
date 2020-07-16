#pragma once

#include <vector>

#include "comms/GenericHandler.h"

#include "tutorial10/Message.h"
#include "tutorial10/frame/Frame.h"
#include "tutorial10/input/ClientInputMessages.h"
#include "tutorial10/options/ClientDefaultOptions.h"

#include "Session.h"

namespace cc_tutorial
{

class ClientSession : public Session
{
    using Base = Session;
public:

    using Base::Base;

    // Common interface class for input messages
    using Message =
        tutorial10::Message<
            comms::option::app::ReadIterator<const std::uint8_t*>, // Polymorphic read
            comms::option::app::WriteIterator<std::back_insert_iterator<std::vector<std::uint8_t> > >, // Polymorphic write
            comms::option::app::LengthInfoInterface, // Polymorphic length calculation
            comms::option::app::IdInfoInterface, // Polymorphic message ID retrieval
            comms::option::app::NameInterface, // Polymorphic message name retrieval
            comms::option::app::Handler<ClientSession> // Polymorphic message dispatch
        >;

    // Protocol configuration options suitable for client
    using ClientOptions = tutorial10::options::ClientDefaultOptions;

    // Definition of messages
    using Msg1 = tutorial10::message::Msg1<Message, ClientOptions>;
    using Msg2 = tutorial10::message::Msg2<Message, ClientOptions>;
    using Msg3 = tutorial10::message::Msg3<Message, ClientOptions>;
    using Msg4 = tutorial10::message::Msg4<Message, ClientOptions>;
    using Msg5 = tutorial10::message::Msg5<Message, ClientOptions>;

    void handle(Msg2& msg);
    void handle(Msg3& msg);
    void handle(Msg4& msg);
    void handle(Msg5& msg);
    void handle(Message& msg);

protected:
    virtual bool startImpl() override final;
    virtual std::size_t processInputImpl(const std::uint8_t* buf, std::size_t bufLen) override final;

private:
    using Frame =
        tutorial10::frame::Frame<
            Message,
            tutorial10::input::ClientInputMessages<Message, ClientOptions>,
            ClientOptions
        >;

    enum CommsStage
    {
        CommsStage_Msg1,
        CommsStage_Msg3,
        CommsStage_Msg4,
        CommsStage_Msg5,
        CommsStage_NumOfValues
    };

    void sendMessage(const Message& msg);
    void doNextStage();
    void sendMsg1();
    void sendMsg3();
    void sendMsg4();
    void sendMsg5();

    Frame m_frame;
    CommsStage m_currentStage = CommsStage_NumOfValues;
};

} // namespace cc_tutorial
