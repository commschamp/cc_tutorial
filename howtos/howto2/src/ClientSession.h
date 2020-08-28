#pragma once

#include <iterator>
#include <vector>

#include "howto2/Message.h"
#include "howto2/frame/Frame.h"
#include "howto2/input/ClientInputMessages.h"
#include "howto2/options/ClientDefaultOptions.h"
#include "howto2/options/DataViewDefaultOptions.h"

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
        howto2::Message<
            comms::option::app::ReadIterator<const std::uint8_t*>, // Polymorphic read
            comms::option::app::WriteIterator<std::back_insert_iterator<std::vector<std::uint8_t> > >, // Polymorphic write
            comms::option::app::IdInfoInterface, // Polymorphic message ID retrieval
            comms::option::app::LengthInfoInterface, // Polymorphic length retrieval
            comms::option::app::NameInterface, // Polymorphic name retrieval
            comms::option::app::Handler<ClientSession> // Polymorphic dispatch        
        >;

    // Protocol options for client
    using ClientProtocolOptions = 
        howto2::options::DataViewDefaultOptionsT<
            howto2::options::ClientDefaultOptions
        >;
        
    // Definition of all the used message classes
    using Msg1 = howto2::message::Msg1<Message, ClientProtocolOptions>;
    using Msg2 = howto2::message::Msg2<Message, ClientProtocolOptions>;
    using Msg3 = howto2::message::Msg3<Message, ClientProtocolOptions>;
    using Msg4 = howto2::message::Msg4<Message, ClientProtocolOptions>;
    
    // Handling functions for all the dispatched message objects
    void handle(Msg1& msg);
    void handle(Msg2& msg);
    void handle(Msg3& msg);
    void handle(Msg4& msg);
    void handle(Message& msg);

protected:
    virtual bool startImpl() override final;
    virtual std::size_t processInputImpl(const std::uint8_t* buf, std::size_t bufLen) override final;

private:
    enum CommsStage
    {
        CommsStage_Msg1Msg2,
        CommsStage_Msg3Msg4,
        CommsStage_NumOfValues
    };

    using OutputBuf = std::vector<std::uint8_t>;

    void writeMessage(const Message& msg, OutputBuf& output) const;
    void sendRawData(const OutputBuf& output);
    void doNextStage();
    void sendMsg1Msg2();
    void sendMsg3Msg4();

    // Client specific frame 
    using Frame = 
        howto2::frame::Frame<
            Message,
            howto2::input::ClientInputMessages<Message, ClientProtocolOptions>,
            ClientProtocolOptions
        >;

    Frame m_frame;
    CommsStage m_currentStage = CommsStage_NumOfValues;
};

} // namespace cc_tutorial
