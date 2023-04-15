# Tutorial 4
Working with `<variant>` fields and defining heterogeneous lists.

## Key-Value Pairs
Some protocols in some cases don't _hardcode_ type of the field value which is supposed to
be in a specific place. It puts some kind of (usually) numeric **ID** 
(sometimes referred as **key** or **type**) which determines the value type that follows.
It makes it ideal to define various _properties_ (or list of _properties_) which can be
or any type and reported in any order.

The [CommsDSL](https://github.com/commschamp/CommsDSL-Specification) supports such constructs
using `<variant>` fields. Let's take a look inside [dsl/schema.xml](dsl/schema.xml)
and see how the following table of properties is implemented.

|ID (1 byte)|Value Type|
|:---:|:---|
|0|Property1 - 2 bytes unsigned integer (uint16)|
|2|Property2 - 4 bytes floating point value (float)|
|5|Property3 - string prefixed with 1 bytes of its length|

First of all the numeric property ID (**key**) is convenient to define
as stand-alone `<enum>` first.
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
        <int reuse="PropKeyCommon" name="Key" defaultValidValue="PropKey.K3" />
        <string name="Val">
            <lengthPrefix>
                <int name="Length" type="uint8" />
            </lengthPrefix>
        </string>
    </bundle>            
</variant>
```
There are multiple important aspects that require a closer look and deeper understanding.

- Every property is a **key**-**value** pair, which are bundled together by the `<bundle>`
  field definition to represent a **single** member field of the `<variant>`.
- Every first (**key**) field inside such `<bundle>` must be of the same size and share
  certain common properties. That's why external **PropKeyCommon** field was defined and all other
  **key** ones inherit (using **reuse** property) the common definition and then apply extra changes / modifications
  on top.
- The `<variant>` field can hold **any** of its listed `<bundle>` members, but only
  single **one** at a time. Think of it as a [union](https://en.cppreference.com/w/cpp/language/union) of
  `<bundle>` fields.
- The **logical** (not necessarily actually implemented in the same way) code flow when
  reading such field is to attempt reading of the defined members (`<bundle>`-s) one
  by one **in order** of their definition and stop reading once the read operation of the 
  member is successful. For that purpose there is a need to **fail** reading of the property if
  its **key** is not as expected. That's how the right one is found.
- To fail reading of the property on different **key** value the latter sets the **validValue**
  property to appropriate one and has **failOnInvalid** property set to **true** as well 
  (defined in and reused from **PropKeyCommon** field).
- In order to default construct a property with the correct key value without any need to implement
  boilerplate code that does so the **defaultValue** property is used to set the same value as a valid one.
- The definition of the key valid values as a separate `<enum>` (PropKey) allows referencing its
  values by a name (instead of hard-coded numeric value) in the **defaultValue** and **validValue** properties.
- Since release **v4.0** of the [CommsDSL](https://github.com/commschamp/CommsDSL-Specification) specification
  and [commsdsl](https://github.com/commschamp/commsdsl) code generators it is possible to replace a 
  combination of **defaultValue** and **validValue** properties with a single one **defaultValidValue**, like
  it was done for the _Prop3_.

Sometimes there is a need to combine such heterogeneous properties into a list. It is easy to do using
a `<list>` covered in one of the earlier tutorials.
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
referenced by the **element** XML attribute rather than being defined inside `<element>` child.

Another valid definition of such message could be like this:
```xml
<message name="Msg1" id="MsgId.M1" displayName="^Msg1Name">
    <list name="F1">
        <element>
            <ref field="KeyValueProp" name="Element" />
        </element>
        <countPrefix>
            <int name="Count" type="uint8" />
        </countPrefix>
    </list>
</message>
```

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

    ...
};
```
The field is defined by extending [comms::field::Variant](https://commschamp.github.io/comms_doc/classcomms_1_1field_1_1Variant.html)
provided by the [COMMS Library](https://github.com/commschamp/comms). The 
class definition uses `COMMS_VARIANT_MEMBERS_NAMES()` macro to provide names to all the member fields it
might contain. For every such name **X** the following is defined:

- `FieldIdx_X` - Numeric compile time known index of the member field **X** in order of members definition inside the schema.
- `initField_X()` - Member function to initialize the variant field to hold member **X**, returns reference to the initialized member.
  To be able to use this member function the variant mustn't contain other field before.
- `deinitField_X()` - Member funttion to de-initialize (destruct) the help member **X**.
- `accessField_X()` - Member function to access (via cast to appropriate type) held member of known type.

Note, that `ValueType` inner type defined by every field class is a variant of 
[std::aligned_storage](https://en.cppreference.com/w/cpp/types/aligned_storage) and should not be
accessed directly via usual `.value()` member function. Instead, generated `initField_X()` and/or
`accessField_X()` member functions need to be used to access the storage and perform the cast to 
the appropriate type.

It is important to understand that the defult implementation provided by the
[comms::field::Variant](https://commschamp.github.io/comms_doc/classcomms_1_1field_1_1Variant.html) class
is sufficient to be used "as-is" without any extra functionality. However, it has to do a lot of
meta-programming and regular code magic to translate runtime information of the detected member field
to its type known at compile time. It creates a significant burden on the compiler increasing compilation
time as well as memory consumption. The final code may also have sub-optimal performance.

To workaround this issue, the **commsdsl2comms** code generator overrides most of the inherited member
functions with better `switch` statement based implementation.

For example, the `read()` member function. The default (inherited) `read()` operation of the
[comms::field::Variant](https://commschamp.github.io/comms_doc/classcomms_1_1field_1_1Variant.html) implements
the logic mentioned earlier when definition of the `<variant>` field explained. It invokes `read()`
operation of every member **in order** of their definition and stops when the operation is successful. It 
is quite inefficient. The [commsdsl2comms](https://github.com/commschamp/commsdsl) code generation utility
analyses the way how the `<variant>` field is defined and generates more efficient code for `read()` when
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
member, and then redirect the rest of the `read()` operation to it, to read rest of the value (because
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
The variant fields are default constructed (when storage vector gets resized) 
in an invalid state (not holding any real member field). That's what
we see in the code above (after vector resizing the variant fields are invalid and don't produce any output
when serialized).

It is paramount to understand how the values are being assigned in the code above.

- `listOfProps[0]` gives us a reference to the first `<variant>` field in the list (still not properly initialized).
- `listOfProps[0].initField_prop1()` - initializes the first `<variant>` field to hold **Prop1**
  ([tutorial4::field::KeyValuePropMembers<...>::Prop1](include/tutorial4/field/KeyValueProp.h)), which is a `<bundle>`
  having its own member fields, and gives a reference to initialized member.
- `listOfProps[0].initField_prop1().field_val()` - access the **Val** member field (defined as `<int>`).
- `listOfProps[0].initField_prop1().field_val().value()` - provides a reference to actual value storage (of `std::uint16_t` type).

The rest of the values are assigned in a similar way. The last `<variant>` in the list contains **Prop2**,
which in turn contains floating point value. The code above assigns appropriate **infinity** value to it.
It is important to understand how the actual type is chosen to be a template parameter for 
`std::numeric_limits`. Of course, just by the look at the [dsl/schema.xml](dsl/schema.xml) it is clear that
the type is `float` (due to `type="float"` property assignment). However, using this type directly is a 
boilerplate code which needs to be updated manually in case the property is changed in the schema. Such
hard-coding is not recommended.

- `Msg1::Field_f1` - generated by the `COMMS_MSG_FIELDS_NAMES()` macro in the message definition and 
  gives a type of the **F1** field which is a `<list>`
  (extends [comms::field::ArrayList](https://commschamp.github.io/comms_doc/classcomms_1_1field_1_1ArrayList.html)).
- `Msg1::Field_f1::ValueType` - gives a storage type of the `<list>` which is `std::vector` of
  [tutorial4::field::KeyValueProp](include/tutorial4/field/KeyValueProp.h) `<variant>`-s.
- `Msg1::Field_f1::ValueType::value_type` - gives a type of the held values 
  ([tutorial4::field::KeyValueProp](include/tutorial4/field/KeyValueProp.h)).
- `Msg1::Field_f1::ValueType::value_type::Field_prop2` - gives us a type of **Prop2** (`<bundle>`
  defined as [tutorial4::field::KeyValuePropMembers<...>::Prop2](include/tutorial4/field/KeyValueProp.h)) generated
  by `COMMS_VARIANT_MEMBERS_NAMES()` macro inside `<variant>` field class definition.
- `Msg1::Field_f1::ValueType::value_type::Field_prop2::Field_val` - gives us a type of **Val** member of
  the **Prop2** ([tutorial4::field::KeyValuePropMembers<...>::Prop2Members::Val](include/tutorial4/field/KeyValueProp.h)),
  which is `<float>` field (extends [comms::field::FloatValue](https://commschamp.github.io/comms_doc/classcomms_1_1field_1_1FloatValue.html)).
- `Msg1::Field_f1::ValueType::value_type::Field_prop2::Field_val::ValueType` - finally gives as a real storage type of
  the used `<float>` field.
  
The next stage is to understand how to properly process such variant fields. In this example the sent `Msg1` is
echoed back by the server and processes inside `void ClientSession::handle(Msg1& msg)`.
```cpp
void ClientSession::handle(Msg1& msg)
{
    ...
    auto& f1Vec = msg.field_f1().value();
    for (auto idx = 0U; idx < f1Vec.size(); ++idx) {
        const auto& elem = f1Vec[idx]; // access to the variant element
        elem.currentFieldExec(PropDispatchHelper(*this));
    }
    ...
}
```
The code above iterates over received `<variant>` fields in the list and dispatches them for
proper processing using `currentFieldExec()` member function. Note, that at the time of the processing
the `read()` operation has been successfully completed and the index of the member (**0** based) in 
order of their definition is held as a private data and can be retrieved using 
[comms::field::Variant::currentField()](https://commschamp.github.io/comms_doc/classcomms_1_1field_1_1Variant.html)
member function. Please pay attention that this is a **run-time** (not compile-time) information and the
actual type of the stored value (to cast to) needs to be determined at run-time. The `currentFieldExec()`
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
See also the documentation on [comms::field::Variant::currentFieldExec()](https://commschamp.github.io/comms_doc/classcomms_1_1field_1_1Variant.html).

Note that `operator()` above in addition to actual type of the member receives also the index of the
detected member as a template parameter, so the run-time information of the index becomes a compile-time
one. In many cases the compile-time information about the detected member index is not really needed (like
in this example) and can be safely ignored. What is used in this example is the actual type of the member. 
Once the type of the held member is determined, its handling is forwarded to appropriate `ClientSession::handleProp()`
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
The `handleProp()` in turn prints the values of the detected property `<bundle>`. As the result
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
The `currentFieldExec()` member function provided by the 
[comms::field::Variant](https://commschamp.github.io/comms_doc/classcomms_1_1field_1_1Variant.html) field 
implements static binary search (**O(log(n)** complexity) with similar logic to the code below to determine 
the real type to cast to.
```cpp
auto totalCount = ...; // Total number of defined memebers
auto idx = currentField();
if (idx < totalCount/2) {
    if (idx < totalCount/4) {
        ...
    }
    else {
        ...
    }
}
else {
    if (idx < (totalCount*3)/4) {
        ...
    }
    else {
        ...
    }
}
```
It gets the job done, however the [commsdsl2comms](https://github.com/commschamp/commsdsl) code generator
overrode the definition of inherited `currentFieldExec()` from [comms::field::Variant](https://commschamp.github.io/comms_doc/classcomms_1_1field_1_1Variant.html)
with a custom [implementation](include/tutorial4/field/KeyValueProp.h):
```cpp
template <typename TFunc>
void currentFieldExec(TFunc&& func) 
{
    switch (Base::currentField()) {
    case FieldIdx_prop1:
        memFieldDispatch<FieldIdx_prop1>(accessField_prop1(), std::forward<TFunc>(func));
        break;
    case FieldIdx_prop2:
        memFieldDispatch<FieldIdx_prop2>(accessField_prop2(), std::forward<TFunc>(func));
        break;
    case FieldIdx_prop3:
        memFieldDispatch<FieldIdx_prop3>(accessField_prop3(), std::forward<TFunc>(func));
        break;
    default:
        COMMS_ASSERT(!"Invalid field execution");
        break;
    }
}
```
The modern compilers generate quite efficient binary code based on dispatch tables for handling 
such `switch` statements with **O(1)** run-time complexity. As the result the code above usually
gives a better runtime as well as compile time performance.

Note usage of `FieldIdx_X` compile time values as well as `accessField_X()` member functions. They
get generated by the `COMMS_VARIANT_MEMBERS_NAMES()` macro. The `FieldIdx_X` gives us an index
of the detected member, while `accessField_X()` just gives as an access to the storage area
(which already is properly initialized and holds the required data)
with cast to the appropriate type.

Similar `switch` statement based functionality for better compilation times as well as runtime performance
is generated for other member functions like `write()`, `refresh()`, `length()`, `valid()`, `reset()`, etc...
```cpp
template <typename TIter>
comms::ErrorStatus write(TIter& iter, std::size_t len) const
{
    switch (Base::currentField()) {
    case FieldIdx_prop1: return accessField_prop1().write(iter, len);
    case FieldIdx_prop2: return accessField_prop2().write(iter, len);
    case FieldIdx_prop3: return accessField_prop3().write(iter, len);
    default: break;
    }

    return comms::ErrorStatus::Success;
}
```

## Type-Length-Value (TLV) Triplets
There are protocols that introduce additional **length** information in their _properties_ definition
to make them type-length-value (TLV) triplets. Let's take a look how such triplet is defined in
this tutorial.
```xml
<enum name="PropKey" type="uint8">
    ...
    <validValue name="K4" val="10" />
    <validValue name="K5" val="15" />
    <validValue name="K6" val="25" />
</enum>

<int name="PropKeyCommon" type="uint8" failOnInvalid="true"/>

<variant name="TlvProp">
    <description>
        Type-Length-Value Property
    </description>
    <members>
        <bundle name="Prop4">
            <int reuse="PropKeyCommon" name="Key" defaultValidValue="PropKey.K4" />
            <int name="Length" type="uint8" semanticType="length" />
            <int name="Val" type="uint32" />
        </bundle>
        
        <bundle name="Prop5">
            <int reuse="PropKeyCommon" name="Key" defaultValidValue="PropKey.K5" />
            <int name="Length" type="uint8" semanticType="length" />
            <float name="Val" type="double" defaultValue="inf" />
        </bundle>            
        
        <bundle name="Prop6">
            <int reuse="PropKeyCommon" name="Key" defaultValidValue="PropKey.K6" />
            <int name="Length" type="uint8" semanticType="length" />
            <string name="Val" />
        </bundle>   
        
        <bundle name="Prop7">
            <int reuse="PropKeyCommon" name="Key" defaultValidValue="PropKey.K7" />
            <int name="Length" type="uint8" semanticType="length" />
            <int name="Val" type="uint64" availableLengthLimit="true" />
        </bundle>  
        
        <bundle name="Any">
            <int reuse="PropKeyCommon" name="Key" failOnInvalid="false" />
            <int name="Length" type="uint8" semanticType="length" />
            <data name="Val" />
        </bundle>  
    </members>
</variant>
```

----

**SIDE NOTE**: In case the `<variant>` field contains other XML child nodes in addition to
member fields definition (like `<description>` in the example above), the member fields need to
be defined as children of `<members>` XML node.

----

The definition of the `<variant>` field above very similar to [Key-Value Pairs](#key-value-pairs)
explained earlier, but with additional
`<int>` field of `Length` between the *Key* and *Val*. Note usage of `semanticType="length"`
property. It is very important to use in order to notify the code generator about special role of this field.

**IMPORTANT**: The the value of the length field (the one with `semanticType="length"`) always contains
the **remaining** length to consume until the end of the field **NOT** including the length of the field
itself. Some protocols may define such field that includes its own length (sometimes even the length of 
preceding key). In such case you need to use **serOffset** property to force adding extra offset for the
serialized value. It would be defined like this:
```xml
<int name="Length" type="uint8" semanticType="length" serOffset="1" />
```

Also note that the `<string>` value field inside `Prop6` does not require additional length prefix
(compared to previous **Key-Value** example). The preceding **Length** field does the job of limiting the
length of the string.

Many developers often wonder who and why would use **TLV** type of properties instead of **Key-Value** ones. If
you take a look at `Prop4` definition, the length will always be **4** bytes (because there is `<int>`
4 bytes long field that follows). Hence, the preceding field of **length** seems to be redundant.

The primary reason to prefer **TLV** properties over **Key-Value** ones is to allow future **forward** compatibility
of the protocol. Let's assume the future version of the protocol adds new property to the ones previously defined.
The older client operating with **Key-Value** types of properties doesn't have any information on how long the unknown property is
when a message containing it is received. The client doesn't have any other choice, but to ignore the rest of the data 
(in best case scenarios) and/or drop the whole message decoding (in most cases). When operating with **TLV** type
of properties, the client has an information about received property length and can skip over and ignore unknown
ones. 

The example above allows ignoring and skipping over unknown properties by defining the **last** member (`Any`) with non-failing
read operation on the `Key`. The latter in the example above doesn't specify which values are considered to be
valid (hence all possible ones are valid). The `Val` in such property is defined to be `<data>`.

Th **TLV** type of properties also allows reducing serialization length of some value types. The example of
is is the definition of `Prop7`. The default serialization length of its `Val` member value (of `uint64` type) is 8 bytes.
However, usage of **availableLengthLimit** property allows having less bytes when value is serialized if the 
stored value allows. The length of such serialization is controlled by the preceding `Length` member.

The `Msg2` in this tutorial is defined to contain a list of **TLV** properties.
```xml
<message name="Msg2" id="MsgId.M2" displayName="^Msg2Name">
    <list name="F1" element="TlvProp" />
</message> 
```

----

**SIDE NOTE**: In this example the length of `F1` list is not bound by any means. It means that the read operation
of the list will continue until the end of the input buffer. As the result such message is not really extendable,
it's impossible to add new fields after the list.

----

Now, it's time to take a look at how such message is prepared to be sent out.
```cpp
void ClientSession::sendMsg2()
{
    Msg2 msg;

    auto& listOfProps = msg.field_f1().value(); // vector of variant fields
    listOfProps.resize(4);
    assert(msg.doLength() == 0U);
    assert(!listOfProps[0].valid());
    assert(!listOfProps[1].valid());
    assert(!listOfProps[2].valid());
    assert(!listOfProps[3].valid());

    listOfProps[0].initField_prop4().field_val().value() = 0xdeadbeef;
    listOfProps[1].initField_prop6().field_val().value() = "blabla";
    listOfProps[2].initField_prop5().field_val().value() = 1.234;
    listOfProps[3].initField_prop7().field_val().value() = 100;

    msg.doRefresh(); // Bring message to a consistent state
    sendMessage(msg);
}
```
It looks very similar to the previously explained `sendMsg1()` (which worked with **Key-Value** type
of properties) with one key difference of call to `doRefresh()` member function of the message object.
It is required to bring the field contents into a **consistent** state. Note, that the code above
updates only values of `Val` member, while the value of the `Length` remains unchanged (default constructed as **0**).
When such field is serialized, the other end may fail to deserialize such message correctly. There is a need
to update the `Length` information in accordance with the value of the `Val` field that follows. The call
to `doRefresh()` does exactly that. It is possible to update the `Length` information by other means, such
as writing relevant explicit code, but such approach is obviously not recommended. It might create a boilerplate
error-prone code.

----

**SIDE NOTE**:

- The `doRefresh()` member function of the message object is a **non-virtual** one which iterates over all the member
  fields and calls their `refresh()` member function.
- The `refresh()` member function of the `<list>` field will call `refresh()` member function of all the
  stored fields (`<variant>`-s).
- The `refresh()` member function of the `<variant>` field will call `refresh()` member function of the
  actual member (`<bundle>`) it contains at the moment.
- Every definition of such `<bundle>` member (inside [include/tutorial4/field/TlvProp.h](include/tutorial4/field/TlvProp.h))
  uses `comms::option::def::RemLengthMemberField<>` option in their definition (generated as the result of
  `semanticType="length"` assignment). It notifies the 
  [COMMS Library](https://github.com/commschamp/comms) about the existence of the
  `Length` field inside the [comms::field::Bundle](https://commschamp.github.io/comms_doc/classcomms_1_1field_1_1Bundle.html)
  and allows implementation of the correct `refresh()` functionality.


**ANOTHER SIDE NOTE**: As a reminder, all the message definitions (the ones that extend 
[comms::MessageBase](https://commschamp.github.io/comms_doc/classcomms_1_1MessageBase.html))
define multiple **non-virtual** `do*()` member functions (including `doRefresh()` mentioned earlier).
In order to call them the actual type of the message needs to be known. It is possible to implement
automatic unconditional call to the **refresh** functionality for every message before being sent. To do 
so there is a need to add support for polymorphic (**virtual**) refresh functionality in the message
interface definition:
```cpp
using Message =
    tutorial4::Message<
        ...,
        comms::option::app::RefreshInterface // Support polymorphic refresh
    >;
```
The function that sends the message out needs to be changed to call the polymorphic `refresh()`
member function before message being serialized.
```cpp

void ClientSession::sendMessage(Message& msg)
{
    msg.refresh(); // polymorphic call
    ...
}
```
The `refresh()` functionality is **non-const** because it might modify the message object contents. As the
result the function signature needs also to be changed to receive reference to **non-const** message object.

----

Handling of the `Msg2` inside `void ClientSession::handle(Msg2& msg)` is very similar to handling of
the `Msg1` described earlier. It uses the same `PropDispatchHelper` with call to `currentFieldExec()` to
dispatch held property into appropriate `ClientSession::handleProp()` member function.

## Summary

- The heterogeneous fields are defined using `<variant>` XML node of
  [CommsDSL](https://github.com/commschamp/CommsDSL-Specification).
- Usually the heterogeneous fields are defined as **Key-Value** pairs or **Type-Length-Value** (**TLV**)
  triplets.
- The **TLV** variant is usually chosen when **forward** compatibility of the protocol is important.
- In **TLV** variant it is required to mark the `Length` field with `semanticType="length"` attribute.
- The `Length` inside **TLV** always represents the **remaining** length of the value that follows **NOT**
  including its own length. If length of the `Length` field needs to be included, then **serOffset** 
  property needs to be used.
- When **TLV** variant is prepared to be sent out, quite often it ends up being in an inconsistent state
  (the `Length` information needs to be updated contain the right length of the value that follows). To
  do so the field/message contents need to be `refresh()`-ed.
- When the actual message type is known it is recommended to call `doRefresh()` **non-virtual** member function
  of the message object to bring it to consistent state. 
- When actual message object is not known (referenced by the interface class), the interface class needs to
  provide polymorphic refresh using `comms::option::app::RefreshInterface` option and then polymorphic call to the `refresh()` 
  member function of the interface becomes available.
- All the `<variant>` fields are defined by extending
  [comms::field::Variant](https://commschamp.github.io/comms_doc/classcomms_1_1field_1_1Variant.html) class.
- All the member fields are named using `COMMS_VARIANT_MEMBERS_NAMES()` macro.
- For every member name `X` there is compile-time known `FieldIdx_X` numeric index as well as 
  `initField_X()` member function used to initialize the member, and `accessField_X()` to access
  the member that was properly initialized before. The `deinitField_X()` member functions are usually not
  expected to be used by the client code, but by the `reset()` to be able to destruct the held member correctly.
- At run-time after the successful **read** operation the index of the held member can be retrieved using
  [comms::field::Variant::currentField()](https://commschamp.github.io/comms_doc/classcomms_1_1field_1_1Variant.html)
  member function.
- To determine the type of the held member and dispatch it to the appropriate handler the 
  `currentFieldExec()` member function needs to be used (see 
  [comms::field::Variant::currentFieldExec()](https://commschamp.github.io/comms_doc/classcomms_1_1field_1_1Variant.html)
  for documentation).

[Read Previous Tutorial](../tutorial3) &lt;-----------------------&gt; [Read Next Tutorial](../tutorial5) 
