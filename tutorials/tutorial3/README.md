# Tutorial 3
Working with scaling and units in numeric fields.

## Scaling
Many protocols need to report non-integral values but don't allow usage of floating point encoding when serializing their fields.
Usually such values are serialized as integral ones which treated as 
[fixed point values](https://en.wikipedia.org/wiki/Fixed-point_arithmetic) with predefined scaling multiplier, i.e. predefined 
number of digits after decimal points.

To help with such cases [CommsDSL](https://github.com/commschamp/CommsDSL-Specification) has
**scaling** property applicable to **&lt;int&gt;** fields. Message `Msg1` (defined in [dsl/schema.xml](dsl/schema.xml) 
and implemented inside [include/tutorial3/message/Msg1.h](include/tutorial3/message/Msg1.h)) comes to
demonstrate definition of such fields.

The message and its fields are defined in the following way:
```xml
<message name="Msg1" id="MsgId.M1" displayName="^Msg1Name">
    <int name="F1" type="uint16" scaling="1/1000" />
    <int name="F2" type="int32" scaling="1/1000000" />
</message>
```
The **scaling** property defines rational number fraction by which the stored integral value needs to get
multiplied in order the receive required floating point value. Also the 
[comms::field::IntValue](https://commschamp.github.io/comms_doc/classcomms_1_1field_1_1IntValue.html) class
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
gets assigned using `.setScaled()` member function, then it's automatically divided by the scaling
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
[CommsDSL](https://github.com/commschamp/CommsDSL-Specification) allows usage of 
reference strings as well. In the case above they reference the defined **&lt;validValue&gt;**-s
of the `MsgId` field. The value of the **displayName** property needs to be
as string. [CommsDSL](https://github.com/commschamp/CommsDSL-Specification) allows
referencing of common definitions for strings as well. 
There must be a way to differentiate between an actual string value and a reference to other
field. The [CommsDSL](https://github.com/commschamp/CommsDSL-Specification) specifies that
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
In many cases the protocol specifies that some field's value reports some measurement units, like **seconds** or
**meters**. In most cases this is "hard-coded" meta-information which doesn't get reported over I/O link. As the
result the integration logic may contain some boilerplate code, especially if reported units need to be converted
to something else, i.e. seconds to milliseconds or meters to millimeters, etc... It is also not uncommon for the
integration logic being implemented before the protocol specification is finalized. There is a possibility that
the chosen units for a specific field can get changed in the process. In such case all the written integration
boilerplate code needs to be modified as well, which is error-prone of course.

The [CommsDSL](https://github.com/commschamp/CommsDSL-Specification) allows usage of **units** property when
defining **&lt;int&gt;** and **&lt;float&gt;** fields. The list of supported values can be found in
the [specification](https://commschamp.github.io/commsdsl_spec/#appendix-units).

Message `Msg2` (defined in [dsl/schema.xml](dsl/schema.xml) 
and implemented inside [include/tutorial3/message/Msg2.h](include/tutorial3/message/Msg2.h)) comes to
demonstrate usage of **units** property.
```xml
<message name="Msg2" id="MsgId.M2" displayName="^Msg2Name">
    <int name="F1" type="uint32" units="sec" />
    <float name="F2" type="double" units="mm" />
</message> 
```
In the example above the `F1` field is defined to contain **seconds** while `F2` is defined to contain
millimeters.

In order to efficiently work with units the [COMMS Library](https://github.com/commschamp/comms)
provides multiple functions defined in [comms::units](https://commschamp.github.io/comms_doc/namespacecomms_1_1units.html)
namespace (requires `#include "comms/units.h"` statement).

The generated code of the fields definition looks like this:
```cpp
template <typename TOpt = tutorial3::options::DefaultOptions>
struct Msg2Fields
{
    struct F1 : public
        comms::field::IntValue<
            ...,
            comms::option::def::UnitsSeconds
        >
    {
        ...
    };
    
    struct F2 : public
        comms::field::FloatValue<
            ...,
            comms::option::def::UnitsMillimeters
        >
    {
        ...
    };
        
    ...
};
```
The units information is passed as an extension option to the field class definition.

The preparation of the `Msg2` before being sent looks like this:
```cpp
void ClientSession::sendMsg2()
{
    Msg2 msg;

    comms::units::setMinutes(msg.field_f1(), 1.5);
    comms::units::setMeters(msg.field_f2(), 1.2);

    sendMessage(msg);
}
```
**IMPORTANT**: Please note that the reference to the **field** object itself (not its stored **value**) is
passed as the first parameter to the units set function. It is required to determine the actual
class of the field which in turn contains the meta-information of what actual units the field's value must
contain. The required math is automatically implemented by the compiler.

Also note that [COMMS Library](https://github.com/commschamp/comms) contains compile-time
checks of whether units being assigned are compatible with the ones that field contains, i.e. attempt to 
assign say **meters** to **seconds** will result in compile time error.

The `void ClientSession::handle(Msg2& msg)` function uses multiple `comms::units::get*()` functions to
retrieve required units from the field's value. Just like with the `comms::units::set*()` functions the
first parameter is expected to be a reference to the **field** object itself, not its **value** in order
to determine the used field class and use appropriate math for required units. Also pay attention that
the `comms::units::get*()` functions require a template parameter that specifies type of the returned value.

The output of handling `Msg2` looks like this:
```
Received "Message 2" with ID=2
    F1 = 90
        = 90000000 us
        = 90000 ms
        = 90 s
        = 1.500000 min
        = 0.025000 h
    F2 = 1200.000000
        = 1200000.000000 um
        = 1200.000000 mm
        = 1.200000 m
```
If units are changed in the protocol definition (schema), such code doesn't need to be changed to work correctly, just recompiled.

**NOTE** that [CommsChampion Ecosystem](https://commschamp.github.io) is about binary protocol definition, not
efficient and/or convenient work with units. The support for the units is very limited and definitely incomplete, but
still useful in many cases.
If the support for new units is desired please [get in touch](https://commschamp.github.io/contact/) and request what you need. 
There are multiple available libraries (like Boost.Units) for proper work with units.

In order to support usage of third party units libraries the [COMMS Library](https://github.com/commschamp/comms)
provides a **compile-time** check functions that the field contains an assumed units. If units are changed in the
protocol definition, the compile time checks introduced before the boilerplate units conversion code should fail the compilation
and help finding places that need to be updated.
```cpp
void ClientSession::handle(Msg2& msg)
{
    // Compile time checks could be used before third party units conversions (like Boost.Units)
    static_assert(comms::units::isSeconds<Msg2::Field_f1>(), "Unexpected units");
    static_assert(comms::units::isMillimeters<Msg2::Field_f2>(), "Unexpected units");

    ...
}
```

## Combining Scaling and Units
The [scaling](#scaling) and [units](#units) can easily be combined together as
`Msg3` (defined in [dsl/schema.xml](dsl/schema.xml) 
and implemented inside [include/tutorial3/message/Msg3.h](include/tutorial3/message/Msg3.h)) demonstrates.
```xml
<message name="Msg3" id="MsgId.M3" displayName="^Msg3Name">
    <int name="F1" type="uint32" units="cm" scaling="1/100000" />
</message>
```
All the previously introduced `comms::units::set*()` and `comms::units::get*()` functions also seamlessly 
work with scaling and do the proper math before assigning field's actual value:
```cpp
void ClientSession::sendMsg3()
{
    Msg3 msg;

    comms::units::setMillimeters(msg.field_f1(), 123.45678);

    sendMessage(msg);
}
```
The output produced by `void ClientSession::handle(Msg3& msg)` looks like this:
```
Received "Message 3" with ID=3
    F1 = 1234568
        = 123456.800000 um
        = 123.456800 mm
        = 12.345680 cm
        = 0.123457 m
```

## Summary

- The string values can reference other fields with '^' prefix.
- The [fixed point values](https://en.wikipedia.org/wiki/Fixed-point_arithmetic) are defined as **&lt;int&gt;** and 
  use **scaling** property to define their scaling ratio.
- The [comms::field::IntValue](https://commschamp.github.io/comms_doc/classcomms_1_1field_1_1IntValue.html) class
  used to define **&lt;int&gt;** fields provides **getScaled()** and **setScaled()** member functions to get / set
  scaled floating point values.
- Measurement units are defined using **units** property.
- List of supported units can be found in the CommsDSL [specification](https://commschamp.github.io/commsdsl_spec/#appendix-units).
- Functions that allow working with units reside in [comms::units](https://commschamp.github.io/comms_doc/namespacecomms_1_1units.html)
  namespace and require `#include "comms/units.h"` statement.
- The `comms::units::set*()` and `comms::units::get*()` stand alone functions are used to set particular units and  
  require reference to the **field** object itself (not its **value**) to use appropriate assignment math.
- The support for units is very basic and limited. There are **compile-time** inquiry `comms::units::is*()` functions
  which allow check of units assumption before introducing boilerplate code of units conversions.
- All the units conversion functions in [comms::units](https://commschamp.github.io/comms_doc/namespacecomms_1_1units.html) 
  work seamlessly with [scaling](#scaling).

[Read Previous Tutorial](../tutorial2) &lt;-----------------------&gt; [Read Next Tutorial](../tutorial4) 
