# Tutorial 21
Cast between different field types.

There maybe a case when the the same serialized bytes need to be interepreted in different ways. This tutorial
implements the following framing:

```
SIZE (2 bytes) | ID (1 byte) | FLAGS (1 byte) | PAYLOAD
```

The [schema](dsl/schema.xml) file defines two different messages `Msg1` and `Msg2`. The contents
of the messages are not important. The important part is that the `FLAGS` byte in 
the framing needs to be interpreted differently when handling the `Msg1` and `Msg2`.

As was already described in one of the previous tutorials the value which resides in the framing, but needs 
to be available when message object is handled has to be propagated to the message `<interface>`.

```xml
<fields>
    <int name="BasicFlags" type="uint8" displayName="Flags" />
</fields>

<interface name="Interface" description="Common Interface for all the messages.">
    <ref field="BasicFlags" name="Flags" />
</interface>    
    
<frame name="Frame">
    <size name="Size">
        <int name="Field" type="uint16" displayName="Size" />
    </size>
    <id name="Id" field="MsgId" />
    <value name="Flags" field="BasicFlags" interfaceFieldName="Flags" />
    <payload name="Data" />
</frame>
```

The interpretation of the flags for each message is defined as separate fields:
```xml
<set name="Msg1Flags" length="1" forceGen="true">
    <bit name="B0" idx="0" />
    <bit name="B1" idx="1" />
    <bit name="B2" idx="2" />
</set>

<bitfield name="Msg2Flags" forceGen="true">
    <enum name="EnumMem" type="uint8" bitLength="2">
        <validValue name="V0" val="0" />
        <validValue name="V1" val="1" />
        <validValue name="V2" val="2" />
        <validValue name="V3" val="3" />
    </enum>
    <int name="IntMem" type="uint8" bitLength="6" />
</bitfield>  
```
Note the presence of **forceGen** property. It forces the code generator to 
generate the definition of the field when it's not referenced anywhere in the 
schema.

When sending `Msg1` and `Msg2` the [ClientSession](src/ClientSession.cpp) uses
[comms::field_cast()](https://commschamp.github.io/comms_doc/cast_8h.html) stand alone function
to cast between the fields values:
```cpp
void ClientSession::sendMsg1()
{
    Msg1 msg;

    // prepare flags of Msg1
    using Msg1Flags = tutorial21::field::Msg1Flags<ClientProtocolOptions>;
    Msg1Flags flags;
    flags.setBitValue_B1(true);

    // Assign the flags
    msg.transportField_flags() = comms::field_cast<Message::TransportField_flags>(flags);
    
    sendMessage(msg);
}

void ClientSession::sendMsg2()
{
    Msg2 msg;

    // prepare flags of Msg2
    using Msg2Flags = tutorial21::field::Msg2Flags<ClientProtocolOptions>;
    Msg2Flags flags;
    flags.field_enumMem().value() = Msg2Flags::Field_enumMem::ValueType::V1;
    flags.field_intMem().value() = 111;

    // Assign the flags
    msg.transportField_flags() = comms::field_cast<Message::TransportField_flags>(flags);
    
    sendMessage(msg);
}
```

When the same messages are received back from the echo server, the cast is performed in opposite
direction:
```cpp
void ClientSession::handle(Msg1& msg)
{
    ...
    using Msg1Flags = tutorial21::field::Msg1Flags<ClientProtocolOptions>;
    auto flags = comms::field_cast<Msg1Flags>(msg.transportField_flags());
    printSetField(flags);
    ...
}

void ClientSession::handle(Msg2& msg)
{
    ...
    using Msg2Flags = tutorial21::field::Msg2Flags<ClientProtocolOptions>;
    auto flags = comms::field_cast<Msg2Flags>(msg.transportField_flags());
    printEnumField(flags.field_enumMem());
    printIntField(flags.field_intMem());
    ...
}
```

The **comms::field_cast()** function is defined in [comms/cast.h](https://commschamp.github.io/comms_doc/cast_8h.html)
file. Relevant include statement may be required:
```cpp
#include "comms/cast.h"
```

**IMPORTANT**: For the cast operation to be successful the field types must have the 
same length.

According to the function documentation, the [COMMS Library](https://github.com/commschamp/comms) 
performs some compile time analysis and will do a simple `static_cast` between the contained values 
if their value types are convertible. Otherwise the write + read operations will be performed, i.e. the source field 
will be written into a temporary buffer, and the target field will perform a read operation from that buffer. 

In case of this tutorial the conversion between `BasicFlags` and `Msg1Flags` flags is simple `static_cast` 
(because their inner `ValueType` types are convertible), 
while conversion between `BasicFlags` and `Msg2Flags` will be performed using write to and read from 
a temporary buffer (because their inner `ValueType` types are NOT convertible).

## Summary

- Cast between fields of different types is performed using **comms::field_cast()**
  stand alone function defined in [comms/cast.h](https://commschamp.github.io/comms_doc/cast_8h.html)
- For the cast to be successful the fields must be of the same length.
- The [COMMS Library](https://github.com/commschamp/comms) implements the field cast using 
  `static_cast` when field's inner `ValueType` types are convertible and uses temporary buffer
  with write / read operations when such conversion is not possible.

[Read Previous Tutorial](../tutorial20) &lt;-----------------------&gt; [Read Next Tutorial](../tutorial22) 
