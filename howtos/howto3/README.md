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

In order to handle such case it is highly recommended to pre-process the input and strip 
all the special characters before passing it for processing to the 
[COMMS Library](https://github.com/commschamp/comms_champion#comms-library).
The same goes for post-processing the output and inject special characters before sending raw bytes 
over the I/O link.

The [schema](dsl/schema.xml) of this tutorial doesn't mention any prefix/suffix fields:
```xml
<frame name="Frame">
    <id name="Id" field="MsgId" />
    <payload name="Data" />
</frame>
```

The pre- and post-processing functionality is common for both **client** and **server** and is implemented
inside [src/CommonSessionBase.cpp](src/CommonSessionBase.cpp).

When new input arrives, it's been pre-processed to remove all the special characters before passing 
the identified message to the [COMMS Library](https://github.com/commschamp/comms_champion#comms-library)
for processing.
```cpp
std::size_t ClientSession::processInputImpl(const std::uint8_t* buf, std::size_t bufLen)
{
    ...
    std::size_t consumed = 0;
    while (true) {
        MsgBuf msgBuf;
        auto consumedTmp = preProcessInput(buf + consumed, bufLen - consumed, msgBuf);

        if (consumedTmp == 0) {
            // Empty buffer or incomplete message remaining
            break;
        }

        consumed += consumedTmp;

        if (!msgBuf.empty()) {
            comms::processAllWithDispatch(&msgBuf[0], msgBuf.size(), m_frame, *this);
        }
    }

    return consumed;
}
```

Please note that the input is processed in a loop to make sure that all the reported bytes are 
processes, while the call to `comms::processAllWithDispatch()` is performed per identified post-processed
**single** message buffer.

In order to test such scenario the [client](src/ClientSession.cpp) concatenates buffers of `Msg2` and
`Msg3` before sending them:
```cpp
void ClientSession::sendMsg2Msg3()
{
    ...
    writeMessage(msg2, output);
    ...
    writeMessage(msg3, outputTmp);

    // Concatenate buffers
    output.insert(output.end(), outputTmp.begin(), outputTmp.end());

    // Send serialized message 
    sendOutput(&output[0], output.size());
}
```

The [server](src/ServerSession.cpp) side receives this single buffer and successfully differentiates
between the messages:
```
Processing input: 2 10 2 0 1 10 2 10 3 4 5 10 10 11 12 3 2 10 3 ab cd 3 
Received message "Message 2" with ID=2
Sending message "Message 2" with ID=2
Sending raw data: 2 10 2 0 1 10 2 10 3 4 5 10 10 11 12 3 
Received message "Message 3" with ID=3
Sending message "Message 3" with ID=3
Sending raw data: 2 10 3 ab cd 3 
```
