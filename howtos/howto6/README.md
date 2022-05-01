# How-To 6
Multiple run-time determined checksum algorithms in the same protocol.

Some protocols use multiple checksum algorithms with possibly different checksum lengths 
in their framing and use some extra runtime information in their framing to specify type 
of the checksum being used.

This howto uses the following frame
```
SYNC (2 bytes) | SIZE (2 bytes) | ID (1 byte) | CHECKSUM_TYPE (1 byte) | PAYLOAD | CHECKSUM
```
where:

- **SYNC** - is a constant synchronization prefix, expected to be `0xab 0xcd`.
- **SIZE** - size of the rest of the message until end of the PAYLOAD, not including CHECKSUM.
- **ID** - numeric ID of the message.
- **CHECKSUM_TYPE** - specifies type of the checksum at the end, can be **Sum8** (1 byte sum of all other bytes),
**CRC-16** (2 bytes), or **CRC-32** (4 bytes).
- **PAYLOAD** - variable length message payload
- **CHECKSUM** - variable length checksum, depends on the value of **CHECKSUM_TYPE**, calculated on the
whole frame starting from **SYNC**.

The checksum type information is determined by the `CHECKSUM_TYPE` layer (implemented as `<value>`)
and communicated to other interested parties (like `CHECKSUM` layer) via message interface
(see [schema](dsl/schema.xml)).

```xml
<fields>
    <enum name="ChecksumType" type="uint8">
        <validValue name="Sum8" val="0" />
        <validValue name="Crc16" val="1" />
        <validValue name="Crc32" val="2" />
    </enum>    
</fields>

<interface name="Interface" description="Common Interface for all the messages.">
    <ref field="ChecksumType" />
</interface> 
```

Before proceeding to the actual `<frame>` definition explanation please take a closer look at the
[Protocol Stack Definition Tutorial](https://commschamp.github.io/comms_doc/page_prot_stack_tutorial.html)
page from the [COMMS Library](https://github.com/commschamp/comms) documentation.

It explains that the checksum layer class needs to wrap all the other layers checksum on which needs to be
calculated. Such wrapping is also explained and shown in [tutorial5](../../tutorials/tutorial5).

Also due to the fact that the checksum calculation in this howto scenario is not "standard", i.e. cannot
use `<checksum>` layer, instead must be defined as `<custom>` and custom implementation is provided. Although
checksum value is written after the message payload, the [CommsDSL](https://commschamp.github.io/commsdsl_spec/)
does NOT support definition of the `<custom>` layer after the `<payload>`. Instead the `<custom>` checksum
layer must precede all other layers which participate in the checksum calculation. In this howto the 
checksum is calculated on the whole frame, as the result the `<custom>` checksum calculation layer must
be the first one in the frame definition:
```xml
<frame name="Frame">
    <custom name="Checksum">
        <int name="ChecksumField" type="uint32" />
    </custom>    
    <sync name="Sync">
        <int name="SyncField" type="uint16" defaultValue="0xabcd" />
    </sync>
    <size name="Size">
        <int name="SizeField" type="uint16" />
    </size>
    <id name="Id" field="MsgId" />
    <value name="ChekcusmType" field="ChecksumType" interfaceFieldName="ChecksumType"/>
    <payload name="Data" />
</frame>
```
**NOTE** that the field used for the `Checksum` layer is defined to contain `uint32` types to be able
to fit all the used checksums.

The implementation of the `Checksum` layer resides in 
[dsl_src/include/howto6/frame/layer/Checksum.h](dsl_src/include/howto6/frame/layer/Checksum.h) and
copied to the protocol definition 
([include/howto6/frame/layer/Checksum.h](include/howto6/frame/layer/Checksum.h)) 
by the code generator.

The `Checksum` layer is implemented by extending the 
[comms::protocol::ChecksumLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1ChecksumLayer.html)
class provided by the [COMMS Library](https://github.com/commschamp/comms), and
customizing various operations.
```cpp
template<typename TField, typename TNextLayer, typename... TOptions>
class Checksum : public
    comms::protocol::ChecksumLayer<
        TField,
        comms::protocol::checksum::Crc_32, // Not really used, but the parameter needs to be populated
        TNextLayer,
        TOptions...,
        comms::option::def::ExtendingClass<Checksum<TField, TNextLayer, TOptions...> >
    >
{
    // Repeat base type
    using Base = ...;
};
```
**NOTE**, that the code above uses 
[Curiously Recurring Template Pattern](https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern) 
to provide the base
[comms::protocol::ChecksumLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1ChecksumLayer.html) class with the 
actual extending layer type using **comms::option::def::ExtendingClass** option. It makes the customization 
of the default operations possible.

In order to support different checksum algorithms the following default operations are overridden:
```cpp
template<typename TField, typename TNextLayer, typename... TOptions>
class Checksum : public
    comms::protocol::ChecksumLayer<...>
{
public:

    // Override default way of calculating checksum
    template <typename TMsg, typename TIter>
    static typename Field::ValueType calculateChecksum(const TMsg* msgPtr, TIter& iter, std::size_t len, bool& checksumValid)
    {
        ... // Use transportField_checksumType() to determine type of the required algorithm.
    }    
 
    // Due to the fact that the used checksums have different lengths, the
    // functionality of reading a field's value also needs to be customized.
    template <typename TMsg, typename TIter>
    static comms::ErrorStatus doReadField(const TMsg* msgPtr, Field& field, TIter& iter, std::size_t len)
    {
        ... // Use transportField_checksumType() to determine type of the required field serialization length
            // and perform read operation accordingly
    }
 
    // Due to the fact that the used checksums have different lengths, the
    // functionality of reading a field's value also needs to be customized.
    template <typename TMsg, typename TIter>
    static comms::ErrorStatus doWriteField(const TMsg* msgPtr, const Field& field, TIter& iter, std::size_t len)
    {
        ... // Use transportField_checksumType() to determine type of the required field serialization length
            // and perform write operation accordingly
    }
 
    // Due to the fact that the used checksums have different lengths, the
    // functionality of calculating the field's length needs to be overridden
    template <typename TMsg>
    static std::size_t doFieldLength(const TMsg& msg)
    {
        ... // Use transportField_checksumType() to determine type of the required field serialization length
    }
};
```
Please refer to the [actual code](dsl_src/include/howto6/frame/layer/Checksum.h) for the implementation details.

In cases where the checksum length remains the same, but different algorithms are used, the overriding of the
default implement of the **doReadField()**, **doWriteField()** and **doFieldLength()** becomes non necessary.

The **COMMS** library tutorial contains a separate page
called [Defining Custom Checksum Protocol Stack Layer](https://commschamp.github.io/comms_doc/page_custom_checksum_layer.html)
with a bit more details on the available customization.

Let's also take a look how the [client](src/ClientSession.cpp) prepares message to be sent:
```cpp
void ClientSession::sendMsg1()
{
    Msg1 msg;
    msg.field_f1().value() = 1111;

    // Send the message with "Sum8" checksum
    msg.transportField_checksumType().value() = ChecksumType::Sum8;

    assert(m_frame.length(msg) == 9U); // Verify total message length
    sendMessage(msg);
}
```
Having the checksum type information being part of every `<interface>`, i.e. every message object it 
allows the sender to decide (based on some criteria) the checksum algorithm to use when preparing the 
message to be sent out.
