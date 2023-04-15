# Tutorial 15
Avoiding unnecessary decoding of messages.

In all the previous tutorials both **client** and **server** decoded all the **input** messages
even if such messages were discarded as irrelevant. The decoding process involves reading of
the message payload. Now imagine the situation where the application being developed is 
some kind of filter / proxy which is required to monitor / change / drop only limited set 
of messages and let all the rest (majority) of the messages through. It is not uncommon for 
such application to change the framing as well when the message is forwarded on different I/O link.
In such case the decoding of all the irrelevant messages seems like a waste of CPU cycles and
maybe even memory.

To help with such cases the [COMMS Library](https://github.com/commschamp/comms)
introduced [comms::GenericMessage](https://commschamp.github.io/comms_doc/classcomms_1_1GenericMessage.html).
It extends [comms::MessageBase](https://commschamp.github.io/comms_doc/classcomms_1_1MessageBase.html)
like any regular message definition and has a single member field (payload) which is 
[comms::field::ArrayList](https://commschamp.github.io/comms_doc/classcomms_1_1field_1_1ArrayList.html)
of raw data `std::uint8_t` (equivalent to basic `<data>` field without any prefixes).
However, it doesn't specify any numeric message ID, i.e. its ID information is available at run-time,
not compile-time like any other.

In order to show how to use such message the **server** of this tutorial is implemented to 
recognize and **drop** `Msg1` while echo back all other messages.

The [src/ServerSession.h](src/ServerSession.h) has the following definition(s):
```cpp
// Common interface class for all the messages
using Message = 
    tutorial15::Message<
        ...
    >;

// Generic message
using GenericMessage = 
    comms::GenericMessage<
        Message,
        comms::option::app::OrigDataView // Passed to raw data storage field
    >;
```
The second template parameter of the [comms::GenericMessage](https://commschamp.github.io/comms_doc/classcomms_1_1GenericMessage.html)
is options passed to its [comms::field::ArrayList](https://commschamp.github.io/comms_doc/classcomms_1_1field_1_1ArrayList.html)
member field. Passing of the `comms::option::app::OrigDataView` option allows avoiding data copying from the
input buffer to the the inner storage of the [comms::field::ArrayList](https://commschamp.github.io/comms_doc/classcomms_1_1field_1_1ArrayList.html).
Just to remind the reader that the storage type will be [comms::util::ArrayView](https://commschamp.github.io/comms_doc/classcomms_1_1util_1_1ArrayView.html)
or [std::span](https://en.cppreference.com/w/cpp/container/span) depending on the C++ standard been used during the compilation.
Note that the `comms::option::app::OrigDataView` option cannot be used if the input buffer is not sequential, i.e.
some kind of circular buffer.

The **input** messages to recognize tuple contains only single `Msg1`:
```cpp
// Definition of relevant messages
using Msg1 = tutorial15::message::Msg1<Message, ServerProtocolOptions>;

// Relevant input messages
using InputMessages = 
    std::tuple<
        Msg1
    >;
```
If the configuration is left like this, then all other messages won't even be recognized and will be dropped by the 
framing management. In order to force creation of `GenericMessage` for all other unknown messages, the `Id` framing layer
needs to receive [comms::option::app::SupportGenericMessage](https://commschamp.github.io/comms_doc/options_8h.html)
option.

----

**SIDE NOTE**: As was already explained in one of the previous tutorials, it's actually 
[comms::MsgFactory](https://commschamp.github.io/comms_doc/classcomms_1_1MsgFactory.html)
class that is responsible to create message objects. It is used by the 
[comms::protocol::MsgIdLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1MsgIdLayer.html). 
All the options passed to the later are forwarded to the former. As the result if 
the tuple of **input** messages doesn't contain any class with specified message ID, then the specified `GenericMessage` is 
created and returned instead.

----

Hence, the protocol options for the **server** application are defined to be:
```cpp
using ServerProtocolOptionsBase = 
    tutorial15::options::DataViewDefaultOptionsT<
        tutorial15::options::ServerDefaultOptions
    >;

// Protocol options for server
class ServerProtocolOptions : public ServerProtocolOptionsBase
{
    using Base = ServerProtocolOptionsBase;
public:
    struct frame : public Base::frame
    {
        struct FrameLayers : public Base::frame::FrameLayers
        {
            // Extra options for tutorial15::frame::FrameLayers::Id layer.
            using Id = 
                std::tuple<
                    comms::option::app::SupportGenericMessage<GenericMessage>,
                    Base::frame::FrameLayers::Id
                >;
        }; // struct FrameLayers
    }; // struct Frame
};
```
The handling of the incoming messages the [ServerSession](src/ServerSession.cpp) implements in 
the following way:
```cpp
void ServerSession::handle(Msg1& msg)
{
    std::cout << "Received message \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << 
        ", dropping it..." << std::endl;
}

void ServerSession::handle(GenericMessage& msg)
{
    std::cout << "Received message \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << 
        ", echoing it back..." << std::endl;
    
    sendMessage(msg);
}

void ServerSession::handle(Message& msg)
{
    // The statement below uses polymorphic message name and ID retrievals.
    std::cout << "Received unexpected message \"" << msg.name() << "\" with ID=" << (unsigned)msg.getId() << 
        ", ignoring..." << std::endl;

    assert(!"Should not happen");
}
```
When **client** sends `Msg1`, `Msg2` and `Msg3` to the **server**, the latter produces the following output:
```
Processing input: 0 7 1 0 0 aa bb 0 9 2 5 68 65 6c 6c 6f 
Received message "Message 1" with ID=1, dropping it...
Received message "Generic Message" with ID=2, echoing it back...
Sending message "Generic Message" with ID=2: 0 9 2 5 68 65 6c 6c 6f 
Processing input: 0 9 3 5 ab cd ef 1 2 
Received message "Generic Message" with ID=3, echoing it back...
Sending message "Generic Message" with ID=3: 0 9 3 5 ab cd ef 1 2 
```
Please take a look how the `comms::GenericMessage` is actually [implemented](https://commschamp.github.io/comms_doc/GenericMessage_8h_source.html).
It contains definition of the `doName()` which results in printing "Generic Message" as recognized message name.

## Summary
- To avoid decoding of some messages the [COMMS Library](https://github.com/commschamp/comms)
  provides [comms::GenericMessage](https://commschamp.github.io/comms_doc/classcomms_1_1GenericMessage.html).
- To support creation of the `GenericMessage` object instead of unrecognized messages the 
  [comms::option::app::SupportGenericMessage](https://commschamp.github.io/comms_doc/options_8h.html)
  option needs to be passed the Id framing layer ([comms::protocol::MsgIdLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1MsgIdLayer.html))
- It is recommended to also pass `comms::option::app::OrigDataView` option to the inner field definition of 
  the `GenericMessage` to avoid unnecessary copy of the data from the **input** buffer, unless the 
  input buffer is not sequential and/or the message object outlives the input buffer.

[Read Previous Tutorial](../tutorial14) &lt;-----------------------&gt; [Read Next Tutorial](../tutorial16) 
