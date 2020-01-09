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
see [dsl/msg1.xml](dsl/msg1.xml).
```
<?xml version="1.0" encoding="UTF-8"?>
<schema>
    ...
</schema>
```

## Defining Fields
Every message may define internal fields. Let's take a look at [dsl/msg1.xml](dsl/msg1.xml).
```
<message name="Msg1" id="MsgId.M1" displayName="Message 1">
    <ref field="I1" name="12" />
    <int name="F1" type="int16" />
</message>
```
The message can define its field internally:
```
<int name="F1" type="int16" />
```
or reference the previously defined global field (using **&lt;ref&gt;** node):
```
<ref field="I1" name="12" />
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

## Summary

- The protocol definition does not necessarily need to be defined in a single
schema files, it can be split into multiple ones and being processed in specified
order.
- There fields can be defined as member nodes of the **&lt;message&gt;**
definition or global ones (members of global **&lt;fields&gt;** XML node) and
then referenced by other message member fields.
