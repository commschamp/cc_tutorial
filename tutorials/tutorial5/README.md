# Tutorial 5
Deeper understanding of `<frame>`-ing and working with multiple `<frame>`-s.

Many embedded systems have multiple I/O interfaces for communication with external world. It is also
not uncommon for new I/O interfaces been added in the future versions of the hardware. Many developers
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

The whole [CommsChampion Ecosystem](https://commschamp.github.io/) was designed with clean separation
of message definitions with their payloads and the actual framing. It also allows definition of multiple
frames in the same protocol schema file(s) and allows the end application to pick at compile time the one 
that is needed.

In this tutorial we will use two different frames: one for messages sent from **client** to **server** 
and another for the opposite direction. In the process we'll get a deeper understanding of `<frame>`
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

The relevant generated code reside in 
[include/tutorial5/frame/ServerToClientFrame.h](include/tutorial5/frame/ServerToClientFrame.h)
and [include/tutorial5/frame/ClientToServerFrame.h](include/tutorial5/frame/ClientToServerFrame.h)


To properly understand the schema definition above and the implementation implications let's go through the
important points one by one.

First of all, every `<frame>` must define internal so called **layers** (`<sync>`, 
`<size>`, etc...). Every such layer handles only one specific value inside the message frame. To
properly describe the length and type of such value, the layer needs to define suitable inner **field**:
```xml
<sync name="Sync">
    <int name="SyncField" type="uint16" defaultValue="0xabcd" />
</sync>
```

----

**SIDE NOTE**: In case the `<frame>` XML node has properties other than **layers** defined as XML children,
then the layers themselves need to be defined inside `<layers>` XML node.
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
defined as XML children, then the field definition needs to be defined as a child of `<field>` XML
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

Let's take a look at the defined layers of `ClientToServerFrame` (from
[include/tutorial5/frame/ClientToServerFrame.h](include/tutorial5/frame/ClientToServerFrame.h)) one by one. 

## &lt;payload&gt; Layer
The `<payload>` layer represents message payload (serialized fields). It is **the only**
layer that doesn't have any inner field that represents framing value.
```xml
<payload name="Data" />
```
Such layer is implemented by extending or aliasing 
[comms::protocol::MsgDataLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1MsgDataLayer.html).
```cpp
using Data =
    comms::protocol::MsgDataLayer<
        ...
    >;
```

