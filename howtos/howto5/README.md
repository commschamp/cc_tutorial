# How-To 5
Custom transport value containing protocol version and extra flags.

This howto demonstrates having protocol version information in message framing sharing 
its 2 bytes with extra flags which influence the way message payload is read. 

The protocol message framing for this howto is defined to be:
```
SIZE (2 bytes) | ID (1 byte) | VERSION (12 bits) + FLAGS (4 bits) | PAYLOAD
```

Having values (version and flags) in the message framing which influence how 
message payload is read and/or how message is processed requires definition of common message interface (see [schema](dsl/schema.xml)):
```xml
<fields>
    <int name="Version" type="uint16" semanticType="version" />

    <set name="InterfaceFlags" length="1">
        <bit name="B0" idx="0" />
        <bit name="B1" idx="1" />
    </set>        
</fields>

<interface name="Interface" description="Common Interface for all the messages.">
    <ref field="Version" />
    <ref field="InterfaceFlags" name="Flags" />
</interface>    
```
As a reminder to the reader the current protocol version is defined as the version of the
schema:
```xml
<schema name="howto5" endian="big" version="5">
```
The field that represents protocol version is defined with `semanticType="version"`
property. As the result it is default constructed with the default version
equal to the protocol version (see [include/howto5/field/Version.h](include/howto5/field/Version.h)):
```cpp
template <typename TOpt = howto5::options::DefaultOptions, typename... TExtraOpts>
struct Version : public
    comms::field::IntValue<
        howto5::field::FieldBase<>,
        std::uint16_t,
        TExtraOpts...,
        comms::option::def::DefaultNumValue<5U>
    >
{
    ...
};
```
In order to make the messages version dependent the generated interface code 
(see [include/howto5/Interface.h](include/howto5/Interface.h)) uses
**comms::option::def::VersionInExtraTransportFields** option to specify index 
of the field containing the protocol version:
```cpp
template <typename... TOpt>
class Interface : public
    comms::Message<
        TOpt...,
        comms::option::def::BigEndian,
        comms::option::def::MsgIdType<howto5::MsgId>,
        comms::option::def::ExtraTransportFields<InterfaceFields::All>,
        comms::option::def::VersionInExtraTransportFields<0U>
    >
{
    ...
};
```
The usage of **comms::option::def::VersionInExtraTransportFields** option requres
a version information to be a separate field inside the interface and not a member
of a `<bitfield>` like one defined and used for framing.
```xml
<fields>
    <bitfield name="VersionWithFlags">
        <ref field="Version" bitLength="12"/>
        <ref field="InterfaceFlags" name="Flags" bitLength="4" />
    </bitfield>  
</fields>

<frame name="Frame">
    <size name="Size">
        <int name="SizeField" type="uint16" />
    </size>
    <id name="Id" field="MsgId" />
    <custom name="VersionWithFlags" field="VersionWithFlags" />
    <payload name="Data" />
</frame>
```
The mismatch between having a single field in the `<frame>` and two separate
fields in the `<interface>` prevents us from using standard `<value>`
layer in the frame definition. There is a need to inject a custom
layer code, which can still use 
[comms::protocol::TransportLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1TransportValueLayer.html) (used to implement
standard `value` layer), but with extra customization (see
[dsl_src/include/howto5/frame/layer/VersionWithFlags.h](dsl_src/include/howto5/frame/layer/VersionWithFlags.h)).
```cpp
template<typename TField, typename TNextLayer, typename... TOptions>
class VersionWithFlags : public
    comms::protocol::TransportValueLayer<
        TField,
        std::numeric_limits<std::size_t>::max(), // Not used, the value doesn't matter
        TNextLayer,
        TOptions...,
        comms::option::def::ExtendingClass<VersionWithFlags<TField, TNextLayer, TOptions...> >
    >
{

protected:     
    // Re-assign the values from the field to message object
    template <typename TMsg>
    static void reassignFieldValue(TMsg& msg, const Field& field)
    {
        msg.transportField_version().value() = field.field_version().value();
        msg.transportField_flags().value() = field.field_flags().value();
    }  

    // Prepare field value to be written
    template <typename TMsg>
    static void prepareFieldForWrite(const TMsg& msg, Field& field)
    {
        field.field_version().value() = msg.transportField_version().value();
        field.field_flags().value() = msg.transportField_flags().value();
    }      
};
```
**NOTE**, that the code above uses 
[Curiously Recurring Template Pattern](https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern) 
to provide the base
[comms::protocol::TransportLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1TransportValueLayer.html) class with the 
actual extending layer type using **comms::option::def::ExtendingClass** option.

In addition it overrides the default implementation of the **reassignFieldValue()**
member function to re-assign the read field values to the message object as
well as **prepareFieldForWrite()** to prepare the field being written when
the message is serialized. The **COMMS** library tutorial contains a separate page
called [Defining Custom Transport Value Protocol Stack Layer ](https://commschamp.github.io/comms_doc/page_custom_transport_value_layer.html)
with a bite more details on the available customization.

Other aspects of this howto are described in more details in the:

- [tutorial16](../../tutorials/tutorial16) - influence of the flags from the framing on the
presence of the fields in the messages' payloads.
- [tutorial19](../../tutorials/tutorial19) - influence of the protocol version on the
presence of some fields in the messages' payloads.


