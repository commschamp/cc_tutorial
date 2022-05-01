# Tutorial 11
Avoiding virtual functions.

All the previous tutorials exposed polymorphic behavior when defining common message interface
class. The [COMMS Library](https://github.com/commschamp/comms) also
properly supports message classes without any virtual functions.

Let's take a look at inner definitions inside [src/ServerSession.h](src/ServerSession.h).
```cpp
class ServerSession : public Session
{
public:
    // Common interface class for all the messages
    using Message = tutorial11::Message<>;
};
```
The common message interface class does not receive any extension options, hence does **NOT** 
expose any polymorphic behavior, i.e. there are no virtual functions. As the result all the
actual messages (`Msg1`, `Msg2`, ...) that extend 
[comms::MessageBase](https://commschamp.github.io/comms_doc/classcomms_1_1MessageBase.html) don't
have any v-tables and are equivalent to being simple structs of data.

It was explained in one of the previous tutorials that 
[message dispatch](https://commschamp.github.io/comms_doc/page_dispatch.html) logic can 
also generate polymorphic dispatch table with virtual functions. If the main goal is to
avoid virtual functions altogether, not just for messages, then the dispatch when processing
incoming message needs to be forced to be "static-binary-search" one or the 
`switch` statement based provided by the generated code.
```cpp
std::size_t ServerSession::processInputImpl(const std::uint8_t* buf, std::size_t bufLen)
{
    ...

    // Force switch statement based dispatch
    using Dispatcher =
        tutorial11::dispatch::ServerInputMsgDispatcher<ServerProtocolOptions>;    

    // Process reported input, create relevant message objects and
    // dispatch all the created messages
    // to this object for handling (handle() member function will be called)
    return comms::processAllWithDispatchViaDispatcher<Dispatcher>(buf, bufLen, m_frame, *this);
}
```
There is another place that can potentially contain virtual functions. It's when the message
framing is processed, there is a need to map numeric message ID into appropriate message class.
The [COMMS Library](https://github.com/commschamp/comms) uses the same
[dispatch logic](https://commschamp.github.io/comms_doc/page_dispatch.html) for this process.
If the message IDs are sequential with less than 10% holes, then the polymorphic dispatch tables
may be created. To avoid that there is a need to request "static-binary-search" dispatch for this
process as well. In order to understand how to do it there is a need to dive a little bit into the 
[COMMS Library](https://github.com/commschamp/comms) internals.

The framing uses [comms::protocol::MsgIdLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1MsgIdLayer.html)
which is responsible to read received numeric message ID and create appropriate message object.
In order to create such object the 
[comms::protocol::MsgIdLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1MsgIdLayer.html)
contains [comms::MsgFactory](https://commschamp.github.io/comms_doc/classcomms_1_1MsgFactory.html) in its
private data members. The 
contained [comms::MsgFactory](https://commschamp.github.io/comms_doc/classcomms_1_1MsgFactory.html)
can be configured to use appropriate dispatch logic via its options. The relevant options are:
`comms::option::app::ForceDispatchPolymorphic`, `comms::option::app::ForceDispatchStaticBinSearch`, or 
`comms::option::app::ForceDispatchLinearSwitch`. The 
[comms::protocol::MsgIdLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1MsgIdLayer.html) 
has its own supported options which it processes. The ones it doesn't expect are passed to the 
[comms::MsgFactory](https://commschamp.github.io/comms_doc/classcomms_1_1MsgFactory.html).
It means in order to avoid creation of virtual functions inside 
[comms::MsgFactory](https://commschamp.github.io/comms_doc/classcomms_1_1MsgFactory.html) the
[comms::protocol::MsgIdLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1MsgIdLayer.html) 
needs to receive `comms::option::app::ForceDispatchStaticBinSearch` option.

The used `Frame` inside the [include/tutorial11/frame/Frame.h](include/tutorial11/frame/Frame.h) is defined
like this:
```cpp
template <typename TOpt = tutorial11::options::DefaultOptions>
struct FrameLayers
{
    ...
    /// @brief Definition of layer "Id".
    template <typename TMessage, typename TAllMessages>
    using Id =
        comms::protocol::MsgIdLayer<
            ...,
            typename TOpt::frame::FrameLayers::Id
        >;
    
    ...
    template<typename TMessage, typename TAllMessages>
    using Stack = ...
};

template <
   typename TMessage,
   typename TAllMessages = tutorial11::input::AllMessages<TMessage>,
   typename TOpt = tutorial11::options::DefaultOptions
>
class Frame : public
    FrameLayers<TOpt>::template Stack<TMessage, TAllMessages>
{
    ...
};
```
**NOTE** that there is a way to pass extra options to the definition of `Id` layer.
To do so this tutorial defines separate protocol options ([src/ProtocolOptions.h](src/ProtocolOptions.h))
shared by both **server** and **client**.
```cpp
template <typename TBase = tutorial11::options::DefaultOptions>
struct ProtocolOptionsT : public TBase
{
    struct frame : public TBase::frame
    {
        struct FrameLayers : public TBase::frame::FrameLayers
        {
            using Id = 
                std::tuple<
                    comms::option::app::ForceDispatchStaticBinSearch,
                    typename TBase::frame::FrameLayers::Id
                >;
            
        }; // struct FrameLayers
        
    }; // struct frame
};

using ProtocolOptions = ProtocolOptionsT<>;
```
Please pay attention that the code above is written to support extension of **any**
pre-defined options that can be passed as a template parameter.

The definition of the frame inside [src/ServerSession.h](src/ServerSession.h) is:
```cpp
class ServerSession : public Session
{
public:
    ...
    
    // Common interface class for all the messages
    using Message = tutorial11::Message<>;

    // Protocol options for server
    using ServerProtocolOptions = 
        ProtocolOptionsT<
            tutorial11::options::ServerDefaultOptions
        >;
        
    ...
private:
    using Frame = 
        tutorial11::frame::Frame<
            Message,
            tutorial11::input::ServerInputMessages<Message, ServerProtocolOptions>,
            ServerProtocolOptions
        >;

    ...
};
```
Note that the [schema](dsl/schema.xml) file of this tutorial does not specify 
uni-directional messages, i.e. the definitions of the 
[tutorial11::input::AllMessages](include/tutorial11/input/AllMessages.h), 
[tutorial11::input::ServerInputMessages](include/tutorial11/input/ServerInputMessages.h), and
[tutorial11::input::ClientInputMessages](include/tutorial11/input/ClientInputMessages.h) look
exactly the same. Also the protocol options defined as
[tutorial11::options::DefaultOptions](include/tutorial11/options/DefaultOptions.h),
[tutorial11::options::ServerDefaultOptions](include/tutorial11/options/ServerDefaultOptions.h), and
[tutorial11::options::ClientDefaultOptions](include/tutorial11/options/ClientDefaultOptions.h) do not
differ in terms of defined options. It is still a good practice to force **server** and/or 
**client** application specific configuration even if it doesn't differ from the general case
(usage of [tutorial11::input::AllMessages](include/tutorial11/input/AllMessages.h) and/or
[tutorial11::options::DefaultOptions](include/tutorial11/options/DefaultOptions.h)).
There is always a potential for uni-directional message to be added to the protocol in the future which 
will cause the configurations to be different.

Another important thing to understand is how the outgoing message is serialized. Due to the 
fact that the message interface class does **NOT** expose any polymorphic behavior, the 
knowledge about real message type is needed to be able to write message numeric ID as well as
properly write all message fields as the payload. There is no other choice but to make 
the serialization function to be a template one:
```cpp
class ServerSession : public Session
{
    ///
private:
    template <typename TMsg>
    void sendMessage(TMsg& msg)
    {
        ...
    }

};
```

Another curious thing to notice is a lack of virtual destructor for the common message interface 
class (due to the lack of any polymorphic behaviour). During the `read()` operation the frame 
dynamically allocates proper message object and holds it by the `std::unique_ptr` to the 
**common message interface** class (see [Frame::MsgPtr](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1ProtocolLayerBase.html)). 
After reading these statements any experienced C++ developer should scream about 
incorrect message destruction and potential memory leaks. **HOWEVER**, this is not the case
with the [COMMS Library](https://github.com/commschamp/comms). It 
recognizes lack of virtual destructor at **compile-time** and uses a custom deleter for 
the `std::unique_ptr`. The deleter stores numeric ID of the allocated message object and uses 
[Static Binary Search](https://commschamp.github.io/comms_doc/page_dispatch.html)
way of dispatching to map stored numeric ID into appropriate message type. Before actual
deletion the provided pointer is cast to the right class and properly destructed.

To test this, all of the available message definitions inside 
[include/tutorial11/message](include/tutorial11/message) were modified to
print their destructor function name when it is invoked:
```cpp
template <typename TMsgBase, typename TOpt = tutorial11::options::DefaultOptions>
class Msg1 : public
    comms::MessageBase<...>
{
public:
    
    /// @brief Custom destructor
    ~Msg1()
    {
        std::cout << "Proper destruction: " << __FUNCTION__ << std::endl;
    }
    
    ...
};

```
The **client** side of this tutorial sends `Msg1`, `Msg2`, and `Msg3` to the 
**server**. The latter identifies the messages, dynamically allocates appropriate message object 
(held by `std::unique_ptr` to the common interface class), dispatches it to the handling function, 
and then destructs the message object when it's no longer needed. The output produced by the **server** application
looks like this:
```
Processing input: 0 1 1 
Received message "Message 1" with ID=1
Proper destruction: ~Msg1
Processing input: 0 1 2 
Received message "Message 2" with ID=2
Proper destruction: ~Msg2
Processing input: 0 1 3 
Received message "Message 3" with ID=3
Proper destruction: ~Msg3
```

----

**SIDE NOTE:** The [commsdsl2comms](https://github.com/commschamp/commsdsl) code generator allows injection 
of custom C++ code snippets into the generated one. It is explained in 
[Injecting Custom Code](https://github.com/commschamp/commsdsl/blob/master/doc/Manual_commsdsl2comms.md#injecting-custom-code)
section of [commsdsl2comms manual](https://github.com/commschamp/commsdsl/blob/master/doc/Manual_commsdsl2comms.md) documentation page.
The [dsl_src](dsl_src) folder of this tutorial contains code snippets injected into the message definitions.
The [dsl_src/include/tutorial11/message/MsgX.h.inc](dsl_src/include/tutorial11/message/Msg1.h.inc) contains 
extra include statements to be added at the beginning of `MsgX.h` file, while 
[dsl_src/include/tutorial11/message/MsgX.h.public](dsl_src/include/tutorial11/message/Msg1.h.public)
contains extra code to be added to the `public` section of the message definition.

---

The [ClientSession](src/ClientSession.h) is defined in very similar way but choosing client specific
configuration:
```cpp
class ClientSession : public Session
{
public:

    // Common interface class for all the messages
    using Message = tutorial11::Message<>;

    // Protocol options for client
    using ClientProtocolOptions = 
        ProtocolOptionsT<
            tutorial11::options::ClientDefaultOptions
        >;        
        
    // Definition of all the used message classes
    using Msg1 = tutorial11::message::Msg1<Message, ClientProtocolOptions>;
    using Msg2 = tutorial11::message::Msg2<Message, ClientProtocolOptions>;
    using Msg3 = tutorial11::message::Msg3<Message, ClientProtocolOptions>;

private:
    // Send the message requires knowledge about the full message type
    template <typename TMsg>
    void sendMessage(const TMsg& msg)
    {
        ...
    }

    // Client specific frame 
    using Frame = 
        tutorial11::frame::Frame<
            Message,
            tutorial11::input::ClientInputMessages<Message, ClientProtocolOptions>,
            ClientProtocolOptions
        >;

};
```
The dispatch of the **client** input messages was also chosen to be the
`switch` statement based.
```cpp
std::size_t ClientSession::processInputImpl(const std::uint8_t* buf, std::size_t bufLen)
{
    ...

    // Force switch statement based dispatch
    using Dispatcher =
        tutorial11::dispatch::ClientInputMsgDispatcher<ClientProtocolOptions>;    

    // Process reported input, create relevant message objects and
    // dispatch all the created messages
    // to this object for handling (appropriate handle() member function will be called)
    return comms::processAllWithDispatchViaDispatcher<Dispatcher>(buf, bufLen, m_frame, *this);
}
```

## Summary 
- The [COMMS Library](https://github.com/commschamp/comms) provides
  multiple means to avoid any polymorphic functionality, i.e. virtual functions.
- When no polymorphic behavior options are passed to the common interface definition, the
  message objects don't have any v-table and their destructors are non-virtual.
- All the dynamically allocated message objects are still held by the `std::unique_ptr`
  to the common message interface class, but with a custom deleter which insures
  correct destruction and de-allocation of the object.
- The framing layer responsible for allocation of the message object is 
  [comms::protocol::MsgIdLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1MsgIdLayer.html), which
  uses [comms::MsgFactory](https://commschamp.github.io/comms_doc/classcomms_1_1MsgFactory.html) in its 
  private data members to allocate appropriate message object when the ID value is known.
- The message allocation options passed to the 
  [comms::protocol::MsgIdLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1MsgIdLayer.html) are
  also forwarded to [comms::MsgFactory](https://commschamp.github.io/comms_doc/classcomms_1_1MsgFactory.html). They
  can be used to force a particular dispatch policy for mapping numeric message ID into the message type.
- In order to forcefully avoid generation on polymorphic dispatch table inside 
  [comms::MsgFactory](https://commschamp.github.io/comms_doc/classcomms_1_1MsgFactory.html) the 
  `comms::option::app::ForceDispatchStaticBinSearch` option needs to be passed to the 
  `Id` layer definition of the framing.
- The generated dispatch functions and classes inside [include/&lt;namespace&gt;/dispatch](include/tutorial11/dispatch)
  folder can also be used for dispatch functionality when virtual functions are been avoided.
  

[Read Previous Tutorial](../tutorial10) &lt;-----------------------&gt; [Read Next Tutorial](../tutorial12) 
