#pragma once

#include <iterator>
#include <vector>

#include "howto11/options/ClientDefaultOptions.h"
#include "howto11/options/DefaultOptions.h"
#include "howto11/options/DataViewDefaultOptions.h"
#include "howto11/prot/Message.h"
#include "howto11/prot/frame/Frame.h"
#include "howto11/prot/input/ClientInputMessages.h"
#include "howto11/var1/Interface.h"
#include "howto11/var1/frame/KeyValueProp.h"
#include "howto11/var1/input/ClientInputMessages.h"
#include "howto11/var2/Interface.h"
#include "howto11/var2/frame/TlvProp.h"
#include "howto11/var2/input/ClientInputMessages.h"


#include "Session.h"

namespace cc_tutorial
{

class ClientSession : public Session
{
    using Base = Session;
public:
    using Base::Base; // Inherit constructors

    // Common interface class for all the messages
    using ProtMessage =
        howto11::prot::Message<
            comms::option::app::ReadIterator<const std::uint8_t*>, // Polymorphic read
            comms::option::app::WriteIterator<std::back_insert_iterator<std::vector<std::uint8_t> > >, // Polymorphic write
            comms::option::app::LengthInfoInterface, // Polymorphic length calculation
            comms::option::app::IdInfoInterface, // Polymorphic message ID retrieval
            comms::option::app::NameInterface, // Polymorphic message name retrieval
            comms::option::app::Handler<ClientSession> // Polymorphic dispatch
        >;

    using ProtOpts = 
        howto11::options::DataViewDefaultOptionsT<
            howto11::options::ClientDefaultOptions
        >;

    // Definition of all the used message classes
    HOWTO11_PROT_ALIASES_FOR_ALL_MESSAGES(,,ProtMessage,ProtOpts)

    using Var1Interface = 
        howto11::var1::Interface<
            comms::option::app::ReadIterator<const std::uint8_t*>, // Polymorphic read
            comms::option::app::WriteIterator<std::back_insert_iterator<std::vector<std::uint8_t> > >, // Polymorphic write
            comms::option::app::LengthInfoInterface, // Polymorphic length calculation
            comms::option::app::IdInfoInterface, // Polymorphic message ID retrieval
            comms::option::app::NameInterface, // Polymorphic message name retrieval
            comms::option::app::Handler<ClientSession> // Polymorphic dispatch
        >;

    using Var2Interface = 
        howto11::var2::Interface<
            comms::option::app::ReadIterator<const std::uint8_t*>, // Polymorphic read
            comms::option::app::WriteIterator<std::back_insert_iterator<std::vector<std::uint8_t> > >, // Polymorphic write
            comms::option::app::LengthInfoInterface, // Polymorphic length calculation
            comms::option::app::IdInfoInterface, // Polymorphic message ID retrieval
            comms::option::app::NameInterface, // Polymorphic message name retrieval
            comms::option::app::Handler<ClientSession> // Polymorphic dispatch
        >;        

    using PropsOpts = howto11::options::DefaultOptions;

    using KeyValuePropFrame = howto11::var1::frame::KeyValueProp<Var1Interface, howto11::var1::input::ClientInputMessages<Var1Interface, PropsOpts>, PropsOpts>;
    using TlvPropFrame = howto11::var2::frame::TlvProp<Var2Interface, howto11::var2::input::ClientInputMessages<Var2Interface, PropsOpts>, PropsOpts>;

    // Definition of all the used properties classes
    HOWTO11_VAR1_ALIASES_FOR_ALL_MESSAGES(,,Var1Interface,PropsOpts)
    HOWTO11_VAR2_ALIASES_FOR_ALL_MESSAGES(,,Var2Interface,PropsOpts)

    // Handling functions for all the dispatched message objects
    void handle(Msg1& msg);
    void handle(Msg2& msg);
    void handle(ProtMessage& msg);

    // Handling functions for all the dispatched property objects
    void handle(Prop1& prop);
    void handle(Prop2& prop);
    void handle(Prop3& prop);
    void handle(Prop4& prop);
    void handle(Prop5& prop);
    void handle(Prop6& prop);
    void handle(Prop7& prop);
    void handle(Var1Interface& prop);
    void handle(Var2Interface& prop);

protected:
    virtual bool startImpl() override final;
    virtual std::size_t processInputImpl(const std::uint8_t* buf, std::size_t bufLen) override final;

private:
    enum CommsStage
    {
        CommsStage_Msg1,
        CommsStage_Msg2,
        CommsStage_NumOfValues
    };

    void sendMessage(const ProtMessage& msg);
    void doNextStage();
    void sendMsg1();
    void sendMsg2();

    using ProtFrame = howto11::prot::frame::Frame<ProtMessage, howto11::prot::input::ClientInputMessages<ProtMessage, ProtOpts>, ProtOpts>;

    ProtFrame m_frame;
    CommsStage m_currentStage = CommsStage_NumOfValues;
};

} // namespace cc_tutorial
