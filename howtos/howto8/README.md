# How-To 8
Optional fields in message framing.

There are protocols that may contain some extra optional fields as part of message 
framing, presence of which is determined by some other condition, for example
some bit is set in one of the preceding framing fields.

This howto uses the following frame:
```
SIZE (2 bytes) | ID | FLAGS (optional 1 byte) | PAYLOAD
```
Where `ID` is 7 bit numeric ID with most significant bit indicating presence of the optional `FLAGS` 
that might follow. The value of `FLAGS` may have an influence on presence of some fields in the
`PAYLOAD`.

Due to the fact that the value of `FLAGS` may have an influence on how the message payload 
is read/processes, the [schema](dsl/schema.xml) needs to define common `<interface>`.
```xml
<fields>
    <set name="Flags" length="1">
        <bit name="B0" idx="0" />
        <bit name="B1" idx="1" />
    </set>
</fields>

<interface name="Interface">
    <ref field="Flags" />
</interface>
```

The protocol framing is defined the following way:
```xml
<frame name="Frame">
    <size name="Size">
        <int name="SizeField" type="uint16" />
    </size>
    <custom name="Id" idReplacement="true">
        <bitfield name="Field">
            <ref field="MsgId" bitLength="7" />
            <set name="Ctrl" bitLength="1">
                <bit name="HasFlags" idx="0" />
            </set>
        </bitfield>
    </custom>
    <custom name="Flags">
        <optional name="OptFlags" field="Flags" defaultMode="missing" />
    </custom>
    <payload name="Data" />
</frame>
```
The `ID` processing framing layer cannot not be defined using built-in `<id>` because the latter is expected to deal with
the pure numeric value ID without any extra (most significant) control bit indicating presence of the optional flags.
As the result `<custom>` one needs to be used with `idReplacement="true"` property set.

The `FLAGS` processing framing layer also cannot be defined using built-in `<value>` because it needs
additional processing logic of whether the field is present.

The `<custom>` layers require C++ code to be provided. The `Id` layer is implemented inside
[dsl_src/include/howto8/frame/layer/Id.h](dsl_src/include/howto8/frame/layer/Id.h)
(copied by the code generator to [include/howto8/frame/layer/Id.h](include/howto8/frame/layer/Id.h))
and the `Flags` layer is implemented inside 
[dsl_src/include/howto8/frame/layer/Flags.h](dsl_src/include/howto8/frame/layer/Flags.h)
(copied by the code generator to [include/howto8/frame/layer/Flags.h](include/howto8/frame/layer/Flags.h))

The [Id](dsl_src/include/howto8/frame/layer/Id.h) is implemented by extending
and customizing [comms::protocol::MsgIdLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1MsgIdLayer.html).
```cpp
template<typename TField, typename TMessage, typename TAllMessages, typename TNextLayer, typename... TOptions>
class Id : public
    comms::protocol::MsgIdLayer<
        TField,
        TMessage,
        TAllMessages,
        TNextLayer,
        TOptions...,
        comms::option::def::ExtendingClass<Id<TField, TMessage, TAllMessages, TNextLayer, TOptions...> >
    >
{
    // Repeat base type
    using Base = ...

public:
    // Repeat some types from the base class
    using Field = typename Base::Field;    
    using MsgIdType = typename Base::MsgIdType;
    using MsgIdParamType = typename Base::MsgIdParamType;

    // Given the combined bitfield field, retrieve message ID value
    static MsgIdType getMsgIdFromField(const Field& field)
    {
        return field.field_msgId().value();
    }

    // Before forwarding read to the next layer let the flags layer know
    // whether its field is present
    template<typename TMsg> 
    void beforeRead(const Field& field, TMsg& msg)
    {
        static_cast<void>(msg);
        bool hasFlags = field.field_ctrl().getBitValue_HasFlags();
        Base::nextLayer().setFieldPreset(hasFlags);
    } 

    // Prepare field value to be written
    template <typename TMsg>
    void prepareFieldForWrite(MsgIdParamType id, const TMsg& msg, Field& field) const
    {
        bool hasFlags = Base::nextLayer().isFieldPresent(msg);
        field.field_msgId().value() = id;
        field.field_ctrl().setBitValue_HasFlags(hasFlags);
    }
};
```
**NOTE** that the inner (wrapped) layers like `Flags` can be accessed using a 
sequence of [nextLayer()](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1MsgIdLayer.html)
member functions invocations (`Base::nextLayer().nextLayer().nextLayer()....`). 
In this case the `Flags` is actually the next one and only single invocation needs to be used.

