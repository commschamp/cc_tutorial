# How-To 10
Replacing `<variant>` with sub-protocol.

The [tutorial4](../../tutorials/tutorial4) presented `<variant>` field and explained how to use it, while
the [tutorial27](../../tutorials/tutorial27) presented sub-protocols definition. This how-to shows how
to define variant fields from the [tutorial4](../../tutorials/tutorial4) as sub-protocol messages.

The `KeyValueProp` `<variant>` field is replaced by the sub-protocol defined in the `var1` namespace.
```
<ns name="var1">
    <fields>
        <enum name="PropKey" type="uint8" semanticType="messageId">
            <validValue name="K1" val="0" />
            <validValue name="K2" val="2" />
            <validValue name="K3" val="5" />
        </enum>
    </fields>

    <interface name="Interface" />

    <frame name="KeyValueProp">
        <id name="Key" field="var1.PropKey" />
        <payload name="Val" />
    </frame>

    <message name="Prop1" id="var1.PropKey.K1">
        <int name="Val" type="uint16" />
    </message>

    <message name="Prop2" id="var1.PropKey.K2">
        <float name="Val" type="float" defaultValue="nan" />
    </message>

    <message name="Prop3" id="var1.PropKey.K3">
        <string name="Val">
            <lengthPrefix>
                <int name="Length" type="uint8" />
            </lengthPrefix>
        </string>
    </message>
</ns>
```
The frame is implemented as a pair of `<id>` and `<payload>` layers. Every property is implemented as a
separate `<message>` with a single **Val** field.

Similarly the `TlvProp` `<variant>` field is replaced by the sub-protocol defined in the `var2` namespace.
```
<ns name="var2">
    <fields>
        <enum name="PropKey" type="uint8" semanticType="messageId">
            <validValue name="K4" val="10" />
            <validValue name="K5" val="15" />
            <validValue name="K6" val="25" />
            <validValue name="K7" val="30" />
        </enum>
    </fields>

    <interface name="Interface" />

    <frame name="TlvProp">
        <id name="Key" field="var2.PropKey" />
        <size name="Length">
            <int name="LengthField" type="uint8"/>
        </size>
        <payload name="Val" />
    </frame>

    <interface name="Message" />

    <message name="Prop4" id="var2.PropKey.K4">
        <int name="Val" type="uint32" />
    </message>

    <message name="Prop5" id="var2.PropKey.K5">
        <float name="Val" type="double" defaultValue="inf" />
    </message>

    <message name="Prop6" id="var2.PropKey.K6">
        <string name="Val" />
    </message>

    <message name="Prop7" id="var2.PropKey.K7">
        <int name="Val" type="uint64" availableLengthLimit="true" />
    </message>
</ns>
```
The frame in this case is implemented as `<id>`, `<size>` and `<payload>` triplet.

The original protocol definition was moved into the `prot` namespace.
```
<ns name="prot">
    <fields>
        <string name="Msg1Name" defaultValue="Message 1" />
        <string name="Msg2Name" defaultValue="Message 2" />

        <enum name="MsgId" type="uint8" semanticType="messageId">
            <validValue name="M1" val="1" displayName="^prot.Msg1Name" />
            <validValue name="M2" val="2" displayName="^prot.Msg2Name" />
        </enum>
    </fields>

    <interface name="Message" />

    <frame name="Frame">
        <size name="Size">
            <int name="SizeField" type="uint16" />
        </size>
        <id name="ID" field="prot.MsgId" />
        <payload name="Data" />
    </frame>

    <message name="Msg1" id="prot.MsgId.M1" displayName="^prot.Msg1Name">
        <int name="Count" type="uint8" />
        <data name="KeyValueProps" />
    </message>

    <message name="Msg2" id="prot.MsgId.M2" displayName="^prot.Msg2Name">
        <data name="TlvProps" />
    </message>
</ns>
```
Note the changes in the messages definitions. The whole sequence of the `<variant>` fields was replaced with
a single `<data>` field.

The [server](ServerSession.cpp) implementation is not really interesting or useful. Being an echo server it doesn't bother to
decode the sub-protocol messages, it just echoes back raw data.

The [client](ClientSession.cpp) on the other hand has to introduce some extra smarts. The
original `Msg1` is defined having a count prefixed list of the `KeyValueProp` `<variant>` field.
```
<message name="Msg1" id="MsgId.M1" displayName="^Msg1Name">
    <list name="F1" element="KeyValueProp">
        <countPrefix>
            <int name="Count" type="uint8" />
        </countPrefix>
    </list>
</message>
```
To be able to properly decode it the message handling member function needs to decode sub-protocol messages one by one:
```cpp
void ClientSession::handle(Msg1& msg)
{
    ...
    KeyValuePropFrame keyValueFrame;
    auto& keyValuePropsData = msg.field_keyValueProps().value();
    auto readIter = keyValuePropsData.begin();

    for (auto idx = 0U; idx < msg.field_count().value(); ++idx) {
        auto consumed = static_cast<std::size_t>(std::distance(keyValuePropsData.begin(), readIter));
        KeyValuePropFrame::MsgPtr propPtr;
        auto es = comms::processSingleWithDispatch(readIter, keyValuePropsData.size() - consumed, keyValueFrame, propPtr, *this);
        if (es != comms::ErrorStatus::Success) {
            std::cerr << "ERROR: encountered unexpected property" << std::endl;
        }
    }
    ...
}
```
The list of TLV properties encoded in the `Msg2` can be processed right away though:
```cpp
void ClientSession::handle(Msg2& msg)
{
    ...
    TlvPropFrame tlvFrame;
    auto& tlvPropsData = msg.field_tlvProps().value();
    auto readIter = tlvPropsData.begin();

    comms::processAllWithDispatch(readIter, tlvPropsData.size(), tlvFrame, *this);
    ...
}
```

Another important aspect to notice is the way the protocol options are defined.
```
using ProtOpts =
    howto11::options::DataViewDefaultOptionsT<
        howto11::options::ClientDefaultOptions
    >;
```
Note that by default the `<data>` fields used by the `Msg1` and `Msg2` messages use `std::vector<std::uint8_t>`
ass the inner storage type. It is fine and will work as expected. However, it will result in
the unnecessary copy of the bytes from the input buffer to the value storage.
Applying [DataViewDefaultOptions](include/howto11/options/DataViewDefaultOptions.h) results in replacing
the said default storage type with the [comms::util::ArrayView](https://commschamp.github.io/comms_doc/classcomms_1_1util_1_1ArrayView.html) or
[std::span](https://en.cppreference.com/w/cpp/container/span) (if compiling with C++20 standard). Basically a "view" on
the input buffer is used eliminating unnecessary copy of the raw bytes.
