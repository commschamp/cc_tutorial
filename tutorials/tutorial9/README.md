# Tutorial 9
Dealing with multiple uni-directional messages.

Some protocols define uni-directional messages that always travel one direction and never back,
i.e. only sent or only received, but never both.

The [CommsDSL](https://github.com/commschamp/CommsDSL-Specification) allows specifying the 
direction of the message using **sender** property. The available values are
"client", "server", and "both" (default). All the previous tutorials didn't use this property and
as the result were assumed to be bi-directional.

The [schema](dsl/schema.xml) of this tutorial defines the following messages:
```xml
<message name="Msg1" id="MsgId.M1" displayName="^Msg1Name" sender="client" />
<message name="Msg2" id="MsgId.M2" displayName="^Msg2Name" sender="server" />
<message name="Msg3" id="MsgId.M3" displayName="^Msg3Name" sender="client" />
<message name="Msg4" id="MsgId.M4" displayName="^Msg4Name" sender="server" />
```
In this particular tutorial the **client** sends `Msg1` and `Msg3` to the **server**,
which responds with `Msg2` and `Msg4` respectively.

All the previous tutorials defined a single interface class for all the messages that implemented 
various polymorphic behaviors including **read** and **write**. If such approach is
taken for this particular case, then all the messages will have various virtual
functions that are never really used. For example **client** application will never
invoke polymorphic `read()` of `Msg1` and `Msg3`, while **server** will never invoke
polymorphic `write()` of these messages.

For cases like this, where majority of messages are uni-directional, it is highly 
recommended to split the messages into **input** and **output** ones and 
have different polymorphic interfaces for them defined. It will improve the
generated code size as well as compilation speed.

Let's take a look at inner definitions inside the [ServerSession](src/ServerSession.h).
The common message interface for input messages is defined to be:
```cpp
using InMessage =
    tutorial9::Message<
        comms::option::app::ReadIterator<const std::uint8_t*>, // Polymorphic read
        comms::option::app::Handler<ServerSession> // Polymorphic message dispatch
    >;
```
It requires only polymorphic read and polymorphic dispatch. The input messages are 
defined as:
```cpp
using InMsg1 = tutorial9::message::Msg1<InMessage>;
using InMsg3 = tutorial9::message::Msg3<InMessage>;
```
While the common interface for output messages is defined to be:
```cpp
using OutMessage =
    tutorial9::Message<
        comms::option::app::WriteIterator<std::uint8_t*>, // Polymorphic write
        comms::option::app::LengthInfoInterface, // Polymorphic length calculation
        comms::option::app::IdInfoInterface, // Polymorphic message ID retrieval
        comms::option::app::NameInterface // Polymorphic message name retrieval
    >;
```
While the output messages themselves are:
```cpp
using OutMsg2 = tutorial9::message::Msg2<OutMessage>;
using OutMsg4 = tutorial9::message::Msg4<OutMessage>;
```
There is also an important thing to note. The 
[commsdsl2comms](https://github.com/commschamp/commsdsl) code generator produces
[include/tutorial9/input/ClientInputMessages.h](include/tutorial9/input/ClientInputMessages.h) and 
[include/tutorial9/input/ServerInputMessages.h](include/tutorial9/input/ServerInputMessages.h) which define input messages
for the **client** and **server** sides respectively.

Please also pay closer attention to the frame class definition inside 
[include/tutorial9/frame/Frame.h](include/tutorial9/frame/Frame.h).
```cpp
template <
   typename TMessage,
   typename TAllMessages = tutorial9::input::AllMessages<TMessage>,
   typename TOpt = tutorial9::options::DefaultOptions
>
class Frame ...
```
All the previous tutorials provided only the common message interface class as 
the first template parameter while leaving all others as default. The
second template parameter specifies all **input** messages the frame is 
expected to recognize in order to properly create message object. The 
default configuration is to use all the defined messages 
(defined in [include/tutorial9/input/AllMessages.h](include/tutorial9/input/AllMessages.h)).

In this tutorial the **server** needs to recognize only limited number of messages,
hence it can use [tutorial9::input::ServerInputMessages](include/tutorial9/input/ServerInputMessages.h)
instead of default [tutorial9::input::AllMessages](include/tutorial9/input/AllMessages.h)
```cpp
using Frame =
    tutorial9::frame::Frame<
        InMessage,
        tutorial9::input::ServerInputMessages<InMessage>
    >;
```
In such case if any of the unexpected messages (like `Msg2` or `Msg4`) arrives from the
client, they will just be ignored because the frame won't recognize them and appropriate
message object won't even be created to perform a dispatch for handling.

The [ClientSession](src/ClientSession.h) looks very similar:
```cpp
class ClientSession : public Session
{
public:

    ...
    
    using InMessage =
        tutorial9::Message<
            comms::option::app::ReadIterator<const std::uint8_t*>, // Polymorphic read
            comms::option::app::Handler<ClientSession> // Polymorphic message dispatch
        >;

    using InMsg2 = tutorial9::message::Msg2<InMessage>;
    using InMsg4 = tutorial9::message::Msg4<InMessage>;

    void handle(InMsg2& msg);
    void handle(InMsg4& msg);
    void handle(InMessage& msg);

private:
    using OutMessage =
        tutorial9::Message<
            comms::option::app::WriteIterator<std::back_insert_iterator<std::vector<std::uint8_t> > >, // Polymorphic write
            comms::option::app::LengthInfoInterface, // Polymorphic length calculation
            comms::option::app::IdInfoInterface, // Polymorphic message ID retrieval
            comms::option::app::NameInterface // Polymorphic message name retrieval
        >;

    using OutMsg1 = tutorial9::message::Msg1<OutMessage>;
    using OutMsg3 = tutorial9::message::Msg3<OutMessage>;

    using Frame =
        tutorial9::frame::Frame<
            InMessage,
            tutorial9::input::ClientInputMessages<InMessage>
        >;

    ...
};
```
Please pay attention that the frame uses [tutorial9::input::ClientInputMessages](include/tutorial9/input/ClientInputMessages.h)
as the list of input messages suitable for the **client**.

Now it's time to take a closer look at the **client** code that sends the 
messages out to the **server**.
```cpp
void ClientSession::sendMsg1()
{
    // This code sends legitimate message expected by the server
    OutMsg1 msg;
    sendMessage(msg);

    // This code demonstrates sending unexpected message ignored by the server
    using OutMsg2 = tutorial9::message::Msg2<OutMessage>;
    OutMsg2 messageToIgnore;
    sendMessage(messageToIgnore);
}

void ClientSession::sendMsg3()
{
    // This code demonstrates sending unexpected message ignored by the server
    using OutMsg4 = tutorial9::message::Msg4<OutMessage>;
    OutMsg4 messageToIgnore;
    sendMessage(messageToIgnore);

    // This code sends legitimate message expected by the server
    OutMsg3 msg;
    sendMessage(msg);
}
```
Although `Msg2` and `Msg4` are marked as sent only by the **server** and 
never by the **client**, nothing prevents us from creating such output
messages by the **client** and successfully send them to the **server**.
The latter however does **NOT** include `Msg2` and `Msg4` as its input
messages and will just ignore them.

Another thing to note is that the `Frame` definition requires only
knowledge about the **input** messages that it can create and process during `read()`
operation. The `write()`
functionality of the **frame** supports any type of message interface class and
does **NOT** care about a list of supported **output** messages.

## Summary
- The [CommsDSL](https://github.com/commschamp/CommsDSL-Specification) allows definition 
  of the direction of the message using **sender** property.
- When majority of the protocol messages are uni-directional it is highly recommended
  to split the common interface class into two for **input** and **output** messages
  to avoid generation of unnecessary virtual functions.
- The [frame](include/tutorial/frame/Frame.h) definition requires information about
  **input** message interface as well as list of supported **input** messages and 
  does **NOT** care how the **output** messages are defined.
- The generated code contains 
  [include/&lt;namespace&gt;/input/ClientInputMessages.h](/include/tutorial9/input/ClientInputMessages.h)
  and [include/&lt;namespace&gt;/input/ServerInputMessages.h](/include/tutorial9/input/ServerInputMessages.h)
  to define list of **input** messages relevant for **client** and **server** respectively.
- The default list of **input** messages for the [frame](include/tutorial/frame/Frame.h) is
  [include/&lt;namespace&gt;/input/AllMessages.h](/include/tutorial9/input/AllMessages.h). 
  It is highly recommended to replace it with more appropriate one depending on the
  end application logic.

[Read Previous Tutorial](../tutorial8) &lt;-----------------------&gt; [Read Next Tutorial](../tutorial10) 
