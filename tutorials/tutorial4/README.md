# Tutorial 4
Working with **&lt;variant&gt;** fields and defining heterogeneous lists.

## Heterogeneous Fields
Some protocols in some cases don't _hardcode_ type of the field value which is supposed to
be in a specific place. It puts some kind of (usually) numeric **ID** 
(sometimes referred as **key** or **type**) which determines the value type that follows.
It makes it ideal to define various _properties_ (or list of _properties_) which can be
or any type and reported in any order.

The [CommsDSL](https://github.com/arobenko/CommsDSL-Specification) supports such constructs
using **&lt;variant&gt;** fields. Let's take a look inside [dsl/schema.xml](dsl/schema.xml) 
and see how the following table of properties is implemented.

|ID (1 byte)|Value Type|
|:---:|:---|
|0|Property1 - 2 bytes unsigned integer (uint16)|
|2|Property2 - 4 bytes floating point value (float)|
|5|Property3 - string prefixed with 1 bytes of its length|

First of all the numeric property ID (**key**) is convenient to define
as stand-alone **&lt;enum&gt;** first.
```xml
<enum name="PropKey" type="uint8">
    <validValue name="K1" val="0" />
    <validValue name="K2" val="2" />
    <validValue name="K3" val="5" />
    ...
</enum>
```
The definition of a heterogeneous field that can hold **any** (but one at a time) of the properties listed
above looks like this:
```xml
<int name="PropKeyCommon" type="uint8" failOnInvalid="true"/>

<variant name="KeyValueProp">
    <bundle name="Prop1">
        <int reuse="PropKeyCommon" name="Key" defaultValue="PropKey.K1" validValue="PropKey.K1" />
        <int name="Val" type="uint16" />
    </bundle>
    
    <bundle name="Prop2">
        <int reuse="PropKeyCommon" name="Key" defaultValue="PropKey.K2" validValue="PropKey.K2" />
        <float name="Val" type="float" defaultValue="nan" />
    </bundle>            
    
    <bundle name="Prop3">
        <int reuse="PropKeyCommon" name="Key" defaultValue="PropKey.K3" validValue="PropKey.K3" />
        <string name="Val">
            <lengthPrefix>
                <int name="Length" type="uint8" />
            </lengthPrefix>
        </string>
    </bundle>            
</variant>
```
There are multiple important aspects that require a closer look and deeper understanding.

- Every property is a **key**-**value** pair, which are bundled together by the **&lt;bundle&gt;** 
  field definition to represent a **single** member field of the **&lt;variant&gt;**.
- Every first (**key**) field inside such **&lt;bundle&gt;** must be of the same size and share
  certain common properties. That's why external **PropKeyCommon** field was defined and all other
  **key** ones inherit (using **reuse** property) the common definition and then apply extra changes / modifications
  on top.
- The **&lt;variant&gt;** field can hold **any** of its listed **&lt;bundle&gt;** members, but only
  single **one** at a time. Think of it as a [union](https://en.cppreference.com/w/cpp/language/union) of
  **&lt;bundle&gt;** fields.
- The **logical** (not necessarily actually implemented in the same way) code flow when
  reading such field is to attempt reading of the defined members (**&lt;bundle&gt;**-s) one
  by one **in order** of their definition and stop reading once the read operation of the 
  member is successful. For that purpose there is a need to **fail** reading of the property if
  its **key** is not as expected. That's how the right one is found.
- To fail reading of the property on different **key** value the latter sets the **validValue**
  property to appropriate one and has **failOnInvalid** property set to **true** as well 
  (defined in and reused from **PropKeyCommon** field).
- In order to default construct a property with the correct key value without any need to implement
  boilerplate code that does so the **defaultValue** property is used to set the same value as a valid one.
- The definition of the key valid values as a separate **&lt;enum&gt;** (PropKey) allows referencing its
  values by a name (instead of hard-coded numeric value) in the **defaultValue** and **validValue** properties.

Sometimes there is a need to combine such heterogeneous properties into a list. It is easy to do using
a **&lt;list&gt;** covered in one of the earlier tutorials.
```xml
<message name="Msg1" id="MsgId.M1" displayName="^Msg1Name">
    <list name="F1" element="KeyValueProp">
        <countPrefix>
            <int name="Count" type="uint8" />
        </countPrefix>
    </list>
</message>
```
Note, that element field is defined in the global space in this example and hence can be 
referenced by the **element** XML attribute rather than being defined inside **&lt;element&gt;** child.

Before diving into the code that property handles such fields let's take a closer look at how the
field is actually defined (in [include/tutorial4/field/KeyValueProp.h](include/tutorial4/field/KeyValueProp.h))
```cpp
template <typename TOpt = tutorial4::options::DefaultOptions, typename... TExtraOpts>
class KeyValueProp : public
    comms::field::Variant<...>
{
public:
    COMMS_VARIANT_MEMBERS_NAMES(
        prop1,
        prop2,
        prop3
    );
    
    comms::ErrorStatus read(TIter& iter, std::size_t len)
    {
        ...
    }
    
    ...
};
```
The field is defined by extending [comms::field::Variant](https://arobenko.github.io/comms_doc/classcomms_1_1field_1_1Variant.html)
provided by the [COMMS Library](https://github.com/arobenko/comms_champion#comms-library). The 
class definition uses `COMMS_VARIANT_MEMBERS_NAMES()` macro to provide names to all the member fields it
might contain. For every such name **X** the following is defined:

- `FieldIdx_X` - Numeric compile time known index of the member field **X** in order of members definition inside the schema.
- `initField_X()` - Member function to (re)initialize the variant field to hold member **X**, returns reference to the initialized member.
- `accessField_X()` - Member function to access (via cast to appropriate type) held member of known type.

Note, that `ValueType` inner type defined by every field class is a variant of 
[std::aligned_storage](https://en.cppreference.com/w/cpp/types/aligned_storage) and should not be
accessed directly via usual `.value()` member function. Instead generated `initField_X()` and/or
`accessField_X()` member functions need to be used to access the storage cast to an appropriate type.

Another thing to pay attention to at this stage is an existence of custom `read()` member function which
overrides a default one provided by the [comms::field::Variant](https://arobenko.github.io/comms_doc/classcomms_1_1field_1_1Variant.html)
itself. The default `read()` operation of the 
[comms::field::Variant](https://arobenko.github.io/comms_doc/classcomms_1_1field_1_1Variant.html) implements
the logic mentioned earlier when definition of the **&lt;variant&gt;** field explained. It invokes `read()`
operation of every member **in order** of their definition and stops when the operation is successful. It 
is quite inefficient. The [commsdsl2comms](https://github.com/arobenko/commsdsl) code generation utility
analyses the way how the **&lt;variant&gt;** field is defined and generates more efficient code for `read()` when
appropriate. The generated code will read the first _key_ member and then will use `switch` statement to
handle the rest of the read operation when actual type of the property is known. 
```cpp
switch (commonKeyField.value()) {
case 0U:
    {
        auto& field_prop1 = initField_prop1();
        COMMS_ASSERT(field_prop1.field_key().value() == commonKeyField.value());
        return field_prop1.template readFrom<1>(iter, len);
    }
case 2U:
    {
        auto& field_prop2 = initField_prop2();
        COMMS_ASSERT(field_prop2.field_key().value() == commonKeyField.value());
        return field_prop2.template readFrom<1>(iter, len);
    }
case 5U:
    {
        auto& field_prop3 = initField_prop3();
        COMMS_ASSERT(field_prop3.field_key().value() == commonKeyField.value());
        return field_prop3.template readFrom<1>(iter, len);
    }
default:
    break;
};
```
Inside every case the `initField_X()` member is used to initialize the field to hold an appropriate
member, and then redirect the rest of the `read()` operation to it to read rest of the value (because
the key information was already consumed).

[Read Previous Tutorial](../tutorial3) &lt;-----------------------&gt; [Read Next Tutorial](../tutorial5) 
