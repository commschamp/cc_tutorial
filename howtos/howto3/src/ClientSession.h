#pragma once

#include <iterator>
#include <vector>

#include "howto3/options/DataViewDefaultOptions.h"
#include "howto3/options/ClientDefaultOptions.h"

#include "howto3/prot1/Prot1Interface.h"
#include "howto3/prot1/frame/Prot1Frame.h"
#include "howto3/prot1/input/ClientInputMessages.h"

#include "howto3/prot2/Prot2Interface.h"
#include "howto3/prot2/frame/Prot2Frame.h"
#include "howto3/prot2/input/ClientInputMessages.h"

#include "CommonSessionBase.h"
#include "Session.h"

namespace cc_tutorial
{

class ClientSession : public Session, public CommonSessionBase
{
    using Base = Session;
public:
    using Base::Base; // Inherit constructors

    // // Common interface classes for all the messages
    using Prot1Interface = 
        howto3::prot1::Prot1Interface<
            comms::option::app::ReadIterator<const std::uint8_t*>, // Polymorphic read
            comms::option::app::WriteIterator<std::back_insert_iterator<std::vector<std::uint8_t> > >, // Polymorphic write
            comms::option::app::IdInfoInterface, // Polymorphic message ID retrieval
            comms::option::app::LengthInfoInterface, // Polymorphic length retrieval
            comms::option::app::NameInterface, // Polymorphic name retrieval
            comms::option::app::Handler<ClientSession> // Polymorphic dispatch        
        >;    

    using Prot2Interface = 
        howto3::prot2::Prot2Interface<
            comms::option::app::ReadIterator<const std::uint8_t*>, // Polymorphic read
            comms::option::app::WriteIterator<std::back_insert_iterator<std::vector<std::uint8_t> > >, // Polymorphic write
            comms::option::app::IdInfoInterface, // Polymorphic message ID retrieval
            comms::option::app::LengthInfoInterface, // Polymorphic length retrieval
            comms::option::app::NameInterface, // Polymorphic name retrieval
            comms::option::app::Handler<ClientSession> // Polymorphic dispatch        
        >;

    // // Protocol options for client
    using ClientProtocolOptions = 
        howto3::options::DataViewDefaultOptionsT<
            howto3::options::ClientDefaultOptions
        >;

    // Definition of all the used message classes
    using Prot1PseudoMsg = howto3::prot1::message::Prot1PseudoMsg<Prot1Interface, ClientProtocolOptions>;

    using Prot2Msg1 = howto3::prot2::message::Msg1<Prot2Interface, ClientProtocolOptions>;
    using Prot2Msg2 = howto3::prot2::message::Msg2<Prot2Interface, ClientProtocolOptions>;
    using Prot2Msg3 = howto3::prot2::message::Msg3<Prot2Interface, ClientProtocolOptions>;
    
    // Handling functions for all the dispatched message objects
    void handle(Prot1PseudoMsg& msg);
    void handle(Prot1Interface& msg);
    void handle(Prot2Msg1& msg);
    void handle(Prot2Msg2& msg);
    void handle(Prot2Msg3& msg);
    void handle(Prot2Interface& msg);

protected:
    virtual bool startImpl() override final;
    virtual std::size_t processInputImpl(const std::uint8_t* buf, std::size_t bufLen) override final;

private:
    enum CommsStage
    {
        CommsStage_Msg1,
        CommsStage_Msg2Msg3,
        CommsStage_NumOfValues
    };


    void writeMessage(const Prot2Interface& msg, MsgBuf& output);
    void doNextStage();
    void sendMsg1();
    void sendMsg2Msg3();

    // Client specific frames
    using Prot1Frame = 
        howto3::prot1::frame::Prot1Frame<
            Prot1Interface,
            howto3::prot1::input::ClientInputMessages<Prot1Interface, ClientProtocolOptions>,
            ClientProtocolOptions
        >;

    using Prot2Frame = 
        howto3::prot2::frame::Prot2Frame<
            Prot2Interface,
            howto3::prot2::input::ClientInputMessages<Prot2Interface, ClientProtocolOptions>,
            ClientProtocolOptions
        >;

    Prot1Frame m_prot1Frame;
    Prot2Frame m_prot2Frame;
    CommsStage m_currentStage = CommsStage_NumOfValues;
};

} // namespace cc_tutorial