The `Flags` layer class is also expected to provide `setFieldPreset()` and 
`isFieldPresent()` member functions.

For more details on available customization of the 
[comms::protocol::MsgIdLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1MsgIdLayer.html)
please refer to 
[Defining Custom Message ID Protocol Stack Layer](https://commschamp.github.io/comms_doc/page_custom_id_layer.html)
COMMS library tutorial page.

The [Flags](dsl_src/include/howto8/frame/layer/Flags.h) is implemented by extending
and customizing 
[comms::protocol::TransportValueLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1TransportValueLayer.html).
```cpp
template<typename TField, typename TNextLayer, typename... TOptions>
class Flags : public
    comms::protocol::TransportValueLayer<
        TField,
        0, // Index of the "flags" extra transport fields in the interface
        TNextLayer,
        TOptions...,
        comms::option::def::ExtendingClass<Flags<TField, TNextLayer, TOptions...> >
    >
{
    // Repeat base type
    using Base = ...;

public:
    // Repeat types defined in the base class (not visible by default)
    using Field = typename Base::Field; 

    // Extra public functions
    void setFieldPreset(bool value)
    {
        m_hasFlagsOnRead = value;    
    }

    template <typename TMsg>
    static bool isFieldPresent(const TMsg& msg)
    {
        return msg.transportField_flags().value() != 0U;
    }

    // Overriding default read field functionality
    template <typename TMsg, typename TIter>
    comms::ErrorStatus doReadField(const TMsg* msgPtr, Field& field, TIter& iter, std::size_t len)
    {
        auto mode = comms::field::OptionalMode::Missing;
        if (m_hasFlagsOnRead) {
            mode = comms::field::OptionalMode::Exists;
        }

        field.setMode(mode);
        return Base::doReadField(msgPtr, field, iter, len);
    }

    // Reassign the field value
    template <typename TMsg>
    static bool reassignFieldValueToMsg(const Field& field, TMsg* msgPtr)
    {
        assert(msgPtr != nullptr);
        msgPtr->transportField_flags().value() = field.field().value();
        return true;
    }    

    // Overriding default field preparation functionality
    template <typename TMsg>
    static void prepareFieldForWrite(const TMsg& msg, Field& field)
    {
        field.field().value() = msg.transportField_flags().value();
        auto mode = comms::field::OptionalMode::Missing;
        if (isFieldPresent(msg)) {
            mode = comms::field::OptionalMode::Exists;
        }
        field.setMode(mode);
    } 

    template <typename TMsg>
    static std::size_t doFieldLength(const TMsg& msg)
    {
        if (isFieldPresent(msg)) {
            return Field::maxLength(); // returns 1
        }

        return Field::minLength(); // returns 0
    }    
    
private:
    bool m_hasFlagsOnRead = false;    
};
```
Note that only the read of the field needs to be customized by forcing a mode of the `<optional>` field. 
The write operation is performed normally due to the mode preparation is done inside
the `prepareFieldForWrite()`.

For more details on available customization of the 
[comms::protocol::TransportValueLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1TransportValueLayer.html)
please refer to 
[Defining Custom Transport Value Protocol Stack Layer](https://commschamp.github.io/comms_doc/page_custom_transport_value_layer.html)
COMMS library tutorial page.


Note that the flags inside the interface influence the presence of some fields in
`Msg1` and `Msg2`, some operations of which are customized by providing relevant
files inside [dsl_src/include/howto8/message](dsl_src/include/howto8/message).
