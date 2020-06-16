# Tutorial 6
Deeper understanding of message dispatch.

All the previous tutorials used a polymorphic dispatch functionality exposed by the
common message interface. Let's remember how it looks and works.

The common interface definition uses 
[comms::option::app::Handler](https://arobenko.github.io/comms_doc/options_8h.html) 
option to specify type of of the handler.
```cpp
class ClientSession
{
public:
    using Message =
        tutorialX::Message<
            ...,
            comms::option::Handler<ClientSession>
        >;

};
```

As the result the defined above `Message` interface exposes the following type and functions:
```cpp
struct Message
{
public:
    using Handler = ClientSession;
    
    void dispatch(Handler& handler)
    {
        dispatchImpl(handler);
    }
    
protected:
    virtual void dispatchImpl(Handler& handler) = 0; // Implemented by the comms::MessageBase
}
```
See also [comms::Message](https://arobenko.github.io/comms_doc/classcomms_1_1Message.html) 
for details.

The [comms::MessageBase](https://arobenko.github.io/comms_doc/classcomms_1_1MessageBase.html),
which is used as a base class for all the defined messages, implements the 
`dispatchImpl()` virtual member function in the following way:
```cpp
template <...>
class comms::MessageBase
{
protected:
    virtual dispatchImpl(Handler& handler) override
    {
        handler.handle(static_cast<RealMessageType&>(*this));
    }
};
```
Where the `RealMessageType` is a type of the message passed to 
[comms::MessageBase](https://arobenko.github.io/comms_doc/classcomms_1_1MessageBase.html)
using [comms::option::def::MsgType](https://arobenko.github.io/comms_doc/options_8h.html) 
option.

Basically it's [Double Dispatch Idiom](https://en.wikipedia.org/wiki/Double_dispatch).

The call to [comms::processAllWithDispatch()](https://arobenko.github.io/comms_doc/process_8h.html)
function performs a **compile-time** analysis of the used interface class and if it exposes
polymorphic dispatch functionality (with `comms::option::app::Handler`) then it is used 
to dispatch message to appropriate handling function. It results in **O(1)** run-time 
performance complexity. However, it generates `dispatchImpl()` for every used message class
(which just redirects the call to the handling function) as well as extends 
v-table of every message to contain a pointer to the function. In some constrained 
environments, such as bare-metal, the code size penalty might be too high. Let's take
a look at other available dispatch options when 
[comms::option::app::Handler](https://arobenko.github.io/comms_doc/options_8h.html)
option is not used, i.e. the message object does NOT support polymorphic dispatch.

The [ServerSession](src/ServerSession.h) of this tutorial defines the common message interface
as:
```cpp
using Message =
    tutorial6::Message<
        comms::option::app::ReadIterator<const std::uint8_t*>, // Polymorphic read
        comms::option::app::WriteIterator<std::uint8_t*>, // Polymorphic write
        comms::option::app::LengthInfoInterface, // Polymorphic length calculation
        comms::option::app::IdInfoInterface // Polymorphic message ID retrieval
    >;
```
Note that `comms::option::app::Handler` is not used. The 
`ServerSession::processInputImpl()` member function still uses 
the [comms::processAllWithDispatch()](https://arobenko.github.io/comms_doc/process_8h.html)
and the message object is dispatched to template `handle()` member function with the 
correctly recognized message type.
```cpp
template <typename TMsg>
void handle(TMsg& msg)
{
    std::cout << "Received message \"" << msg.doName() << "\" with ID=" << (unsigned)msg.doGetId() << std::endl;
    sendMessage(msg);
}
```
Everything seems to work the same way out of the box without any additional effort on the
integrating application side. However, the integrating developer needs to understand what's
going on "under the hood" and how the dispatch is implemented in order to be able to 
fine-tune the code size and/or run-time performance if needed. The 
[Advanced Guide to Message Dispathing](https://arobenko.github.io/comms_doc/page_dispatch.html)
tutorial page from the [COMMS Library](https://github.com/arobenko/comms_champion#comms-library)
documentation contains a detailed description of various available dispatch functionalities and 
their implications.

The [comms::processAllWithDispatch()](https://arobenko.github.io/comms_doc/process_8h.html) 
function calls [comms::dispatchMsg()](https://arobenko.github.io/comms_doc/dispatch_8h.html)
(defined in [comms/dispatch.h](https://arobenko.github.io/comms_doc/dispatch_8h.html)) 
after the message object is successfully created. The 
[comms::dispatchMsg()](https://arobenko.github.io/comms_doc/dispatch_8h.html) function
performs the following **compile-time** analysis to choose a proper dispatch option.

- If message interface class defines polymorphic dispatch (`comms::option::app::Handler` option)
  then it is used.
- If polymorphic dispatch via interface is not supported, then the message IDs are analysed to determine if it's
  worthwhile to create separate polymorphic dispatch tables. The condition for such a dispatch is 
  that messages are not too sparse (no more than 10% holes in the sequence of message IDs or 
  the max ID number of all the messages does not exceed 10). If this is the case (like with
  this tutorial) then **static** dispatch array is created where the access index is actually
  message numeric ID, resulting in **O(1)** run-time performance.
- If message IDs are too sparse then **Static Binary Search** dispatch (explained a bit later) is used.

The dispatch strategy in case of the used schema (with sequential IDs and low number of messages)
and lack of polymorphic dispatch via interface is chosen to still be polymorphic but with
separate static dispatch tables. The [ServerSession](src/ServerSession.cpp) code 
uses compile time verification:
```cpp
std::size_t ServerSession::processInputImpl(const std::uint8_t* buf, std::size_t bufLen)
{
    ...
    using AllMessages = tutorial6::input::AllMessages<Message>;
    static_assert(comms::dispatchMsgTypeIsPolymorphic<AllMessages>(), "Unexpected dispatch type");
    ...
}
```

----

**SIDE NOTE**: The definition of the [frame](include/tutorial6/frame/Frame.h) receives
`std::tuple` of all the supported **input** message types which defaults to
[tutorial6::input::AllMessages](include/tutorial6/input/AllMessages.h)
```cpp
template <
   typename TMessage,
   typename TAllMessages = tutorial6::input::AllMessages<TMessage>,
   typename TOpt = tutorial6::options::DefaultOptions
>
class Frame ...
```

That's why `tutorial6::input::AllMessages` was passed as a template parameter to 
`comms::dispatchMsgTypeIsPolymorphic()` in the code above. Please note that 
this is a **boilerplate** code that may become irrelevant and/or incorrect when
definition of the frame type is changed to have a different set of input messages.
```cpp
using Frame = tutorial6::frame::Frame<Message>;
```

The much better approach would be to reuse `AllMessages` inner type defined by the
[comms::protocol::ProtocolLayerBase](https://arobenko.github.io/comms_doc/classcomms_1_1protocol_1_1ProtocolLayerBase.html)
class which serves as a base type of any framing **layer**. The better code would be:
```cpp
using AllMessages = Frame::AllMessages;
static_assert(comms::dispatchMsgTypeIsPolymorphic<AllMessages>(), "Unexpected dispatch type");
```

----

The [COMMS Library](https://github.com/arobenko/comms_champion#comms-library) strives to
provide sensible default behavior suitable for most cases, but also provides a way
to change / fine-tune it for specific cases. As we already discovered the **default**
behavior for this tutorial is to create independent polymorphic dispatch tables and use
them in case polymorphic dispatch via message interface is not supported. In this 
tutorial [ClientSession](src/ClientSession.cpp) forces **Static Binary Search** way
of dispatching.
```cpp
std::size_t ClientSession::processInputImpl(const std::uint8_t* buf, std::size_t bufLen)
{
    ...
    
    // Force static binary search dispatch
    using Dispatcher =
        comms::MsgDispatcher<comms::option::app::ForceDispatchStaticBinSearch>;

    // Process reported input, create relevant message objects and
    // dispatch all the created messages
    // to this object for handling (appropriate handle() member function will be called)
    auto result = comms::processAllWithDispatchViaDispatcher<Dispatcher>(buf, bufLen, m_frame, *this);
    ...
}
```
The forcing is performed by defining a dispatcher type by aliasing 
[comms::MsgDispatcher](https://arobenko.github.io/comms_doc/classcomms_1_1MsgDispatcher.html)
with appropriate forcing option and using `comms::processAllWithDispatchViaDispatcher()`
function instead of `comms::processAllWithDispatch()`.

----

**SIDE NOTE**: The "Static Binary Search" dispatch is equivalent to having the following 
`if` statements folding.
```cpp
if (msgId < IdOfMidMessageInAllMessages) {
    if (msgId < IdOfOtherRelevantMessageInAllMessages) {
        ...
    }
    else {
        ...
    }
    
else {
    if (msgId < IdOfSomeRelevantMessageInAllMessages) {
        ...
    }
    else {
        ...
    }
}
```
The run-time performance complexity of such code is **O(log(n))**. The benefit of such
dispatch logic is that there are no virtual functions and v-tables involved. It might
be much better approach for bare-metal systems with small ROM size.

## Summary

- The [COMMS Library](https://github.com/arobenko/comms_champion#comms-library) supports
  multiple ways to dispatch message object to the appropriate handling function.
- The [COMMS Library](https://github.com/arobenko/comms_champion#comms-library) has 
  a compile-time logic for choosing a sensible default dispatch code while providing an
  ability to forcing a particular dispatch logic which better suites the application.
- The default way of dispatch used by the 
  [comms::processAllWithDispatch()](https://arobenko.github.io/comms_doc/process_8h.html) 
  function is to call [comms::dispatchMsg()](https://arobenko.github.io/comms_doc/dispatch_8h.html).
- The forcing of the dispatch way is performed by defining `Dispatcher` type using
  [comms::MsgDispatcher](https://arobenko.github.io/comms_doc/classcomms_1_1MsgDispatcher.html) 
  as well as using [comms::processAllWithDispatchViaDispatcher()](https://arobenko.github.io/comms_doc/process_8h.html)
  function.
- The [COMMS Library](https://github.com/arobenko/comms_champion#comms-library) documentation contains
  a separate [detailed tutorial page](https://arobenko.github.io/comms_doc/page_dispatch.html) 
  on various supported ways of message dispatch.
  
[Read Previous Tutorial](../tutorial5) &lt;-----------------------&gt; [Read Next Tutorial](../tutorial7) 
