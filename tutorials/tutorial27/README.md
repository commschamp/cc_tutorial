# Tutorial 27
Sub-protocols (using namespaces)

Some protocols can be divided to two or more sub-protocols with usually different framing and different messages.
It is recommended to use different namespaces (using `<ns>` XML node) in the schema definition (see [schema](dsl/schema.xml)).
```
<ns name="sub1">
    ...
</ns>

<ns name="sub2">
    ...
</ns>
```
When using namespaces in the schema definition, the [CommsDSL Specification](https://commschamp.github.io/commsdsl_spec) requires
full path when referencing fields or other components even if the referenced element resides in the same namespace:
```
<message name="Msg1" id="sub1.MsgId.M0" order="0" displayName="^Msg1Name" />
...
<message name="Msg4" id="sub2.MsgId.M4" displayName="^Msg4Name" />
```
Please pay attention that the protocol definition classes are functions have found their way to the
[include/tutorial27/sub1](include/tutorial27/sub1) and the [include/tutorial27/sub2](include/tutorial27/sub2) folders
respectively. The options definitions though are common and are defined in the parent
[include/tutorial27/options](include/tutorial27/options) folder and namespace.

Due to the fact that the schema doesn't define any `<interface>` it is generated automatically and resides
in the parent namespace (see [include/tutorial27/Message.h](include/tutorial27/Message.h)).

In this particular tutorial two sub protocols are defined. The first one is the same as defined in the
[previous tutorial](../tutorial26), i.e. stateful one of where certain order of messages sequence is expected.
Once all the messages from the first sub-protocol are received the flow is expected to switch to the second
sub protocol where the messages are differentiated by proper ID field in the framing and can be received in any order.

Let's take a look how the generated classes and other definitions are used, [server](src/ServerSession.h) for example:
```cpp
// Definition of all the used message classes
TUTORIAL27_SUB1_ALIASES_FOR_ALL_MESSAGES(,,Message,ServerProtocolOptions);
TUTORIAL27_SUB2_ALIASES_FOR_ALL_MESSAGES(,,Message,ServerProtocolOptions);
```
The macros above are defined in the [include/tutorial27/sub1/input/AllMessages.h](include/tutorial27/sub1/input/AllMessages.h)
and [include/tutorial27/sub2/input/AllMessages.h](include/tutorial27/sub2/input/AllMessages.h) respectively. Please not
the presence of the `SUB1` and `SUB2` after the `TUTORIAL27` prefix, which don't exist when there is only one global namespace.

The frames are also defined referencing different namespaces:
```cpp
using Sub1Frame =
    tutorial27::sub1::frame::Frame<
        Message,
        tutorial27::sub1::input::ServerInputMessages<Message, ServerProtocolOptions>,
        ServerProtocolOptions
    >;
using Sub2Frame =
    tutorial27::sub2::frame::Frame<
        Message,
        tutorial27::sub2::input::ServerInputMessages<Message, ServerProtocolOptions>,
        ServerProtocolOptions
    >;
```

Both [server](src/ServerSession.cpp) and [client](src/ClientSession.cpp) are implemented more or less in the same way.
They both track the stage of their communication and choose what framing to use to decode and dispatch the message.
```cpp
std::size_t ServerSession::processInputImpl(const std::uint8_t* buf, std::size_t bufLen)
{
    std::cout << "Processing input: " << std::hex;
    std::copy_n(buf, bufLen, std::ostream_iterator<unsigned>(std::cout, " "));
    std::cout << std::dec << std::endl;

    using ProcFunc = std::size_t (ServerSession::*)(const std::uint8_t* buf, std::size_t bufLen);
    static const ProcFunc ProcMap[] = {
        /* ProtStage_sub1 */ &ServerSession::processInputSub1,
        /* ProtStage_sub2 */ &ServerSession::processInputSub2,
    };
    static const std::size_t ProcMapSize = std::extent<decltype(ProcMap)>::value;
    static_assert(ProcMapSize == ProtStage_numOfValues, "Invalid map");

    auto idx = static_cast<unsigned>(m_protStage);
    assert(idx < ProcMapSize);

    auto func = ProcMap[idx];
    return (this->*func)(buf, bufLen);
}
```
The same goes for sending the message:
```cpp
void ServerSession::sendMessage(const Message& msg)
{
    std::cout << "Sending message \"" << msg.name() << "\"" << std::endl;

    std::vector<std::uint8_t> output;

    // Serialize message into the buffer (including framing)
    // The serialization uses polymorphic write functionality.
    auto writeIter = std::back_inserter(output);

    using WriteFunc = comms::ErrorStatus (ServerSession::*)(const Message& msg, WriteIter& iter, std::size_t bufLen);
    static const WriteFunc WriteMap[] = {
        /* ProtStage_sub1 */ &ServerSession::writeMessageSub1,
        /* ProtStage_sub2 */ &ServerSession::writeMessageSub2,
    };
    static const std::size_t WriteMapSize = std::extent<decltype(WriteMap)>::value;
    static_assert(WriteMapSize == ProtStage_numOfValues, "Invalid map");

    auto idx = static_cast<unsigned>(m_protStage);
    assert(idx < WriteMapSize);

    auto func = WriteMap[idx];
    auto es = (this->*func)(msg, writeIter, output.max_size());
    if (es != comms::ErrorStatus::Success) {
        assert(!"Write operation failed unexpectedly");
        return;
    }

    // Send (re)serialized message back
    sendOutput(&output[0], output.size());
}
```

---

**SIDE NOTE**: The namespaces can also be used to sub-divide the messages and/or fields to some sub-categories, not necessarily
for the sub-protocols division.

---

## Summary

- It is recommended to use different namespaces (`<ns>` XML node) to divide the protocol to sub-protocols.
- The namespaces in schema are defined in the relevant sub-namespace and folder in the generated code.

[Read Previous Tutorial](../tutorial26) &lt;-----------------------
