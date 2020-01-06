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
template <typename TMsgBase, ... /* irrelevant for now */>
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

## Client / Server Sessions
Every tutorial (not just this one) uses common I/O management code, which operates on 
[Session](../lib/include/Session.h) object(s). Every **tutorialX** / **howtoX** is expected
to extend it and implement all the relevant virtual functions to make the common code function
properly. The sessions are split into **server** and **client** ones. The **server**
side code is implemented in [src/SeverSession.h](src/ServerSession.h) and 
[src/ServerSession.cpp](src/ServerSession.cpp). The **client**
side code is implemented in [src/ClientSession.h](src/ClientSession.h) and 
[src/ClientSession.cpp](src/ClientSession.cpp) respectively. 

## Server
Let's take a look at definition of the message interface class inside [SeverSession.h](src/ServerSession.h)
```cpp
using Message =
    tutorial1::Message<
        comms::option::ReadIterator<const std::uint8_t*>, // Polymorphic read
        comms::option::WriteIterator<std::uint8_t*>, // Polymorphic write
        comms::option::LengthInfoInterface, // Polymorphic length calculation
        comms::option::IdInfoInterface, // Polymorphic message ID retrieval
        comms::option::NameInterface // Polymorphic message name retrieval
    >;
```
The generated **tutorial1::Message** common interface class is extended
with multiple options, which create various function with **polymorphic**
behavior.

**SIDE NOTE**: **Polymorphic** behavior implies usage of `virtual` function(s).
To implement it the **COMMS Library** uses 
[Non-Virtual Interface Idiom](https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Non-Virtual_Interface). 
Something like:
```
class Message 
{
public:
    void someFunc()
    {
        someFuncImpl();
    }
    
protected:
    virtual void someFuncImpl() = 0;
};
```

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

#### Polymorphic Message Name Retrieval
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

#### Virtual Destructor
Existence of polymorphic (virtual) functions in the common interface
class definition also implies existence of the virtual destructor. It
can be checked using standard type traits:
```
static_assert(std::has_virtual_destructor<Message>::value, "Destructor is not virtual");
```

