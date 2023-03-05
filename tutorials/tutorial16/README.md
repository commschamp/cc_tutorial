# Tutorial 16
Extra values in transport framing.

Some protocols define member fields common to all the messages and move them into transport framing instead of
having them as normal members of message payload. Such fields may influence the way how the 
message payload decoded and/or handled.

The [CommsChampion Ecosystem](https://commschamp.github.io) completely separates message framing and message
contents. As the result the proper handling of such scenarios may be a bit challenging. It is solved by
making such extra fields (from the transport framing) to be a member of common message interface. The schema
file(s) of the previous tutorials didn't contain any special common message interface definition. The 
generated code created the default empty `Message` class which was reused to define application specific 
common message interface. The [schema](dsl/schema.xml) file of this tutorial contains the following 
definition:
```xml
<fields>
    ...
    
    <set name="InterfaceFlags" length="1">
        <bit name="B0" idx="0" />
        <bit name="B1" idx="1" />
        <bit name="B2" idx="2" />
        <bit name="B3" idx="3" />        
    </set>
    
</fields>

<interface name="Interface" description="Common Interface for all the messages.">
    <ref field="InterfaceFlags" name="Flags" />
</interface>
```
The code generated for such interface class resides in [include/tutorial16/Interface.h](include/tutorial16/Interface.h).
```cpp
struct InterfaceFields
{
    struct Flags : public
        tutorial16::field::InterfaceFlags<
            tutorial16::options::DefaultOptions
        >
    {
        ...
    };
    
    /// @brief All the fields bundled in std::tuple.
    using All = std::tuple<
        Flags
    >;
};

template <typename... TOpt>
class Interface : public
    comms::Message<
        TOpt...,
        comms::option::def::BigEndian,
        comms::option::def::MsgIdType<tutorial16::MsgId>,
        comms::option::def::ExtraTransportFields<InterfaceFields::All>
    >
{
    ...
public:
    COMMS_MSG_TRANSPORT_FIELDS_NAMES(
        flags
    );
};
```
The defined interface class extends [comms::Message](https://commschamp.github.io/comms_doc/classcomms_1_1Message.html) like 
all other interfaces but also uses `comms::option::def::ExtraTransportFields` option to define the extra transport fields
it's going to contains as well as uses `COMMS_MSG_TRANSPORT_FIELDS_NAMES()` macro to set convenience access names for them.
It's very similar to [COMMS_MSG_FIELDS_NAMES()](https://commschamp.github.io/comms_doc/classcomms_1_1MessageBase.html) one
which is used to set names of the normal message payload fields.

For every name **X** the `COMMS_MSG_TRANSPORT_FIELDS_NAMES()` macro defines the following enum value as well as access
member functions:
```cpp
template <typename... TOpt>
class Interface : public
    comms::Message<...>
{
    using Base = ...
public:
    enum TransportFieldIdx {
        ...
        TransportFieldIdx_X, // Index of the field in the containing tuple
        ...
    };
 
    // Field access
    auto transportField_X() -> decltype(std::get<TransportFieldIdx_X>(Base::transportFields()))
    {
        return std::get<TransportFieldIdx_X>(Base::transportFields());
    }
 
    // Const field access
    auto transportField_X() const -> decltype(std::get<TransportFieldIdx_X>(Base::transportFields()))
    {
        return std::get<TransportFieldIdx_X>(Base::transportFields());
    }
};
```
**IMPORTANT**: The fields of the message interface are only the value holders, they are **not** getting 
serialized when `write()` operation of the message is invoked. When `read()` operation on the 
message is invoked, it is assumed that the transport fields already have correct values assigned
and can be accessed if needed. It is the job of the message framing to assign such values when 
they are known and message object is created, **before** the payload of the message being read.

----

**SIDE NOTE**: When schema file does not contain any **&lt;interface&gt;** definition the 
empty one is assumed having the `Message` **name**, i.e. equivalent to the following definition:
```xml
<interface name="Message">
    <!-- No fields -->
</interface>
```
That's why the common interface class in all the previous tutorials was defined as
`<namespace>::Message` class inside the `include/<namespace>/Message.h` file.

For this tutorial the common interface class is defined as 
`tutorial16::Interface` class inside the [include/tutorial16/Interface.h](include/tutorial16/Interface.h)
file and both [src/ClientSession.h](src/ClientSession.h) and [src/ServerSession.h](src/ServerSession.h) 
define their common message interface class by aliasing `tutorial16::Interface` class:
```cpp
using Message = 
    tutorial16::Interface<
        ...        
    >;
```

----

The message frame is defined like this:
```xml
<frame name="Frame">
    <size name="Size">
        <int name="SizeField" type="uint16" />
    </size>
    <value name="Flags" interfaceFieldName="Flags">
        <ref field="InterfaceFlags" name="Field" />
    </value>        
    <id name="Id" field="MsgId" />
    <payload name="Data" />
</frame>
```
The [&lt;value&gt;](https://commschamp.github.io/commsdsl_spec/#frames-value) layer represents extra values
to be re-assigned to the message interface. Note usage of **interfaceFieldName** property, which specifies 
the **name** of the relevant field inside the **&lt;interface&gt;**, value of which needs to be assigned.

----

**SIDE NOTE**: The [CommsDSL](https://github.com/commschamp/CommsDSL-Specification) describes usage of **interfaces**
property to specify the list of the interfaces it supports. It's applicable to the situation when the protocol schema
file(s) contain multiple **&lt;interface&gt;** definitions. It is not the case for this tutorial, hence the 
usage of **interfaces** property is omitted.

----

The **&lt;value&gt;** layer is implemented by extending 
[comms::protocol::TransportValueLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1TransportValueLayer.html)
(see [include/tutorial16/frame/Frame.h](include/tutorial16/frame/Frame.h)).
```cpp
template <typename TOpt = tutorial16::options::DefaultOptions>
struct FrameLayers
{
    ...
    /// @brief Definition of layer "Flags".
    template <typename TMessage, typename TAllMessages>
    using Flags =
        comms::protocol::TransportValueLayer<
            typename FlagsMembers::Field,
            0U,
            Id<TMessage, TAllMessages>
        >;
    
    ...
};
```

----

**SIDE NOTE**: In this particular tutorial the **&lt;value&gt;** layer precedes the **&lt;id&gt;** one,
which creates a situation when the extra transport value is known **before** the message object is created
(by the **&lt;id&gt;** layer) and cannot be re-assigned to appropriate message object right away.
The [COMMS Library](https://github.com/commschamp/comms) contains inner 
~~magic~~ **compile-time** logic which identifies such scenario and results in some kind of `read()` multi-pass
between the layers (excluding the **&lt;payload&gt;** one) to allow the **&lt;value&gt;** layer to assign the 
transport values to the created message object **before** the `read()` operation is forwarded to the **&lt;payload&gt;**
layer. It's just inner implementation details of the [COMMS Library](https://github.com/commschamp/comms) and 
the integrating developer doesn't need to worry about it.

----

Now, let's dive into the definition of the messages themselves:
```xml
<message name="Msg1" id="MsgId.M1" displayName="^Msg1Name">
    <int name="F1" type="uint16" />
    <int name="F2" type="uint16" />
    <optional name="F3" defaultMode="missing" cond="%Flags.B0">
        <int name="Field" type="uint16" displayName="F3" />
    </optional>
</message>

<message name="Msg2" id="MsgId.M2" displayName="^Msg2Name">
    <string name="F1" defaultValue="hello">
        <lengthPrefix>
            <int name="Length" type="uint8" />
        </lengthPrefix>
    </string>
    
    <optional name="F2" defaultMode="missing" cond="%Flags.B1">
        <int name="Field" type="uint16" displayName="F2" />
    </optional>        
</message>   
```
The `F3` field of the `Msg1` is defined as **&lt;optional&gt;** and is expected to exist only 
if `B0` inside the `Flags` is set. The `F2` of the `Msg` also defined as 
**&lt;optional&gt;** and is expected to exist only if `B1` inside the `Flags` is set. 
Since version **v6.0** the [CommsDSL](https://github.com/commschamp/CommsDSL-Specification)
allows referencing interface fields prefixing the reference string with `%` character.

----

**WARNING**: The [CommsDSL](https://github.com/commschamp/CommsDSL-Specification) specification 
supports multiple interfaces and doesn’t impose any restriction on how they are used in the end 
application. The schema parser is responsible to do a check that **any** (not all) of the previously 
encountered <interface>-es contains the referenced field.
The code generator also does not impose many restrictions on such references. Usage of the wrong
<interface> class with the missing referenced field in the end application may result in compilation
errors.

----


**NOTE** that the **defaultMode** of the both optional fields are set to **missing** in order to allow
default constructions of the message objects to end up being in the consistent state (without any 
need for **refresh**), because the 
default constructed `Flags` member field of the **&lt;interface&gt;** has its bits cleared.

Now let's take a look how the message(s) are prepared to be sent out by the [ClientSession](src/ClientSession.cpp):
```cpp
void ClientSession::sendMsg1()
{
    Msg1 msg;
    assert(msg.field_f3().isMissing()); // F3 is missing when default constructed

    msg.field_f1().value() = 1111;
    msg.field_f2().value() = 2222;
    msg.field_f3().field().value() = 1234;
    msg.transportField_flags().setBitValue_B0(true);

    msg.doRefresh(); // Bring everything into consistent state
    assert(msg.field_f3().doesExist()); // F3 must exist after refresh
    
    sendMessage(msg);
}
```
The code above sets `B0` in the message interface flags then calls `doRefresh()` member 
function of the message object to bring the message into a consistent state, which 
updates mode of the `F3` field.

When the whole message is serialized by the **frame**, the value of `Flags` is retrieved by the 
**&lt;value&gt;** ([comms::protocol::TransportValueLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1TransportValueLayer.html))
and properly written in the correct place in the frame.

In addition to allowing referencing of the **&lt;interface&gt;** fields in the **cond** properties,
the **v6.0** of the [CommsDSL](https://github.com/commschamp/CommsDSL-Specification) specification
allows using similar syntax to assign values to the **&lt;interface&gt;** fields in the
constructor of the relevant **&lt;message&gt;** class using the **construct** property.
```xml
<message name="Msg3" id="MsgId.M3" displayName="^Msg3Name" construct="%Flags.B2" ...>
    <int name="F1" type="uint16" />
</message>
```

The generated `Msg3` constructor code (in the [include/tutorial16/message/Msg3.h](include/tutorial16/message/Msg3.h))
looks like this:
```cpp
Msg3()
{
    Base::transportField_flags().setBitValue_B2(true);
}
```
The **construct** property use the same syntax as the **cond** one, but with limitations. Only bit references
and equality statements are allowed.

Multiple **construct** properties are supported as the **&lt;construct&gt;** child node with a single
**&lt;and&gt;** child:
```xml
<message name="Msg4" id="MsgId.M4" displayName="^Msg4Name" ...>
    <construct>
        <and>
            <construct value="%Flags.B2" />
            <construct value="%Flags.B3" />
        </and>
    </construct>
    ...
</message>
```
The generated `Msg4` constructor code (in the [include/tutorial16/message/Msg4.h](include/tutorial16/message/Msg3.h))
looks like this:
```cpp
Msg4()
{
    Base::transportField_flags().setBitValue_B2(true);
    Base::transportField_flags().setBitValue_B3(true);
}
```

The [CommsDSL](https://github.com/commschamp/CommsDSL-Specification) also supports a check that the
**&lt;interface&gt;** fields have particular value in the **read** operation before proceeding to
reading the message payload (inner fields). It is performed using the **readCond** property.
```xml
<message name="Msg3" id="MsgId.M3" ... readCond="%Flags.B2">
    ...
</message>
```
The **readCond** property uses the same syntax as the previously mention **cond** of the **&lt;optional&gt;** field.
The generated **read** functionality of the [Msg3](include/tutorial16/message/Msg3.h) looks like this:
```cpp
/// @brief Generated read functionality.
template <typename TIter>
comms::ErrorStatus doRead(TIter& iter, std::size_t len)
{
    bool validRead =
        Base::transportField_flags().getBitValue_B2();

    if (!validRead) {
        return comms::ErrorStatus::InvalidMsgData;
    }

    return Base::doRead(iter, len);
}
```
Quite often **readCond** property value will be the same as the **construct** one. To avoid unnecessary code
duplication the [CommsDSL](https://github.com/commschamp/CommsDSL-Specification) specification introduced
**constructAsReadCond** property with boolean value.
```xml
<message name="Msg4" id="MsgId.M4" displayName="^Msg4Name" constructAsReadCond="true">
    <construct>
        <and>
            <construct value="%Flags.B2" />
            <construct value="%Flags.B3" />
        </and>
    </construct>
    ...
</message>
```
It is equivalent to having the following definition:
```xml
<message name="Msg4" id="MsgId.M4" displayName="^Msg4Name">
    <construct>
        <and>
            <construct value="%Flags.B2" />
            <construct value="%Flags.B3" />
        </and>
    </construct>
    <readCond>
        <and>
            <readCond value="%Flags.B2" />
            <readCond value="%Flags.B3" />
        </and>
    </readCond>
    ...
</message>
```
The generated **read** functionality of the [Msg4](include/tutorial16/message/Msg4.h) looks like this:
```cpp
/// @brief Generated read functionality.
template <typename TIter>
comms::ErrorStatus doRead(TIter& iter, std::size_t len)
{
    bool validRead =
        ((Base::transportField_flags().getBitValue_B2()) &&
         (Base::transportField_flags().getBitValue_B3()));

    if (!validRead) {
        return comms::ErrorStatus::InvalidMsgData;
    }

    return Base::doRead(iter, len);
}
```

## Summary
- When there is a common value for all the messages that resides in message framing, the 
  **&lt;value&gt;** framing layer needs to be used.
- The **&lt;value&gt;** framing layer is implemented by extending 
  [comms::protocol::TransportValueLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1TransportValueLayer.html) class.
- In many cases such transport value has an influence on how message payload is decoded and/or the message is handled.
  To allow transfer of the information to message object custom **&lt;interface&gt;** needs to be defined.
- The common fields defined as members of the **&lt;interface&gt;** are **NOT** getting serialized as part 
  of message payload, only by the **&lt;value&gt;** framing layer.
- Referencing **&lt;interface&gt;** fields is allowing using `%` character prefix.
- Use **construct** property (or **&lt;construct&gt;** node) to specify extra construction requirements.
- Use **readCond** property (or **&lt;readCond&gt;** node) to specify reading conditions that take place before reading of the payload.

[Read Previous Tutorial](../tutorial15) &lt;-----------------------&gt; [Read Next Tutorial](../tutorial17) 
