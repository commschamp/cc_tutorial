#pragma once

#include <vector>

#include "comms/GenericHandler.h"

#include "tutorial9/Message.h"
#include "tutorial9/frame/Frame.h"
#include "tutorial9/input/ClientInputMessages.h"

#include "Session.h"

namespace cc_tutorial
{

class ClientSession : public Session
{
    using Base = Session;
public:

    using Base::Base;

    // Common interface class for input messages
    using InMessage =
        tutorial9::Message<
            comms::option::app::ReadIterator<const std::uint8_t*>, // Polymorphic read
            comms::option::app::Handler<ClientSession> // Polymorphic message dispatch
        >;

    // Definition of all the used message classes
    using InMsg2 = tutorial9::message::Msg2<InMessage>;
    using InMsg4 = tutorial9::message::Msg4<InMessage>;

    void handle(InMsg2& msg);
    void handle(InMsg4& msg);
    void handle(InMessage& msg);

protected:
    virtual bool startImpl() override final;
    virtual std::size_t processInputImpl(const std::uint8_t* buf, std::size_t bufLen) override final;

private:
    // Common interface class for output messages
    using OutMessage =
        tutorial9::Message<
            comms::option::app::WriteIterator<std::back_insert_iterator<std::vector<std::uint8_t> > >, // Polymorphic write
            comms::option::app::LengthInfoInterface, // Polymorphic length calculation
            comms::option::app::IdInfoInterface, // Polymorphic message ID retrieval
            comms::option::app::NameInterface // Polymorphic message name retrieval
        >;

    // Declaration of output messages
    using OutMsg1 = tutorial9::message::Msg1<OutMessage>;
    using OutMsg3 = tutorial9::message::Msg3<OutMessage>;

    using Frame =
        tutorial9::frame::Frame<
            InMessage,
            tutorial9::input::ClientInputMessages<InMessage>
        >;

    enum CommsStage
    {
        CommsStage_Msg1,
        CommsStage_Msg3,
        CommsStage_NumOfValues
    };

    void sendMessage(const OutMessage& msg);
    void doNextStage();
    void sendMsg1();
    void sendMsg3();

    Frame m_frame;
    CommsStage m_currentStage = CommsStage_NumOfValues;
};

} // namespace cc_tutorial
