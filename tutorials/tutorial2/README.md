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

## Defining Fields
Every message may define internal fields. Let's take a look inside [dsl/msg1.xml](dsl/msg1.xml).
```
<message name="Msg1" id="MsgId.M1" displayName="Message 1">
    <ref field="I1" name="F1" />
    <int name="F2" type="int16" />
</message>
```
The message can define its field internally:
```
<int name="F2" type="int16" />
```
or reference the previously defined global field (using **&lt;ref&gt;** node):
```
<ref field="I1" name="F1" />
```
The globally defined fields need to reside inside **&lt;fields&gt;** XML node:
```
<fields>
    <int name="I1" type="uint8" />
    ...
</fields>
```
The code generated for every message and its fields resides in inside the 
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
In general, every field is an abstracting wrapper around value storage in
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
inconvenient, not to mention being a bad practice. That what
usage of `COMMS_MSG_FIELDS_NAMES()` macro comes to resolve. It receives the
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
        NumOfValues
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
- The provided names ('f1', 'f2') find their way to `FieldIdx_X` enum values, inner
`Field_X` alias types and `field_x()` access member functions.

Usage of the access member functions can be demonstrated in the function that prepares and
sends the `Msg1` into the server:
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
        "\tf1 = " << (unsigned)msg.field_f1().value() << '\n' <<
        "\tf2 = " << msg.field_f2().value() << '\n' << std::endl;
    ...
}

```

## Supported Field Types
The [CommsChampion Ecosystem](https://arobenko.github.io/cc) has multiple 
supported field types which are covered below one by one.

### Enum Fields
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
common, template parameter's independent types and functions in
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
This field definition will reside in 
[include/tutorial2/field/E2_2.h](include/tutorial2/field/E2_2.h) with its
common, template parameter's independent types and functions in
[include/tutorial2/field/E2_2Common.h](include/tutorial2/field/E2_2Common.h)

Please note the following:

- By default the value of the default-constructed `enum` field object is `0`. It
is possible to change it using **defaultValue** property of the field, which can
have either numeric value of reference one of its **&lt;valueValue&gt;**-es. In
case of `E2_2` it is `V2`.


## Summary

- The protocol definition does not necessarily need to be defined in a single
schema files, it can be split into multiple ones and being processed in specified
order.
- There fields can be defined as member nodes of the **&lt;message&gt;**
definition or global ones (members of global **&lt;fields&gt;** XML node) and
then referenced by other message member fields.
- The fields are abstractions around actual value storage to provide common
interface for all field types. 
- The primary and most frequently used member function of the field objects
is **value()**. It is used to access the storage **by-reference**.
- Every message definition class containing inner fields uses 
**COMMS_MSG_FIELDS_NAMES()** macro (provided by the 
[COMMS Library](https://github.com/arobenko/comms_champion#comms-library))
to create convenience access member functions for member fields.
