#pragma once

#include <iterator>
#include <vector>

#include "tutorial12/Message.h"
#include "tutorial12/frame/Frame.h"
#include "tutorial12/input/ClientInputMessages.h"
#include "tutorial12/options/ClientDefaultOptions.h"

#include "Session.h"
#include "DataViewBareMetalProtocolOptions.h"

namespace cc_tutorial
{

class ClientSession : public Session
{
    using Base = Session;
public:
    using Base::Base; // Inherit constructors

    // Common interface class for all the messages
    using Message = tutorial12::Message<>;

    // Protocol options for client
    using ClientProtocolOptions = 
        DataViewBareMetalProtocolOptionsT<
            tutorial12::options::DataViewDefaultOptionsT<
                tutorial12::options::ClientDefaultOptions
            >
        >;        
        
    // Definition of all the used message classes
    using Msg1 = tutorial12::message::Msg1<Message, ClientProtocolOptions>;
    using Msg2 = tutorial12::message::Msg2<Message, ClientProtocolOptions>;
    using Msg3 = tutorial12::message::Msg3<Message, ClientProtocolOptions>;

    // Handling functions for all the dispatched message objects
    void handle(Msg1& msg);
    void handle(Msg2& msg);
    void handle(Msg3& msg);
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

    // Send the message requires knowledge about the full message type
    template <typename TMsg>
    void sendMessage(const TMsg& msg)
    {
        std::cout << "Sending message \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << std::endl;        

        // The statement below uses polymorphic message name and ID retrievals.
        std::vector<std::uint8_t> output;

        // Use polymorphic serialization length calculation to reserve
        // needed capacity
        output.reserve(m_frame.length(msg));

        // Serialize message into the buffer (including framing)
        // The serialization uses polymorphic write functionality.
        auto writeIter = std::back_inserter(output);

        // The frame will use polymorphic message ID retrieval to
        // prefix message payload with message ID
        auto es = m_frame.write(msg, writeIter, output.max_size());
        if (es != comms::ErrorStatus::Success) {
            assert(!"Write operation failed unexpectedly");
            return;
        }

        // Send serialized message back
        sendOutput(&output[0], output.size());
    }

    void doNextStage();
    void sendMsg1();
    void sendMsg2();
    void sendMsg3();

    // Client specific frame 
    using Frame = 
        tutorial12::frame::Frame<
            Message,
            tutorial12::input::ClientInputMessages<Message, ClientProtocolOptions>,
            ClientProtocolOptions
        >;

    Frame m_frame;
    CommsStage m_currentStage = CommsStage_NumOfValues;
};

} // namespace cc_tutorial