Fore more details on message interface extensions please read
[How to Use Defined Custom Protocol](https://arobenko.github.io/comms_doc/page_use_prot.html)
page of the **COMMS Library** docuementation.


#### Processing I/O Input
The `turorial1::ServerSession::processInputImpl()` virtual function is invoked
by the driving common I/O library to report unprocessed input. The arguments are 
pointer to the input buffer and its size. The function is expected to 
return number of consumed bytes. To help with such task **COMMS Library** provides
`comms::processAllWithDispatch()` function (requires 
"[comms/process.h](https://arobenko.github.io/comms_doc/process_8h.html)" to be 
included). 
```cpp
std::size_t ServerSession::processInputImpl(const std::uint8_t* buf, std::size_t bufLen)
{
    return comms::processAllWithDispatch(buf, bufLen, m_frame, *this);
}
```
The **first** parameter to the function is pointer to input buffer. The **second**
one is the size of the buffer. The **third** is the frame object that is
responsible to wrap / unwrap the transport information. The last (**fourth**)
parameter is reference to the handling object, which must implement
**handle()** member function for every message type it needs to handle. In
this particular tutorial `ServerSession` implement one common function for
all the messages `void ServerSession::handle(Message& msg)`.

The handling function (`void ServerSession::handle(Message& msg)`) 
uses **polymorphic** interface to report what message was
received (using `msg.name()` and `msg.getId()` calls), 
serialize it into output buffer and send the same message
back. In other words it's an "echo" server.

The serialization of the message uses polymorphic interface to determine
size of the output buffer (call to `m_frame.length(msg)` will result in
call to polymorphic `msg.length()`) as well as write message payload
(call to `m_frame.write(...)` will result in call to polymorphic
`msg.write(...)`).

## Client
The client side is implemented in [ClientSession.h](src/ClientSession.h) and
[ClientSession.cpp](src/ClientSession.cpp). The common interface class the
**client** side has chosen is a bit different to the **server**.
```cpp
using Message =
    tutorial1::Message<
        comms::option::ReadIterator<const std::uint8_t*>, // Polymorphic read
        comms::option::WriteIterator<std::back_insert_iterator<std::vector<std::uint8_t> > >, // Polymorphic write
        comms::option::LengthInfoInterface, // Polymorphic length calculation
        comms::option::IdInfoInterface, // Polymorphic message ID retrieval
        comms::option::NameInterface, // Polymorphic message name retrieval
        comms::option::Handler<ClientSession> // Polymorphic dispatch
    >;
```

#### Polymorphic Write
The **client** side also uses polymorphic write similar to the **server**. However
the iterator used for writing is `std::back_insert_iterator<std::vector<std::uint8_t> >`.
It results in a bit different serialization code for the message that needs
to be sent out:
```cpp
void ClientSession::sendMessage(const Message& msg)
{
    ... // Printing what is being sent

    std::vector<std::uint8_t> output;

    // Use polymorphic serialization length calculation to reserve
    // needed capacity
    output.reserve(m_frame.length(msg));

    // Serialize message into the buffer (including framing)
    // The serialization uses polymorphic write functionality.
    auto writeIter = std::back_inserter(output);

    // The frame will use polymorphic message ID retrieval to
    // prefix message payload with message ID
    auto es = m_frame.write(msg, writeIter, output.max_size());
    if (es != comms::ErrorStatus::Success) {
        assert(!"Write operation failed unexpectedly");
        return;
    }

    ... // Sending serialized buffer
}
```
The capacity of the output buffer is **reserved** rather than the buffer
being **resized** (compared to the **server**). The chosen iterator will
result in usage of `push_back()` member function of the used output vector
when message being serialized into it.

#### Polymorphic Dispatch
Another difference is that **client** side chose to add polymorphic
dispatch functionality to the message interface by using `comms::option::Handler`
option. The template parameter specifies type of the handling object. Usage
of this object results in adding the following type and polymorphic member
function to the message interface class.
```cpp
class Message 
{
public: 
    // Handler class (parameter passed to comms::option::Handler)
    using Handler = tutorial1::ClientSession;
    
    // Polymorphic dispatch
    void dispatch(Handler& handler);
};
```
The handler class (`tutorial::ClientSession`) is expected to define
`handle()` member function for any message type it is expected to handle. 
It also needs to define `handle()` member function for the common interface class
which is going to be called when there is no appropriate `handle()` member
function being defined for the real message type.
```cpp
class ClientSession : public Session
{
public:

    // Common interface class for all the messages
    using Message = tutorial1::Message<...>;

    // Definition of all the used message classes
    using Msg1 = tutorial1::message::Msg1<Message>;
    using Msg2 = tutorial1::message::Msg2<Message>;

    // Handling functions for all the dispatched message objects
    void handle(Msg1& msg);
    void handle(Msg2& msg);
    void handle(Message& msg);
    
    ... // Irrelevant code
};
```
**SIDE NOTE**: The **COMMS Library** provides an ability to return values
from message handling (`handle()`) member functions, but this is subject
for another tutorial.

#### Processing I/O Input
The `turorial1::ClientSession::processInputImpl()` virtual function is invoked
by the driving common I/O library to report unprocessed input. The arguments are 
pointer to the input buffer and its size. The function is expected to 
return number of consumed bytes. It is possible to invoke `comms::processAllWithDispatch()`
function provided by the **COMMS Library**, which will strip off the transport
framing, create appropriate message object and will dispatch it to appropriate
handling function. However, just to show the usage of `dispatch()` member function
of the message object, the manual processing code (similar to one
inside the `comms::processAllWithDispatch()` has been written. Please
pay closer attention on the dispatch statement:
```cpp
if (es == comms::ErrorStatus::Success) {
    assert(msg); // Message object must be allocated

    msg->dispatch(*this); // Uses polymorphic dispatch, appropriate
                          // handle() member function will be called.
}
```
The internals of `comms::processAllWithDispatch()` (when used) perform **compile time**
evaluation of the message interface class options and perform similar polymorphic
dispatch if it is supported (`comms::option::Handler` option is used). In case
this option is not provided different dispatch method is used. Various dispatch
methods will be covered in details in later tutorial(s).

#### Non-Polymorphic Message Interface
As was mentioned earlier the 
[comms::MessageBase](https://arobenko.github.io/comms_doc/classcomms_1_1MessageBase.html)
class is used (inherited from) to define proper message definition class.
As the result the latter automatically defines the following **NON-polymorphic** (non-virtual)
member functions, which can be used when actual message type is known to
avoid unnecessary redirection of polymorphic (virtual) functions.
```cpp
class Msg1 : public comms::MessageBase<...>
{
public:
    // NON-polymorphic read of payload
    template <typename TIter>
    comms::ErrorStatus doRead(TIter& iter, std::size_t len);
    
    // NON-polymorphic write of payload
    template <typename TIter>
    comms::ErrorStatus doWrite(TIter& iter, std::size_t len) const;
    
    // NON-polymorphic message ID retrieval
    MsgIdType doGetId() const;
    
    // NON-polymorphic payload serialization length calculation
    std::size_t doLength() const
    
    // NON-polymorphic human readable name of the message
    static const char* doName();
    
    // NON-polymorphic validity check
    bool doValid() const;
    
    // NON-polymorphic bring message to consistent state 
    // (will be covered in later tutorial(s).
    bool doRefresh();
}
```
The usage of these functions is demonstrated inside handling function(s):
```cpp
void ClientSession::handle(Msg1& msg)
{
    // The report below uses NON-polymorphic name and ID retrievals
    std::cout << "Received " << msg.doName() << " with ID=" << msg.doGetId() << std::endl;

    ... // Irrelevant code
}
```

## Summary

- **COMMS Library** allows creation of common protocol definition code which
is customized (what features are compiled in) by the end application.
- One of the application customizations is extending common interface
class with multiple options, which define polymorphic interface for every message.
- The **CommsDSL** allows definition of various transport frames and generates
appropriate code the wrap / unwrap message payload with relevant fields.
- The **COMMS Library** provides `comms::processAllWithDispatch()` helper
function that can be used to unwrap transport framing and dispatch
detected messages to relevant handling functions.
- The input / output buffers are responsibility of the end application. The
**COMMS Library** as well as generated code use only provided iterators to the
input / output data.
- By default the message object is dynamically allocated and held by `std::unique_ptr`.
How to modify this default behavior will be explained in one of the later
tutorials.
- Every message object has also non-polymorphic interface functions named
`doX()`, which should be used when real message type is known to avoid
unnecessary indirection of polymorphic calls.
