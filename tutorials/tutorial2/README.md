# Tutorial 2
Introduction to message fields definitions and their usage.

## Multiple CommsDSL Schema Files
The [CommsDSL](https://github.com/arobenko/CommsDSL-Specification) specification 
as well as [commsdsl2comms](https://github.com/arobenko/commsdsl) code generator
allow usage of multiple schema files for the same protocol definition. It can
be used to split protocol definition into multiple sub-sections for convenience,
especially when protocol is quite big and it becomes difficult to find and update
things in the single schema file.

The [CommsDSL](https://github.com/arobenko/CommsDSL-Specification) does not
have any "include" statements. Instead the code generated must process the
schema files in the provided order and allow references to the other elements
if they were defined **before** being referenced (in earlier processed schema
file or earlier in the same file).

The [CMakeLists.txt](CMakeLists.txt) file of this tutorial code creates a list
of schema files, which are processed by the 
[commsdsl2comms](https://github.com/arobenko/commsdsl) code generator in the
specified order.
```
set (schema_files
    ${CMAKE_CURRENT_SOURCE_DIR}/dsl/main.xml
    ${CMAKE_CURRENT_SOURCE_DIR}/dsl/msg1.xml
    ${CMAKE_CURRENT_SOURCE_DIR}/dsl/msg2.xml
    ...
)
```

NOTE, that when splitting schema into multiple files, the **first**
processed file must properly define protocol name and endian (see 
[dsl/main.xml](dsl/main.xml)).
```
<?xml version="1.0" encoding="UTF-8"?>
<schema name="tutorial2" endian="big">
    ...
</schema>
```
All the subsequent files **may** (but don't have to) omit such definition (
see [dsl/msg1.xml](dsl/msg1.xml)).
```
<?xml version="1.0" encoding="UTF-8"?>
<schema>
    ...
</schema>
```

## Framing
This tutorial uses the following framing for all the messages:
```
<frame name="Frame">
    <size name="Size">
        <int name="SizeField" type="uint16" />
    </size>
    <id name="ID">
        <field>
            <ref field="MsgId" />
        </field>
    </id>
    <payload name="Data" />
</frame>
```
In other words it is:

- 2 bytes of remaining length (ID + PAYLOAD), not including the length field itself.
- 1 byte of numeric message ID.
- N bytes of payload itself.

## Defining Fields
Every message may define internal fields. Let's take a look inside [dsl/msg1.xml](dsl/msg1.xml).
```
<message name="Msg1" id="MsgId.M1" displayName="Message 1">
    <ref name="F1" field="I1" />
    <int name="F2" type="int16" />
</message>
```
The message can define its field internally:
```
<int name="F2" type="int16" />
```
or reference the previously defined global field (using **&lt;ref&gt;** node):
```
<ref name="F1" field="I1" />
```
The globally defined fields need to reside inside **&lt;fields&gt;** XML node:
```
<fields>
    <int name="I1" type="uint8" />
    ...
</fields>
```
The code generated for every message and its fields resides inside the 
[include/tutorial2/message](include/tutorial2/message) folder. The primary
file containing definition of `Msg1` message class is
[include/tutorial2/message/Msg1.h](include/tutorial2/message/Msg1.h). 
Let's take a look inside. It contains two class / struct definitions:
```cpp
template <typename TOpt = tutorial2::options::DefaultOptions>
struct Msg1Fields
{
    ...
}; 

template <typename TMsgBase, typename TOpt = tutorial2::options::DefaultOptions>
class Msg1 : public comms::MessageBase<...>
{
    ...
};
```

The `Msg1` class is the one that defines the actual message, while `Msg1Fields` is
the wrapping `struct` that contains definitions of the `Msg1` member fields.

The secondary file containing `Msg1` and its fields related definitions is
[include/tutorial2/message/Msg1Common.h](include/tutorial2/message/Msg1Common.h). 
It contains common definitions of `Msg1` message as well as its fields, which are 
template parameters independent and common for all `Msg1` instantiations. 

As was mentioned earlier, the `Msg1` references external field `I1`. All the 
global fields (if referenced) end up being defined in separate file(s) inside
[include/tutorial2/field](include/tutorial2/field) folder.

The mentioned `I1` field is defined inside 
[include/tutorial2/field/I1.h](include/tutorial2/field/I1.h) and its common,
template parameters independent definitions reside in 
[include/tutorial2/field/I1Common.h](include/tutorial2/field/I1Common.h)

Note, that [dsl/msg1.xml](dsl/msg1.xml) file also contains definition of
a dummy field, which is not referenced anywhere.
```
<int name="Dummy" type="uint8" description="Not referenced anywhere" />
```
If the field is not referenced anywhere the 
[commsdsl2comms](https://github.com/arobenko/commsdsl) code generator 
does **NOT** generate unnecessary definition file(s).

## Client / Server Sessions
Both server and client sessions are very similar to the ones 
presented in [tutorial1](../tutorial1). The **server** is just the simple
"echo" one, which decodes and then sends the same message back to the client.

The client prepares and sends messages one-by-one to the server. As the result,
in order to demonstrate working with fields, this tutorial will focus on the
client side session code. In the real life application working with fields on
the sever side is no different than on the client.

## Working With Field Classes
In general, every field is an abstraction wrapper around value storage in
order to provide common interface for all the fields. All the presented later
supported field types will have the following public member types and functions:
```
class SomeField
{
public:
    // Define type used to store the field value
    using ValueType = ...;
    
    // Access to stored field value
    ValueType& value();
    const ValueType& value() const;
    
    // Read the field value
    template <typename TIter>
    comms::ErrorStatus read(TIter& iter, std::size_t len);
    
    // Write the field value
    tempalte <typename TIter>
    comms::ErrorStatus write(TIter& iter, std::size_t) const;
    
    // Get the serialization length of the stored value
    std::size_t length() const
    
    // Get compile time known min and max serialization length of the field
    static constexpr std::size_t minLength();
    static constexpr std::size_t maxLength();
    
    // Check that field has the valid value
    bool valid() const;
    
    // Bring field into a consistent state, will be explained in one
    // of the later tutorials
    bool refresh();
    
    // Get human readable name of the field 
    static const char* name();
};
```
Please note the following

- The main and most frequently used member functions are **value()** ones. The
rest are automatically used by the message class definition in order to
implement message class functionality. In most cases these other member functions
won't be used by the end application.
- The stored value access **value()** member function returns reference to 
the stored value and can be used to assign value to the field as well.
- All of the field abstraction member functions are **NON-virtual**, i.e. fields
don't exhibit polymorphic behavior.
- The iterators to **read()** and **write()** member functions are passed by
reference and are advanced during the operation.
- All of the presented member functions are provided by the 
[COMMS Library](https://github.com/arobenko/comms_champion#comms-library) except
**name()** which is a product of **commsdsl2comms** code generation.

Let's also take a look inside the message class definition.
```cpp
template <typename TMsgBase, typename TOpt = tutorial2::options::DefaultOptions>
class Msg1 : public
    comms::MessageBase<
        ...,
        comms::option::def::FieldsImpl<typename Msg1Fields<TOpt>::All>,
        ...
    >
{
    ...
public:
    ...
    COMMS_MSG_FIELDS_NAMES(
        f1,
        f2
    );
    ...    
};
```
Usage of `comms::option::def::FieldsImpl` option lets the 
[comms::MessageBase](https://arobenko.github.io/comms_doc/classcomms_1_1MessageBase.html)
base class know the types of fields the message has. As the result the `comms::MessageBases`
has defines the following member types and functions that allow external access to the fields
```cpp
template <typename TMsgBase, typename TOpt = tutorial2::options::DefaultOptions>
class Msg1 
{
public:
    // Type of tuple containing all member fields
    using AllFields = typename Msg1Fields<TOpt>::All;
    
    // Access tuple of fields
    AllFields& fields();
    const Allfields& fields() const;
};
```

Just using these member functions it is possible to access the fields while
providing the index of the field.
```
auto& msgFields = msg.fields();
auto& f1 = std::get<0>(msgFields);
auto& f2 = std::get<1>(msgFields);

f1.value() = 1;
f2.value() = 100;
```
However, accessing the fields by hard-coded numeric indices is quite
inconvenient, not to mention being a bad practice. That's what
usage of `COMMS_MSG_FIELDS_NAMES()` macro comes to resolve. It receives 
arguments, which are names of the fields (**f1** and **f2**) and results in generating the 
following types and member functions:
```cpp
template <typename TMsgBase, typename TOpt = tutorial2::options::DefaultOptions>
class Msg1 : public
    comms::MessageBase<...>
{
public:
    // Enum with access indices names
    enum FieldIdx
    {
        FieldIdx_f1,
        FieldIdx_f2,
        FieldIdx_numOfValues
    };
    
    // Alias types to member fields
    using Field_f1 = Msg1Fields<TOpt>::F1;
    using Field_f2 = Msg1Fields<TOpt>::F2;
    
    // Convenience access to member fields
    Field_f1& field_f1();
    const Field_f1& field_f1() const;
    
    Field_f2& field_f2();
    const Field_f2& field_f2() const;
    ...    
};
```
Please pay attention to the following:

- According to [CommsDSL](https://github.com/arobenko/CommsDSL-Specification) specification
the code generator (**commsdsl2comms**) is allowed to change the first latter of the
field name by either capitalizing or making it a lower case. That's what happens
with `Msg1` member fields. When their class is defined the first letter is capitalized,
while the access names changed to start with lower case.
- The provided names ('f1', 'f2') find their way to `FieldIdx_x` enum values, inner
`Field_x` alias types and `field_x()` access member functions.

Usage of the access member functions can be demonstrated in the function that prepares and
sends the `Msg1` to the server:
```cpp
void ClientSession::sendMsg1()
{
    Msg1 msg;
    msg.field_f1().value() = 1;
    msg.field_f2().value() = 100;
    sendMessage(msg);
}
```
also when the message is received back from the server and its contents are printed:
```cpp
void ClientSession::handle(Msg1& msg)
{
    std::cout << "Received \"" << msg.doName() << "\" with ID=" << msg.doGetId() << '\n' <<
        '\t' << msg.field_f1().name() << " = " << (unsigned)msg.field_f1().value() << '\n' <<
        '\t' << msg.field_f2().name() << " = " << msg.field_f2().value() << '\n' << std::endl;
    ...
}

```

## Supported Field Types
The [CommsChampion Ecosystem](https://arobenko.github.io/cc) has multiple 
supported field types which are covered below one by one. Due to the nature of
these tutorials it is not possible to cover **all** aspects (properties) of all
the available fields, it is highly recommended to read 
[CommsDSL](https://github.com/arobenko/CommsDSL-Specification) specification in
full after this tutorial.

In general, the fields are defined as XML node. Available field types are:

- [&lt;enum&gt;](#enum-fields) - Enumeration values.
- [&lt;int&gt;](#int-fields) - Integral values.
- [&lt;set&gt;](#set-fields) - Bitset where every bit has different meaning (up to 64 bits).
- [&lt;float&gt;](#float-fields) - Floating point values.
- [&lt;string&gt;](#string-fields) - Strings.
- [&lt;data&gt;](#data-fields) - Raw binary data.
- [&lt;bundle&gt;](#bundle-fields) - Bundling of multiple fields into a single composite field.
- [&lt;bitfield&gt;](#bitfield-fields) - Similar to **&lt;bundle&gt;**, but allows member fields
having length in bits (not bytes), up to max of 64 bits.
- **&lt;list&gt;** - List of fields.
- **&lt;variant&gt;** - Union of possible fields, containing one value of any
time, suitable for creation of heterogeneous lists.
- **&lt;ref&gt;** - Reference (alias) to any other field.
- **&lt;optional&gt;** - Wrapper around any other field to make the latter optional.

Every field type has its own set of properties. However, there are also properties
which are common for **all** the fields. Here are some of them:

- **name** - Name of the field, will end up being a class name when appropriate
field type is being defined.
- **displayName** - Specifies a human readable name of the field. If not specified
defaults to be the same as **name**. The value of this property finds its way to
be returned of the **name()** member function of the field.
- **description** - Description of the field, will find its way into the field's
doxygen documentation.

**SIDE NOTE**: The [CommsDSL](https://github.com/arobenko/CommsDSL-Specification)
supports multiple ways to set the field's property value with the same end result:

- As attribute's value:
```
<int name="F1" ... />
```
- As child node with **value** property:
```
<int ...>
    <name value="F1" />
</int>
```
- As child node text:
```
<int ...>
    <name>F1</name>
</int>
```

### &lt;enum&gt; Fields
The `Msg2` message (defined inside [dsl/msg2.xml](dsl/msg2.xml)) is there to
demonstrate usage of enum fields. Let's take a look inside. There is definition
of external field `E2_1` which is referenced by the `Msg1` definition:
```
<fields>
    <enum name="E2_1" type="uint8">
        <validValue name="V1" val="0" description="Some value" />
        <validValue name="V2" val="1" />
        <validValue name="V3" val="2" />
    </enum>

...
</fields>

<message name="Msg2" id="MsgId.M2" displayName="Message 2">
    <ref name="F1" field="E2_1" />
    ...
</message>    
```
As the result the field definition will reside in 
[include/tutorial2/field/E2_1.h](include/tutorial2/field/E2_1.h) with its
common, template parameters independent types and functions in
[include/tutorial2/field/E2_1Common.h](include/tutorial2/field/E2_1Common.h)

Please note the following:

- Internal `ValueType` of the field is defined to be `tutorial2::field::E2_1Val`,
which in turn is alias to `tutorial2::field::E2_1Common::ValueType`. Both defined
in [include/tutorial2/field/E2_1Common.h](include/tutorial2/field/E2_1Common.h).
- The value of **type** property in XML definition (`uint8`) is an underlying type of the
generated `enum` and is also used to determine serialization length of the field.
```cpp
struct E2_1Common
{
    ...
    enum class ValueType : std::uint8_t
    {
        ...        
    };
    ...
};

```
- Underlying type is specified using **type** property.
- Supported values of underlying type are: **int8**, **uint8**, **int16**,
**uint16**, **int32**, **uint32**, **int64**, **uint64**, **intvar**, **uintvar**.
- Many elements in [CommsDSL](https://github.com/arobenko/CommsDSL-Specification)
schema have **description** property, which finds its way to element's doxygen
documentation.
- There are extra `enum` values added by the code generator for convenience:
```cpp
struct E2_1Common
{
    ...
    enum class ValueType : std::uint8_t
    {
        ...  
        // --- Extra values generated for convenience ---
        FirstValue = 0, ///< First defined value.
        LastValue = 2, ///< Last defined value.
        ValuesLimit = 3, ///< Upper limit for defined values.
    };
    ...
};

```
- The field is defined using 
[comms::field::EnumValue](https://arobenko.github.io/comms_doc/classcomms_1_1field_1_1EnumValue.html) 
class provided by the [COMMS Library](https://github.com/arobenko/comms_champion#comms-library).
- The field's value is considered to be valid (determined by the call to the
`valid()` member function) if it is equal to one of
the **&lt;validValue&gt;**-es. It is implemented by using `comms::option::def::ValidNumValueRange`
option provided by the [COMMS Library](https://github.com/arobenko/comms_champion#comms-library).
```cpp
template <typename TOpt = tutorial2::options::DefaultOptions, typename... TExtraOpts>
class E2_1 : public
    comms::field::EnumValue<
        ...
        comms::option::def::ValidNumValueRange<0, 2>
    >
{
    ...
};
```

There is also a definition
of external `enum` field `E2_2` which is referenced by the `Msg1` definition:
```
<fields>
    <enum name="E2_2" type="uint16" defaultValue="V2">
        <validValue name="V1" val="0" />
        <validValue name="V2" val="100" />
        <validValue name="V3" val="0x10f" />
    </enum>        


...
</fields>

<message name="Msg2" id="MsgId.M2" displayName="Message 2">
    ...
    <ref name="F2" field="E2_2" />
    ...
</message>
```    
This field definition will reside in 
[include/tutorial2/field/E2_2.h](include/tutorial2/field/E2_2.h) with its
common, template parameter's independent types and functions in
[include/tutorial2/field/E2_2Common.h](include/tutorial2/field/E2_2Common.h)

Please note the following:

- By default the value of the default-constructed `enum` field object is `0`. It
is possible to change it using **defaultValue** property of the field, which can
have either numeric value of reference one of its **&lt;valueValue&gt;**-es. In
case of `E2_2` it is `V2`. It is implemented using `comms::option::def::DefaultNumValue`
option passed to the class definition.
- Any numeric value can be assigned as decimal or or as hexadecimal value prefixed
with `0x`.
- When the **&lt;valueValue&gt;**-es cannot be unified into one range, the 
[COMMS Library](https://github.com/arobenko/comms_champion#comms-library)
allows usage of multiple `comms::option::def::ValidNumValue` options:
```cpp
template <typename TOpt = tutorial2::options::DefaultOptions, typename... TExtraOpts>
class E2_2 : public
    comms::field::EnumValue<
        ...
        comms::option::def::ValidNumValue<0>,
        comms::option::def::ValidNumValue<100>,
        comms::option::def::ValidNumValue<271>
    >
{
    ...
};
```

The `Msg2` message defines its third field internally:
```cpp
<message name="Msg2" id="MsgId.M2" displayName="Message 2">
    ...
    <enum name="F3" type="int8" description="Some Inner enum" defaultValue="V3">
        <validValue name="V1" val="-100" />
        <validValue name="V2" val="0" />
        <validValue name="V3" val="10" />
    </enum>
    ...
</message> 
```
In this case, the field itself is defined as member of 
[tutorial2::message::Msg2Fields](include/tutorial2/message/Msg2.h) and its
common, template parameters independent definition is a member of
[tutorial2::message::Msg2FieldsCommon](include/tutorial2/message/Msg2Common.h)

The fourth `enum` field of the `Msg2` is also defined internally:
```cpp
<message name="Msg2" id="MsgId.M2" displayName="Message 2">
    ...
    <enum name="F4" type="uint16" hexAssign="true">
        <validValue name="V1" val="0" displayName="Value 1"/>
        <validValue name="V2" val="0xff"  displayName="Value 2"/>
        <validValue name="V3" val="0x2ff" displayName="Value 3"/>
        <validValue name="V4" val="0xfff" displayName="Value 4"/>
    </enum>
    ...
</message> 
```

Please note the setting of **hexAssign** boolean property to **true**. It results
in having hexadecimal values assigned (instead of usual decimals) in the generated
code. It can improve the generated code clarity in in some cases.
```cpp
struct Msg2FieldsCommon
{
    ...
    struct F4Common
    {
        enum class ValueType : std::uint16_t
        {
            V1 = 0x0000U, ///< value @b V1
            V2 = 0x00FFU, ///< value @b V2
            V3 = 0x02FFU, ///< value @b V3
            V4 = 0x0FFFU, ///< value @b V4
            ...
        };
    };    
};
```

Now, let's take a look at the code that prepares `Msg2` to be sent out
to the server. It demonstrates usage of several ways to reference the actual
enumeration value to be assigned to the field.
```cpp
void ClientSession::sendMsg2()
{
    Msg2 msg;
    msg.field_f1().value() = tutorial2::field::E2_1Val::V2;
    msg.field_f2().value() = tutorial2::field::E2_2Common::ValueType::V3;
    msg.field_f3().value() = Msg2::Field_f3::ValueType::V1;
    comms::cast_assign(msg.field_f4().value()) = 0xff;
    sendMessage(msg);
}
```
Note, that sometimes there may be a need to assign value of different type
with a cast. The [COMMS Library](https://github.com/arobenko/comms_champion#comms-library)
provides `comms::cast_assign()` stand-alone helper function which automatically casts the value
on the right side of the assignment operation to appropriate type and assigns it
to the value specified on the left side. It eliminates the necessity to explicitly specify
cast type. To use the `comms::cast_assign()` function it is necessary to
include [comms/cast.h](https://arobenko.github.io/comms_doc/cast_8h.html) header file.
```
#include "comms/cast.h"
```

The definition of the enum fields also provides `valueName()` member function
which allows retrieval of the human readable name of the current value. Note, that
by default the value's name is the value of **name** property of the **&lt;validValue&gt;**
XML note, unless **displayName** property is set, which takes over. 
The usage of the `valueName()` member function is demonstrated inside 
message handling function when the received message content is printed:
```cpp
void ClientSession::handle(Msg2& msg)
{
    std::cout << "Received \"" << msg.doName() << "\" with ID=" << msg.doGetId() << '\n' <<
        '\t' << msg.field_f1().name() << " = " << (unsigned)msg.field_f1().value() << " (" << msg.field_f1().valueName()  << ")\n" <<
        '\t' << msg.field_f2().name() << " = " << (unsigned)msg.field_f2().value() << " (" << msg.field_f2().valueName()  << ")\n" <<
        '\t' << msg.field_f3().name() << " = " << " (" << msg.field_f3().valueName()  << ")\n" <<
        '\t' << msg.field_f4().name() << " = " << (unsigned)msg.field_f4().value() << " (" << msg.field_f4().valueName()  << ")\n" <<
        std::endl;

    ...
}

```

### &lt;int&gt; Fields
The `Msg3` message (defined inside [dsl/msg3.xml](dsl/msg3.xml) and implemented
in [include/tutorial2/message/Msg3.h](include/tutorial2/message/Msg3.h)) is there to
demonstrate basic usage of integral fields. The previous section showed that
the fields can be defined as global ones or internally as members of 
**&lt;message&gt;** XML node. For reference and demonstration convenience, the
explained fields in this and most of subsequent section will be defined as
global ones and referenced using **&lt;ref&gt;** XML node.

The first defined **&lt;int&gt;** field is:
```
<fields>
    <int name="I3_1" type="int32" defaultValue="10" />
    ...
</fields>

<message name="Msg3" id="MsgId.M3" displayName="Message 3">
    <ref name="F1" field="I3_1" />
    ...
</message>
```

Please note the following:

- The storage type of the field is specified using **type** property. The
supported types are the same as for `enum` field: **int8**, **uint8**, 
**int16**, **uint16**, **int32**, **uint32**, **int64**, **uint64**, 
**intvar**, and **uintvar**.
- The numeric value of the default constructed field specified using
**defaultValue** property.
- The field is defined using 
[comms::field::IntValue](https://arobenko.github.io/comms_doc/classcomms_1_1field_1_1IntValue.html) 
class provided by the [COMMS Library](https://github.com/arobenko/comms_champion#comms-library).
- The generated code resides in [include/tutorial2/field/I3_1.h](include/tutorial2/field/I3_1.h)
file.

In this particular example, the field's value is not updated when message is
prepared for sending and assert statement checks that the field has assumed
default value (**10**).
```cpp
void ClientSession::sendMsg3()
{
    Msg3 msg;
    assert(msg.field_f1().value() == 10); // Keep default value of f1
    ...
}

```

The second defined **&lt;int&gt;** field is:
```
<fields>
    <int name="I3_2" type="uint32" length="3" />
</fields>

<message name="Msg3" id="MsgId.M3" displayName="Message 3">
    ...
    <ref name="F2" field="I3_2" />
    ...
</message>
```
The generated code resides in [include/tutorial2/field/I3_2.h](include/tutorial2/field/I3_2.h).

Please note the usage of **length** property. It can be used to limit
serialization length of the specified field to lower number of bytes. In the
example above, it is limited to be **3** bytes instead of default **4** (due
to **uint32** storage type). In this case the 
[COMMS Library](https://github.com/arobenko/comms_champion#comms-library)
will serialize the field using correct number of bytes.
```cpp
void ClientSession::sendMsg3()
{
    ...
    msg.field_f2().value() = 0xabcdef;
    assert(msg.field_f2().length() == 3U); // the f2 has fixed length of 3 bytes
    static_assert(Msg3::Field_f2::minLength() == 3U, "Invalid assumption");
    static_assert(Msg3::Field_f2::maxLength() == 3U, "Invalid assumption");
    ...
}
```
Let's take a closer look at the code snippet above. The `f2` field object has
a member function `length()` that can be used at runtime to determine current
serialization length of the field and `minLength()` as well as `maxLength()`
static member functions that can be used at compile time to verify minimal and
maximal serialization lengths of the field.

The third defined **&lt;int&gt;** field uses variable length encoding:
```
<fields>
    <int name="I3_3" type="uintvar" length="4" />
</fields>

<message name="Msg3" id="MsgId.M3" displayName="Message 3">
    ...
    <ref name="F3" field="I3_3" />
    ...
</message>
```
The variable length **type** uses [Base-128](https://en.wikipedia.org/wiki/LEB128)
encoding by default and no other encoding is **currently** implemented / supported.

**SIDE NOTE**: In case there is a need for any other standard encoding please create a request
issue for [commsdsl](https://github.com/arobenko/commsdsl) project.

The value of the **length** property in the case above means **maximal** 
allowed serialization length of the field. The 
[generated code](include/tutorial2/field/I3_3.h)
uses `comms::option::VarLength` option to provide the required information to
the [COMMS Library](https://github.com/arobenko/comms_champion#comms-library).
```cpp
template <typename TOpt = tutorial2::options::DefaultOptions, typename... TExtraOpts>
struct I3_3 : public
    comms::field::IntValue<
        ...,
        comms::option::def::VarLength<1U, 4U>
    >
{
    ...
};
```

The preparation before being sent looks like this:
```cpp
void ClientSession::sendMsg3()
{
    ...
    assert(msg.field_f3().length() == 1U); // It takes 1 byte to serialize default value 0
    msg.field_f3().value() = 128;
    assert(msg.field_f3().length() == 2U); // the f3 is encoded with base-128
    static_assert(Msg3::Field_f3::minLength() == 1U, "Invalid assumption");
    static_assert(Msg3::Field_f3::maxLength() == 4U, "Invalid assumption");
    ...
}
```

In some protocols values of some fields may have special meaning. In order
to prevent boilerplate code the 
[CommsDSL](https://github.com/arobenko/CommsDSL-Specification) specification
provides and ability to specify names for some values, while 
[commsdsl2comms](https://github.com/arobenko/commsdsl) code generator creates
necessary helper functions to get/set special values.

The fourth defined **&lt;int&gt;** field demonstrates usage of such special values.
```
<fields>
    <int name="I3_4" type="uint8" defaultValue="S1">
        <special name="S1" val="1" />
        <special name="S2" val="5" />
    </int>
</fields>

<message name="Msg3" id="MsgId.M3" displayName="Message 3">
    ...
    <ref name="F4" field="I3_4" />
</message>
```
Also note that **defaultValue** property can reference one of the special
values. The [I3_4](include/tutorial2/field/I3_4.h)
field definition contains the following helper member functions:
```
template <typename TOpt = tutorial2::options::DefaultOptions, typename... TExtraOpts>
class I3_4 : public
    comms::field::IntValue<...>
{
    ...
public:
    static constexpr ValueType valueS1();
    bool isS1() const;
    void setS1();
    
    static constexpr ValueType valueS2();
    bool isS2() const;
    void setS2();
    
    ...
};

```
The preparation before being sent looks like this:
```cpp
void ClientSession::sendMsg3()
{
    ...
    assert(msg.field_f4().isS1()); // Check default value
    msg.field_f4().setS2();
    ...
}
```

The fifth defined **&lt;int&gt;** field 
([I3_5](include/tutorial2/field/I3_5.h)) demonstrates usage of **serOffset**
property. It is used to automatically add / subtract predefined value before / after
field value serialization. The classic example is having a year number to be serialized
as offset from year **2000** as single byte.
```
<fields>
    ...
    <int name="I3_5" type="int16" length="1" defaultValue="2020" serOffset="-2000">
        <description value="Year as offset since 2000" />
    </int>
</fields>

<message name="Msg3" id="MsgId.M3" displayName="Message 3">
    ...
    <ref name="F5" field="I3_5" />
</message>
```
The preparation before being sent looks like this:
```cpp
void ClientSession::sendMsg3()
{
    ...
    assert(msg.field_f5().value() == 2020); // Check default value
    msg.field_f5().value() = 2021;
    assert(msg.field_f5().length() == 1U); // the f5 has fixed length of 1 bytes
    static_assert(Msg3::Field_f5::minLength() == 1U, "Invalid assumption");
    static_assert(Msg3::Field_f5::maxLength() == 1U, "Invalid assumption");
    ...
}
```
Note that the field's value contains proper year number and the integration code does
not need to know or care about applied serialization offset.

### &lt;set&gt; Fields
The **&lt;set&gt;** field allows creation of bitset / bitmask fields where
every bit has independent meaning. The `Msg4` message 
(defined inside [dsl/msg4.xml](dsl/msg4.xml) and implemented
in [include/tutorial2/message/Msg4.h](include/tutorial2/message/Msg4.h)) demonstrates usage of such fields.

The first defined **&lt;set&gt;** field is ([S4_1](include/tutorial2/field/S4_1.h)):
```
<fields>
    <set name="S4_1" length="1">
        <bit name="B0" idx="0" />
        <bit name="B1" idx="1" />
        <bit name="B2" idx="2" />
    </set>
    ...
</fields>

<message name="Msg4" id="MsgId.M4" displayName="Message 4">
    <ref name="F1" field="S4_1" />
    ...
</message>
```
Please note the following:

- The length of the field is specified using **length** property. The value
of the property is length of the field in **bytes**. 
- The information of the bit is defined using **&lt;bit&gt;** XML node, which
also uses **name** property to specify name of the bit as well as **idx**
property to specify bit index.

The [field class definition](include/tutorial2/field/S4_1.h) extends
[comms::field::BitmaskValue](https://arobenko.github.io/comms_doc/classcomms_1_1field_1_1BitmaskValue.html)
class and uses `COMMS_BITMASK_BITS_SEQ()` macro to specify names of the bits.
```cpp
template <typename TOpt = tutorial2::options::DefaultOptions, typename... TExtraOpts>
class S4_1 : public 
    comms::field::BitmaskValue<...>
{
    ...
public:
    COMMS_BITMASK_BITS_SEQ(
        B0,
        B1,
        B2
    );
    
    ...
};
```
Usage of `COMMS_BITMASK_BITS_SEQ()` macro is equivalent of having the following
inner types and functions defined.
```cpp
class S4_1 
{
public:
    // Enumeration for bit indices
    enum BitIdx
    {
        BitIdx_B0,
        BitIdx_B1,
        BitIdx_B2,
        BitIdx_numOfValues,
    };
    
    // Get/Set for B0
    bool getBitValue_B0() const;
    void setBitValue_B0(bool value);

    // Get/Set for B1
    bool getBitValue_B1() const;
    void setBitValue_B1(bool value);

    // Get/Set for B2
    bool getBitValue_B2() const;
    void setBitValue_B2(bool value);
};
```
It's worth mentioning that 
[comms::field::BitmaskValue](https://arobenko.github.io/comms_doc/classcomms_1_1field_1_1BitmaskValue.html)
class defines `getBitValue()` and `setBitValue()` member functions that receive index of the bit as
their parameter. The get/set functions generated by the `COMMS_BITMASK_BITS_SEQ()` macro are a mere 
wrappers around these functions.

Please take a closer look at the extension options used to define the field
```cpp
class S4_1 : public
    comms::field::BitmaskValue<
        tutorial2::field::FieldBase<>,
        TExtraOpts...,
        comms::option::def::FixedLength<1U>,
        comms::option::def::BitmaskReservedBits<0xF8U, 0x0U>
    >
```

- The value of the **length** property finds its way as an argument of
`comms::option::def::FixedLength` option.
- All unspecified bits are considered to be **reserved** ones with default
reserved value to be **0**. 
- The information about reserved bits is passed to 
[comms::field::BitmaskValue](https://arobenko.github.io/comms_doc/classcomms_1_1field_1_1BitmaskValue.html)
base class using `comms::option::def::BitmaskReservedBits` option, first template
parameter of which is the mask of the reserved bits, while the second template
parameter specifies the expected outcome when binary `and` operation is applied
on the currently held field's value and the mask of the reserved bits. If the
result differs, then the field's value is reported to be **invalid** (call 
to `valid()` member function returns **false**).
- The inner value storage type (`ValueType` member type) is always unsigned
integral one and based on the specified field length. It can be one of the 
following: **std::uint8_t**, **std::uint16_t**, **std::uint32_t**, or **std::uint64_t**.
- By default all the bits in such default constructed field are initialized
to **false** (**0**).

The preparation of such field for sending looks like this:
```cpp
void ClientSession::sendMsg4()
{
    Msg4 msg;
    msg.field_f1().setBitValue_B0(false);
    msg.field_f1().setBitValue_B2(true);
    assert(msg.field_f1().valid());
    ...
}
```

The second defined **&lt;set&gt;** field is ([S4_2](include/tutorial2/field/S4_2.h)):
```
<fields>
    ...
    <set name="S4_2" type="uint16" defaultValue="true">
        <bit name="B0" idx="0" defaultValue="false" />
        <bit name="B5" idx="5" />
        <bit name="B15" idx="15" />
    </set> 
    ...
</fields>

<message name="Msg4" id="MsgId.M4" displayName="Message 4">
    ...
    <ref name="F2" field="S4_2" />
    ...
</message>
```

The main difference to the first field is usage of **defaultValue** property
to specify default value of each bit (**true** in the example above). It
is also possible to overwrite it with specifying **defaultValue** property
for the bit itself. The example above specifies that the default value of `B0`
is **false** (**0**). As the result such field, when default constructed, will
have internal value of **0xFFFE**.

Also note that it is possible to directly specify **type** property instead of
**length** one. The specified type value must always be of unsigned integral one:
**uint8**, **uint16**, **uint32**, **uint64**. The **type** and **length** properties
can co-exist, but mustn't contradict each other and at least one of them needs
to be used in field definition.

Due to the fact that the specified bits are not sequential, the usage of
`COMMS_BITMASK_BITS_SEQ()` macro has been replaced with a combination of
`COMMS_BITMASK_BITS()` (defines `BitIdx` enum) and `COMMS_BITMASK_BITS_ACCESS()`
(defines bit access helper functions) macros with the same effect:
```cpp
template <typename TOpt = tutorial2::options::DefaultOptions, typename... TExtraOpts>
class S4_2 : public
    comms::field::BitmaskValue<...>
{
public:
    COMMS_BITMASK_BITS(...);
    COMMS_BITMASK_BITS_ACCESS(...);
};
```

The third defined **&lt;set&gt;** field ([S4_3](include/tutorial2/field/S4_3.h))
demonstrates better control of reserved fields:
```
<fields>
    ...
    <set name="S4_3" length="3" reservedValue="true">
        <bit name="B0" idx="0" defaultValue="true" />
        <bit name="B1" idx="1" reserved="true" reservedValue="false" />
        <bit name="B5" idx="5" />
        <bit name="B20" idx="20" />
    </set> 
</fields>

<message name="Msg4" id="MsgId.M4" displayName="Message 4">
    ...
    <ref name="F3" field="S4_3" />
</message>
```
By default the expected value of every reserved bit is **false** (**0**). However,
it may be changed using **reservedValue** property. In the example above it
states that every reserved bit expected to be **true** (**1**). Also such
default definition can be updated for a specific bit using a combination of
**reserved** (to mark the bit as reserved) and **reservedValue** 
(to specify the expected value for the bit) properties, as was done for bit **B1**
in the example above.

One more thing to notice is that **length** property can have any value up to **8**
bytes. The example above limits the length of the field to 3 bytes only. 

Let's also take a closer look at the code that prepares this bit for being sent:
```cpp
void ClientSession::sendMsg4()
{
    ...
    msg.field_f3().value() = 0xff;
    assert(msg.field_f3().length() == 3U);
    static_assert(Msg4::Field_f3::minLength() == 3U, "Invalid assumption");
    static_assert(Msg4::Field_f3::maxLength() == 3U, "Invalid assumption");
    assert(!msg.field_f3().valid());
    ...
}
```
As was mentioned early the internal value storage type of the field (`ValueType`)
is unsigned integral one (**std::uint8_t**, **std::uint16_t**, **std::uint32_t**,
or **std::uint64_t**). It means that it can be accessed and raw bulk value of all
the fields can be assigned directly to it, like in the code example above. 
It is obvious that in such assignment above many reserved bits end up with invalid
value, that's why call to the `valid()` member function is expected to return **false**.

Additional thing to mention is that the field class definition code generated by the
[commsdsl2comms](https://github.com/arobenko/commsdsl) 
contains `bitName()` convenience member function, which can be used to retrieve
human readable name of the bit. By default it is equal to the value of the 
**name** property, but it can be overwritten with **displayName** one.
The usage of the `bitName()` member function is demonstrated by the
following function:
```cpp
template <typename TField>
void printSetField(const TField& field, const std::string& prefix = std::string())
{
    std::cout << '\t' << prefix << field.name() << " = 0x" <<
        std::setfill('0') << std::setw(field.length() * 2) <<
        std::hex << (std::uintmax_t)field.value() << std::dec << '\n';

   for (auto idx = 0U; idx < field.length() * 8; ++idx) {
        auto bitIdx = static_cast<typename TField::BitIdx>(idx);
        const char* bitName = field.bitName(bitIdx);
        if (bitName == nullptr) {
            continue;
        }

        std::cout << "\t\t" << bitName << ": " << std::boolalpha << field.getBitValue(bitIdx) << '\n';
    }
}
```
It is called when `Msg4` message is received back from the server and its contents are printed:
```cpp
void ClientSession::handle(Msg4& msg)
{
    std::cout << "Received \"" << msg.doName() << "\" with ID=" << msg.doGetId() << '\n';
    printSetField(msg.field_f1());
    printSetField(msg.field_f2());
    printSetField(msg.field_f3());
    std::cout << std::endl;
    ...
}

```

### &lt;float&gt; Fields
The **&lt;float&gt;** stores and abstracts away value of floating point type 
with IEEE 754 encoding. The `Msg5` message 
(defined inside [dsl/msg5.xml](dsl/msg5.xml) and implemented in 
[include/tutorial2/message/Msg5.h](include/tutorial2/message/Msg5.h)) 
demonstrates usage of such fields.

The first defined **&lt;float&gt;** field is ([F5_1](include/tutorial2/field/F5_1.h)):
```
<fields>
    <float name="F5_1" type="float" />
    ...
</fields>

<message name="Msg5" id="MsgId.M5" displayName="Message 5">
    <ref name="F1" field="F5_1" />
    ...
</message>
```
Similar to [&lt;int&gt;](#int-fields) fields, **type** property needs to be
used to specify underlying storage type of the field. The available values are
**float** (with 4 bytes serialization length) and **double** (with 8 bytes
serialization length).

The **&lt;float&gt;** field is defined using 
[comms::field::FloatValue](https://arobenko.github.io/comms_doc/classcomms_1_1field_1_1FloatValue.html) 
class provided by the [COMMS Library](https://github.com/arobenko/comms_champion#comms-library).

The second defined **&lt;float&gt;** field 
([F5_2](include/tutorial2/field/F5_2.h)) demonstrates usage of values with
special meaning (similar to special values that can be defined for 
[&lt;int&gt;](#int-fields) fields).
```
<fields>
    ...    
    <float name="F5_2" type="double" defaultValue="S1">
        <special name="S1" val="nan" />
        <special name="S2" val="inf" />
        <special name="S3" val="-inf" />
        <special name="S4" val="5.123" />
    </float>
</fields>

<message name="Msg5" id="MsgId.M5" displayName="Message 5">
    ...
    <ref name="F2" field="F5_2" />
</message>
```
Please note the following:

- In addition to normal floating point values, the definition of the field
can use case-insensitive **nan**, **inf**, and **-inf** strings. They stand for
**NaN**, **infinity** and **-infinity** respectively.
- The **defaultValue** property can reference one of the special values by
name.

The preparation of `Msg5` for sending looks like this:
```cpp
void ClientSession::sendMsg5()
{
    Msg5 msg;
    msg.field_f1().value() = 1.2345;

    assert(msg.field_f2().isS1());
    msg.field_f2().setS3();
    sendMessage(msg);
}
```

### &lt;string&gt; Fields
The **&lt;string&gt;** fields abstract away string values. The `Msg6` message 
(defined inside [dsl/msg6.xml](dsl/msg6.xml) and implemented in
[include/tutorial2/message/Msg6.h](include/tutorial2/message/Msg6.h)) 
demonstrates usage of such fields.

The first defined **&lt;string&gt;** field ([S6_1](include/tutorial2/field/S6_1.h)) 
shows usage of fixed size string field:
```
<fields>
    <string name="S6_1" length="5" />
    ...
</fields>

<message name="Msg6" id="MsgId.M6" displayName="Message 6">
    <ref name="F1" field="S6_1" />
    ...
</message>
```
The **&lt;string&gt;** field is defined using 
[comms::field::String](https://arobenko.github.io/comms_doc/classcomms_1_1field_1_1String.html) 
class provided by the [COMMS Library](https://github.com/arobenko/comms_champion#comms-library).

The **default** storage type of any **&lt;string&gt;** field is `std::string`.
It can be replaced with interface compatible other type at compile time by the application being
developed using one of the extension options. One of the later tutorials will cover this topic in detail.

The **length** property can be used to specified **fixed** length. Note, that
this property insures required number of bytes **on-the-wire**, not size of the
inner `std::string` (or some other string storage type being used) when field is
default constructed.
```cpp
void ClientSession::sendMsg6()
{
    ...
    std::string& f1Str = msg.field_f1().value();
    assert(f1Str.empty()); // Empty string on construction
    assert(msg.field_f1().length() == 5U); // but the reported length is as expected
    f1Str = "abc";
    assert(msg.field_f1().length() == 5U);
    ...
}
```
When such **&lt;string&gt;** field is serialized, the
[COMMS Library](https://github.com/arobenko/comms_champion#comms-library) makes
sure that correct number of bytes is written to the output buffer. In case the
stored string value has shorter length, the output is padded with correct number
of zeroes (**0**). In case the stored string value is longer than allowed, the
serialization output will just be truncated without exceeding maximum allowed 
number of bytes.

The second defined **&lt;string&gt;** field ([S6_2](include/tutorial2/field/S6_2.h))
demonstrates string prefixed with
1 byte of its serialization length:
```
<fields>
    <string name="S6_2" defaultValue="hello">
        <lengthPrefix>
            <int name="Length" type="uint8" />
        </lengthPrefix>
    </string>
    ...
</fields>

<message name="Msg6" id="MsgId.M6" displayName="Message 6">
    ...
    <ref name="F2" field="S6_2" />
    ...
</message>
```
Similar to other fields, it is possible to use **defaultValue** property to
set default value for the default-constructed field.

The preparation of such field for sending looks like this:
```cpp
void ClientSession::sendMsg6()
{
    ...
    assert(msg.field_f2().value() == "hello");
    assert(msg.field_f2().length() == 6U);
    msg.field_f2().value() = "bye";
    assert(msg.field_f2().length() == 4U);
    ...
}
```

The third defined **&lt;string&gt;** field ([S6_3](include/tutorial2/field/S6_3.h)) 
also demonstrates string prefixed with
its serialization length, but this time of variable length.
```
<fields>
    ...
    <int name="L6_3" type="uintvar" length="2" />
    <string name="S6_3" lengthPrefix="L6_3" />
    ...
</fields>

<message name="Msg6" id="MsgId.M6" displayName="Message 6">
    ...
    <ref name="F3" field="S6_3" />
    ...
</message>
```
Note that this time **lengthPrefix** is used as field's property and
it's value references already defined external **&lt;int&gt;** field.

Also note that the length prefix has variable length of 1 or 2 bytes
with [Base-128](https://en.wikipedia.org/wiki/LEB128) encoding. In case the
stored string value has more than 127 characters, the length prefix will occupy 2 bytes 
when string field is serialized.

The fourth defined **&lt;string&gt;** field ([S6_4](include/tutorial2/field/S6_4.h))
demonstrates zero (**0**) terminating 
string fields. Such fields are not prefixed with their length, their length is
determined by the presence of zero (**0**) byte.
```
<fields>
    ...
    <string name="S6_4" zeroTermSuffix="true" />
</fields>

<message name="Msg6" id="MsgId.M6" displayName="Message 6">
    ...
    <ref name="F4" field="S6_4" />
    ...
</message>
```
Usage of zero (**0**) termination suffix is determined by having **zeroTermSuffix**
field property.

The preparation of such field for sending looks like this:
```cpp
void ClientSession::sendMsg6()
{
    ...
    assert(msg.field_f4().length() == 1U); 
    msg.field_f4().value() = "blablabla";
    assert(msg.field_f4().length() == 10U);
    ...
}
```

The fifth defined **&lt;string&gt;** field demonstrates string field without
any size limitations and/or termination character.
```
<message name="Msg6" id="MsgId.M6" displayName="Message 6">
    ...
    <string name="F5" />
</message>
```
Such field usually resides at the end of the message. It 
writes all its contents during serialization stage and consumes
all the available remaining data (bound by the total message length controlled
by the framing).

### &lt;data&gt; Fields
The **&lt;data&gt;** fields abstract away lists of raw binary bytes. The `Msg7` message 
(defined inside [dsl/msg7.xml](dsl/msg7.xml) and implemented in
[include/tutorial2/message/Msg7.h](include/tutorial2/message/Msg7.h)) 
demonstrates usage of such fields.

The **&lt;data&gt;** fields are very similar to **&lt;string&gt;** ones. 
The first defined **&lt;data&gt;** field ([D7_1](include/tutorial2/field/D7_1.h))
shows usage of fixed size raw binary data sequence:
```
<fields>
    <data name="D7_1" length="5" />
    ...
</fields>

<message name="Msg7" id="MsgId.M7" displayName="Message 7">
    <ref name="F1" field="D7_1" />
    ...
</message>
```
The **&lt;data&gt;** field is defined using 
[comms::field::ArrayList](https://arobenko.github.io/comms_doc/classcomms_1_1field_1_1ArrayList.htmll) 
class provided by the [COMMS Library](https://github.com/arobenko/comms_champion#comms-library).

The **default** storage type of any **&lt;data&gt;** field is `std::vector<std::uint8_t>`.
It can be replaced with interface compatible other type at compile time by the application being
developed using one of the extension options. One of the later tutorials will cover this topic in detail.

The **length** property can be used to specified **fixed** length. Note, that
this property insures required number of bytes **on-the-wire**, not size of the
inner `std::vector` (or some other data storage type being used) when field is
default constructed.
```cpp
void ClientSession::sendMsg7()
{
    ...
    std::vector<std::uint8_t>& f1Vec = msg.field_f1().value();
    assert(f1Vec.empty()); // Empty vector on construction
    assert(msg.field_f1().length() == 5U); // but the reported length is as expected
    f1Vec = {0xde, 0xad, 0xbe, 0xef};
    assert(msg.field_f1().length() == 5U);
    ...
}
```
Just like with **&lt;string&gt;** fields, when such **&lt;data&gt;** field is serialized, the
[COMMS Library](https://github.com/arobenko/comms_champion#comms-library) makes
sure that correct number of bytes is written to the output buffer. In case the
stored string value has shorter length, the output is padded with correct number
of zeroes (**0**). In case the stored string value is longer than allowed, the
serialization output will just be truncated without exceeding maximum allowed 
number of bytes.

The second defined **&lt;data&gt;** field ([D7_2](include/tutorial2/field/D7_2.h)) 
demonstrates raw data prefixed with
1 byte of its serialization length:
```
<fields>
    ...
    <data name="D7_2" defaultValue="ab cd ef 012345">
        <lengthPrefix>
            <int name="Length" type="uint8" />
        </lengthPrefix>
    </dataf>
</fields>

<message name="Msg7" id="MsgId.M7" displayName="Message 7">
    ...
    <ref name="F2" field="D7_2" />
    ...
</message>
```
Similar to other fields, it is possible to use **defaultValue** property to
set default value for the default-constructed field. The **defaultValue** must
specify hexadecimal value of each byte. Spaces are allowed 
(just for readability) and ignored when the value is parsed by the code generator.

When preparing the `Msg7` message to be sent, the value of the `F2` field is
not changed in this tutorial.
```cpp
void ClientSession::sendMsg7()
{
    ...
    // msg.field_f2().value() is unchanged
    assert(msg.field_f2().value().size() == 6U); // The vector has 6 bytes
    assert(msg.field_f2().length() == 7U); // The total serialization length is 7
    ...
}
```

The third defined **&lt;data&gt;** field demonstrates raw data field without
any size limitations.
```
<message name="Msg7" id="MsgId.M7" displayName="Message 7">
    ...
    <data name="F3" />
</message>
```
Such field usually resides at the end of the message. It writes all its 
contents during serialization stage and consumes
all the available remaining data (bound by the total message length controlled
by the framing).

### &lt;bundle&gt; Fields
The **&lt;bundle&gt;** fields are composite fields that bundle multiple other
fields into a single one. The `Msg8` message 
(defined inside [dsl/msg8.xml](dsl/msg8.xml) and implemented in
[include/tutorial2/message/Msg8.h](include/tutorial2/message/Msg8.h)) 
demonstrates usage of such fields.

The first defined **&lt;bundle&gt;** field is ([B8_1](include/tutorial2/field/B8_1.h)):
```
<fields>
    <bundle name="B8_1">
        <int name="M1" type="uint16" />
        <enum name="M2" type="uint8">
            <validValue name="V1" val="0" />
            <validValue name="V2" val="1" />
        </enum>
        <string name="M3" length="3" />
    </bundle>
    ...
</fields>

<message name="Msg8" id="MsgId.M8" displayName="Message 8">
    <ref name="F1" field="B8_1" />
    ...
</message>
```
The member fields are listed as child XML elements of the **&lt;bundle&gt;** node.

Let's take a closer look at the generated code of the field class definition 
inside [include/tutorial2/field/B8_1.h](include/tutorial2/field/B8_1.h).
```cpp
template <typename TOpt = tutorial2::options::DefaultOptions, typename... TExtraOpts>
class B8_1 : public
    comms::field::Bundle<...>
{
public:
    ...
    COMMS_FIELD_MEMBERS_NAMES(
        m1,
        m2,
        m3
    );
    ...
};
```
The class is defined using 
[comms::field::Bundle](https://arobenko.github.io/comms_doc/classcomms_1_1field_1_1Bundle.html).
The names of the member fields are provided using **COMMS_FIELD_MEMBERS_NAMES()**
macro. It is quite similar to **COMMS_MSG_FIELDS_NAMES()** (used to define member
fields of the messages), but applicable to composite fields, such as bundles.

The inner `ValueType` type of `comms::field::Bundle` (or its extended type) 
is `std::tuple` of all the member fields.

Having **COMMS_FIELD_MEMBERS_NAMES()** macro inside class definition is equivalent
to having the following types and functions defined:
```cpp
template <typename TOpt = tutorial2::options::DefaultOptions, typename... TExtraOpts>
class B8_1 : public
    comms::field::Bundle<...>
{
public:
    // Access index to the member fields
    enum FieldIdx
    {
        FieldIdx_m1,
        FieldIdx_m2,
        FieldIdx_m3,
        FieldIdx_numOfValues
    };

    // Aliases to member field types
    using Field_m1 = B8_1Members<TOpt>::M1;
    using Field_m2 = B8_1Members<TOpt>::M2;
    using Field_m3 = B8_1Members<TOpt>::M3;

    // Convenience access to member fields:
    Field_m1& field_m1();
    const Field_m1& field_m1() const;

    Field_m2& field_m2();
    const Field_m2& field_m2() const;

    Field_m3& field_m3();
    const Field_m3& field_m3() const;
};
```
Please note that names provided to **COMMS_FIELD_MEMBERS_NAMES()** macro 
('m1', 'm2', 'm3') find their way to `FieldIdx_x` enum values, inner
`Field_x` alias types and `field_x()` access member functions.

The preparation of the field before being sent looks like this:
```cpp
void ClientSession::sendMsg8()
{
    Msg8 msg;

    auto& f1 = msg.field_f1(); // Access to f1 field
    
    // Assign values to f1 members
    f1.field_m1().value() = 1234;
    f1.field_m2().value() = Msg8::Field_f1::Field_m2::ValueType::V1;
    f1.field_m3().value() = "hello";

    ...
}
```
Please take a closer look at assignment of `m2` value.

- `Msg8::Field_f1` is full type ([tutorial2::field::B8_1](include/tutorial2/field/B8_1.h)) 
of `Msg8.F1` field.
- `Msg8::Filed_f1::Field_m2` is a full type ([tutorial2::field::B8_1Members::M2](include/tutorial2/field/B8_1.h)) of 
`Msg8.F1.M2` field.
- `Msg8::Filed_f1::Field_m2::ValueType` is an enumeration type
([comms::field::B8_1MembersCommon::M2Common::ValueType](include/tutorial2/field/B8_1Common.h)) 
used by `Msg8.F1.M2` field.

It is worth mentioning that it is possible to access member fields by index 
instead of name:
```cpp
auto& tupleOfMembers = msg.field_f1().value(); // ValueType of bundle field is tuple of members
auto& m1 = std::get<Msg8::Field_f1::FieldIdx_m1>(tupleOfMembers);
auto& m2 = std::get<Msg8::Field_f1::FieldIdx_m2>(tupleOfMembers);
auto& m3 = std::get<Msg8::Field_f1::FieldIdx_m3>(tupleOfMembers);
```

The second **&lt;bundle&gt;** 
field ([B8_2](include/tutorial2/field/B8_2.h)) is defined to be:
```
<fields>
    ...
    <bundle name="B8_2">
        <description>Some Field Description</description>
        <members>
            <float name="M1" type="float" defaultValue="nan" />
            <set name="M2" length="1">
                <bit name="SomeBit" idx="0" />
                <bit name="SomeOtherbit" idx="5" />
            </set>
            <data name="M3">
              <lengthPrefix>
                    <int name="Length" type="uint8" />
                </lengthPrefix>
            </data>
        </members>
    </bundle> 
</fields>

<message name="Msg8" id="MsgId.M8" displayName="Message 8">
    ...
    <ref name="F2" field="B8_2" />
</message>
```
Please note that the field definition contains its **description** property defined
as **&lt;descrption&gt;** XML child node. As the result the member fields definition
needs to be wrapped in **&lt;members&gt;** XML node instead of being direct
children of **&lt;bundle&gt;**.

### &lt;bitfield&gt; Fields
The **&lt;bitfield&gt;** fields are also composite ones, members of which limit
their serialization lengths in **bits** (not bytes), with total sum of bits not
exceeding **64** and being a multiplication of **8** (to properly fit into 
serialization bytes). The `Msg9` message 
(defined inside [dsl/msg9.xml](dsl/msg9.xml) and implemented in
[include/tutorial2/message/Msg9.h](include/tutorial2/message/Msg9.h)) 
demonstrates usage of such fields.

The first defined **&lt;bitfield&gt;** field is ([B9_1](include/tutorial2/field/B9_1.h)):
```
<fields>
    <bitfield name="B9_1">
        <int name="M1" type="uint8" bitLength="6"/>
        <enum name="M2" type="uint8" bitLength="4">
            <validValue name="V1" val="0" />
            <validValue name="V2" val="1" />
        </enum>
        <set name="M3" bitLength="6">
            <bit name="B0" idx="0" />
            <bit name="B5" idx="5" />
        </set>
    </bitfield>
    ...
</fields>

<message name="Msg9" id="MsgId.M9" displayName="Message 9">
    <ref name="F1" field="B9_1" />
    ...
</message>
```
Similar to [&lt;bundle&gt;](#bundle-fields) field, the member fields 
can be listed as child XML elements of the **&lt;bitfield&gt;** node.

Let's take a closer look at the generated code of the field class definition 
inside [include/tutorial2/field/B9_1.h](include/tutorial2/field/B9_1.h).
```cpp
template <typename TOpt = tutorial2::options::DefaultOptions, typename... TExtraOpts>
class B9_1 : public
    comms::field::Bitfield<...>
{
public:
    COMMS_FIELD_MEMBERS_NAMES(
        m1,
        m2,
        m3
    );
    ...
};
```
The class is defined using 
[comms::field::Bitfield](https://arobenko.github.io/comms_doc/classcomms_1_1field_1_1Bitfield.html).
Similar to [&lt;bundle&gt;](#bundle-fields) the names of the member fields are 
provided using the same **COMMS_FIELD_MEMBERS_NAMES()**
macro. 

The inner `ValueType` type of `comms::field::Bitfield` (or its extended type) 
is `std::tuple` of all the member fields.

Just like with [&lt;bundle&gt;](#bundle-fields) fields, having 
**COMMS_FIELD_MEMBERS_NAMES()** macro inside class definition is equivalent
to having the following types and functions defined:
```cpp
template <typename TOpt = tutorial2::options::DefaultOptions, typename... TExtraOpts>
class B9_1 : public
    comms::field::Bitfield<...>
{
public:
    // Access index to the member fields
    enum FieldIdx
    {
        FieldIdx_m1,
        FieldIdx_m2,
        FieldIdx_m3,
        FieldIdx_numOfValues
    };

    // Aliases to member field types
    using Field_m1 = B9_1Members<TOpt>::M1;
    using Field_m2 = B9_1Members<TOpt>::M2;
    using Field_m3 = B9_1Members<TOpt>::M3;

    // Convenience access to member fields:
    Field_m1& field_m1();
    const Field_m1& field_m1() const;

    Field_m2& field_m2();
    const Field_m2& field_m2() const;

    Field_m3& field_m3();
    const Field_m3& field_m3() const;
};
```

The preparation of the field before being sent looks like this:
```cpp
void ClientSession::sendMsg8()
{
    Msg9 msg;

    ...

    // Assign values to f1 members
    msg.field_f1().field_m1().value() = 55;
    msg.field_f1().field_m2().value() = Msg9::Field_f1::Field_m2::ValueType::V2;
    msg.field_f1().field_m3().setBitValue_B5(true);
    assert(msg.field_f1().length() == 2U); // Runtime verification of serialization length

    ...
}
```

The second **&lt;bitfield&gt;** 
field ([B9_2](include/tutorial2/field/B9_2.h)) is defined to be:
```
<fields>
    ...
    <bitfield name="B9_2">
        <description>Some Field Description</description>
        <members>
            <int name="M1" type="uint16" bitLength="12" defaultValue="16" />
            <enum name="M2" type="uint8" bitLength="4" defaultValue="V1">
                <validValue name="V1" val="2" />
                <validValue name="V2" val="5" />
            </enum>
            <set name="M3" length="1">
                <bit name="B0" idx="0" defaultValue="true" />
                <bit name="B5" idx="5" />
                <bit name="B7" idx="7" defaultValue="true" />
            </set>
        </members>
    </bitfield>
</fields>

<message name="Msg9" id="MsgId.M9" displayName="Message 9">
    ...
    <ref name="F2" field="B9_2" />
</message>
```
Just like with [&lt;bundle&gt;](#bundle-fields) fields, in case some property
of the **&lt;bitfield&gt;** is defined as XML child element (like **&lt;description&gt;**
in the example above), the member fields must be wrapped in **&lt;members&gt;**
XML element. 

Please also note, that only [&lt;int&gt;](#int-fields), [&lt;enum&gt;](#enum-fields),
and [&lt;set&gt;](#set-fields) fields can be members of [&lt;bitfield&gt;](#bitfield-fields),
value of any other field cannot limit its length to number of bits.


## Summary

- The protocol definition does not necessarily need to be defined in a single
schema files, it can be split into multiple ones and being processed in specified
order.
- The fields can be defined as member nodes of the **&lt;message&gt;**
definition or global ones (members of global **&lt;fields&gt;** XML node) and
then referenced by other message member fields.
- The code for global field which is not referenced by other field or message definition
won't be generated.
- The fields are abstractions around actual value storage to provide common
interface for all field types. 
- The primary and most frequently used member function of the field objects
is **value()**. It is used to access the storage **by-reference**.
- Every message definition class containing inner fields uses 
**COMMS_MSG_FIELDS_NAMES()** macro (provided by the 
[COMMS Library](https://github.com/arobenko/comms_champion#comms-library))
to create convenience access member functions for member fields.
- Due to the nature of
these tutorials it is not possible to cover **all** aspects (properties) of all
the available fields, it is highly recommended to read 
[CommsDSL](https://github.com/arobenko/CommsDSL-Specification) specification in
full after this tutorial.
- All the field classes are implemented by extending one of the field definition
classes provided by the [COMMS Library](https://github.com/arobenko/comms_champion#comms-library)
and residing in [comms::field](https://arobenko.github.io/comms_doc/namespacecomms_1_1field.html)
namespace.

