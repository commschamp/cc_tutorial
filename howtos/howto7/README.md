# How-To 7
Alternating values in synchronization framing prefix.

There are protocols for which the provided `<sync>` framing layer is insufficient.
Some extra customization will be required. For example the synchronization prefix 
values are alternating, i.e. for every first message the synchronization prefix
is expected to be `0xabcd` and every second one is `0xdead`.

This howto uses the following frame
```
SYNC (2 bytes) | SIZE (2 bytes) | ID (1 byte) | PAYLOAD | CHECKSUM
```

The [schema](dsl/schema.xml) defines the following frame
```xml
<frame name="Frame">
    <custom name="AlternatingSync">
        <int name="SyncField" type="uint16" />
    </custom>
    <size name="Size">
        <int name="SizeField" type="uint16" />
    </size>
    <id name="Id" field="MsgId" />
    <payload name="Data" />
</frame>
```

The synchronization prefix layer cannot use the provide `<sync>` one and must
use `<custom>` one.

The provided custom layer is implemented inside 
[dsl_src/include/howto7/frame/layer/AlternatingSync.h](dsl_src/include/howto7/frame/layer/AlternatingSync.h) and
copied to the protocol definition 
([include/howto7/frame/layer/AlternatingSync.h](include/howto7/frame/layer/AlternatingSync.h)) 
by the code generator.

The [AlternatingSync](dsl_src/include/howto7/frame/layer/AlternatingSync.h) layer
is implemented by extending 
[comms::protocol::SyncPrefixLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1SyncPrefixLayer.html).
```cpp
template<typename TField, typename TNextLayer, typename... TOptions>
class AlternatingSync : public
    comms::protocol::SyncPrefixLayer<
        TField,
        TNextLayer,
        TOptions...,
        comms::option::def::ExtendingClass<AlternatingSync<TField, TNextLayer, TOptions...> >
    >
{
    // Repeat base type
    using Base = ...;
    ...
};
```
**NOTE**, that the code above uses 
[Curiously Recurring Template Pattern](https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern) 
to provide the base
[comms::protocol::SyncPrefixLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1SyncPrefixLayer.html) class with the 
actual extending layer type using **comms::option::def::ExtendingClass** option. It makes the customization 
of the default operations possible.

In order to support alternating synchronization prefix the following member functions are overriden:
```cpp
template<typename TField, typename TNextLayer, typename... TOptions>
class AlternatingSync : public
    comms::protocol::SyncPrefixLayer<...>
{
public:
    // Repeat types defined in the base class (not visible by default)
    using Field = typename Base::Field; 

    // Customizing input field value verification logic
    bool verifyFieldValue(const Field& field)
    {
        ...
    } 

    // Customizing output field preparation logic
    void prepareFieldForWrite(Field& field) const
    {
        ...
    }
};
```
Please refer to the [actual code](dsl_src/include/howto7/frame/layer/AlternatingSync.h) for the implementation details.

**NOTE**, that **prepareFieldForWrite()** member function is called during the write operation, which
is a `const` function. As the result, the **prepareFieldForWrite()** also needs to be `const`.
In case it needs to update any private member data, the latter must be declared `mutable`.
```cpp
template<typename TField, typename TNextLayer, typename... TOptions>
class AlternatingSync : public
    comms::protocol::SyncPrefixLayer<...>
{
    ...
    unsigned m_inputCount = 0;
    mutable unsigned m_outputCount = 0;
};
```
The **COMMS** library tutorial contains a separate page
called [Defining Custom Sync Prefix Protocol Stack Layer](https://commschamp.github.io/comms_doc/page_custom_sync_prefix_layer.html)
with a bit more details on the available customization.
