# Tutorial 6
Deeper understanding of message dispatch.

All the previous tutorials used a polymorphic dispatch functionality exposed by the
common message interface. Let's remember how it looks and works

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
    
    void handle(Handler& handler)
    {
        handleImpl(handler);
    }
    
protected:
    virtual handleImpl(Handler& handler) = 0; // Implemented by the comms::MessageBase
}
```
See also [comms::Message](https://arobenko.github.io/comms_doc/classcomms_1_1Message.html) 
for details.

The [comms::MessageBase](https://arobenko.github.io/comms_doc/classcomms_1_1MessageBase.html) 
which is used as a base class for all the defined messages implements the 
`handleImpl()` virtual member function in the following way:
```cpp
template <...>
class comms::MessageBase
{
protected:
    virtual handleImpl(Handler& handler) override
    {
        handler.handle(static_cast<RealMessageType&>(*this));
    }
};
```
Where the `RealMessageType` is a type of the message passed to 
[comms::MessageBase](https://arobenko.github.io/comms_doc/classcomms_1_1MessageBase.html)
using [comms::option::def::MsgType](https://arobenko.github.io/comms_doc/options_8h.html) 
option.

The call to [comms::processAllWithDispatch()](https://arobenko.github.io/comms_doc/process_8h.html)
function performs a **compile-time** analysis of the used interface class and if it exposes
polymorphic dispatch functionality (with `comms::option::app::Handler`) then it is used 
to dispatch message to appropriate handling function. In results in **O(1)** run-time 
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
  
[Read Previous Tutorial](../tutorial5) &lt;-----------------------&gt; [Read Next Tutorial](../tutorial7) 
