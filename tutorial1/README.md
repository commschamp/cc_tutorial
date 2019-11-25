# Tutorial 1
Introducing basic protocol definition, polymorphic message interfaces, and dispatching message object into appropriate handling function.

## CommsDSL Schema
The [schema](dsl/schema.xml) file contains very simple protocol definition.
There are two messages without any internal fields. The enum `MsgId` field
is used to define numeric IDs of the messages. The framing is also very
simple, it just prefixes message payload (empty in this specific case) with
numeric message ID.

## Generated Code
Let's take a look at generated code relevant for this tutorial.

The numeric message IDs find their way to `MsgId` enum definition inside
[include/tutorial1/MsgId.h](include/tutorial1/MsgId.h).

The common interface class for **all** the messages resides in 
[include/tutorial1/Message.h](include/tutorial1/Message.h). Please take a
look at its definition.
```cpp
template <typename... TOpt>
using Message =
    comms::Message<
        TOpt...,
        comms::option::def::BigEndian,
        comms::option::def::MsgIdType<tutorial1::MsgId>
    >;
```
It uses [comms::Message](https://arobenko.github.io/comms_doc/classcomms_1_1Message.html) class
definition and extends its default function with various **options**. The options
that should be used for **protocol definition** reside in 
[comms::option::def](https://arobenko.github.io/comms_doc/namespacecomms_1_1option_1_1def.html)
namespace. In this tutorial, the used options specify the serialization endian
(`Big`) and enum type used for message numeric IDs (`MsgId`). The `TOpt` variadic
template parameter allows introducing additional **application specific** customization
options. In this specific tutorial they are going to be used to introduce
polymorphic interface (virtual functions) for protocol message objects.

All the defined message classes (`Msg1` and `Msg2`) reside in 
[include/tutorial1/message](include/tutorial1/message) folder.
[Every](include/tutorial1/message/Msg1.h) message definition class
receives its common interface (base) class as the **first** template parameter.
```cpp
template <typename TMsgBase, ... /* irrelevan for now */>
class Msg1 : public
    comms::MessageBase<
        TMsgBase,
        ... /* irrelevant for now */
    >
```
The defined message class extends 
[comms::MessageBase](https://arobenko.github.io/comms_doc/classcomms_1_1MessageBase.html), which in
turn extends the provided interface class passed as first template parameter.

The **comms::MessageBase** class is there to implement various operations of message payload as
well as implement all relevant virtual functions depending on the used message interface class
extension options. In case the application doesn't really customizes the common message interface
(The `TOpt` variadic template parameter is empty) the message object is like a `struct` of
stored fields without any polymorphic behavior.

The transport framing of the message payload is defined inside 
[include/tutorial1/frame/Frame.h](include/tutorial1/frame/Frame.h) file. It manages all wrap / unwrap
of the message payload with extra transport fields (just prefixing it with message ID in this 
tutorial).

## Clint / Server Sessions
Every tutorial (not just this one) uses common I/O management code, which operates on 
[Session](../lib/include/Session.h) object(s). Every tutorial / howto is expected
to implement all the relevant virtual functions to make the common code function
properly. The sessions are split into **server** and **client** ones. The **server**
side code is implemented in [SeverSession.h](src/ServerSession.h) and 
[ServerSession.cpp](src/ServerSession.cpp). The **client**
side code is implemented in [ClientSession.h](src/ClientSession.h) and 
[ClientSession.cpp](src/ClientSession.cpp) respectively. 

## Server