## &lt;id&gt; Layer
The `<id>` layer represents numeric message ID.
```xml
<id name="Id" field="MsgId" />
```
Note that the `MsgId` field is defined in the global space and is used to enumerate messages. The 
[CommsDSL](https://github.com/commschamp/CommsDSL-Specification) allows reference of such field
with **field** property rather than defining a field as XML child element. 

Such layer is implemented by extending or aliasing 
[comms::protocol::MsgIdLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1MsgIdLayer.html),
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
Note, that [COMMS Library](https://github.com/commschamp/comms) implement message framing
by folding layers, where one layer wraps another and keeps the latter as its private data member. Such architecture
allows assembling a required framing out of multiple building blocks as well as 
having any extra logic **before** and **after** read/write operations are forwarded the the next layer
for processing.

The definition above receives two template parameters `TMessage` and `TAllMessages`. The first one
(`TMessage`) is expected to be a type of common **interface** class (descendant of 
[comms::Message](https://commschamp.github.io/comms_doc/classcomms_1_1Message.html)) of all the message
types, while second (`TAllMessages`) is `std::tuple` of all the **input** message types
(descendants of [comms::MessageBase](https://commschamp.github.io/comms_doc/classcomms_1_1MessageBase.html)), which 
the `ID` layer is expected to recognize and create relevant object during **read** operation.

----

**SIDE NOTE**: The last template parameter passed to the [comms::protocol::MsgIdLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1MsgIdLayer.html)
is actually a compile time configuration parameter that can be used by the end-application to configure the
behavior of the layer, such as replace default dynamic memory allocation of message objects with in-place allocation more 
suitable for bare-metal development. Such compile time configuration is a subject for another a bit later tutorial.

----

## &lt;size&gt; Layer
The `<size>` layer represent a **remaining** data length **until** end of the `<payload>` layer
**NOT** including the length of the size field itself and **NOT** including any
values after `<payload>`.
```xml
<size name="Size">
    <int name="SizeField" type="uint16" serOffset="2" displayOffset="2" />
</size>
```
Note, that in this particular tutorial the `SIZE` value in the framing represents remaining length until
end of the message **including** checksum (which follows the `<payload>`). To satisfy this
requirement, the **serOffset="2"** property has been used to add extra 2 bytes (length of the checksum) to the 
serialized value.

There are protocols that include length of the size field itself as the value of the `SIZE` in the
protocol framing. In such case the **serOffset** property also needs to be used.

Usage of the **displayOffset** property can be used the force adding the same offset to the
value displayed in [CommsChampion Tools](https://github.com/commschamp/cc_tools_qt) and it's
not really relevant to this tutorial.

The `<size>` layer is implemented by extending or aliasing 
[comms::protocol::MsgSizeLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1MsgSizeLayer.html).
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
The `<checksum>` layer is used to define checksum information that needs to be calculated.
```xml
<checksum name="Checksum" alg="crc-ccitt" from="Size" >
    <int name="ChecksumField" type="uint16" />
</checksum>        
```
The [CommsChampion Ecosystem](https://commschamp.github.io/) has a list of supported built-in checksum 
algorithms which can be specified using **alg** property. Please refer to 
[CommsDSL](https://commschamp.github.io/commsdsl_spec/#frames-checksum) specification for a full list. In this
particular tutorial [CRC-CCITT](https://en.wikipedia.org/wiki/Cyclic_redundancy_check) is used. 

----

**SIDE NOTE**: It is possible to implement and add usage of custom checksum calculation algorithm, which
is a bit out of scope for this particular tutorial. This subject will be covered in one of the later
tutorials.

----

Please also pay attention to usage of **from** property in `<checksum>` layer definition. 
It specifies from which layer the checksum calculation needs to be performed. In the case of
this tutorial it's from `SIZE` layer until the `CHECKSUM` itself. The
[CommsDSL](https://github.com/commschamp/CommsDSL-Specification) also supports 
usage of `<checksum>` layer as prefix to the area on which the checksum needs to be
calculated. In this case the **until** property needs to be used.

The suffix `<checksum>` layer is implemented by extending or aliasing 
[comms::protocol::ChecksumLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1ChecksumLayer.html)
or [comms::protocol::ChecksumPrefixLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1ChecksumPrefixLayer.html)
depending on whether the checksum follows or precedes the data used for checksum
calculation.
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
The `<sync>` layer is used to define synchronization prefix. The **defaultValue** property of the field 
needs to be used to define the synchronization value.
```xml
<sync name="Sync">
    <int name="SyncField" type="uint16" defaultValue="0xabcd" />
</sync>
```
The `<sync>` layer is implemented by extending or aliasing 
[comms::protocol::SyncPrefixLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1SyncPrefixLayer.html).
```cpp
template <typename TMessage, typename TAllMessages>
using Sync =
    comms::protocol::SyncPrefixLayer<
        typename SyncMembers::SyncField,
        Checksum<TMessage, TAllMessages>
    >;
```
Note, that there is no real need to use **validValue** and/or **failOnInvalid** properties for the definition 
of the `SyncField` to force the read operation to fail on invalid value. The implementation of the
[comms::protocol::SyncPrefixLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1SyncPrefixLayer.html)
just compares the read field with the default constructed one and fails the read operation if they are
not equal. During write operation the layer will just invoke `write()` member function on
the default constructed field, which will write the correct value thanks to 
usage of **defaultValue** property in the field definition.

## Full Frame
The last (outermost) layer is actually used as a transport frame.
```cpp
template <typename TOpt = tutorial5::options::DefaultOptions>
struct ClientToServerFrameLayers
{
    ...
    
    template<typename TMessage, typename TAllMessages>
    using Stack = Sync<TMessage, TAllMessages>;
};

template <
   typename TMessage,
   typename TAllMessages = tutorial5::input::AllMessages<TMessage>,
   typename TOpt = tutorial5::options::DefaultOptions
>
class ClientToServerFrame : public
    ClientToServerFrameLayers<TOpt>::template Stack<TMessage, TAllMessages>
{
public:
    COMMS_PROTOCOL_LAYERS_ACCESS(
        data,
        id,
        size,
        checksum,
        sync
    );
};
```
As the result the documentation of the last layer type 
([comms::protocol::SyncPrefixLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1SyncPrefixLayer.html) 
for the current example) can be used for reference on available framing API.

The final definition of `ClientToServerFrame` frame class uses `COMMS_PROTOCOL_LAYERS_ACCESS()`
macro to assign names for the defined layers. For every name **X** the macro generates 
`layer_X()` member function to allow access to it if needed. This particular tutorial doesn't
have such a need, so these functions are not really used.

Now, let's take a look at the sending and processing code inside the [src/ClientSession.cpp](src/ClientSession.cpp).
```cpp
void ClientSession::sendMessage(const Message& msg)
{
    std::vector<std::uint8_t> output;
    ...
    auto writeIter = std::back_inserter(output);

    auto es = m_clientToServerFrame.write(msg, writeIter, output.max_size());
    if (es == comms::ErrorStatus::UpdateRequired) {
        auto updateIter = output.begin();
        es = m_clientToServerFrame.update(updateIter, output.size());
    }

    if (es != comms::ErrorStatus::Success) {
        assert(!"Write operation failed unexpectedly");
        return;
    }
    ...
}
```
The important code is listed above. Note, that the write operation uses 
[output](https://en.cppreference.com/w/cpp/named_req/OutputIterator) iterator
to write the code (`std::back_inserter(output)`) which cannot be returned back 
to and used to re-read the written data in order to calculate the checksum value 
before it's been written. As the result the call to `m_clientToServerFrame.write(...)`
will put some dummy (`0`) two bytes as the checksum and return 
[commms::ErrorStatus::UpdateRequired](https://commschamp.github.io/comms_doc/ErrorStatus_8h.html)
to indicate that the `write()` operation is not complete. The call to 
`update()` with [random access](https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator) 
iterator needs to follow. It will be used to re-read the written data as well as
overwrite the dummy checksum with a correct value.

Similar situation may occur when the interface class doesn't expose polymorphic
`length()` member function (the `comms::option::app::LengthInfoInterface` option
has **NOT** been provided). In such case when `SIZE` value needs to be written the
proper value cannot be retrieved (because length of message payload is not known).
In this case the [comms::protocol::MsgSizeLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1MsgSizeLayer.html)
will write a dummy value and force a return of `commms::ErrorStatus::UpdateRequired`.
After that when the `update()` is called, the layer will calculate size of the written 
code and update previously written dummy value with the correct one.

---

**SIDE NOTE**: In the example above the `update()` functionality doesn't require
any knowledge about the recently written message to be able to analyse the recently
written data and update values where needed. However, in some cases the
access to previously written message needs to be provided. 
The [COMMS Library](https://github.com/commschamp/comms)
provides such overloaded `update()` member function which receives a reference to
the message object as its first parameter.

---

Note that this particular tutorial focuses on the deeper understanding of message framing rather
than messages and their fields. All the exchanged messages are defined not to contain 
any payload:
```xml
<message name="Msg1" id="MsgId.M1" displayName="^Msg1Name" />
<message name="Msg2" id="MsgId.M2" displayName="^Msg2Name" />
<message name="Msg3" id="MsgId.M3" displayName="^Msg3Name" />
```
In this particular case there is no real need to do a separate `handle()` 
message for every message type. There is only one common function:
```cpp
void ClientSession::handle(Message& msg)
{
    std::cout << "Received \"" << msg.name() << "\" with ID=" << (unsigned)msg.getId() << '\n';
    ...
}

```
Note, that the compiler still looks for the **best** match of the handling function to invoke when compiling code relevant for
the message dispatch. In this particular case there is only one function to choose from. However,
if you add a handling function with better type match say `void ClientSession::handle(Msg1& msg)`,
then this function will be called to handle `Msg1` message instead of common one
when the code is recompiled.


## Summary

- The [CommsChampion Ecosystem](https://commschamp.github.io/) allows clear separation of the protocol 
  messages definition and the transport framing.
- The transport framing is defined using `<frame>` XML node.
- The protocol schema allows definition of multiple transport frames and the generated code
  allows the end application to select required one at compile time.
- Every `<frame>` uses internal layers to specify transport fields and their 
  roles.
- The generated C++ code of the frame(s) resides in [include/&lt;namespace&gt;/frame](include/tutorial5/frame) folder and
  uses classes from [comms::protocol](https://commschamp.github.io/comms_doc/namespacecomms_1_1protocol.html)
  namespace to define the layers.
- The defined framing layers wrap one another, as the result the outermost layer is used 
  to handle the whole transport framing.
- For available frame API reference open the documentation of the 
  [outermost layer](https://commschamp.github.io/comms_doc/namespacecomms_1_1protocol.html) type.
- The polymorphic behavior of the common interface class may influence the ability of the 
  frame to perform its `write()` operation. 
- When write operation returns [commms::ErrorStatus::UpdateRequired](https://commschamp.github.io/comms_doc/ErrorStatus_8h.html)
  use [random access](https://en.cppreference.com/w/cpp/named_req/RandomAccessIterator) iterator to 
  perform `update()` operation.

  
[Read Previous Tutorial](../tutorial4) &lt;-----------------------&gt; [Read Next Tutorial](../tutorial6) 
