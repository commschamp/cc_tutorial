# Tutorial 3
Working with scaling and units in numeric fields.

## Scaling
Many protocols need to report non-integral values but don't allow usage of floating point encoding when serializing their fields.
Usually such values are serialized as integral ones which treated as 
[fixed point values](https://en.wikipedia.org/wiki/Fixed-point_arithmetic) with predefined scaling multiplier, i.e. predefined 
number of digits after decimal points.

To help with such cases [CommsDSL](https://github.com/arobenko/CommsDSL-Specification) has
**scaling** property applicable to **&lt;int&gt;** fields. Message `Msg1` (defined in [dsl/schema.xml](dsl/schema.xml) 
and implemented inside [include/tutorial3/message/Msg1.h](include/tutorial3/message/Msg1.h)) comes to
demostrate definition of such fields.

The message and its fields are defined in the following way:
```xml
<message name="Msg1" id="MsgId.M1" displayName="^Msg1Name">
    <int name="F1" type="uint16" scaling="1/1000" />
    <int name="F2" type="int32" scaling="1/1000000" />
</message>
```
The **scaling** property defines rational number fraction on which the stored integral value needs to get
multiplied in order the receive required floating point value. Also the 
[comms::field::IntValue](https://arobenko.github.io/comms_doc/classcomms_1_1field_1_1IntValue.html) class
used to implement defined **&lt;int&gt;** fields provides `getScaled()` and `setScaled()` member functions
which allow retrieving and setting proper floating point values taking the scaling ratio into account.
```cpp
void ClientSession::sendMsg1()
{
    Msg1 msg;

    msg.field_f1().setScaled(1.234f);
    assert(msg.field_f1().value() == 1234);

    msg.field_f2().setScaled(12.345678);
    assert(msg.field_f2().value() == 12345678);

    sendMessage(msg);
}
```
Note that field's stored value (accessed by `.value()`) is an integral one. When floating point value
gets assigned using `.setScaled()` member function, then it's automatically multiplied by the scaling
ratio and then cast to the storage integral type which drops the remaining fraction part if such exists.

Also note that the scaling fraction is a meta-information of the protocol definition and it does 
**NOT** get reported to the other side anywhere in the field / message payload.

The `void ClientSession::handle(Msg1& msg)` function prints the received message contents echoed back from the server.
The floating point values are retrieved using `getScaled<ret_type>()` member function which receives a template parameter
specifying the result type.

The output printed by the handling function looks like this:
```
Received "Message 1" with ID=1
    F1 = 1.234000 (orig = 1234)
    F2 = 12.345678 (orig = 12345678)
```

---

**SIDE NOTE**: Please pay attention to the way of how **displayName** property is set to the values of
`MsgId` **&lt;enum&gt;** field as well as messages themselves.
```xml

<fields>
    <string name="Msg1Name" defaultValue="Message 1" />
    <string name="Msg2Name" defaultValue="Message 2" />
    <string name="Msg3Name" defaultValue="Message 3" />
        
    <enum name="MsgId" type="uint8" semanticType="messageId">
        <validValue name="M1" val="1" displayName="^Msg1Name" />
        <validValue name="M2" val="2" displayName="^Msg2Name" />
        <validValue name="M3" val="3" displayName="^Msg3Name" />
    </enum>
</fields>

<message name="Msg1" id="MsgId.M1" displayName="^Msg1Name">
    ...
</message>

<message name="Msg2" id="MsgId.M2" displayName="^Msg2Name">
    ...
</message>  

<message name="Msg3" id="MsgId.M3" displayName="^Msg3Name">
    ...
</message>       
```
The **id** property of every message is expected to be a numeric value. However, the
[CommsDSL](https://github.com/arobenko/CommsDSL-Specification) allows usage of 
reference strings as well. In the case above they reference the defined **&lt;validValue&gt;**-s
of the `MsgId` field. The value of the **displayName** property needs to be
as string. [CommsDSL](https://github.com/arobenko/CommsDSL-Specification) allows
referencing of common definitions for strings as well. 
There must be a way to differentiate between an actual string value and a reference to other
field. The [CommsDSL](https://github.com/arobenko/CommsDSL-Specification) specifies that
a reference to other field in such case (when value needs to be a string) is prefixed with
`^` character. 

As the result the `Msg1` and `MsgId.M1` (`Msg2` and `MsgId.M2`, `Msg3` and `MsgId.M3`) 
have the same **displayName** property value. The change to **defaultValue** of `Msg1Name` (`Msg2Name`, `Msg3Name`)
automatically propagates to relevant fields.

Also note that `Msg1Name`, `Msg2Name`, `Msg3Name` are there to define some common string values used by other fields, 
they are **NOT** **really** referenced and/or aliased by other fields. As the result the generated code does 
**NOT** have definitions for these fields.
---

## Units
TODO

[Read Previous Tutorial](../tutorial2) &lt;-----------------------&gt; [Read Next Tutorial](../tutorial4) 
