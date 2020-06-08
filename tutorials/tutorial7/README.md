# Tutorial 7
Dispatching single message object to multiple handlers.

In this tutorial the **server** is a usual _echo_ one and of little interest to us. 
The **client** side, however, shows a way of how to dispatch a single message object to 
multiple handlers.

First of all, there is no limitation imposed on the handling class against using
virtual `handle()` functions. It's easy to create such a base class for all the other
candlers and pass it to message interface definition using `comms::option::app::Handler`
option.
```cpp
// Forward declaration
class HandlerBase;

// Interface defintion
using Message = 
    comms::Message<
        ...,
        comms::option::app::Handler<HandlerBase>
    >;
    
// Definition of the messages
using Msg1 = tutorial7::message::Message1<Message>;
using Msg2 = ...

// Definition of the base class of the handlers
class HandlerBase
{
    virtual void handle(Msg1& msg) = 0;
    virtual void handle(Msg2& msg) = 0;
    ...
    virtual void handle(Message& msg) = 0;
}

class Handler1 : public HandlerBase
{
    virtual void handle(Msg1& msg) override {...}
    virtual void handle(Msg2& msg) override {...}
    ...
};

class Handler2 : public HandlerBase
{
    virtual void handle(Msg1& msg) override {...}
    virtual void handle(Msg2& msg) override {...}
    ...
};
```
As the result the message interface class defines `dispatch()` member
function that receives a reference to the `HandlerBase` object, like this:
```cpp
class Message
{
public:
    void dispatch(HandlerBase& handler) {...}
}
```
As the result the following code works fine:
```cpp
using MessagePtr = std::unique_ptr<Message>;
MessagePtr msg(new Msg1);

Handler1 handler1;
Handler2 handler2;

msg->dispatch(handler1);
msg->dispatch(handler2);
```
Please pay attention to the following details:
- The usage of the `comms::option::app::Handler` option requires a knowledge about the
  handler type.
- The handler definition requires knowledge about the message types (`Msg1`, `Msg2`, ...) to
  properly define the handling functions.
- The message types require knowledge about the message interface type.

It's easy to notice that there is a circular dependency on type definition. The good thing is that the
`dispatch()` member function defined by the [comms::Message](https://arobenko.github.io/comms_doc/classcomms_1_1Message.html)
receives the handler type by reference and does **NOT** require a knowledge about the internals of
the handler class, just that it exists. That's why there is a forward declaration of the 
handler base class (`HandlerBase`) before the interface class definition (`Message`).

Similar logic could apply to the definition of the handler classes. When the base class 
(`HandlerBase`) is defined, the `handle()` member functions receive the message objects by
reference. If there is a problem of circular dependencies on type definition for some reason,
the message classes can be forward declared, like this:
```cpp
class Msg1;
class Msg2;

class HandlerBase
{
    virtual void handle(Msg1& msg) = 0;
    virtual void handle(Msg2& msg) = 0;
    ...
    virtual void handle(Message& msg) = 0;
}
```
However, in this case the actual definition of the messages needs to be by inheritance
rather than type aliasing:
```cpp
class Msg1 : public tutorial7::message::Message1<Message> {};
class Msg2 : public tutorial7::message::Message2<Message> {};
...
```
Also note, that when defining the actual handler classes with accessing the message member 
fields and/or member functions the actual type of the message needs to be known, i.e. the
message types / classes need to be defined before defining the handlers.

This was a bit of theory. Now let's take a closer look at the [ClientSession](src/ClientSession.h).
The [comms::GenericHandler](https://arobenko.github.io/comms_doc/classcomms_1_1GenericHandler.html)
helper class provided by the [COMMS Library](https://github.com/arobenko/comms_champion#comms-library) 
is used.
```cpp
class HandlerBase : public
    comms::GenericHandler<
        Message,
        Frame::AllMessages
    >
{
public:
    virtual ~HandlerBase() = default;
};
```
The first template parameter passed to the 
[comms::GenericHandler](https://arobenko.github.io/comms_doc/classcomms_1_1GenericHandler.html)
is the common message interface class. The second one is `std::tuple` of all the message types
handling of which needs to be supported. In this example we reuse the definition of all the
input messages provided to the framing definition.

The [comms::GenericHandler](https://arobenko.github.io/comms_doc/classcomms_1_1GenericHandler.html)
creates a common `virtual void handle(Message& msg)` member function that receives a reference to
the common interface class and does nothing it its body. It also
creates `virtual void handle(...)` member function for every message type provided as a member of the
tuple passed as the second template parameter. The default implementation of such function is to
upcast the message object into the common interface and invoke the common handling function (which 
does nothing). Something like this:
```cpp
class HandlerBase
{
public:
    virtual void handle(Msg1& msg)
    {
        handle(static_cast<Message&>(msg);
    }
    
    virtual void handle(Msg2& msg)
    {
        handle(static_cast<Message&>(msg);
    }    
    ...
    // Handling with common interface
    virtual void handle(Message& msg)
    {
        // Do nothing
    }      
}
```
The deriving class may override any of the defined virtual `handle()` member function to modify the default
behavior.

Another important thing to note is the explicit definition of the virtual destructor:
```cpp
class HandlerBase : ...
{
public:
    virtual ~HandlerBase() = default;
};
```
The reason for explicit definition is that 
[comms::GenericHandler](https://arobenko.github.io/comms_doc/classcomms_1_1GenericHandler.html)
uses inheritance to properly generate its `handle()` member functions. It's been noticed that if
any of such base classes used in inheritance has a virtual destructor, then the compiler creates
multiple unnecessary v-tables which results in significant code size growth. To improve the binary
code quality and size it has been decided to define destructor of the
[comms::GenericHandler](https://arobenko.github.io/comms_doc/classcomms_1_1GenericHandler.html)
as **non-virtual**. In case the actual handlers are dynamically allocated and held by the pointer
to their base class, the compiler might report and error of destroying the polymorphic object without 
virtual destructor. The explicit definition of the later solves the problem.

The definition of the handlers look like this:
```cpp
class Handler1 : public HandlerBase
{
public:
    using HandlerBase::handle; // to avoid "hiding" warning

    virtual void handle(Msg1& msg) override;
    virtual void handle(Message& msg) override;
};

class Handler2 : public HandlerBase
{
public:
    using HandlerBase::handle; // to avoid "hiding" warning

    virtual void handle(Msg2& msg) override;
    virtual void handle(Message& msg) override;
};
```

[Read Previous Tutorial](../tutorial6) &lt;-----------------------&gt; [Read Next Tutorial](../tutorial8) 
