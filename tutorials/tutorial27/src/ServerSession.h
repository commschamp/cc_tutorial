#pragma once

#include <iterator>
#include <vector>

#include "comms/GenericMessage.h"

#include "tutorial27/Message.h"
#include "tutorial27/options/ServerDefaultOptions.h"
#include "tutorial27/options/ServerInputMessagesDynMemMsgFactoryDefaultOptions.h"
#include "tutorial27/sub1/frame/Frame.h"
#include "tutorial27/sub1/input/ServerInputMessages.h"
#include "tutorial27/sub2/frame/Frame.h"
#include "tutorial27/sub2/input/ServerInputMessages.h"

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
        tutorial27::Message<
            comms::option::app::ReadIterator<const std::uint8_t*>, // Polymorphic read
            comms::option::app::WriteIterator<std::back_insert_iterator<std::vector<std::uint8_t> > >, // Polymorphic write
            comms::option::app::LengthInfoInterface, // Polymorphic length calculation
            comms::option::app::IdInfoInterface, // Polymorphic message ID retrieval
            comms::option::app::NameInterface, // Polymorphic name retrieval
            comms::option::app::Handler<ServerSession> // Polymorphic dispatch
        >;

    using ServerProtocolOptions = tutorial27::options::ServerDefaultOptions;

    // Definition of all the used message classes
    TUTORIAL27_SUB1_ALIASES_FOR_ALL_MESSAGES(,,Message,ServerProtocolOptions);
    TUTORIAL27_SUB2_ALIASES_FOR_ALL_MESSAGES(,,Message,ServerProtocolOptions);

    // Handle all the received messages
    void handle(Msg1& msg);
    void handle(Msg2& msg);
    void handle(Msg3& msg);
    void handle(Msg4& msg);
    void handle(Msg5& msg);
    void handle(Msg6& msg);
    void handle(Message& msg);

protected:
    virtual bool startImpl() override final;
    virtual std::size_t processInputImpl(const std::uint8_t* buf, std::size_t bufLen) override final;

private:
    enum ProtStage
    {
        ProtStage_sub1,
        ProtStage_sub2,
        ProtStage_numOfValues
    };

    // Server specific frames
    using Sub1Frame =
        tutorial27::sub1::frame::Frame<
            Message,
            tutorial27::sub1::input::ServerInputMessages<Message, ServerProtocolOptions>,
            ServerProtocolOptions
        >;
    using Sub2Frame =
        tutorial27::sub2::frame::Frame<
            Message,
            tutorial27::sub2::input::ServerInputMessages<Message, ServerProtocolOptions>,
            ServerProtocolOptions
        >;

    using WriteIter = std::back_insert_iterator<std::vector<std::uint8_t> >;

    void sendMessage(const Message& msg);
    std::size_t processInputSub1(const std::uint8_t* buf, std::size_t bufLen);
    std::size_t processInputSub2(const std::uint8_t* buf, std::size_t bufLen);
    comms::ErrorStatus writeMessageSub1(const Message& msg, WriteIter& iter, std::size_t bufLen);
    comms::ErrorStatus writeMessageSub2(const Message& msg, WriteIter& iter, std::size_t bufLen);

    Sub1Frame m_sub1Frame;
    Sub1Frame::MsgPtr m_sub1Msg;
    Sub2Frame m_sub2Frame;
    ProtStage m_protStage = ProtStage_sub1;
};

} // namespace cc_tutorial
