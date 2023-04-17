# Tutorial 25
Dealing with big protocols.

Most of the binary communication protocols use numeric message ID information reported in the
message frame. The [CommsDSL](https://github.com/commschamp/CommsDSL-Specification) specification
provides [&lt;id&gt;](https://commschamp.github.io/commsdsl_spec/#frames-id) framing layer for this purpose, while the generated code uses
[comms::protocol::MsgIdLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1MsgIdLayer.html) class
to implement the required functionality. During the **read** operation the
[comms::protocol::MsgIdLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1MsgIdLayer.html) class
is responsible to provide the functionality for reading the message ID and create appropriate message object before forwarding
the request to the next framing layer. The
default mapping of the numeric message ID to the actual message type is implemented using
[comms::MsgFactory](https://commschamp.github.io/comms_doc/classcomms_1_1MsgFactory.html) class.
The latter receives a `tuple` of all the message classes it is expected to support as its second template parameter
and uses multiple meta-programming techniques to analyze the provided messages at **compile-time** and
create proper mapping of numeric message IDs to their respective actual types. Such compile time analysis may incur
a significant burden on compilation time as well as memory consumption of the compiler. Depending on the
development machine characteristics, the compilation performance issues may get noticeable when number of the
messages approaches 30 - 50. In some specific cases (like small RAM and/or compiler being 32 bit application)
the compilation may report an error due to being out of heap space.

To mitigate this problem / annoyance the **v6.1** of the **commsdsl2comms** code generator added extra `switch`
based message factories in the [&lt;protocol_namespace&gt;/factory](include/tutorial25/factory) folder.

- [&lt;protocol_namespace&gt;::<zero-width space>factory::AllMessagesDynMemMsgFactory](include/tutorial25/factory/AllMessagesDynMemMsgFactory.h) class -
  a factory for all the messages of the protocol.
- [&lt;protocol_namespace&gt;::<zero-width space>factory::ClientInputMessagesDynMemMsgFactory](include/tutorial25/factory/ClientInputMessagesDynMemMsgFactory.h) class -
  a factory for the client input messages of the protocol.
- [&lt;protocol_namespace&gt;::<zero-width space>factory::ServerInputMessagesDynMemMsgFactory](include/tutorial25/factory/ServerInputMessagesDynMemMsgFactory.h) class -
  a factory for the server input messages of the protocol.

The **DynMem** part of the name implies dynamic memory allocation.

Note that in this tutorial **sender** property hasn't been used, i.e. all the messages are sent both ways. It means that all the message factories
mentioned above contain the same code. For the cases when uni-directional messages are present they'll differ.

The [comms::protocol::MsgIdLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1MsgIdLayer.html) layer provided by the
[COMMS Library](https://github.com/commschamp/comms) allows replacing the default message factory
([comms::MsgFactory](https://commschamp.github.io/comms_doc/classcomms_1_1MsgFactory.html))
using the **comms::option::app::MsgFactory** or **comms::option::app::MsgFactoryTempl** application specific customization options.

The **v6.1** of the **commsdsl2comms** code generator also generates extra protocol options that can be used to apply the relevant
option to the [comms::protocol::MsgIdLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1MsgIdLayer.html) class:

- [&lt;protocol_namespace&gt;::optoins::AllMessagesDynMemMsgFactoryDefaultOptions](include/tutorial25/options/AllMessagesDynMemMsgFactoryDefaultOptions.h) - the options forcing usage
  of the [&lt;protocol_namespace&gt;::<zero-width space>factory::AllMessagesDynMemMsgFactory](include/tutorial25/factory/AllMessagesDynMemMsgFactory.h).
- [&lt;protocol_namespace&gt;::optoins::ClientInputMessagesDynMemMsgFactoryDefaultOptions](include/tutorial25/options/ClientInputMessagesDynMemMsgFactoryDefaultOptions.h) -
  the options forcing usage of the [&lt;protocol_namespace&gt;::<zero-width space>factory::ClientInputMessagesDynMemMsgFactory](include/tutorial25/factory/ClientInputMessagesDynMemMsgFactory.h).
- [&lt;protocol_namespace&gt;::optoins::ServerInputMessagesDynMemMsgFactoryDefaultOptions](include/tutorial25/options/ServerInputMessagesDynMemMsgFactoryDefaultOptions.h) -
  the options forcing usage of the [&lt;protocol_namespace&gt;::<zero-width space>factory::ServerInputMessagesDynMemMsgFactory](include/tutorial25/factory/ServerInputMessagesDynMemMsgFactory.h).

Let's take a look how the protocol options above can be used to force usage of the more efficient message factories.

The [ServerSession](src/ServerSession.h) defines its protocol options like this:
```cpp
using ServerProtocolOptions =
    ServerInputMessagesDynMemMsgFactoryDefaultOptionsT<
        tutorial25::options::ServerDefaultOptions
    >;
```

The definition used by the [ClientSession](src/ClientSession.h) is very similar:
```cpp
using ClientProtocolOptions =
    tutorial25::options::ClientInputMessagesDynMemMsgFactoryDefaultOptionsT<
        tutorial25::options::ClientDefaultOptions
    >;
```

When it comes to aliasing of the message types, the **v6.1** of the commsdsl2comms code generator added
convenience macros to the definitions of the input messages:

- **&lt;PROT_NS&gt;_ALIASES_FOR_ALL_MESSAGES** and **&lt;PROT_NS&gt;_ALIASES_FOR_ALL_MESSAGES_DEFULT_OPTIONS** in
  [&lt;protocol_namespace&gt;/input/AllMessages.h](include/tutorial25/input/AllMessages.h)
- **&lt;PROT_NS&gt;_ALIASES_FOR_CLIENT_INPUT_MESSAGES** and **&lt;PROT_NS&gt;_ALIASES_FOR_CLIENT_INPUT_MESSAGES_DEFULT_OPTIONS** in
  [&lt;protocol_namespace&gt;/input/ClientInputMessages.h](include/tutorial25/input/ClientInputMessages.h)
- **&lt;PROT_NS&gt;_ALIASES_FOR_SERVER_INPUT_MESSAGES** and **&lt;PROT_NS&gt;_ALIASES_FOR_SERVER_INPUT_MESSAGES_DEFULT_OPTIONS** in
  [&lt;protocol_namespace&gt;/input/ServerInputMessages.h](include/tutorial25/input/ServerInputMessages.h)

Please take a look at the definition:
```cpp
/// @brief Create type aliases for the all messages of the protocol.
/// @param prefix_ Prefix of the alias message type.
/// @param suffix_ Suffix of the alias message type.
/// @param interface_ Type of the common message interface.
/// @param opts_ Type of the used protocol definition options.
#define TUTORIAL25_ALIASES_FOR_ALL_MESSAGES(prefix_, suffix_, interface_, opts_) \
    using prefix_ ## Msg1 ## suffix_ = tutorial25::message::Msg1<interface_, opts_>; \
    using prefix_ ## Msg2 ## suffix_ = tutorial25::message::Msg2<interface_, opts_>; \
    ...
```

The [ClientSession](src/ClientSession.h) uses the **TUTORIAL25_ALIASES_FOR_ALL_MESSAGES** macro to alias all message types:
```cpp
TUTORIAL25_ALIASES_FOR_ALL_MESSAGES(,,Message,ClientProtocolOptions);
```

Please note the empty `prefix_` and `suffix_` parameters.

It is equivalent of having the following alias types defined:
```cpp
using Msg1 = tutorial25::message::Msg1<Message, ClientProtocolOptions>;
using Msg2 = tutorial25::message::Msg2<Message, ClientProtocolOptions>;
using Msg3 = tutorial25::message::Msg3<Message, ClientProtocolOptions>;
...
```

These alias types are used when sending messages to the **server**:
```cpp
void ClientSession::sendMsg1()
{
    Msg1 msg;
    sendMessage(msg); // Should get received and echoed back
}

void ClientSession::sendMsg2()
{
    Msg2 msg;
    sendMessage(msg); // Should get received and echoed back
}

...
```

## Summary

- As the number of messages in the protocol grow, the burden on the compilation time and memory consumption can grow exponentially.
- When number of the messages exceeds 30-50 messages, it is recommended to use more optimized generated message factories.
- The message factory classes reside in the **&lt;protocol_namespace&gt;/factory** folder.
- The **&lt;protocol_namespace&gt;/options** folder will also contain new relevant option classes which can be used to
  force usage of the new factories.
- The files containing definitions of relevant input messages in the **&lt;protocol_namespace&gt;/input** folder also contain
  definition of the macros helping with message type aliasing.

[Read Previous Tutorial](../tutorial24) &lt;-----------------------
