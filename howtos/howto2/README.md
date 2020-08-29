# How-To 1
Having single field for message ID and remaining size in message framing.

Some protocols have quite small number of available messages and in order to save some 
I/O traffic the developers decide to allocate several bits from the size information to be
used as message ID. Something like:
```
ID (4 bits) + SIZE (12 bits) | PAYLOAD
```
The [schema](dsl/schema.xml) of this tutorial defines the such frame in the following way:
```xml
<frame name="Frame">
    <custom name="IdWithSize" idReplacement="true"> 
        <bitfield name="Field">
            <int name="Size" type="uint16" bitLength="12" />
            <ref field="MsgId" bitLength="4" />
        </bitfield>
    </custom>
    <payload name="Data" />
</frame>
```
Please note that the defined **&lt;custom&gt;** layer is marked as the replacement of the 
**&lt;id&gt;** layer using **idReplacement** property 
(because there must be a layer responsible for the message object allocation).

The [tutorial17](../../tutorials/tutorial17) explains usage of the custom framing 
layers and how it is implemented.

The [dsl_src/include/howto2/frame/layer/IdWithSize.h](dsl_src/include/howto2/frame/layer/IdWithSize.h)
(which finds its way to be [include/howto2/frame/layer/IdWithSize.h](include/howto2/frame/layer/IdWithSize.h) 
in the generated code) implements the required functionality.

Due to the fact of this class is a replacement to the **&lt;id&gt;** layer it must extend 
the [comms::protocol::MsgIdLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1MsgIdLayer.html)
and implement its member functions that allow set / get of the message ID value out of the 
field object 
```cpp
template<typename TField, typename TMessage, typename TAllMessages, typename TNextLayer, typename... TOptions>
class IdWithSize : public
    comms::protocol::MsgIdLayer<...>
{
    // Repeat base type
    using Base = 
        comms::protocol::MsgIdLayer<...>;

public:
    // Repeat some types from the base class
    using Field = typename Base::Field;    
    using MsgIdType = typename Base::MsgIdType;
    using MsgIdParamType = typename Base::MsgIdParamType;

    // Given the combined bitfield field, retrieve message ID value
    static MsgIdType getMsgIdFromField(const Field& field)
    {
        return field.field_msgId().value();
    }

    // Prepare field value to be written
    template <typename TMsg>
    void prepareFieldForWrite(MsgIdParamType id, const TMsg& msg, Field& field) const
    {
        field.field_msgId().value() = id;
        comms::cast_assign(field.field_size().value()) = Base::nextLayer().length(msg);
    }
};
```
Note that the remaining size information is also updated inside the `prepareFieldForWrite()` member function.

Now comes the tricky part. Every default layer implementation class (including 
[comms::protocol::MsgIdLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1MsgIdLayer.html))
defines `doRead()` member function which is invoked by the `read()` and `readFieldsCached()` ones, which are used
to drive the framing read functionality. The `doRead()` function is expected to read the field's value 
(ID of the message), do relevant operation(s) (allocate message object) and forward the read operation to the 
next layer. However in our special case there is an additional need to read and process the remaining message 
length information. In order to add this extra functionality the `doRead()` member function needs to be 
redefined.
```cpp
template<typename TField, typename TMessage, typename TAllMessages, typename TNextLayer, typename... TOptions>
class IdWithSize : public
    comms::protocol::MsgIdLayer<...>
{
    using Base = 
        comms::protocol::MsgIdLayer<...>;

public:
    // Repeat some types from the base class
    using Field = typename Base::Field;    
    using MsgIdType = typename Base::MsgIdType;
    using MsgIdParamType = typename Base::MsgIdParamType;

    // Replacement of comms::MsgIdLayer::doRead
    template <typename TMsg, typename TIter, typename TNextLayerReader, typename... TExtraValues>
    comms::ErrorStatus doRead(
        Field& field, 
        TMsg& msg, 
        TIter& iter, 
        std::size_t size, 
        TNextLayerReader&& nextLayerReader, 
        TExtraValues... extraValues)
    {
        auto iterTmp = iter;
        Field fieldTmp;

        auto es = fieldTmp.read(iterTmp, size);
        if (es != comms::ErrorStatus::Success) {
            return 
                Base::doRead(
                    field, 
                    msg, 
                    iter, 
                    size, 
                    std::forward<TNextLayerReader>(nextLayerReader), 
                    extraValues...);
        }

        auto lenInField = static_cast<std::size_t>(fieldTmp.field_size().value());
        auto remLen = std::min(size, lenInField + fieldTmp.length());
        return 
            Base::doRead(
                field, 
                msg, 
                iter, 
                remLen, 
                std::forward<TNextLayerReader>(nextLayerReader), 
                extraValues...);
    }
};
```
Once the actual remaining length (`remLen`) is known, the default `doRead()` of the base class 
([comms::protocol::MsgIdLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1MsgIdLayer.html))
is invoked to properly handle the message creation, but with new length value.

In order to properly test the message separation this tutorial defines `Msg1` and `Msg3` to be bound only 
by the framing size:
```xml
<message name="Msg1" id="MsgId.M1" displayName="^Msg1Name">
    <string name="F1" defaultValue="hello" />
</message>
```
The inner **&lt;string&gt;** field doesn't have any length limitation and will consume all the available data 
(which is limited by the frame size).

The [ClientSession](src/ClientSession.cpp) sends two messages in a row:
```cpp
void ClientSession::sendMsg1Msg2()
{
    Msg1 msg1;
    Msg2 msg2;

    OutputBuf output;
    writeMessage(msg1, output);
    writeMessage(msg2, output);
    sendRawData(output);
}
```
The [ServerSession](src/ServerSession.cpp) implements an echo server it processes the input buffer (of the 
two combined messages) and successfully separates the messages:
```
Processing input: 10 5 68 65 6c 6c 6f 20 4 30 39 b2 6e 
Received message "Message 1" with ID=1
Sending message "Message 1" with ID=1: 10 5 68 65 6c 6c 6f 
Received message "Message 2" with ID=2
Sending message "Message 2" with ID=2: 20 4 30 39 b2 6e 
```
