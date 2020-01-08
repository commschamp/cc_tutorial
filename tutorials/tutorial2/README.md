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
