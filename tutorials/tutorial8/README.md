# Tutorial 8
Returning values from message handling functions.

The message handling functions in all the previous tutorials didn't return any value.
```cpp
class ClientSession
{
public:
    ...
    void handle(...);
    ...
};
```

In some use cases it might be beneficial to return some value, processing status for example.
The [COMMS Library](https://github.com/arobenko/comms_champion#comms-library) supports creation
of such constructs.

Let's take a look at the [ClientSession](src/ClientSession.h) definition of this tutorial.
```cpp
class ClientSession : public Session
{
public:
    ...

    // Return type of handle() member functions
    using RetType = bool;

    // Common interface class for all the messages
    using Message =
        tutorial8::Message<
            ...
            comms::option::app::Handler<ClientSession> // Polymorphic dispatch
        >;

    // Definition of all the used message classes
    using Msg1 = tutorial8::message::Msg1<Message>;
    using Msg2 = tutorial8::message::Msg2<Message>;
    using Msg3 = tutorial8::message::Msg3<Message>;

    bool handle(Msg1& msg);
    bool handle(Msg2& msg);
    bool handle(Message& msg);
    ...
};
```
The message interface class defines support for polymorphic dispatch
(thanks to `comms::option::app::Handler` option). The handler class is 
`ClientSession` itself. It also defines `RetType` inner type which
specifies the return type of the `handle()` member functions. 

There is a **compile-time** meta-programming logic inside the
[COMMS Library](https://github.com/arobenko/comms_champion#comms-library) which
determines the return type of the 
[comms::Message](https://arobenko.github.io/comms_doc/classcomms_1_1Message.html)'s 
`dispatch()` member function. If the used handler type defines `RetType` inner type, then
it is taken and defined as return type of the `dispatch()` member function.

In other words the definition of the common message interface class for this tutorial is
equivalent to:
```cpp
class comms::Message
{
public:
    bool dispatch(ClientSession& handler)
    {
        return dispatchImpl(ClientSession& handler)
    }
    
protected:
    virtual bool dispatchImpl(ClientSession& handler) = 0;
};
```
The [comms::MessageBase](https://arobenko.github.io/comms_doc/classcomms_1_1MessageBase.html), 
which serves as the base class for every message implements the virtual function taking
the return type into account:
```cpp
class comms::MessageBase
{
    
protected:
    virtual bool dispatchImpl(ClientSession& handler) override
    {
        return handler.handle(static_cast<RealMessageType&>(*this));
    }
};
```

----

**SIDE NOTE**: One of the previous tutorials showed that the handler type may be 
forward declared bofore the definition of the common message interface class.
It is important to understand that the presence of the `RetType` inner type
inside the handler class cannot be determined. As the result `void` as the
handling return type will be assumed.

---

The input processing function of the `ClientSession` implements the following logic to determine if the
message was processed successfully:
```cpp
std::size_t ClientSession::processInputImpl(const std::uint8_t* buf, std::size_t bufLen)
{
    ...

            if (!msg->dispatch(*this)) {
                std::cerr << "ERROR: Unexpected message processing error" << std::endl;
                getIo().stop(); // Terminate the client after return from the function
                break;
            }

            doNextStage();
    ...
}
```
If the call to `dispatch()` returned false, then the client's execution is interrupted.
In this particular tutorial the **client** sends 3 messages (`Msg1`, `Msg2`, and `Msg3`) 
to the **server** which echoes them back. 

Also the client defines the following handling functions:
```cpp
bool handle(Msg1& msg);
bool handle(Msg2& msg);
bool handle(Message& msg);
```
Please pay attention that only `Msg1` and `Msg2` are properly handled (with `true`
returned by the `handle()` (and `msg.dispatch(...)`). However, when `Msg3` arrives
the common handling function (`bool handle(Message& msg)`) is called, which will
return `false`. As the result, the **client** is expected to report the error message
above and exit.

----

**SIDE NOTE**: All the `comms::dispatch*()` functions defined in
[comms/dispatch.h](https://arobenko.github.io/comms_doc/dispatch_8h.html) also
return the same type as `handle()` member functions of the used handler.
It can be useful for cases when message interface does **NOT** expose polymorphic dispatch and
one of these functions need to be used instead.

---

## Summary
- Returning non-void values from the handling functions is also supported.
- There is a need to define inner `RetType` type which specifies the return
  type of every `handle()` member function.
- The [comms::Message::dispatch()](https://arobenko.github.io/comms_doc/classcomms_1_1Message.html)
  as well as all the functions in [comms/dispatch.h](https://arobenko.github.io/comms_doc/dispatch_8h.html)
  use the inner `RetType` of the handler class to define their own return types.
- In case the handler class is forward declared, the automatic determination of the return 
  type is not possible and as the result `void` is assumed.


[Read Previous Tutorial](../tutorial7) &lt;-----------------------&gt; [Read Next Tutorial](../tutorial9) 
