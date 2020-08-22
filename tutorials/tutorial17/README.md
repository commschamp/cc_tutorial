# Tutorial 17
Custom transport framing layers.

So far, in all the previous tutorials every frame layer had a well defined single
responsibility. However, there are protocols that may split the used field to 
multiple parts where every part has its own influence on how the message is 
decoded and/or handled. In most such cases, the **&lt;id&gt;** or **&lt;size&gt;**
layers allocate a couple of extra bits of its field to make some extra flags.

This tutorial is quite similar to the [previous](../tutorial16) in terms of 
having the common `Flags` field in its interface definition which influence 
whether some fields exist in both `Msg1` and `Msg2`.
```xml
<interface name="Interface" description="Common Interface for all the messages.">
    <set name="Flags" length="1">
        <bit name="B0" idx="0" />
        <bit name="B1" idx="1" />
    </set>        
</interface>    
```
However instead of having separate **&lt;value&gt;** layer in its frame, both
**&lt;id&gt;** and **&lt;size&gt;** layers have their fields split into actual 
**id** and **size** values, but also having some extra flags bits.
```xml
    <frame name="Frame">
        <custom name="IdWithFlags" idReplacement="true"> 
            <bitfield name="Field">
                <ref field="MsgId" bitLength="6" />
                <set name="Flags" bitLength="2">
                    <bit name="F1" idx="0" description="Re-assigned to B1 of interface flags" />
                </set>
            </bitfield>
        </custom>
        <custom name="SizeWithFlags">
            <bitfield name="Field">
                <int name="Size" type="uint16" bitLength="12"/>
                <set name="Flags" bitLength="4">
                    <bit name="F1" idx="0" description="Re-assigned to B0 of interface flags" />
                </set>
            </bitfield>
        </custom>        
        <payload name="Data" />
    </frame>
```
Please pay attention to the following details:

- The default **&lt;id&gt;** and **&lt;size&gt;** do **NOT** support the intended split of the value into
  multiple sub-fields. Hence the **&lt;custom&gt;** layer definition needs to be used instead.
- The layer that replaces **&lt;id&gt;** must set **idReplacement** property to **true**.
- The **&lt;bitfield&gt;** field is used to split the field in multiple members.
- In this particular tutorial `SizeWithFlags` follows the `IdWithFlags`, i.e the frame is 
  ` ID (with flags) | SIZE (with flags) | PAYLOAD`. The opposite case where the size handling 
  precedes the id is also supported but it has its nuances. It will be covered in one of the **howto**-s.
  
