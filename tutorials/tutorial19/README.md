# Tutorial 19
Introduction to protocol version support.

Many protocols allow extensions by adding new messages and/or new fields to the existing messages 
in the future versions of the protocols. In order to properly support forward / backward 
compatibility of the protocol there may be a report of the used version number in the message 
frame and/or in one of the exchanged messages. This tutorial will focus on the case which 
reports a version of every message in the frame (because it's simpler), the case of reporting 
a protocol version in one of the messages will be covered in the [next](../tutorial20) tutorial.

The protocol version support starts with declaring the current (latest) version of the 
protocol as the [schema](dsl/schema.xml) **version** property.
```xml
<?xml version="1.0" encoding="UTF-8"?>
<schema name="tutorial19" endian="big" version="5">
    ...
</schema>
```
The [CommsDSL](https://github.com/arobenko/CommsDSL-Specification) defines value of the **version** property 
as [unsigned numeric](https://arobenko.github.io/commsdsl_spec/#intro-numeric) one. If there is a need 
to define a version as [semantic](https://semver.org/) one, then it is recommended to mentally split the 
version number into bytes and use something like `version="0x105` (for version 1.5) or 
`version=0x10502` (for version 1.5.2).

The version information can be added to message fields using **senceVersion** and **deprecated** properties:
```xml
<message name="Msg1" id="MsgId.M1" displayName="^Msg1Name">
    <int name="F1" type="uint16" />
    <int name="F2" type="uint16" sinceVersion="2" deprecated="4" />
    <int name="F3" type="uint16" sinceVersion="5" />
</message>
```
Note that value of the **sinceVersion** may not exceed the value of the schema's **version** property, 
and value of the **deprecated** must be greater than the value of the **sinceVersion**. 

The omitted **sinceVersion** value defaults to **0**, i.e. first version of the protocol or the 
first version when the message was added to the protocol.

**IMPORTANT**: The **deprecated** fields are **NOT** removed from the serialization in order to properly
support backward compatibility of the protocol. In order the forcefully remove the **deprecated** field from
being serialized there is a need to add usage of **removed** property (`removed="true"`). Be careful though,
removing deprecated field may break backward compatibility of the protocol.

The **sinceVersion** and **deprecated** properties are applicable to the whole messages as well:
```xml
<message name="Msg3" id="MsgId.M3" displayName="^Msg3Name" sinceVersion="2">
    ... 
    <int name="F4" type="uint16" sinceVersion="3" />
</message> 
```
In such case the value of the **sinceVersion** applied to the member field must be greater than the 
value of the **sinceVersion** applied to the message definition.

The version dependent presence of the fields requires knowledge of the reported version number attached 
to the message object before the message payload is deserialized (fields are read). The usual way of 
attaching such information is to have a common interface class with extra fields being defined:
```xml
<interface name="Interface" description="Common Interface for all the messages.">
    <int name="Version" type="uint16" semanticType="version" />
</interface> 
```
Note usage of **semanticType** property, which specifies the special role of the field. In this case 
the field is used to hold protocol version. The message payload deserialization will take it
into account when needed.

Also the implicit **defaultValue** of the _version_ (marked with `semanticType="version"`) is
equal to the version of the schema.
```cpp
struct Version : public
    comms::field::IntValue<
        ...,
        comms::option::def::DefaultNumValue<5U>
    >
{
    ...
};
```

----

**SIDE NOTE**: In case the defined **&lt;interface&gt;** does not have version field (marked 
with `semanticType="version"`) the generated code won't be really version dependent, and all 
**sinceVersion** and **deprecated** properties will be ignored.

----

As was already mentioned earlier this tutorial will report a version for every message as part of the 
message framing. In order to re-assign the value from the frame to the message object usual 
**&lt;value&gt;** layer can be used:
```xml
<frame name="Frame">
    <size name="Size">
        <int name="Field" type="uint16" displayName="Size" />
    </size>
    <value name="Version" interfaceFieldName="Version">
        <int name="Field" type="uint16" semanticType="version" displayName="Version"/>
    </value>        
    <id name="Id" field="MsgId" />
    <payload name="Data" />
</frame>
```
**REMINDER**: The value of **interfaceFieldName** property needs to contain a name of the 
field inside the **&lt;interface&gt;** to which it needs to be re-assigned.

Now it's time to take a closer look at the generated code. Let's take a look at the 
generated common interface class:
```cpp
template <typename... TOpt>
class Interface : public
    comms::Message<
        TOpt...,
        comms::option::def::BigEndian,
        comms::option::def::MsgIdType<tutorial19::MsgId>,
        comms::option::def::ExtraTransportFields<InterfaceFields::All>,
        comms::option::def::VersionInExtraTransportFields<0U>
    >
{
public:
    COMMS_MSG_TRANSPORT_FIELDS_NAMES(
        version
    );
};
```
Please note the usage of [comms::option::def::VersionInExtraTransportFields](https://arobenko.github.io/comms_doc/options_8h.html)
option. It is used to specify index of the transport field containing the version information. 
It also creates [version()](https://arobenko.github.io/comms_doc/classcomms_1_1Message.html) member function which is 
basically an alias to `transportField_version().value()`. They can be used interchangeably.

Now let's take a look how version dependent fields are defined in the generated code. Let's take a look at 
the definition of `F2` inside [include/tutorial19/message/Msg1.h](include/tutorial19/message/Msg1.h).
```cpp
struct F2Field : public
    comms::field::IntValue<
        tutorial19::field::FieldBase<>,
        std::uint16_t
    >
{
    /// @brief Name of the field.
    static const char* name()
    {
        return tutorial19::message::Msg1FieldsCommon::F2Common::name();
    }
    
};

struct F2 : public
    comms::field::Optional<
        F2Field,
        comms::option::def::ExistsByDefault,
        comms::option::def::ExistsSinceVersion<2U>
    >
{
    /// @brief Name of the field.
    static const char* name()
    {
        return F2Field::name();
    }
};
```
Due to the fact that the version dependent field may or may not exist then it has to be defined as 
[comms::field::Optional](https://arobenko.github.io/comms_doc/classcomms_1_1field_1_1Optional.html).
Its version information since which the field must exist is defined using 
[comms::option::def::ExistsSinceVersion](https://arobenko.github.io/comms_doc/options_8h.html) option.
The actual field being wrapped by the [comms::field::Optional](https://arobenko.github.io/comms_doc/classcomms_1_1field_1_1Optional.html)
is defined as `F2Field` (**Field** suffix is added to the field's name). It is equivalent to the following pseudo definition:
```xml
<optional name="F2" cond="_version_ &gt;= 2">
    <int name="F2Field" type="uint16" />
</optional>
```
Note that the definition above is invalid (you cannot put a condition on the protocol version), it is just to 
demonstrate the idea.

The preparation of the `Msg1` to be sent out is the usual way of working with optional fields:
```cpp
void ClientSession::sendMsg1()
{
    Msg1 msg;
    assert(msg.version() == 5U); // Schema version by default

    // The version based optional fields must exist by default
    assert(msg.field_f2().doesExist());
    assert(msg.field_f3().doesExist());
    
    msg.field_f1().value() = 1111;
    msg.field_f2().field().value() = 2222;
    msg.field_f3().field().value() = 3333;

    msg.version() = 3U;
    msg.doRefresh(); // Update version fields;

    assert(msg.field_f2().doesExist());
    assert(msg.field_f3().isMissing()); // Does not exist for version 3    
    
    sendMessage(msg);
}
```
Note that every message is default constructed to the valid state of the latest (current) 
version of the schema. In this tutorial the version of the message which is going to be 
sent out is forcefully set to be **3**. After call to `doRefresh()`, which brings message to 
the consistent state, the `F3` field is marked as "missing". The message is echoed back 
by the **server** and successfully received by the **client** and processed by the 
`void ClientSession::handle(Msg1& msg)`. The printed output is correct:
```
Received message "Message 1" with ID=1 and version=3
        F1 = 1111
        F2 (exists)
                F2 = 2222
        F3 (missing)
```

Let's also take a closer look at the definition of `Msg2`.
```xml
<message name="Msg2" id="MsgId.M2" displayName="^Msg2Name">
    <enum name="F1" type="uint8" sinceVersion="1">
        <validValue name="V0" val="0" />
        <validValue name="V1" val="1" sinceVersion="3" deprecated="5" />
        <validValue name="V2" val="2" sinceVersion="4" />
    </enum>
    
    <enum name="F2" type="uint8" sinceVersion="3" validCheckVersion="true">
        <validValue name="V0" val="0" />
        <validValue name="V1" val="1" sinceVersion="4" deprecated="5" />
        <validValue name="V2" val="2" sinceVersion="5" />
    </enum>        
</message>
```
Every **&lt;validValue&gt;** of the **&lt;enum&gt;** field can also have 
version information specified with **sinceVersion** and/or **deprecated** properties.
In most cases such version information is for documentation purposes only and doesn't 
have any influence on the generated code, i.e. all the deprecated and 
newly introduced **&lt;validValue&gt;** are considered valid ones 
**unless** **validCheckVersion** property is set to **true**. In such case 
(`F2` in the example above) the code generator creates special code for the 
`valid()` member function of the field to check the validity of the value 
based on the reported protocol version:
```cpp
template <typename TOpt = tutorial19::options::DefaultOptions>
struct Msg2Fields
{
    /// @brief Inner field of @ref F1 optional.
    /// @see @ref tutorial19::message::Msg2FieldsCommon::F1Val
    class F1Field : public
        comms::field::EnumValue<
            tutorial19::field::FieldBase<>,
            tutorial19::message::Msg2FieldsCommon::F1Val,
            comms::option::def::ValidNumValueRange<0, 2>
        >
    {
        ...
    };
    
    ...
    
    class F2Field : public
        comms::field::EnumValue<
            tutorial19::field::FieldBase<>,
            tutorial19::message::Msg2FieldsCommon::F2Val,
            comms::option::def::VersionStorage,
            comms::option::def::InvalidByDefault
        >
    {

    public:
        
        /// @brief Validity check function.
        bool valid() const
        {
            if (Base::valid()) {
                return true;
            }
        
            if (3U <= Base::getVersion()) {
                if (Base::value() == static_cast<typename Base::ValueType>(0)) {
                    return true;
                }
            }
            
            if ((4U <= Base::getVersion()) &&
                (Base::getVersion() < 5U)) {
                if (Base::value() == static_cast<typename Base::ValueType>(1)) {
                    return true;
                }
            }
            
            if (5U <= Base::getVersion()) {
                if (Base::value() == static_cast<typename Base::ValueType>(2)) {
                    return true;
                }
            }
            
            return false;
        }
        
    };
    
    ...
};
```
The same thing is applicable to the **&lt;set&gt;** field with its **&lt;bit&gt;**-s. 
Every specified **&lt;bit&gt;** (regardless of the version it has been introduced) is 
considered to be valid (non-reserved) unless **validCheckVersion** property is set, 
which will result is the generation of the special `valid()` member function.

Another important aspect is demonstrated by the `Msg3`:
```xml
<message name="Msg3" id="MsgId.M3" displayName="^Msg3Name" sinceVersion="2">
    <set name="F1" length="1">
        <bit name="B0" idx="0" />
        <bit name="B1" idx="1" />
    </set>
    <optional name="F2" cond="$F1.B0" defaultMode="missing">
        <int name="Field" type="uint16" displayName="F2" />
    </optional>
    <optional name="F3" cond="$F1.B1" defaultMode="missing">
        <int name="Field" type="uint16" displayName="F3" />
    </optional>   
    <int name="F4" type="uint16" sinceVersion="3" />
</message> 
```
In this example the presence of `F2` and `F3` depends on the values of bits 
inside `F1` (unrelated to the protocol version) while the 
presence of the `F4` depends on the reported protocol version. Such message definition requires 
custom `Msg3::doRead()` member function generation.
```cpp
template <typename TMsgBase, typename TOpt = tutorial19::options::DefaultOptions>
class Msg3 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::def::StaticNumIdImpl<tutorial19::MsgId_M3>,
        comms::option::def::FieldsImpl<typename Msg3Fields<TOpt>::All>,
        comms::option::def::MsgType<Msg3<TMsgBase, TOpt> >,
        comms::option::def::HasName,
        comms::option::def::HasCustomRefresh
    >
{
    
public:
    ...
    template <typename TIter>
    comms::ErrorStatus doRead(TIter& iter, std::size_t len)
    {
        Base::doFieldsVersionUpdate();
        
        ...
    }
    
    ... // Code that properly deserializes fields
    
};
```
Note the call of the `doFieldsVersionUpdate()` provided by the 
[comms::MessageBase](https://arobenko.github.io/comms_doc/classcomms_1_1MessageBase.html).
It updates the modes of all the version based [comms::field::Optional](https://arobenko.github.io/comms_doc/classcomms_1_1field_1_1Optional.html)
fields. It means that in case **custom** read code functionality is injected to the code 
generator, it needs to call `Base::doFieldsVersionUpdate()` at the beginning of the function in 
case there are version dependent fields.

----

**SIDE NOTE**: The [commsdsl2comms](https://github.com/arobenko/commsdsl) code generator 
allows selecting a [minimal remote version](https://github.com/arobenko/commsdsl/wiki/commsdsl2comms-Manual#selecting-minimal-remote-version),
which means all the possible remote endpoints won't use any earlier version then specified. In such 
case all version dependent fields that where introduced before the specified version will be implemented
as normal fields, not as [comms::field::Optional](https://arobenko.github.io/comms_doc/classcomms_1_1field_1_1Optional.html)
ones for improved run-time and code size performance.

----

## Summary
- To specify version of the protocol (schema) assign **version** property of the **&lt;schema&gt;**.
- Newly introduced field and/or message need to specify version when it happened using **sinceVersion** property.
- The deprecated fields should be marked with **deprecated**.
- By default deprecated fields are not removed to maintain backward compatibility of the protocol. In order to
  forcefully remove it use `removed="true"` property assignment.
- In order to let the [commsdsl2comms](https://github.com/arobenko/commsdsl) generate the version dependent
  code, the **&lt;interface&gt;** needs to contain a field marked as version (having `semanticType="version"`
  property assignment).
- Use usual **&lt;value&gt;** framing layer when version is reported as a field inside the transport frame.
- All the version dependent fields are implemented as 
  [comms::field::Optional](https://arobenko.github.io/comms_doc/classcomms_1_1field_1_1Optional.html) fields.
- All the **&lt;validValue&gt;**-s of the **&lt;enum&gt;** field are considered to be valid (regardless of 
  the version they where introduced or their deprecation status) as well as all the **&lt;bit&gt;**-s of the 
  **&lt;set&gt;** field are considered to be not reserved unless **validCheckVersion** property is set to 
  **true**. In this case the generated `valid()` member function will take the version into account.
- When custom `doRead()` member function is injected into the version dependent message, it must call
  [Base::doFieldsVersionUpdate()](https://arobenko.github.io/comms_doc/classcomms_1_1MessageBase.html)
  to properly update the modes of the version dependent 
  [comms::field::Optional](https://arobenko.github.io/comms_doc/classcomms_1_1field_1_1Optional.html)
  fields.


[Read Previous Tutorial](../tutorial18) &lt;-----------------------&gt; [Read Next Tutorial](../tutorial20) 
