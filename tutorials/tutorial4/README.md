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

Now, let's take a look how the `Msg1` is prepared to be sent out.
```cpp
void ClientSession::sendMsg1()
{
    Msg1 msg;

    auto& listOfProps = msg.field_f1().value(); // vector of variant fields
    listOfProps.resize(3);
    assert(msg.doLength() == 1U); // just 1 byte prefix
    assert(!listOfProps[0].valid());
    assert(!listOfProps[1].valid());
    assert(!listOfProps[2].valid());

    listOfProps[0].initField_prop1().field_val().value() = 0xabcd;
    listOfProps[1].initField_prop3().field_val().value() = "hello";
    listOfProps[2].initField_prop2().field_val().value() =
            std::numeric_limits<Msg1::Field_f1::ValueType::value_type::Field_prop2::Field_val::ValueType>::infinity();

    sendMessage(msg);
}
```
By variant field is default constructed in an invalid state (not holding any real member field). That's what
we see in the code above (after vector resizing the variant fields are invalid and don't produce any output
when serialized).

It is paramount to understand the values are being assigned.

- `listOfProps[0]` gives us a reference to the first **&lt;variant&gt;** field in the list (still not properly initialized).
- `listOfProps[0].initField_prop1()` - initializes the first **&lt;variant&gt;** field to hold **Prop1**
  ([tutorial4::field::KeyValuePropMembers<...>::Prop1](include/tutorial4/field/KyValueProp.h)), which is a **&lt;bundle&gt;**
  having its own member fields, and gives a reference to initialized member.
- `listOfProps[0].initField_prop1().field_val()` - access the **Val** member field (defined as **&lt;int&gt;**).
- `listOfProps[0].initField_prop1().field_val().value()` - provides a reference to actual value storage (of `std::uint16_t` type).

The rest of the values are assigned in a similar way. The last **&lt;variant&gt;** in the list contains **Prop2**,
which in turns contains floating point value. The code above assigns appropriate **infinity** value to it.
It is important to understand how the actual type is chosen to be a template parameter for 
`std::numeric_limits`. Of course, just by the look at the [dsl/schema.xml](dsl/schema.xml) it is clear that
the type is `float` (due to `type="float"` property assignment). However, using this type directly is a 
boilerplate code which needs to be updated manually in case the property is changed in the schema. Such
hard-coding is not recommended.

- `Msg1::Field_f1` - generated by the `COMMS_MSG_FIELDS_NAMES()` macro and gives a type of the **F1** field which is
  a **&lt;list&gt;**.
- `Msg1::Field_f1::ValueType` - gives a storage type of the **&lt;list&gt;** which is `std::vector` of 
  [tutorial4::field::KeyValueProp](include/tutorial4/field/KeyValueProp.h) **&lt;variant&gt;**-s.
- `Msg1::Field_f1::ValueType::value_type` - gives a type of the held values 
  ([tutorial4::field::KeyValueProp](include/tutorial4/field/KeyValueProp.h)).
- `Msg1::Field_f1::ValueType::value_type::Field_prop2` - gives us a type of **Prop2** (**&lt;bundle&gt;**
  defined as [tutorial4::field::KeyValuePropMembers<...>::Prop2](include/tutorial4/field/KyValueProp.h)) generated
  by `COMMS_VARIANT_MEMBERS_NAMES()` macro.
- `Msg1::Field_f1::ValueType::value_type::Field_prop2::Field_val` - gives us a type of **Val** member of
  the **Prop2** ([tutorial4::field::KeyValuePropMembers<...>::Prop2Members::Val](include/tutorial4/field/KyValueProp.h)),
  which is **&lt;floag&gt;** field.
- `Msg1::Field_f1::ValueType::value_type::Field_prop2::Field_val::ValueType` - finally gives as a real storage type of
  the used **&lt;float&gt;** field.
  
The next stage is to understand how to properly process such variant fields. In this example the sent `Msg1` is
echoed back by the server and processes inside `void ClientSession::handle(Msg1& msg)`.
```cpp
void ClientSession::handle(Msg1& msg)
{
    ...
    auto& f1Vec = msg.field_f1().value();
    for (auto idx = 0U; idx < f1Vec.size(); ++idx) {
        const auto& elem = f1Vec[idx]; // access to the variant element
        elem.currFieldExec(PropDispatchHelper(*this));
    }
    ...
}
```
The code above iterates over received **&lt;variant&gt;** fields in the list and dispatches them for
proper processing using `currFieldExec()` member function. Note, that at the time of the processing
the `read()` operation has been successfully completed and the index of the member (**0** based) in 
order of their definition is held as a private data and can be retrieved using 
[comms::field::Variant::currentField()](https://arobenko.github.io/comms_doc/classcomms_1_1field_1_1Variant.html)
member function. Please pay attention that this is a **run-time** (not compile-time) information and the
actual type of the stored value (to cast to) needs to be determined at run-time. The `currFieldExec()`
member function of the variant field receives a functor object, which is expected to define its `operator()` with
appropriate signature, determines the correct type of the member for the cast and invokes `operator()` of the
passed functor object with the correct reference to the held member. The definition of the `PropDispatchHelper` in
this example is:
```cpp
class PropDispatchHelper
{
public:
    explicit PropDispatchHelper(ClientSession& session)
      : m_session(session)
    {
    }

    template <std::size_t TIdx, typename TField>
    void operator()(const TField& field)
    {
        m_session.handleProp(field);
    }

private:
    ClientSession& m_session;
};
```
See also the documentation on [comms::field::Variant::currFieldExec()](https://arobenko.github.io/comms_doc/classcomms_1_1field_1_1Variant.html).

Note that `operator()` above in addition to actual type of the member receives also the index of the
detected member as a template parameter, so the run-time information of the index becomes a compile-time
one. In many cases the compile-time information about the detected member index is not really needed (like
in this example) and can be safely ignored. What is used in this example is the actual type of the member. 
Once the type of the held member is determined its handling is forwarded to appropriate `ClientSession::handleProp()`
member function. The handling functions are defined like this:
```cpp
class ClientSession
{
   ...
    using Prop1 = Msg1::Field_f1::ValueType::value_type::Field_prop1;
    using Prop2 = Msg1::Field_f1::ValueType::value_type::Field_prop2;
    using Prop3 = Msg1::Field_f1::ValueType::value_type::Field_prop3;

    void handleProp(const Prop1& prop);
    void handleProp(const Prop2& prop);
    void handleProp(const Prop3& prop);
};
```
The `handleProp()` in turn prints the values of the detected property **&lt;bundle&gt;**. As the result
the output of `Msg1` handling looks like this:
```
Received "Message 1" with ID=1
    F1 (3 elements)
        Prop1:
            Key = 0
            Val = 43981
        Prop3:
            Key = 5
            Val = hello
        Prop2:
            Key = 2
            Val = inf
```
The `currFieldExec()` member function provided by the [comms::field::Variant](https://arobenko.github.io/comms_doc/classcomms_1_1field_1_1Variant.html) field has the following run-time logic of determining the real type of the held 
member to cast to.


[Read Previous Tutorial](../tutorial3) &lt;-----------------------&gt; [Read Next Tutorial](../tutorial5) 
