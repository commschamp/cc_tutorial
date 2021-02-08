# How-To 4
Single message protocol without message ID in framing.

There are some protocols which don't have multiple types of messages. Usually such protocols use a 
single list of TLV (type-length-value) triplets wrapped in some extra
framing. This example protocol has the following form:
```
SYNC (0xabcd) | LENGTH (2 bytes) | TLV1 | TLV2 | .... | TLVN | CHECKSUM (CRC-CCITT)
```

Although the protocol specification might not define any particular message structure there is still a 
need to define a **&lt;message&gt;** with some dummy numeric ID.
```xml
<fields>
    <string name="MsgName" defaultValue="Message" />
        
    <enum name="MsgId" type="uint8" semanticType="messageId">
        <validValue name="M0" val="0" displayName="^MsgName" />
    </enum>

</fields>

<message name="Msg" id="MsgId.M0" displayName="^MsgName">
    ...
</message>
```
The TLV triplets are defined using **&lt;variant&gt;** field and are described in detail in the 
[tutorial4](../../tutorials/tutorial4).
```xml
<fields>
    <variant name="TlvProp">
        ...
    </variant>
</fields>

<message name="Msg" id="MsgId.M0" displayName="^MsgName">
    <list name="Props" element="TlvProp" />
</message>
```
The message frame is defined the following way:
```xml
<frame name="Frame">
    <sync name="Sync">
        <int name="SyncField" type="uint16" defaultValue="0xabcd" />
    </sync>
    <size name="Size">
        <int name="SizeField" type="uint16" serOffset="2" />
    </size>
    <id name="Id">
        <int name="IdField" type="uint8" defaultValue="MsgId.M0" pseudo="true" />
    </id>
    <payload name="Data" />
    <checksum name="Checksum" alg="crc-ccitt" from="Size">
        <int name="ChecksumField" type="uint16" />
    </checksum>
</frame>
```
**NOTE**, that **&lt;id&gt;** layer is still present, but its field has **pseudo** property set (`pseudo="true"`).
It means that the field is not really written / read during serialization / deserialization. 
The field is [defined](include/howto4/frame/Frame.h) using 
[comms::option::def::EmptySerialization](https://commschamp.github.io/comms_doc/structcomms_1_1option_1_1def_1_1EmptySerialization.html)
option.
```cpp
template <typename TOpt = howto4::options::DefaultOptions>
struct FrameLayers
{
    struct IdMembers
    {
        struct IdField : public
            comms::field::IntValue<
                howto4::field::FieldBase<>,
                std::uint8_t,
                comms::option::def::EmptySerialization
            >
        {
            ...
        };
        
    };
};
```
When input data is processed the **&lt;id&gt;** field is assumed to read the default value, which is **0**.

Now let's take a look at the handling code. The [server](src/ServerSession.h) is defined in its usual way, 
using polymorphic interface:
```cpp
// Common interface class for all the messages
using Message = 
    howto4::Message<
        comms::option::app::ReadIterator<const std::uint8_t*>, // Polymorphic read
        comms::option::app::WriteIterator<std::uint8_t*>, // Polymorphic write
        comms::option::app::LengthInfoInterface, // Polymorphic length calculation
        comms::option::app::IdInfoInterface, // Polymorphic message ID retrieval
        comms::option::app::NameInterface, // Polymorphic name retrieval
        comms::option::app::Handler<ServerSession> // Polymorphic dispatch
    >;
```

The [client](src/ClientSession.h) on the other side can use non-polymorphic definition:
```cpp
// Common interface class for all the messages
using Message = howto4::Message<>;
```
Preparing and sending the message out looks like this:
```cpp
void ClientSession::sendMsg()
{
    Msg msg;
    auto& propsVec = msg.field_props().value();
    propsVec.resize(3);
    propsVec[0].initField_prop1().field_val().value() = 0x12345678;
    propsVec[1].initField_prop2().field_val().value() = 1.23;
    propsVec[2].initField_prop3().field_val().value() = "hello";
    
    msg.doRefresh(); // Update the length fields.

    std::vector<std::uint8_t> output;
    output.reserve(m_frame.length(msg));
    auto writeIter = std::back_inserter(output);
    auto es = m_frame.write(msg, writeIter, output.max_size());
    if (es == comms::ErrorStatus::UpdateRequired) {
        auto updateIter = &output[0];
        es = m_frame.update(updateIter, output.size());
    }
    assert(es == comms::ErrorStatus::Success);
    sendOutput(&output[0], output.size());
}
```
**NOTE**, that the frame receives a reference to the actual message, not the 
interface, and as the 
result is capable of finding all the necessary non-polymorphic functions needed
to calculate required length and perform actual write.
