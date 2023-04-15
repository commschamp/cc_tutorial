# Tutorial 20
Reporting protocol version in one of the messages.

This tutorial is a logical continuation of the [previous](../tutorial19) one. It demonstrates 
a protocol definition when client reports its version in one of the messages. 

Usually in such the **client** has a special `Connect` (or similar) message that reports
its version to the **server**. The latter either adjusts its communication version to match 
the **client**'s (like in this tutorial) or reports its own version in some kind of 
acknowledgement response message.

The relevant parts of this tutorial [schema](dsl/schema.xml) looks like this:
```xml
<fields>
    <string name="ConnectMsgName" defaultValue="Connect" />
    ...
        
    <enum name="MsgId" type="uint8" semanticType="messageId">
        <validValue name="Connect" val="0" displayName="^ConnectMsgName" />
        ...
    </enum>
    
    <int name="Version" type="uint16" semanticType="version" />
</fields>

<interface name="Interface" description="Common Interface for all the messages.">
    <ref field="Version" />
</interface>  

<message name="Connect" id="MsgId.Connect" displayName="^ConnectMsgName" sender="client">
    <ref field="Version" />
</message> 
```
**REMINDER**: The _version_ field (marked with `semanticType="version"`) is default constructed to have
a value equal to the schema version (**5** in this tutorial).

This creates a problem for the **server** that was compiled with version **5** (with default value of 
the `Version` field inside the `<interface>` to be **5**), but the connected **client** 
has version **4**. There is a need for the `Version` field of the `<interface>` to have updated
value before the `read()` operation of the newly created message object is invoked.

In order to properly support such case the following trick is required:
```xml
<frame name="Frame">
    <size name="Size">
        <int name="Field" type="uint16" displayName="Size" />
    </size>
    <id name="Id" field="MsgId" />
    <value name="Version" interfaceFieldName="Version" field="Version" pseudo="true" />
    <payload name="Data" />
</frame>
```
There is still `<value>` layer (like in [previous](../tutorial19) tutorial) 
which is responsible to assign proper value to the `Value` field, but it is marked as 
**pseudo** (`pseudo="true"`). The **pseudo** value layer does not really serialize/deserialize
any field, it just pretends to. Such layer contains inner field member in its private data, 
which can be accessed via API and assigned proper value. During the `read()` operation
such pseudo layer pretends to read the value and just takes the data from its inner field as 
if read.

Note, that **pseudo** layer can be put anywhere in the frame, but it is recommended (for
performance reasons) to put it right before the `<payload>` to make sure that 
the message object is properly created.

Let's take a look how the `Connect` message is handled by the [ServerSession](src/ServerSession.cpp):
```cpp
void ServerSession::handle(ConnectMsg& msg)
{
    std::cout << "Received message \"" << msg.doName() << 
        "\" with ID=" << (unsigned)msg.getId() << 
        " and version=" << (unsigned)msg.version() << std::endl;

    // Assign version for all future messages.
    m_frame.layer_version().pseudoField().value() = msg.field_version().value();
}
```
**REMINDER**: The [frame](include/tutorial20/frame/Frame.h) definition uses 
`COMMS_PROTOCOL_LAYERS_ACCESS()` macro which assigns names to the used framing layers.
The macro also generates `layer_*()` member functions for all the provided names to 
access relevant layer. As the result `m_frame.layer_version()` provides an access to the
`Version` layer.

The pseudo `<value>` layer is defined with usage of 
[comms::option::def::PseudoValue](https://commschamp.github.io/comms_doc/options_8h.html) option.
```cpp
using Version =
    comms::protocol::TransportValueLayer<
        tutorial20::field::Version<TOpt, comms::option::def::EmptySerialization>,
        0U,
        Data,
        comms::option::def::PseudoValue
    >;
```
When the `comms::option::def::PseudoValue` option is passed to the 
[comms::protocol::TransportValueLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1TransportValueLayer.html)
it creates `pseudoField()` member functions to access the field stored in the private data members.
The code above (`m_frame.layer_version().pseudoField()`) accesses it and assigns the reported 
version.

As the result, for all the messages that follow, the `Version` member field 
(in the `<interface>`) will be assigned the right value before
the `read()` operation is forwarded to the `<payload>` layer, which in turn invokes `read()` operation of 
the message object. 

----

**SIDE NOTE**: If [CommsChampion Tools](https://github.com/commschamp/cc_tools_qt/wiki/How-to-Use-CommsChampion-Tools)
are intended to be used for the protocol visualization and/or debugging, it is better to hide the `Version` field 
inside the transport framing from being displayed altogether (because it's not really there). In such case it is
recommended to slightly update the definition of the `<value>` layer above into the following:
```xml
<value name="Version" interfaceFieldName="Version" pseudo="true">
    <ref field="Version" displayHidden="true" />
</value>
```

---

Note that in this tutorial the client is also compiled to have the default version **5** (the default state of all the 
fields in all the messages is valid for version **5**). In order to emulate version **4** client the 
field of the pseudo `Version` `<value>` layer is modified when `Connect` message is sent:
```cpp
void ClientSession::sendConnect()
{
    static const unsigned UsedVersion = 4U;

    ConnectMsg msg;
    assert(msg.version() == 5U); // Schema version by default

    comms::cast_assign(msg.field_version().value()) = UsedVersion; 
    m_frame.layer_version().pseudoField().value() = msg.field_version().value();

    sendMessage(msg);
    doNextStage();
}
```
Also when every message is sent out its version info is updated and message contents are refreshed to 
make sure that the message has the right consistent state:
```cpp
void ClientSession::sendMessage(Message& msg)
{
    // Update the version and refresh
    msg.version() = m_frame.layer_version().pseudoField().value();
    msg.refresh();
    ...
}
```
Note that the refresh functionality is **polymorphic**. It is available thanks to the passing the 
[comms::option::app::RefreshInterface](https://commschamp.github.io/comms_doc/options_8h.html) 
option to the message interface definition:
```cpp
using Message = 
    tutorial20::Interface<
        ...,        
        comms::option::app::RefreshInterface // Polymorphic refresh        
    >;
```
It is important to understand that manual update of the version information and forceful `refresh()`
is done in this example to emulate client of older version. It is **NOT** required in normal
operation.

## Summary
- When the version is reported in one (usually the first) of the messages, the 
  definition is very similar to the one that reports the version in the frame of 
  every message (described in the [previous](../tutorial19) tutorial).
- The main difference is that `<value>` layer needs to be set as **pseudo**
  (`pseudo="true"`).
- When handling the version reporting message, the relevant pseudo `<value>` layer
  object in the frame needs to be accessed and its pseudo field needs to be updated to the 
  right version. It will result in all subsequent incoming messages to be read as if having 
  the reported version.

[Read Previous Tutorial](../tutorial19) &lt;-----------------------&gt; [Read Next Tutorial](../tutorial21) 
