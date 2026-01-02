# How-To 3
Using message termination suffix instead of message length prefix.

There are many protocols which use special termination suffix (such as ascii `0x03-ETX`)
to indicate end of the message frame rather than using total length prefix. In most such cases the message
frame is also prefixed with another special character (such as ascii `0x02-STX`).
As the result the message frame may look like this:
```
STX | ID | PAYLOAD | ETX
```
There is also a special escape character (such as ascii `0x10-DLE`), which needs to
be placed before any byte inside the rest of the message frame / payload, value of which is equal to one
of the special characters (`STX`, `ETX`, or `DLE`). It ensures that a valid payload byte won't be
confused with the end of the current or beginning of the next message.

In order to handle such case there is a need to split a protocol into two sub-protocols
(covered in the [tutorial27](../../tutorials/tutorial27)). Let's call them `prot1` and `prot2`.
The outer frame uses `<sync>` layers as both prefix and suffix(
features introduced in **v8.0** of the [CommsDSL](https://github.com/commschamp/CommsDSL-Specification)).
```xml
<ns name="prot1">
    ...
    <frame name="Prot1Frame">
        <sync name="Prefix" seekField="true" escField="prot1.EscField">
            <field>
                <int name="SyncField" type="uint8" defaultValue="0x02" />
            </field>
        </sync>
        <id name="Id">
            <int name="IdField" type="uint8" defaultValue="0" pseudo="true" />
        </id>
        <payload name="Data" />
        <sync name="Suffix" seekField="true" from="Id" escField="prot1.EscField">
            <field>
                <int name="SyncField" type="uint8" defaultValue="0x03" />
            </field>
        </sync>
    </frame>
</ns>
```
Note the usage of the **seekField**, **escField**, and **from** (in the suffix) properties. Usage
of the **seekField="true"** in the `Prefix` layer allows silent consuming all the garbabe preceding the escape field.

Another thing to note is having only a single message without actually serializing the message ID value (thanks to setting **pseudo** property).
```xml
<int name="IdField" type="uint8" defaultValue="0" pseudo="true" />
```
Such frame is effectively:
```
PREFIX | DATA | SUFFIX
```
See also [howto4](../howto4) for more details on single message protocol without message ID in framing.

The reception of the input data is simple dispatching it to the frame for handling:
```cpp
std::size_t ClientSession::processInputImpl(const std::uint8_t* buf, std::size_t bufLen)
{
    std::cout << "Processing input: " << std::hex;
    std::copy_n(buf, bufLen, std::ostream_iterator<unsigned>(std::cout, " "));
    std::cout << std::dec << std::endl;

    return comms::processAllWithDispatch(buf, bufLen, m_prot1Frame, *this);
}
```

When such message is received the raw data needs to be post-process to eliminate all the escape characters and
then process it with the second protocol frame.
```cpp
void ClientSession::handle(Prot1PseudoMsg& msg)
{
    std::cout << "Received message \"" << msg.doName() << '\n';

    MsgBuf prot2ProcessBuf;
    dropEscapes(msg.field_data().value().data(), msg.field_data().value().size(), prot2ProcessBuf);

    std::cout << "post-processed input: " << std::hex;
    std::copy(prot2ProcessBuf.begin(), prot2ProcessBuf.end(), std::ostream_iterator<unsigned>(std::cout, " "));
    std::cout << std::dec << std::endl;

    comms::processAllWithDispatch(prot2ProcessBuf.data(), prot2ProcessBuf.size(), m_prot2Frame, *this);
}
```

The second frame is defined as `ID | PAYLOAD`:
```xml
<frame name="Prot2Frame">
    <id name="Id" field="prot2.MsgId" />
    <payload name="Data" />
</frame>
```

The output functionality is performed in reverse. First `prot2` framing is used to serialize message,
then post-processing to introduce escape characters is performed, and only finally the prefix and suffix
framing is added using `prot1` framing.
```cpp
void ClientSession::writeMessage(const Prot2Interface& msg, MsgBuf& output)
{
    MsgBuf outputTmp;

    // Serialize message into the buffer (including framing)
    // The serialization uses polymorphic write functionality.
    auto writeIter = std::back_inserter(outputTmp);

    // The frame will use polymorphic message ID retrieval to
    // prot1fix message payload with message ID
    auto es = m_prot2Frame.write(msg, writeIter, outputTmp.max_size());

    ...

    // Introduce special characters
    addEscapes(outputTmp);

    Prot1PseudoMsg pseudoMsg;
    comms::util::assign(pseudoMsg.field_data().value(), outputTmp.begin(), outputTmp.end());

    auto finalWriteIter = std::back_inserter(output);
    auto sizeBeforeWrite = output.size();
    es = m_prot1Frame.write(pseudoMsg, finalWriteIter, output.max_size());
    ...
}
```

In order to test such scenario the [client](src/ClientSession.cpp) concatenates buffers of `Msg2` and
`Msg3` before sending them:
```cpp
void ClientSession::sendMsg2Msg3()
{
    MsgBuf output;
    ...
    writeMessage(msg2, output);
    ...
    writeMessage(msg3, output);

    // Send serialized messages
    sendOutput(&output[0], output.size());
}
```

The [server](src/ServerSession.cpp) side receives this single buffer and successfully differentiates
between the messages:
```
Processing input: 2 1 68 65 6c 6c 6f 3
Received message "Prot1PseudoMsg
post-processed input: 1 68 65 6c 6c 6f
Received message "Message 1" with ID=1
Sending message "Message 1" with ID=1
Sending raw data: 2 1 68 65 6c 6c 6f 3
Processing input: 2 10 2 0 1 10 2 10 3 4 5 10 10 11 12 3 2 10 3 ab cd 3
Received message "Prot1PseudoMsg
post-processed input: 2 0 1 2 3 4 5 10 11 12
Received message "Message 2" with ID=2
Sending message "Message 2" with ID=2
Sending raw data: 2 10 2 0 1 10 2 10 3 4 5 10 10 11 12 3
Received message "Prot1PseudoMsg
post-processed input: 3 ab cd
Received message "Message 3" with ID=3
Sending message "Message 3" with ID=3
Sending raw data: 2 10 3 ab cd 3
```
