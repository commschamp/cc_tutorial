# Tutorial 7
Dispatching single message object to multiple handlers.

In this tutorial the **server** is a usual _echo_ one and of little interest to us. 
The **client** side, however, shows a way of how to dispatch a single message object to 
multiple handlers.

First of all, there is no limitation imposed on the handling class against using
virtual `handle()` functions. It's easy to create such a base class for all the other
handlers and pass it to message interface definition using `comms::option::app::Handler`
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
  handler type (`HandlerBase`).
- The handler definition requires knowledge about the message types (`Msg1`, `Msg2`, ...) to
  properly define the handling functions.
- The message types require knowledge about the message interface type.

It's easy to notice that there is a circular dependency on type definition. The good thing is that the
`dispatch()` member function defined by the [comms::Message](https://commschamp.github.io/comms_doc/classcomms_1_1Message.html)
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
message types / classes need to be defined before defining the handling functions.

This was a bit of theory. Now let's take a closer look at the [ClientSession](src/ClientSession.h).
The [comms::GenericHandler](https://commschamp.github.io/comms_doc/classcomms_1_1GenericHandler.html)
helper class provided by the [COMMS Library](https://github.com/commschamp/comms) 
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
[comms::GenericHandler](https://commschamp.github.io/comms_doc/classcomms_1_1GenericHandler.html)
is the common message interface class. The second one is `std::tuple` of all the message types
handling of which needs to be supported. In this example we reuse the definition of all the
input messages provided to the framing definition.

The [comms::GenericHandler](https://commschamp.github.io/comms_doc/classcomms_1_1GenericHandler.html)
creates a common `virtual void handle(Message& msg)` member function that receives a reference to
the common interface class and does nothing in its body. It also
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
        handle(static_cast<Message&>(msg));
    }
    
    virtual void handle(Msg2& msg)
    {
        handle(static_cast<Message&>(msg));
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
[comms::GenericHandler](https://commschamp.github.io/comms_doc/classcomms_1_1GenericHandler.html)
uses inheritance to properly generate its `handle()` member functions. It's been noticed that if
any of such base classes used in inheritance has a virtual destructor, then the compiler creates
multiple unnecessary v-tables which results in significant code size growth. To improve the binary
code quality and size it has been decided to define destructor of the
[comms::GenericHandler](https://commschamp.github.io/comms_doc/classcomms_1_1GenericHandler.html)
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
The handlers can override any number of of virtual `handle()` member functions and
leave the default behavior for others. Note, that depending on used compiler options
there may be a warning or an error report about hiding other inherited `handle()`
member functions. To suppress such report `using HandlerBase::handle;` statement
is used.

Please also take a look how the `ClientSession::processInputImpl()` is implemented.
It doesn't use `comms::processAllWithDispatch()` as many other tutorials did because
there is no single handler object to dispatch the message to. The handling loop 
needs to be implemented manually.

Once the message object is successfully created the dispatch to multiple handlers is 
implemented like this:
```cpp
assert(msg); // Message object must be allocated

// Dispatch to all the handlers
std::cout << "-----------------------------\n";
for (auto& h : m_handlers) {
    msg->dispatch(*h);
}
```

The handlers are dynamically allocated and held by `std::unique_ptr` to 
the base class.
```cpp
class ClientSession : public Session
{
public:
    ...
    using HandlerPtr = std::unique_ptr<HandlerBase>;
    
private:
    ...
    std::vector<HandlerPtr> m_handlers;
};

ClientSession::ClientSession(boost_wrap::io& io)
  : Base(io)
{
    m_handlers.emplace_back(new Handler1);
    m_handlers.emplace_back(new Handler2);
}
```

--- 

**SIDE NOTE**: Using polymorphic dispatch described above to support multiple
handlers is **NOT** a must have solution. It is still possible to use various
dispatch alternatives defined in [comms/dispatch.h](https://commschamp.github.io/comms_doc/dispatch_8h.html).
For example:
```cpp
// Dispatch to all the handlers
std::cout << "-----------------------------\n";
Handler1 handler1;
Handler2 handler2;

comms::dispatchMsgStaticBinSearch<Frame::AllMessages>(*msg, handler1);
comms::dispatchMsgStaticBinSearch<Frame::AllMessages>(*msg, handler2);
```
However be aware that the types of the handlers differ and the code of 
`comms::dispatchMsgStaticBinSearch()` will be duplicated for every handler
type passed to the function.

In case the handlers are polymorphic themselves like presented in this tutorial, then
it is possible to unify the dispatch logic:
```cpp
// Dispatch to all the handlers
std::cout << "-----------------------------\n";
for (auto& h : m_handlers) {
    comms::dispatchMsgStaticBinSearch<Frame::AllMessages>(*msg, *h);
}
```

Also note that `comms::dispatchMsgStaticBinSearch()` requires knowledge about message ID to 
be able to implement proper comparison statements. The variant of the 
`comms::dispatchMsgStaticBinSearch()` used above does not receive the message ID as
its parameter, hence must retrieve it using polymorphic `msg.getId()` call. There 
might be a case when message interface does not allow polymorphic retrieval of message ID.
In such case the ID information needs to be retrieved during framing processing. How to 
do it is out of scope for this tutorial and will be covered later.

It is also recommended to read 
[Advanced Guide to Message Dispatching](https://commschamp.github.io/comms_doc/page_dispatch.html)
tutorial page for deeper understanding of available dispatch mechanisms provided by 
the [COMMS Library](https://github.com/commschamp/comms).

----

## Summary
- Dispatch of the single message object to multiple handlers can be implemented by using
  common base class for all the handlers with virtual `handle()` member functions.
- The type of such common base class needs to be passed to the message interface 
  using `comms::option::app::Handler` option.
- If there are type definition circular dependencies the handler class can be forward declared.
- It is recommended to use [comms::GenericHandler](https://commschamp.github.io/comms_doc/classcomms_1_1GenericHandler.html)
  to implement polymorphic base class for all the handlers.
- The polymorphic way of dispatch is recommended solution when multiple handlers need to
  be supported, but it's **NOT** a "must have" one. Other dispatch functions 
  defined in [comms/dispatch.h](https://commschamp.github.io/comms_doc/dispatch_8h.html)
  can also be used. See also 
  [Advanced Guide to Message Dispatching](https://commschamp.github.io/comms_doc/page_dispatch.html)
  tutorial page.

[Read Previous Tutorial](../tutorial6) &lt;-----------------------&gt; [Read Next Tutorial](../tutorial8) 
