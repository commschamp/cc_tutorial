# Tutorial 26
Stateful messages sequence.

There are protocols that don't differentiate messages by their IDs. Instead, the sequence of the messages is pre-determined.
In this particular tutorial (see [schema](dsl/schema.xml)) all the messages are the same, i.e. have the same ID and without any fields.
```
<message name="Msg1" id="0" order="0" displayName="^Msg1Name" />
<message name="Msg2" id="0" order="1" displayName="^Msg2Name" />
<message name="Msg3" id="0" order="2" displayName="^Msg3Name" />
```
Please note usage of the `nonUniqueMsgIdAllowed="true"` in the schema definition as well as **order** property for each `<message>`

The frame is defined like this:
```
<frame name="Frame">
    <size name="Size">
        <int name="SizeField" type="uint16" />
    </size>
    <id name="Id">
        <int name="IdField" type="uint8" pseudo="true" />
    </id>
    <payload name="Data" />
</frame>
```
Note that the field for the message ID is marked with `pseudo="true"`, i.e it is not serialized. Basically the real frame is
```
| SIZE (2 bytes) | PAYLOAD |
```

In most of the previous tutorials the messages were decoded and dispatched using the [comms::processAllWithDispatch()](https://commschamp.github.io/comms_doc/process_8h.html)
function, which internally invoked the `read()` member function of the outermost
[framing layer](https://commschamp.github.io/comms_doc/classcomms_1_1frame_1_1MsgSizeLayer.html).
The first parameter to the function can be a reference to a smart pointer (a variant of the `std::unique_ptr`) to the message object or a
reference to the message object itself. When a smart pointer invocation is used the message object is dynamically allocated by the
[comms::frame::MsgIdLayer](https://commschamp.github.io/comms_doc/classcomms_1_1frame_1_1MsgIdLayer.html) framing layer. However,
when a reference to already allocated message object is used it cannot be changed and the processed message ID information must match
the ID reported by the message object. The [comms::processAllWithDispatch()](https://commschamp.github.io/comms_doc/process_8h.html) function
used in previous tutorial internally uses the reference to a smart pointer invocation variant. To be able to support stateful sequence of message
objects there is a need to use a different function ([comms::processSingleWithDispatch](https://commschamp.github.io/comms_doc/process_8h.html))
and process messages one by one while passing the reference to the pre-allocated message object.

Let's take a look at the [server](src/ServerSession.cpp) implementation.
```cpp
std::size_t ServerSession::processInputImpl(const std::uint8_t* buf, std::size_t bufLen)
{
    std::cout << "Processing input: " << std::hex;
    std::copy_n(buf, bufLen, std::ostream_iterator<unsigned>(std::cout, " "));
    std::cout << std::dec << std::endl;

    assert(m_msg);
    auto* prev = buf;
    auto consumed = 0U;
    while (consumed < bufLen) {
        auto es = comms::processSingleWithDispatch(buf, bufLen, m_frame, *m_msg, *this);
        if (es != comms::ErrorStatus::Success) {
            std::cerr << "ERROR: unexpected protocol sequence" << std::endl;
            return consumed;
        }

        consumed += static_cast<std::size_t>(std::distance(prev, buf));
    }
    return consumed;
}
```
The message object is pre-allocated before at the start:
```cpp
bool ServerSession::startImpl()
{
    m_msg.reset(new Msg1);
    return true;
}
```
It means that when the first data buffer is reported the `Msg1` object is pre-allocated and is properly decoded.

When it is properly handled, the next message object (`Msg2`) is pre-allocated for the next input and so on.
```cpp
void ServerSession::handle(Msg1& msg)
{
    std::cout << "Received message \"" << msg.doName() << "\"" << std::endl;
    sendMessage(msg);
    m_msg.reset(new Msg2);
}
```

The [client](src/ClientSession.cpp) is very similar. The input message is pre-allocated every send.
```cpp
void ClientSession::sendMsg1()
{
    m_msg.reset(new Msg1);
    sendMessage(*m_msg);
}

void ClientSession::sendMsg2()
{
    m_msg.reset(new Msg2);
    sendMessage(*m_msg);
}

...
```

When exchanging the messages both client and server allocate and dispatch proper message object (sequentially) for the same
input. Below is the expected client side output.
```
Sending message "Message 1" with ID=0
Sending raw data: 0 0
Processing input: 0 0
Received message "Message 1"
Sending message "Message 2" with ID=0
Sending raw data: 0 0
Processing input: 0 0
Received message "Message 2"
Sending message "Message 3" with ID=0
Sending raw data: 0 0
Processing input: 0 0
Received message "Message 3"
```

Note that the `read()` member function of a [frame](https://commschamp.github.io/comms_doc/classcomms_1_1frame_1_1MsgIdLayer.html) can
receive a reference to the interface class (extends [comms::Message](https://commschamp.github.io/comms_doc/classcomms_1_1Message.html)) or
the actual message object (extends [comms::MessageBase](https://commschamp.github.io/comms_doc/classcomms_1_1MessageBase.html)). In case of
the latter the code will attempt to invoke non-virtual member functions of the message object, such as `doRead()` instead of polymorphic
`read()`.

Another **important** aspect of the stateful message sequence support is the **necessity** to use polymorphic message dispatch.
```cpp
using Message =
    tutorial26::Message<
        ...
        comms::option::app::Handler<ServerSession> // Polymorphic dispatch
    >;
```
The dispatch also needs be **without** usage of the dispatcher.
```cpp
auto es = comms::processSingleWithDispatch(buf, bufLen, m_frame, *m_msg, *this);
```
To be able to dispatch message to handling via the dispatcher object there is a need to know both numeric message ID as well as
index (offset) of the message type within the used [input messages tuple](include/tutorial26/input/ServerInputMessages.h) among
other message types reporting the same ID. When the input message is pre-allocated there is no way to detect the relevant information.

## Summary

- The transport framing allows deserialization of the pre-allocated message object, which allows implementation of the
stateful sequence of messages.
- The processing functions from the [comms/process.h](https://commschamp.github.io/comms_doc/process_8h.html) wrap the
frame function(s) invocations and allow transparent passing of the same message parameter to the frame function,
whether it is a reference to the message object itself or a reference to a smart pointer to the message object.
- It is necessary to use polymorphic dispatch (using `comms::option::app::Handler` option) functionality.
- When dispatching the message object for handling, the polymorphic dispatch functionality needs to be used and
not the dispatcher object.

[Read Previous Tutorial](../tutorial25) &lt;-----------------------&gt; [Read Next Tutorial](../tutorial27)
