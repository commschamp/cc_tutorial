#pragma once

#include <iterator>
#include <vector>

#include "tutorial23/Message.h"
#include "tutorial23/frame/Frame.h"
#include "tutorial23/input/ClientInputMessages.h"
#include "t23_ext/options/ClientDefaultOptions.h"
#include "tutorial23/options/ClientDefaultOptions.h"
#include "tutorial23/options/DataViewDefaultOptions.h"

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
        tutorial23::Message<
            comms::option::app::ReadIterator<const std::uint8_t*>, // Polymorphic read
            comms::option::app::WriteIterator<std::back_insert_iterator<std::vector<std::uint8_t> > >, // Polymorphic write
            comms::option::app::LengthInfoInterface, // Polymorphic length calculation
            comms::option::app::IdInfoInterface, // Polymorphic message ID retrieval
            comms::option::app::NameInterface, // Polymorphic name retrieval
            comms::option::app::Handler<ClientSession>, // Polymorphic dispatch        
            comms::option::app::RefreshInterface // Polymorphic refresh        
        >;

    // Protocol options for client
    using ClientProtocolOptions = 
        tutorial23::options::ClientDefaultOptionsT<
            tutorial23::options::DefaultOptionsT<
                t23_ext::options::ClientDefaultOptions
            >
        >;
        
    // Definition of all the used message classes
    using Msg1 = tutorial23::message::Msg1<Message, ClientProtocolOptions>;
    
    // Handling functions for all the dispatched message objects
    void handle(Msg1& msg);
    void handle(Message& msg);

protected:
    virtual bool startImpl() override final;
    virtual std::size_t processInputImpl(const std::uint8_t* buf, std::size_t bufLen) override final;

private:
    enum CommsStage
    {
        CommsStage_Msg1,
        CommsStage_NumOfValues
    };

    void sendMessage(Message& msg);
    void doNextStage();
    void sendMsg1();

    // Client specific frame 
    using Frame = 
        tutorial23::frame::Frame<
            Message,
            tutorial23::input::ClientInputMessages<Message, ClientProtocolOptions>,
            ClientProtocolOptions
        >;

    Frame m_frame;
    CommsStage m_currentStage = CommsStage_NumOfValues;
};

} // namespace cc_tutorial
