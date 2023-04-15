# Tutorial 18
How to access transport framing fields.

In all the tutorials so far the transport framing fields have been silently stripped 
away by the frame management and only the message object dispatched for handling. 
There are ways to re-assign values from the frame using `<value>` layer in 
conjunction with custom `<interface>`. However, there may be cases when it's not
enough and there is a need to actually know the values of the other fields 
(from `<id>`, `<size>` and other layers). 

This tutorial demonstrates a way of caching and accessing the fields of the framing layers.

The [ServerSession](src/ServerSession.cpp) demonstrates retrieval of only message numeric 
ID and the relative index of the message (there are different forms of the same message which 
are implemented as separate classes).
```cpp
std::size_t ServerSession::processInputImpl(const std::uint8_t* buf, std::size_t bufLen)
{
    ...
    std::size_t consumed = 0U;
    while (consumed < bufLen) {
        ...

        tutorial18::MsgId msgId = tutorial18::MsgId_ValuesLimit;
        std::size_t msgIdx = std::numeric_limits<std::size_t>::max();
        auto es = 
            m_frame.read(
                msg, 
                iter, 
                remLen, 
                comms::protocol::msgId(msgId),
                comms::protocol::msgIndex(msgIdx));

        ...

        if (es == comms::ErrorStatus::Success) {
            assert(msg); // Message object must be allocated

            std::cout << "Detected message: ID=" << (unsigned)msgId << "; idx=" << msgIdx << std::endl; 

            // Dispatch using id + index to map to real type
            comms::dispatchMsg<ServerInputMessages>(msgId, msgIdx, *msg, *this);
        }

        ...
    }

    return consumed;
}
```
The [read()](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1ProtocolLayerBase.html)
member function of every protocol layer receives a variadic `extraValues` last parameter, which can be 
used to add several output parameters to the function. In this example the 
[comms::protocol::msgId()](https://commschamp.github.io/comms_doc/namespacecomms_1_1protocol.html) is used 
to add `msgId` local variable as an output parameter for the message numeric ID. Also the 
[comms::protocol::msgIndex()](https://commschamp.github.io/comms_doc/namespacecomms_1_1protocol.html)
is used to add `msgIdx` local variable as an output parameter for the index of the message (offset in 
the tuple of the input messages starting from the first message sharing the same ID).
Later down the code both `msgId` and `msgIdx` values are used to dispatch message object into the 
appropriate handling function using 
[comms::dispatchMsg](https://commschamp.github.io/comms_doc/dispatch_8h.html) function.


The [ClientSession](src/ClientSession.cpp) on the other hand demonstrates caching of **all** the framing 
fields.
```cpp
std::size_t ClientSession::processInputImpl(const std::uint8_t* buf, std::size_t bufLen)
{
    ...
    std::size_t consumed = 0U;
    while (consumed < bufLen) {
        ...
        Frame::MsgPtr msg;
        Frame::AllFields transportFields;

        auto es = 
            m_frame.readFieldsCached(
                transportFields,
                msg, 
                iter, 
                remLen);

        ...

        if (es == comms::ErrorStatus::Success) {
            assert(msg); // Message object must be allocated

            std::cout << "Message transport fields:\n";
            printIntFieldHex(m_frame.layer_sync().accessCachedField(transportFields));
            printIntFieldHex(m_frame.layer_size().accessCachedField(transportFields));
            printEnumField(m_frame.layer_id().accessCachedField(transportFields));
            printDataFieldNoName(m_frame.layer_data().accessCachedField(transportFields));
            printIntFieldHex(m_frame.layer_checksum().accessCachedField(transportFields));
            std::cout << std::endl;

            msg->dispatch(*this);
        }

        ...
    }

    return consumed;
}
```
Every [layer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1ProtocolLayerBase.html) defines
`AllFields` inner type which is `std::tuple` of all the fields starting from the layer 
being defined and down to the bottom (`<payload>`) one. As the result the `AllFields` type of the outermost layer 
(which is also used as a full frame) is a tuple of all the framing fields.

Also every layer defines [readFieldsCached()](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1ProtocolLayerBase.html)
member function, which is similar to `read()` used so far, but receives the tuple of all the fields it needs to update as 
its first parameter. After the read operation is complete the provided `transportFields` tuple will have updated values which 
can be accessed later.

Please pay attention that the frame definition uses `COMMS_PROTOCOL_LAYERS_ACCESS()` macro, which defines names of the 
used layers and allows convenient access to them using `layer_*()` member function.
```cpp
template <
   typename TMessage,
   typename TAllMessages = tutorial18::input::AllMessages<TMessage>,
   typename TOpt = tutorial18::options::DefaultOptions
>
class Frame : public
    FrameLayers<TOpt>::template Stack<TMessage, TAllMessages>
{
    using Base =
        typename FrameLayers<TOpt>::template Stack<TMessage, TAllMessages>;
public:
    ...
    COMMS_PROTOCOL_LAYERS_ACCESS(
        data,
        id,
        size,
        checksum,
        sync
    );
};
```
Once the layer object is accesses its 
[accessCachedField()](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1ProtocolLayerBase.html)
member function can be used to access appropriate field in the cached fields tuple.

Note that the inner field of the `<payload>` layer is 
[comms::field::ArrayList](https://commschamp.github.io/comms_doc/classcomms_1_1field_1_1ArrayList.html) of 
raw `std::uint8_t` bytes (equivalent to being `<data>`). The options passed to 
[comms::protocol::MsgDataLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1MsgDataLayer.html)
are passed to the field definition. If no special options are passed then the whole payload will be 
**copied** to the cached field. It is highly recommended to pass 
[comms::option::app::OridDataView](https://commschamp.github.io/comms_doc/options_8h.html) to it to 
avoid unnecessary copy of the data. In this particular tutorial the [ClientSession](src/ClientSession.h)
defines its options to be:
```cpp
using ClientProtocolOptions = 
    tutorial18::options::DataViewDefaultOptionsT<
        tutorial18::options::ClientDefaultOptions
    >;
```
The used [tutorial::options::DataViewDefaultOptions](include/tutorial18/options/DataViewDefaultOptions.h)
ensures that appropriate option is passed the payload definition layer:
```cpp
template <typename TBase = tutorial18::options::DefaultOptions>
struct DataViewDefaultOptionsT : public TBase
{
    struct frame : public TBase::frame
    {
        struct FrameLayers : public TBase::frame::FrameLayers
            using Data = std::tuple<
                comms::option::app::OrigDataView,
                typename TBase::frame::FrameLayers::Data
            
        }; // struct FrameLayers
    }; // struct frame
};
```

## Summary
- The [COMMS Library](https://github.com/commschamp/comms) provides multiple ways to access 
  some or all of the framing fields.
- The `read()` member function can receive and update selected output parameters via 
  [comms::protocol::msgId()](https://commschamp.github.io/comms_doc/namespacecomms_1_1protocol.html), 
  [comms::protocol::msgIndex()](https://commschamp.github.io/comms_doc/namespacecomms_1_1protocol.html), etc...
- In order to get **all** the frame fields the 
  [readFieldsCached()](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1ProtocolLayerBase.html)
  member function needs to be used.
- The frame definition allows access of various inner layers using `layer_*()` member function.
- Every layer provides [accessCachedField()](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1ProtocolLayerBase.html)
  member function to access appropriate field from the cached tuple.

[Read Previous Tutorial](../tutorial17) &lt;-----------------------&gt; [Read Next Tutorial](../tutorial19) 
