#pragma once

#include <iterator>
#include <iostream>
#include <vector>

#include "tutorial26/Message.h"
#include "tutorial26/frame/Frame.h"
#include "tutorial26/input/ClientInputMessages.h"
#include "tutorial26/options/ClientInputMessagesDynMemMsgFactoryDefaultOptions.h"
#include "tutorial26/options/ClientDefaultOptions.h"

#include "Session.h"

namespace cc_tutorial
{

class ClientSession : public Session
{
    using Base = Session;
public:
    using Base::Base; // Inherit constructors

    // Common interface class for all the messages
    using Message =
        tutorial26::Message<
            comms::option::app::ReadIterator<const std::uint8_t*>, // Polymorphic read
            comms::option::app::WriteIterator<std::back_insert_iterator<std::vector<std::uint8_t> > >, // Polymorphic write
            comms::option::app::LengthInfoInterface, // Polymorphic length calculation
            comms::option::app::IdInfoInterface, // Polymorphic message ID retrieval
            comms::option::app::NameInterface, // Polymorphic name retrieval
            comms::option::app::Handler<ClientSession> // Polymorphic dispatch
        >;

    // Protocol options for client
    using ClientProtocolOptions = tutorial26::options::ClientDefaultOptions;

    // Definition of all the used message classes
    TUTORIAL26_ALIASES_FOR_ALL_MESSAGES(,,Message,ClientProtocolOptions);

    // Handling functions for all the dispatched message objects
    template <typename TMsg>
    void handle(TMsg& msg)
    {
        std::cout << "Received message \"" << msg.doName() << "\"" << std::endl;
        doNextStage();
    }

    void handle(Message& msg);

protected:
    virtual bool startImpl() override final;
    virtual std::size_t processInputImpl(const std::uint8_t* buf, std::size_t bufLen) override final;

private:
    enum CommsStage
    {
        CommsStage_Msg1,
        CommsStage_Msg2,
        CommsStage_Msg3,
        CommsStage_NumOfValues
    };

    void sendMessage(const Message& msg);
    void doNextStage();
    void sendMsg1();
    void sendMsg2();
    void sendMsg3();

    // Client specific frame
    using Frame =
        tutorial26::frame::Frame<
            Message,
            tutorial26::input::ClientInputMessages<Message, ClientProtocolOptions>,
            ClientProtocolOptions
        >;

    Frame m_frame;
    Frame::MsgPtr m_msg;
    CommsStage m_currentStage = CommsStage_NumOfValues;
};

} // namespace cc_tutorial
