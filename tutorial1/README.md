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
[Session](../lib/include/Session.h) object(s). Every **tutorialX** / **howtoX** is expected
to extend it and implement all the relevant virtual functions to make the common code function
properly. The sessions are split into **server** and **client** ones. The **server**
side code is implemented in [SeverSession.h](src/ServerSession.h) and 
[ServerSession.cpp](src/ServerSession.cpp). The **client**
side code is implemented in [ClientSession.h](src/ClientSession.h) and 
[ClientSession.cpp](src/ClientSession.cpp) respectively. 

## Server
Let's take a look at definition of the message interface class inside [SeverSession.h](src/ServerSession.h)
```cpp
using Message =
    tutorial1::Message<
        comms::option::ReadIterator<const std::uint8_t*>, // Polymorphic read
        comms::option::WriteIterator<std::uint8_t*>, // Polymorphic write
        comms::option::LengthInfoInterface, // Polymorphic length calculation
        comms::option::IdInfoInterface, // Polymorphic message ID retrieval
        comms::option::NameInterface, // Polymorphic message name retrieval
        comms::option::Handler<ServerSession> // Polymorphic dispatch
    >;
```
The generated **tutorial1::Message** common interface class is extended
with multiple options, which create various function with **polymorphic**
behavior.

#### Polymorphic Read
Usage of `comms::option::ReadIterator` option adds the following type and 
function to the message interface.
```cpp
class Message 
{
public: 
    // Type of the iterator used for reading
    using ReadIterator = const std::uint8_t*;
    
    // Polymorphic read functionality
    comms::ErrorStatus read(ReadIterator& iter, std::size_t len);
};
```
Please pay attention to the following details:

- The **read()** function is **polymorphic**, i.e. the read functionality
is performed correctly when the message object is held by the pointer or reference
to the interface class.
- The **read()** function reports its success / failure status via error code defined
as [comms::ErrorStatus](https://arobenko.github.io/comms_doc/ErrorStatus_8h.html).
- The **read** operation receives the iterator used for reading **by reference** and
advances it to perform the read operation. In order to identify how many bytes were
consumed, the caller is expected to store the initial value of the iterator and then
compare it to the value of the advanced one passed as the parameter to the **read()**
function. The caller is also responsible to maintain input data buffer and provides
only an iterator for the message object to perform its read.

#### Polymorphic Write
Usage of `comms::option::WriteIterator` option adds the following type and 
function to the message interface.
```cpp
class Message 
{
public: 
    // Type of the iterator used for writing
    using WriteIterator = std::uint8_t*;
    
    // Polymorphic write functionality
    comms::ErrorStatus write(WriteIterator& iter, std::size_t len) const;
};
```
It is very similar to the **polymorphic read** mentioned earlier.

- The **write()** function is **polymorphic**.
- The success / failure status is reported via **comms::ErrorStatus** return value.
- The iterator passed to **write()** function is advanced during write operation. The
caller is responsible to maintain output data buffer and provides only an iterator 
to it for message object to perform its write.
- The call to **write()** member function is not expected to change the message
object, that's why it's defined to be **const**.

#### Polymorphic Serialization Length Calculation.
Usage of `comms::option::LengthInfoInterface` option adds the following interface
function to the defined class.
```cpp
class Message 
{
public: 
    // Polymorphic serialization length calculation
    std::size_t length() const;
};
```
The call to **length()** member function will return number of bytes required
to serialize the message payload. It can be used to allocate output buffer of
required size.

#### Polymorphic Message ID Retrieval
Usage of `comms::option::IdInfoInterface` option adds the following type and interface
function to the defined class.
```cpp
class Message 
{
public: 
    // Define type used to report message ID
    using MsgIdType = tutorial::MsgId;
    
    // Polymorphic numeric ID retrieval
    MsgIdType getId() const;
};
```
The polymorphic message ID retrieval can be used in transport framing operation.
There is a need to get the message ID when prefixing serialized message payload.

# Polymorphic Message Name Retrieval
Usage of `comms::option::NameInterface` option adds the following 
function to the message interface.
```cpp
class Message 
{
public: 
    // Polymorphic name retrieval
    const char* name() const;
};
```
The polymorphic name retrieval can be used in application when there is a 
need to print human readable name of the message. Note that such name
is provided as `displayName` property of the message definition inside
[CommsDSL](https://github.com/arobenko/CommsDSL-Specification) schema.
```
<message name="Msg1" id="MsgId.M1" displayName="Message 1"/>
```

# Polymorphic Dispatch For Handling
When raw data is received by any endpoint, it is processed and the proper
message object is created. Such message object is held by the pointer / reference
to its interface class / type (`tutorial1::Message`). There is also a need to
dispatch it to appropriate handling function.
