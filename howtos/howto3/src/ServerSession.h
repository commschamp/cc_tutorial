#pragma once

#include "howto3/options/DataViewDefaultOptions.h"
#include "howto3/options/ServerDefaultOptions.h"

#include "howto3/prot1/Prot1Interface.h"
#include "howto3/prot1/frame/Prot1Frame.h"
#include "howto3/prot1/input/ServerInputMessages.h"

#include "howto3/prot2/Prot2Interface.h"
#include "howto3/prot2/frame/Prot2Frame.h"
#include "howto3/prot2/input/ServerInputMessages.h"

#include "Session.h"
#include "CommonSessionBase.h"

namespace cc_tutorial
{

class ServerSession : public Session, public CommonSessionBase
{
    using Base = Session;
public:
    using Base::Base; // Inherit constructors

    // Common interface class for all the messages
    using Prot1Interface = 
        howto3::prot1::Prot1Interface<
            comms::option::app::ReadIterator<const std::uint8_t*>, // Polymorphic read
            comms::option::app::WriteIterator<std::uint8_t*>, // Polymorphic write
            comms::option::app::IdInfoInterface, // Polymorphic message ID retrieval
            comms::option::app::LengthInfoInterface, // Polymorphic length retrieval
            comms::option::app::NameInterface, // Polymorphic name retrieval
            comms::option::app::Handler<ServerSession> // Polymorphic dispatch        
        >;    

    using Prot2Interface = 
        howto3::prot2::Prot2Interface<
            comms::option::app::ReadIterator<const std::uint8_t*>, // Polymorphic read
            comms::option::app::WriteIterator<std::uint8_t*>, // Polymorphic write
            comms::option::app::IdInfoInterface, // Polymorphic message ID retrieval
            comms::option::app::LengthInfoInterface, // Polymorphic length retrieval
            comms::option::app::NameInterface, // Polymorphic name retrieval
            comms::option::app::Handler<ServerSession> // Polymorphic dispatch        
        >;

    using ServerProtocolOptions = 
        howto3::options::DataViewDefaultOptionsT<
            howto3::options::ServerDefaultOptions
        >;

    using Prot1PseudoMsg = howto3::prot1::message::Prot1PseudoMsg<Prot1Interface, ServerProtocolOptions>;        

    // Handle all the received messages
    void handle(Prot1PseudoMsg& msg);
    void handle(Prot1Interface& msg);    
    void handle(Prot2Interface& msg);

protected:
    virtual std::size_t processInputImpl(const std::uint8_t* buf, std::size_t bufLen) override final;

private:
    // Server specific frames
    using Prot1Frame = 
        howto3::prot1::frame::Prot1Frame<
            Prot1Interface,
            howto3::prot1::input::ServerInputMessages<Prot1Interface, ServerProtocolOptions>,
            ServerProtocolOptions
        >;

    using Prot2Frame = 
        howto3::prot2::frame::Prot2Frame<
            Prot2Interface,
            howto3::prot2::input::ServerInputMessages<Prot2Interface, ServerProtocolOptions>,
            ServerProtocolOptions
        >;

    void sendMessage(const Prot2Interface& msg);

    Prot1Frame m_prot1Frame;
    Prot2Frame m_prot2Frame;
};

} // namespace cc_tutorial
