# Tutorial 22
Complex length fields.

Up until **v5.0** of the [CommsDSL Specification](https://commschamp.github.io/commsdsl_spec/) the 
`semanticType="length"` property was allowed to be assinged only for **&lt;int&gt;** fields. Since **v5.0**
it is allowed for complex fields, such as **&lt;bundle&gt;** or **&lt;bitfield&gt;**. However,
the custom code is required to be injected which implements the functionality of 
setting and retrieving numeric length values.

This tutorial demonstrates using the length field, which is serialized as one byte in case the
remaining length value is `254` or lower. Otherwise is is serialized as 3 bytes, where the 
first one is special value `0xff (255)`, followed by the 2 bytes of real length.

The [schema](dsl/schema.xml) file defines the `Length` field as the following **&lt;bundle&gt;**:
```xml
<bundle name="Length" semanticType="length" valueOverride="replace">
    <int name="Short" type="uint8">
        <special name="LongForm" val="0xff" />
    </int>
    <optional name="Long" cond="$Short = 0xff" defaultMode="missing">
        <int name="ActLong" type="uint16" /> 
    </optional>
</bundle>
```
Usage of **valueOverride** property ensures that the custom code 
of value retrieval is injected into the code generation.

The custom code itself
(residing in [dsl_src/include/tutorial22/field/Length.h.value](dsl_src/include/tutorial22/field/Length.h.value)
and finding its way to the actual code in 
[include/tutorial22/field/Length.h](include/tutorial22/field/Length.h)) 
defines three functions:
```cpp
/// @brief Get length value
std::size_t getValue() const
{
    if (!field_short().isLongForm()) {
        return static_cast<std::size_t>(field_short().value());
    }

    COMMS_ASSERT(field_long().doesExist()); // Make sure the field in the consistent state
    return static_cast<std::size_t>(field_long().field().value());
}

/// @brief Set length value
void setValue(std::size_t val)
{
    if (val < Field_short::valueLongForm()) {
        field_short().setValue(val);
        field_long().setMissing();
        return;
    }

    field_short().setLongForm();
    field_long().field().setValue(val);
    field_long().setExists();
}

/// @brief Maximal possible length value
static constexpr std::size_t maxValue()
{
    return std::numeric_limits<typename Field_long::Field::ValueType>::max();
}
```
**NOTE**, that so far (in all the previous tutorials) the field's value has been accessed
by reference using `value()` member functions. Version **v5.0** of the
[COMMS Library](https://github.com/commschamp/comms) introduces extra `getValue()` and
`setValue()` functions for every field class, which are just wrappers around the `value()` one.
They can be overridden when custom functionality of
dealing with field's value is required, like in the case described in this tutorial.

Also when dealing with **remaining length** value, some internal functionality of the
[COMMS Library](https://github.com/commschamp/comms) requires **compile time** knowledge
of maximal possible length value. As the result additional `maxValue()` function
also is required to be provided. It needs to be `constexpr` to provide the information
at compile time.

The test of this tutorial implements list of TLV properties described in the
[tutorial4](../tutorial4). The code in the [ClientSession](src/ClientSession.cpp) that
prepares the message to be sent out looks like this:
```cpp
void ClientSession::sendMsg1()
{
    Msg1 msg;

    auto& listOfProps = msg.field_f1().value(); // vector of variant fields
    listOfProps.resize(2);
    assert(msg.doLength() == 0U);
    assert(!listOfProps[0].valid());
    assert(!listOfProps[1].valid());

    listOfProps[0].initField_prop1().field_val().value() = 0x12;
    listOfProps[1].initField_prop2().field_val().value().assign(300, 'a'); // Force long length form.

    msg.doRefresh(); // Bring message to a consistent state
    sendMessage(msg);
}
```
Please analyze the raw data dump produced by both the "client" and the "server" application
of this tutorial to see that in case of first property the **short** form of the `Length` field
is used, while for the second one the **long** form is in place.

## Summary

- Version **v5.0** of [CommsDSL Specification](https://commschamp.github.io/commsdsl_spec/)
  allows using complex fields like **&lt;bundle&gt;** or **&lt;bitfield&gt;** to be used
  as length with `semanticType="length"` property assigned.
- Version **v5.0** of the [COMMS Library](https://github.com/commschamp/comms) uses
  extra `getValue()` and `setValue()` wrapping functions (in addition to the `value()`),
  which can be overridden in the injected code to provide custom value handling functionality.
- In most cases custom length retrieval functionality also requires providing `maxValue()`
  static constexpr function, which provides maximal remaining length value.


[Read Previous Tutorial](../tutorial21) &lt;-----------------------
