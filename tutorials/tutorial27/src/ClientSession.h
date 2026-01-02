#pragma once

#include <iterator>
#include <iostream>
#include <vector>

#include "tutorial27/Message.h"
#include "tutorial27/options/ClientInputMessagesDynMemMsgFactoryDefaultOptions.h"
#include "tutorial27/options/ClientDefaultOptions.h"
#include "tutorial27/sub1/frame/Frame.h"
#include "tutorial27/sub1/input/ClientInputMessages.h"
#include "tutorial27/sub2/frame/Frame.h"
#include "tutorial27/sub2/input/ClientInputMessages.h"

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
        tutorial27::Message<
            comms::option::app::ReadIterator<const std::uint8_t*>, // Polymorphic read
            comms::option::app::WriteIterator<std::back_insert_iterator<std::vector<std::uint8_t> > >, // Polymorphic write
            comms::option::app::LengthInfoInterface, // Polymorphic length calculation
            comms::option::app::IdInfoInterface, // Polymorphic message ID retrieval
            comms::option::app::NameInterface, // Polymorphic name retrieval
            comms::option::app::Handler<ClientSession> // Polymorphic dispatch
        >;

    // Protocol options for client
    using ClientProtocolOptions = tutorial27::options::ClientDefaultOptions;

    // Definition of all the used message classes
    TUTORIAL27_SUB1_ALIASES_FOR_ALL_MESSAGES(,,Message,ClientProtocolOptions);
    TUTORIAL27_SUB2_ALIASES_FOR_ALL_MESSAGES(,,Message,ClientProtocolOptions);

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
        CommsStage_Msg4,
        CommsStage_Msg5,
        CommsStage_Msg6,
        CommsStage_NumOfValues
    };

    using WriteIter = std::back_insert_iterator<std::vector<std::uint8_t> >;

    std::size_t processInputSub1(const std::uint8_t* buf, std::size_t bufLen);
    std::size_t processInputSub2(const std::uint8_t* buf, std::size_t bufLen);
    void sendMessage(const Message& msg);
    comms::ErrorStatus writeMessageSub1(const Message& msg, WriteIter& iter, std::size_t bufLen);
    comms::ErrorStatus writeMessageSub2(const Message& msg, WriteIter& iter, std::size_t bufLen);
    void doNextStage();
    void sendMsg1();
    void sendMsg2();
    void sendMsg3();
    void sendMsg4();
    void sendMsg5();
    void sendMsg6();

    // Client specific frame
    using Sub1Frame =
        tutorial27::sub1::frame::Frame<
            Message,
            tutorial27::sub1::input::ClientInputMessages<Message, ClientProtocolOptions>,
            ClientProtocolOptions
        >;
    using Sub2Frame =
        tutorial27::sub2::frame::Frame<
            Message,
            tutorial27::sub2::input::ClientInputMessages<Message, ClientProtocolOptions>,
            ClientProtocolOptions
        >;

    Sub1Frame m_sub1Frame;
    Sub1Frame::MsgPtr m_sub1Msg;
    Sub2Frame m_sub2Frame;
    CommsStage m_currentStage = CommsStage_NumOfValues;
};

} // namespace cc_tutorial
