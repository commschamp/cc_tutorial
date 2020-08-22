# Tutorial 13
Supporting multiple message forms with the same numeric ID.

Many protocols define multiple forms of the same message. The actual message 
type depends either on total message payload size or on the value of some particular
member field. In many cases it is convenient to implement such multiple forms as 
independent message types / objects. The [CommsDSL](https://github.com/commschamp/CommsDSL-Specification)
allows such definition when **nonUniqueMsgIdAllowed** property of the [schema](dsl/schema.xml) 
is set to **true**.
```xml
<?xml version="1.0" encoding="UTF-8"?>
<schema name="tutorial13" endian="big" nonUniqueMsgIdAllowed="true">
    ...
    <message name="Msg1_1" id="MsgId.M1" order="0" displayName="Message 1 (1)">
        <int name="F1" type="uint64" />
    </message>
    
    <message name="Msg1_2" id="MsgId.M1" order="1" displayName="Message 1 (2)">
        <int name="F1" type="uint32" />
    </message>    
    
    <message name="Msg1_3" id="MsgId.M1" order="2" displayName="Message 1 (3)">
        <int name="F1" type="uint16" />
    </message>    
</schema>
```
The choice for the default behavior of not to allow repetition of the same message ID 
(without explicit set of **nonUniqueMsgIdAllowed** property) was done as 
a protection against copy-paste errors.

The example above differentiates between the messages based on the payload length, i.e. 
if there are at least 8 bytes left in the input buffer, then `Msg1_1` needs to be chosen,
if not, then the check whether there are at least 4 bytes left in the input buffer needs 
to be performed and `Msg1_2` created in case it is. Otherwise `Msg1_3` needs to be created.

Note the existence of the **order** property assigned to every message. It specifies the 
order in which the message payload reads need to be attempted. The values must be unique 
for the message definitions sharing the same ID, but doesn't necessarily need to be sequential.
The lower **order** number will insure that the relevant message definition will precede the other 
message definition with higher number in the input tuple (like [input::AllMessages](include/tutorial13/input/AllMessages.h))
```cpp
template <typename TBase, typename TOpt = tutorial13::options::DefaultOptions>
using AllMessages =
    std::tuple<
        tutorial13::message::Msg1_1<TBase, TOpt>,
        tutorial13::message::Msg1_2<TBase, TOpt>,
        tutorial13::message::Msg1_3<TBase, TOpt>,
        ...
    >;
```
The `Id` layer of the framing (implemented by [comms::protocol::MsgIdLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1MsgIdLayer.html))
identifies all the message types with the same numeric ID, creates appropriate message object (in order of their definition inside the 
input tuple) and invokes its `read()` operation. If the latter is successful, then the appropriate message is considered to be found and 
returned without any additional attempt to create other messages. If the message payload `read()` operation fails, then the next message type 
in the list is attempted. Hence it is important in the cases like above to give the lower **order** number to the messages
with longest payload.

Another example is to have some special `type` field in message payload which specifies real type of the message:
```xml
<message name="Msg2_1" id="MsgId.M2" order="0" displayName="Message 2 (1)">
    <int name="Type" type="uint8" defaultValue="1" validValue="1" failOnInvalid="true" />
    <int name="F1" type="uint16" />
</message>    

<message name="Msg2_2" id="MsgId.M2" order="10" displayName="Message 2 (2)">
    <int name="Type" type="uint8" defaultValue="2" validValue="2" failOnInvalid="true" />
    <int name="F1" type="uint32" />        
</message>    

<message name="Msg2_3" id="MsgId.M2" order="20" displayName="Message 2 (3)">
    <int name="Type" type="uint8" defaultValue="3" validValue="3" failOnInvalid="true" />
    <int name="F1" type="uint64" />          
</message>    
```
Please note usage of **validValue** and **failOnInvalid** properties for the `Type` field definition. It is
to insure that `read()` operation fails when the read value doesn't match. Also note usage of
**defaultValue** property. It is needed to insure that when message object is default constructed
the `Type` field is to already have a proper value assigned without any need to have explicit boilerplate
assignment code.

In such case the order of the messages is not really important, they will all be tried sequentially and
the right one will be chosen. Maybe for performance reasons the more frequent ones should have the 
lower **order** number.

The [ClientSession](src/ClientSession.h) as well as [ServerSession](src/SeverSession.h) are
implemented in the usual way that was demonstrated in several previous tutorials. Nothing special here.
The **client** sends all the messages one by one, which are echoed back by the **server**.

One other extra thing which is worth paying attention to is how the `switch` based dispatch 
(see [include/tutorial13/dispatch/DispatchMessage.h](include/tutorial13/dispatch/DispatchMessage.h)) 
is implemented.
```cpp
template<typename TProtOptions, typename TMsg, typename THandler>
auto dispatchMessage(
    tutorial13::MsgId id,
    std::size_t idx,
    TMsg& msg,
    THandler& handler) -> decltype(handler.handle(msg))
{
    using InterfaceType = typename std::decay<decltype(msg)>::type;
    switch(id) {
    case tutorial13::MsgId_M1:
    {
        switch (idx) {
        case 0U:
        {
            using MsgType = tutorial13::message::Msg1_1<InterfaceType, TProtOptions>;
            return handler.handle(static_cast<MsgType&>(msg));
        }
        case 1U:
        {
            ...
        }
        ...
        break;
    }
    case tutorial13::MsgId_M2:
    {
        switch (idx) {
        case 0U:
        {
            using MsgType = tutorial13::message::Msg2_1<InterfaceType, TProtOptions>;
            return handler.handle(static_cast<MsgType&>(msg));
        }
        case 1U:
        {
            ...
        }
        ...
        break;
    }
    default:
        break;
    };

    return handler.handle(msg);
}
```
Note the usage of `idx` parameter in addition to `id`. The `idx` specifies index (offset) of the 
detected message type in the **input** tuple (see [include/tutorial13/input/AllMessages.h](include/tutorial13/input/AllMessages.h))
starting from the first message having the same numeric ID. In other word the indices are:

- `Msg1_1`: **0** (offset since definition of `Msg1_1`)
- `Msg1_2`: **1** (offset since definition of `Msg1_1`)
- `Msg1_3`: **2** (offset since definition of `Msg1_1`)
- `Msg2_1`: **0** (offset since definition of `Msg2_1`)
- `Msg2_2`: **1** (offset since definition of `Msg2_1`)
- `Msg2_3`: **2** (offset since definition of `Msg2_1`)

---- 

**SIDE NOTE**: The [comms::protocol::MsgIdLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1MsgIdLayer.html)
used by the framing is capable of returning the detected index / offset information via special extra parameters
(see [comms::protocol::msgIndex()](https://commschamp.github.io/comms_doc/namespacecomms_1_1protocol.html)). These parameters 
are used by the processing functions from [comms/process.h](https://commschamp.github.io/comms_doc/process_8h.html) to 
get the numeric message ID and the index (offset) information in order to perform the message dispatch. Extracting this 
information is a bit out of scope for this tutorial and will be covered in other later one.

---

## Summary
- The [CommsDSL](https://github.com/commschamp/CommsDSL-Specification) supports definition of multiple forms 
  of the same message.
- Definition of such multiple forms requires set of **nonUniqueMsgIdAllowed** property of the protocol schema 
  to **true**.
- The multiple forms of the same message require usage of **order** property to specify order in which the 
  read operation for them will be attempted.
- Some dispatch functionalities may require knowledge about index/offset of the detected message within a 
  sequence of the input messages with the same numeric ID.

[Read Previous Tutorial](../tutorial12) &lt;-----------------------&gt; [Read Next Tutorial](../tutorial14) 
