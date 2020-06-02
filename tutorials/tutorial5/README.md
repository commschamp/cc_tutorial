# Tutorial 5
Deeper understanding of **&lt;frame&gt;**-ing and working with multiple **&lt;frame&gt;**-s.

Many embedded systems have multiple I/O interfaces for communication with external world. It is also
not uncommon for new I/O interfaces being added in the future versions of the hardware. Many developers
make a prudent choice and try to reuse the same communication protocol for multiple available I/O links.
However, every type of I/O has different reliability built-in and may require different message framing.

For example the TCP/IP link uses checksum in its packets to insure that data is not corrupted and 
automatically re-requests packets to be sent again if needed. As the result simple framing below is
suitable in most cases.
```
SIZE | ID | PAYLOAD
```

With RS-232 link (or similar) there is a need to take extra measures to identify where the message packet 
starts and whether the message data was not corrupted on the way with a checksum. It many cases it looks
something like this:
```
SYNC (predefined header) | SIZE | ID | PAYLOAD | CHECKSUM
```

The whole [CommsChampion Ecosystem](https://arobenko.github.io/cc/) was designed with clean separation
of message definitions with their payloads and the actual framing. It also allows definition of multiple
frames in the same protocol schema file(s) and allows the end application to pick one that is needed at
compile time.

In this tutorial we will use two different frames: one for messages sent from **client** to **server** 
and another for the opposite direction. In the process we'll get a deeper understanding of **&lt;frame&gt;**
definition options.

The [schema](dsl/schema.xml) defines two frames. One is for messages being sent by the **server** to the 
**client**.
```xml
<frame name="ServerToClientFrame">
    <size name="Size">
        <int name="SizeField" type="uint16" />
    </size>
    <id name="Id" field="MsgId" />
    <payload name="Data" />
</frame>
```
This is the framing that has been seen in all the previous tutorials. It is simply:
```
SIZE (2 bytes) | ID (1 byte) | PAYLOAD
```

The other one for messages being sent from the **client** to the **server** is:
```xml
<frame name="ClientToServerFrame">
    <sync name="Sync">
        <int name="SyncField" type="uint16" defaultValue="0xabcd" />
    </sync>
    <size name="Size">
        <int name="SizeField" type="uint16" serOffset="2" displayOffset="2" />
    </size>
    <id name="Id" field="MsgId" />
    <payload name="Data" />
    <checksum name="Checksum" alg="crc-ccitt" from="Size" >
        <int name="ChecksumField" type="uint16" />
    </checksum>        
</frame>
```
It represents the following framing:
```
SYNC (0xabcd - 2 bytes) | SIZE (up until and including CHECKSUM - 2 bytes) | ID (1 byte) | PAYLOAD | CHECKSUM (crc-ccitt - 2 bytes)
```

To properly understand the schema definition above and the implementation implications let's go through the
important points one by one.

First of all, all every **&lt;frame&gt;** must define internal so called **layers** (**&lt;sync&gt;**, 
**&lt;size&gt;**, etc...). Every such layer handles only one specific value inside the message frame. To
properly describe the length and type of such value, the **field** definition is used:
```xml
<sync name="Sync">
    <int name="SyncField" type="uint16" defaultValue="0xabcd" />
</sync>
```

----

**SIDE NOTE**: In case the **&lt;frame&gt;** XML node has properties other than **layers** defined as XML children,
then the layers themselves need to be defined inside **&lt;layers&gt;** XML node.
```xml
<frame name="ClientToServerFrame">
    <description>
        This frame is used for messages being sent from client to server.
    </description>
    <layers>
        <sync name="Sync">
            <int name="SyncField" type="uint16" defaultValue="0xabcd" />
        </sync>
        ...
    </layers>
</frame>
```

Similar with the definition of the layer itself. If it has some other non inner field definition properties
defined as XML children, then the field definition needs to be defined as a child of **&lt;field&gt;** XML
node:
```xml
<sync name="Sync">
    <description>
        Synchronization bytes to mark beginning of the message.
    </description>
    <field>
        <int name="SyncField" type="uint16" defaultValue="0xabcd" />
    </field>
</sync>
```

----

Let's take a look at the defined layers one by one. The relevant C++ code can be found in
[include/tutorial5/frame/ClientToServerFrame.h](include/tutorial5/frame/ClientToServerFrame.h).

## &lt;payload&gt; Layer
The **&lt;payload&gt;** layer represents message payload (serialized fields). It is the only 
layer that doesn't have any inner field that represents framing value.
```xml
<payload name="Data" />
```
Such layer is implemented by extending or aliasing 
[comms::protocol::MsgDataLayer](https://arobenko.github.io/comms_doc/classcomms_1_1protocol_1_1MsgDataLayer.html).
```cpp
using Data =
    comms::protocol::MsgDataLayer<
        typename TOpt::frame::ClientToServerFrameLayers::Data
    >;
```

## &lt;id&gt; Layer
The **&lt;id&gt;** layer represents numeric message ID.
```xml
<id name="Id" field="MsgId" />
```
Note that the `MsgId` field is defined in the global space and is used to enumerate messages. The 
[CommsDSL](https://github.com/arobenko/CommsDSL-Specification) allows reference of such field
with **field** property rather than defining a field as XML child element. 

Such layer is implemented by extending or aliasing 
[comms::protocol::MsgIdLayer](https://arobenko.github.io/comms_doc/classcomms_1_1protocol_1_1MsgIdLayer.html),
which is responsible to read the numeric message ID and create (allocate) appropriate message object.
```cpp
template <typename TMessage, typename TAllMessages>
using Id =
    comms::protocol::MsgIdLayer<
        tutorial5::field::MsgId<TOpt>,
        TMessage,
        TAllMessages,
        Data,   // <-- Data layer wrapped
        typename TOpt::frame::ClientToServerFrameLayers::Id
    >;
```
Note, that [COMMS Library](https://github.com/arobenko/comms_champion#comms-library) implement message framing
by folding layers, where one layer wraps another and keeps the latter as its private data member. Such architecture
allows having any extra logic **before** and **after** read/write operations are forwarded the the next layer
for processing.

The definition above receives two template parameters `TMessage` and `TAllMessages`. The first one
(`TMessage`) is expected to be a type of common **interface** class (descendant of 
[comms::Message](https://arobenko.github.io/comms_doc/classcomms_1_1Message.html)) of all the message
types, while second (`TAllMessages`) is `std::tuple` of all the **input** message types
(descendants of [comms::MessageBase](https://arobenko.github.io/comms_doc/classcomms_1_1MessageBase.html)), which 
the `ID` layer is expected to recognize and create relevant object during **read** operation.

**SIDE NOTE**: The last template parameter passed to the [comms::protocol::MsgIdLayer](https://arobenko.github.io/comms_doc/classcomms_1_1protocol_1_1MsgIdLayer.html)
is actually a compile time configuration parameter that can be used by the end-application to configure the
behavior of the layer, such as replace default dynamic memory allocation with in-place allocation more 
suitable for bare-metal development. Such compile time configuration is a subject for another tutorial.

## &lt;size&gt; Layer
The **&lt;size&gt;** layer represent a **remaining** length **until** end of the **&lt;payload&gt;** layer
**NOT** including the length of the size field itself.
```xml
<size name="Size">
    <int name="SizeField" type="uint16" serOffset="2" displayOffset="2" />
</size>
```
Note, that in this particular tutorial the `SIZE` value in the framing represents remaining length until
end of the message **including** checksum (which follows the **&lt;payload&gt;**). To satisfy this
requirement, the **serOffset="2"** property has been used to add extra 2 bytes (length of the checksum) to the 
serialized value.

There are protocols that include length of the size field itself as the value of the `SIZE` in the
protocol framing. In such case the **serOffset** property also needs to be used.

Usage of the **displayOffset** property can be used the force adding the same offset to the
value displayed in [CommsChampion Tools](https://github.com/arobenko/comms_champion#commschampion-tools) and it's
not really relevant to this tutorial.

The **&lt;size&gt;** layer is implemented by extending or aliasing 
[comms::protocol::MsgSizeLayer](https://arobenko.github.io/comms_doc/classcomms_1_1protocol_1_1MsgSizeLayer.html).
```cpp
template <typename TMessage, typename TAllMessages>
using Size =
    comms::protocol::MsgSizeLayer<
        typename SizeMembers::SizeField,
        Id<TMessage, TAllMessages> // <-- Id layer wrapped
    >;
```
Just like described earlier the `Size` layer type definition receives the type of the layer it
wraps (`Id`) as its template parameter.

## &lt;checksum&gt; Layer
The **&lt;checksum&gt;** layer is used to define checksum information that needs to be calculated.
```xml
<checksum name="Checksum" alg="crc-ccitt" from="Size" >
    <int name="ChecksumField" type="uint16" />
</checksum>        
```
The [CommsChampion Ecosystem](https://arobenko.github.io/cc/) has a list of supported built-in checksum 
algorithms which can be specified using **alg** property. Please refer to 
[CommsDSL](https://github.com/arobenko/CommsDSL-Specification) specification for a full list. In this
particular tutorial [CRC-CCITT](https://en.wikipedia.org/wiki/Cyclic_redundancy_check) is used. 

**SIZE NOTE**: It is possible to implement and add usage of custom checksum calculation algorithm, which
is a bit out of scope for this particular tutorial. This subject will be covered in one of the later
tutorials.

Please also pay attention to usage of **from** property in **&lt;checksum&gt;** layer definition. 
It specifies from which layer the checksum calculation needs to be performed. In the case of
this tutorial it's from `SIZE` layer until the `CHECKSUM` itself. The
[CommsDSL](https://github.com/arobenko/CommsDSL-Specification) also supports 
usage of **&lt;checksum&gt;** layer as prefix to the area on which the checksum needs to be
calculated. In this case the **until** prefix needs to be used.

The suffix **&lt;checksum&gt;** layer is implemented by extending or aliasing 
[comms::protocol::ChecksumLayer](https://arobenko.github.io/comms_doc/classcomms_1_1protocol_1_1ChecksumLayer.html).
```cpp
template <typename TMessage, typename TAllMessages>
using Checksum =
    comms::protocol::ChecksumLayer<
        typename ChecksumMembers::ChecksumField,
        comms::protocol::checksum::Crc_CCITT,
        Size<TMessage, TAllMessages>
    >;
```
Note, that the C++ class of `Checksum` layer needs to wrap all the other layers on which
the checksum value is calculated. That's the reason while the `Checksum` wraps the `Size`.

## &lt;sync&gt; Layer
The **&lt;sync;&gt;** layer is used to define synchronization prefix. The **defaultValue** property of the field 
needs to be used to define the synchronization value.
```xml
<sync name="Sync">
    <int name="SyncField" type="uint16" defaultValue="0xabcd" />
</sync>
```


[Read Previous Tutorial](../tutorial4) &lt;-----------------------&gt; [Read Next Tutorial](../tutorial6) 