Let's take a look inside generated [include/tutorial17/frame/Frame.h](include/tutorial17/frame/Frame.h).
It contains the following include statements:
```cpp
#include "tutorial17/frame/layer/IdWithFlags.h"
#include "tutorial17/frame/layer/SizeWithFlags.h"
```
The **&lt;custom&gt;** layers require custom implementation of the frame layer, because the code generator
doesn't produce them. If the relevant code is not injected, then the compilation of the protocol code will
probably fail. The [dsl_src/include/tutorial17/frame/layer/IdWithFlags.h](dsl_src/include/tutorial17/frame/layer/IdWithFlags.h)
and [dsl_src/include/tutorial17/frame/layer/SizeWithFlags.h](dsl_src/include/tutorial17/frame/layer/SizeWithFlags.h)
files implement required layers. The code is just copied to 
[include/tutorial17/frame/layer/IdWithFlags.h](include/tutorial17/frame/layer/IdWithFlags.h)
and [include/tutorial17/frame/layer/SizeWithFlags.h](include/tutorial17/frame/layer/SizeWithFlags.h)
respectively by the [commsdsl2comms](https://github.com/commschamp/commsdsl) code generator.

Let's take a look how the [include/tutorial17/frame/layer/IdWithFlags.h](include/tutorial17/frame/layer/IdWithFlags.h)
is actually implemented.
```cpp
template<typename TField, typename TMessage, typename TAllMessages, typename TNextLayer, typename... TOptions>
class IdWithFlags : public
    comms::protocol::MsgIdLayer<
        TField,
        TMessage,
        TAllMessages,
        TNextLayer,
        TOptions...,
        comms::option::def::ExtendingClass<IdWithFlags<TField, TMessage, TAllMessages, TNextLayer, TOptions...> >
    >
{
    ...
};
```
It extends [comms::protocol::MsgIdLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1MsgIdLayer.html).
The latter supports its extension and customization to support cases like in this tutorial. It is
properly described in [Defining Custom Message ID Protocol Stack Layer ](https://commschamp.github.io/comms_doc/page_custom_id_layer.html)
tutorial page of the [COMMS Library](https://github.com/commschamp/comms_champion#comms-library) documentation.

Please note usage of [comms::option::def::ExtendingClass](https://commschamp.github.io/comms_doc/options_8h.html) option 
which specifies the actual type of extending class. It is basically the [CRTP](https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern)
C++ idiom. The extending class is expected to override the following member functions:

- `getMsgIdFromField()` - retrieve the numeric message ID given the reference to the updated (successfully read) layer **field**.
- `beforeRead()` - provides a chance to update allocated message object with relevant data (if needed) before the **read** operation is 
  forwarded to the next layer. In our example  the flags stored inside the interface are updated accordingly.
- `prepareFieldForWrite()` - update the field's value (assign provided message ID and other field members) before it is written.

Please refer to the API documentation of the 
[comms::protocol::MsgIdLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1MsgIdLayer.html)
class for the full information on the functions' signatures.
```cpp
template<typename TField, typename TMessage, typename TAllMessages, typename TNextLayer, typename... TOptions>
class IdWithFlags : public
    comms::protocol::MsgIdLayer<...>
{
    ...
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

    // Before forwarding read to the next layer update flags extra transport field in the interface
    template<typename TMsg> 
    static void beforeRead(const Field& field, TMsg& msg)
    {
        msg.transportField_flags().setBitValue_B1(field.field_flags().getBitValue_F1());
    } 

    // Prepare field value to be written
    template <typename TMsg>
    static void prepareFieldForWrite(MsgIdParamType id, const TMsg& msg, Field& field)
    {
        field.field_msgId().value() = id;
        field.field_flags().setBitValue_F1(msg.transportField_flags().getBitValue_B1());
    }
};
```

The [include/tutorial17/frame/layer/SizeWithFlags.h](include/tutorial17/frame/layer/SizeWithFlags.h)
is implemented in very similar way, but extending 
[comms::protocol::MsgSizeLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1MsgSizeLayer.html).
```cpp
/// @brief Customizing the size layer
template<typename TField, typename TNextLayer, typename... TOptions>
class SizeWithFlags : public
    comms::protocol::MsgSizeLayer<
        TField,
        TNextLayer,
        TOptions...,
        comms::option::def::ExtendingClass<SizeWithFlags<TField, TNextLayer, TOptions...> >
    >
{
}
```
The [Defining Custom Message Size Protocol Stack Layer](https://commschamp.github.io/comms_doc/page_custom_size_layer.html)
tutorial page of the [COMMS Library](https://github.com/commschamp/comms_champion#comms-library) documentation provides a lot 
of details on how define such layer.

The `SizeWithFlags` class also uses [comms::option::def::ExtendingClass](https://commschamp.github.io/comms_doc/options_8h.html) option 
which specifies the actual type of extending class. 
The extending class is expected to override the following member functions:

- `getRemainingSizeFromField()` - retrieve the remaining message size given the reference to the updated (successfully read) layer **field**.
- `beforeRead()` - provides a chance to update allocated message object (if such is ready) with relevant data (if needed) before the **read** operation is 
  forwarded to the next layer. In our example the flags stored inside the interface are updated accordingly.
- `prepareFieldForWrite()` - update the field's value (assign remaining message size and other field members) before it is written.

Please refer to the API documentation of the 
[comms::protocol::MsgSizeLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1MsgSizeLayer.html)
class for the full information on the functions' signatures.
```cpp
template<typename TField, typename TNextLayer, typename... TOptions>
class SizeWithFlags : public
    comms::protocol::MsgSizeLayer<
        TField,
        TNextLayer,
        TOptions...,
        comms::option::def::ExtendingClass<SizeWithFlags<TField, TNextLayer, TOptions...> >
    >
{
public:
    // Repeat some types from the base class
    using Field = typename Base::Field;    

    // Given the combined bitfield field, retrieve remaining size
    static std::size_t getRemainingSizeFromField(const Field& field)
    {
        return static_cast<std::size_t>(field.field_size().value());
    }

    // Before forwarding read to the next layer update flags extra transport field in the interface
    template<typename TMsg> 
    static void beforeRead(const Field& field, TMsg* msg)
    {
        COMMS_ASSERT(msg != nullptr); // The message object is expected to be created
        msg->transportField_flags().setBitValue_B0(field.field_flags().getBitValue_F1());
    } 

    // Prepare field value to be written
    template <typename TMsg>
    static void prepareFieldForWrite(std::size_t size, const TMsg* msg, Field& field)
    {
        assert(msg != nullptr);
        field.field_size().value() = static_cast<typename Field::Field_size::ValueType>(size);
        field.field_flags().setBitValue_F1(msg->transportField_flags().getBitValue_B0());
    }
};
```
**NOTE** that the `msg` parameter in `beforeRead()` and `prepareFieldForWrite()` member functions 
is passed by **pointer** (not reference like with `IdWithFlags`). It is to allow cases when
`SIZE` precedes `ID` in the framing definition and the message object is not available. In this 
particular tutorial the message object is created **before** the `SizeWithFlags` layer 
performs its `read()` operation, as the result the pointer is expected to be **not** `nullptr`.

Both [ServerSession](src/ServerSession.cpp) and [ClientSession](src/ClientSession.cpp) work as 
usual. There is one small nuance though in how [ClientSession](src/ClientSession.h) is defined
and works.

In this particular tutorial the common interface of the [ClientSession](src/ClientSession.h) 
does **NOT** expose polymorphic length calculation and its output iterator is defined to be
`std::back_insert_iterator<std::vector<std::uint8_t> >`, i.e. not random-access one.
```cpp
using Message = 
    tutorial17::Interface<
        comms::option::app::ReadIterator<const std::uint8_t*>, // Polymorphic read
        comms::option::app::WriteIterator<std::back_insert_iterator<std::vector<std::uint8_t> > >, // Polymorphic write
        comms::option::app::IdInfoInterface, // Polymorphic message ID retrieval
        comms::option::app::NameInterface, // Polymorphic name retrieval
        comms::option::app::Handler<ClientSession> // Polymorphic dispatch        
    >;
```
As the result when client writes the message, the size value is not known during `write()` operation and 
`comms::ErrorStatus::UpdateRequired` is expected to be returned.
```cpp
void ClientSession::sendMessage(const Message& msg)
{
    ...
    auto es = m_frame.write(msg, writeIter, output.max_size());
    if (es == comms::ErrorStatus::UpdateRequired) {
        auto updateIter = &output[0];
        es = m_frame.update(msg, updateIter, output.size());
    }
    ...
}
```
To properly update the size value, the `update()` operation needs to be invoked, but because 
the value also needs to update the flags part of the field, the message object needs to be 
passed as a parameter as well. The `SizeWithFlags::prepareFieldForWrite()` function will be 
called to properly set the size and the flags.

## Summary
- Custom layers are defined using **&lt;custom&gt;** XML node.
- The layer that replaces **&lt;id&gt;** needs to set **idReplacement** property to **true**.
- To implement custom replacement of **&lt;id&gt;**, the custom layer code may extend 
  [comms::protocol::MsgIdLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1MsgIdLayer.html)
  (see [Defining Custom Message ID Protocol Stack Layer ](https://commschamp.github.io/comms_doc/page_custom_id_layer.html)
  for details).
- To implement custom replacement of **&lt;size&gt;**, the custom layer code may extend 
  [comms::protocol::MsgSizeLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1MsgSizeLayer.html)
  (see [Defining Custom Message Size Protocol Stack Layer](https://commschamp.github.io/comms_doc/page_custom_size_layer.html)
  for details).


[Read Previous Tutorial](../tutorial16) &lt;-----------------------&gt; [Read Next Tutorial](../tutorial18) 
