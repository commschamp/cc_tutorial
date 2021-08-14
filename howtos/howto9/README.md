# How-To 9
Frame with checksum of the header.

Some protocols require checksum calculation on the framing header, before proceeding
to the decoding of the message payload.

This howto uses the following frame
```
SYNC (2 bytes) | SIZE (2 bytes) | ID (1 byte) | CHECKSUM (2 bytes) | PAYLOAD 
```
where:

- **SYNC** - is a constant synchronization prefix, expected to be `0xab 0xcd`.
- **SIZE** - size of the rest of the message until end of the PAYLOAD, not including CHECKSUM.
- **ID** - numeric ID of the message.
- **CHECKSUM** - CRC-16 checksum of the whole preceding header starting from SYNC ending with ID.
- **PAYLOAD** - variable length message payload

Classic `<checksum>` framing layer definition implies calculation of the checksum including the message 
payload. Because this is not the case for the demonstrated protocol, `<custom>` layer must be used instead
(see [schema](dsl/schema.xml)).

```xml
<frame name="Frame">
    <sync name="Sync" field="SyncField" />
    <size name="Size" field="SizeField" />
    <id name="Id" field="MsgId" />
    <custom name="Checksum">
        <int name="ChecksumField" type="uint16" />
    </custom>   
    <payload name="Data" />
</frame>
```

The implementation of the `Checksum` layer resides in 
[dsl_src/include/howto9/frame/layer/Checksum.h](dsl_src/include/howto9/frame/layer/Checksum.h)
and copied to the protocol definition 
([include/howto9/frame/layer/Checksum.h](include/howto9/frame/layer/Checksum.h)) 
by the code generator.

It extends [comms::protocol::ChecksumPrefixLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1ChecksumPrefixLayer.html)
because the checksum field is located before the message payload.

Also note the usage of 
[comms::option::def::ChecksumLayerVerifyBeforeRead](https://commschamp.github.io/comms_doc/structcomms_1_1option_1_1def_1_1ChecksumLayerVerifyBeforeRead.html) 
option to the class definition. It insures that 
the checksum is actually calculated and compared to the expected value **before** proceeding to reading the payload.
```cpp
template<typename TField, typename TNextLayer, typename... TOptions>
class Checksum : public
    comms::protocol::ChecksumPrefixLayer<
        TField,
        comms::protocol::checksum::Crc_16, 
        TNextLayer,
        TOptions...,
        comms::option::def::ChecksumLayerVerifyBeforeRead,
        comms::option::def::ExtendingClass<Checksum<TField, TNextLayer, TOptions...> >
    >
{
    ...
};
```

The default implementation of the checksum calculation functionality inside the 
[comms::protocol::ChecksumPrefixLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1ChecksumPrefixLayer.html)
proceeds forward to the payload calculation. However, the protocol specification demands calculation of the checksum on
the preceding framing header instead. The customization of the default behaviour is possible by overriding the 
[comms::protocol::ChecksumPrefixLayer::calculateChecksum()](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1ChecksumPrefixLayer.html) member function.
```cpp
template<typename TField, typename TNextLayer, typename... TOptions>
class Checksum : public comms::protocol::ChecksumPrefixLayer<...>
{
    ...
    
    // Repeat types defined in the base class (not visible by default)
    using Field = typename Base::Field; 
    using Calc = comms::protocol::checksum::Crc_16;
 
    // Override default way of calculating checksum
    template <typename TMsg, typename TIter>
    static typename Field::ValueType calculateChecksum(const TMsg* msgPtr, TIter& iter, std::size_t len, bool& checksumValid)
    {
        static_cast<void>(msgPtr); // Not used
        static_cast<void>(len); // Not used

        static const std::size_t CalcAreaSize = 
                sizeof(howto9::field::SyncFieldCommon::ValueType) + 
                sizeof(howto9::field::SizeFieldCommon::ValueType) + 
                sizeof(howto9::field::MsgIdCommon::ValueType);

        static const std::size_t HeaderSize = 
            CalcAreaSize + Field::maxLength();

        checksumValid = true;

        auto fromIter = iter;
        std::advance(iter, -HeaderSize);

        return Calc()(fromIter, CalcAreaSize);
    }  
};
```
Please pay attention to the following details:

- When the function is invoked, the checksum value field has already been read, i.e. the `iter` 
points right after the checksum value. The calculation of the header starting location must take 
it into account.
- The size of the checksum calculation area does NOT include the checksum field itself.
