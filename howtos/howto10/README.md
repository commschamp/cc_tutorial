# How-To 10
Dealing with "Read split is disallowed by at least one of the inner layers" static assertion.

There may be cases when the developer encounters static assertion failure mentioned in the subject
of this howto. It may happen when the developer is trying to implement a frame similar to one
below:
```
SYNC | SIZE | FLAGS | ID | PAYLOAD | CHECKSUM (of PAYLOAD)
```

The naive and straightforward way to implement such frame would be something like that
```xml
<interface name="Interface">
    <ref field="Flags" />
</interface>

<frame name="Frame">
    <sync name="Sync">
        <int name="SyncField" type="uint16" defaultValue="0xabcd" />
    </sync>
    <size name="Size">
        <int name="SizeField" type="uint16" />
    </size>
    <value name="Flags" field="Flags" interfaceFieldName="Flags" />
    <id name="Id" field="MsgId" />
    <payload name="Data" />
    <checksum name="Checksum" from="Data" alg="crc-ccitt" verifyBeforeRead="true">
        <int name="ChecksumField" type="uint16" />
    </checksum>
</frame>
```
Such definition will cause the error being explained here. In order to understand the error and the solution,
the developer needs to understand some aspects of the 
[COMMS Library](https://github.com/commschamp/comms) architecture and as a 
consequence the limitations of the latter.

The [tutorial5](../../tutorials/tutorial5) explains that the 
[COMMS Library](https://github.com/commschamp/comms) implements framing
by they "layer" classes wrapping one another, while the 
[comms::protocol::ChecksumLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1ChecksumLayer.html)
(defined using [&lt;checksum&gt;](https://commschamp.github.io/commsdsl_spec/#frames-checksum) in the schema)
wraps all the layers, checksum on which needs to be implemented. In this particular case it is only the
`PAYLOAD`. So the wrapping looks something like that:
```
SYNC( SIZE( FLAGS( ID( CHECKSUM( PAYLOAD ) ) ) ) )
```
Now, let's take a closer look at the `FLAGS` layer. The [&lt;value&gt;](https://commschamp.github.io/commsdsl_spec/#frames-value)
definition is implemented using 
[comms::protocol::TransportValueLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1TransportValueLayer.html)
class, which is expected to re-assign the read field's value to the message object. However, in this particular scenario
the message object hasn't been created yet, because the `ID` information hasn't been processed yet. To help with 
such cases the [COMMS Library](https://github.com/commschamp/comms) has compile-time
meta-programming logic to recognize the scenario and automatically forces splitting its read operation to "until the payload" and 
"from the payload". When such split occurs, the relevant flags field is re-assigned to message object right before the read 
operation is forwarded to process the message payload.

The [comms::protocol::ChecksumLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1ChecksumLayer.html)
(implements [&lt;checksum&gt;](https://commschamp.github.io/commsdsl_spec/#frames-checksum)) on the other hand
disallows such split of read operation to "until" and "from" payload, because in order to finalize its read operation the
payload processing needs to be complete.

Such contradiction creates a conflict, which is manifested by the static assertion mentioned in the subject of this howto. In
order to resolve it, the framing definition needs to be modified as if the `FLAGS` resides **after** the `ID`. The 
[schema](dsl/schema.xml) of this howto does exactly that:
```xml
<frame name="Frame">
    <sync name="Sync">
        <int name="SyncField" type="uint16" defaultValue="0xabcd" />
    </sync>
    <size name="Size">
        <int name="SizeField" type="uint16" />
    </size>
    <custom name="Flags" field="Flags" />
    <id name="Id" field="MsgId" />
    <value name="PseudoFlags" pseudo="true" field="Flags" interfaceFieldName="Flags" />
    <payload name="Data" />
    <checksum name="Checksum" from="Data" alg="crc-ccitt" verifyBeforeRead="true">
        <int name="ChecksumField" type="uint16" />
    </checksum>
</frame>
```
Note, that `PseudoFlags` layer is marked with `pseudo="true"` to indicate that its field is not really
serialized. The definition of the `PseudoFlags` in the 
[generated code](include/howto10/frame/Frame.h) uses `comms::option::def::PseudoValue` option to ensure that.
```cpp
using PseudoFlags =
    comms::protocol::TransportValueLayer<
        howto10::field::Flags<TOpt, comms::option::def::EmptySerialization>,
        0U,
        Checksum,
        comms::option::def::PseudoValue
    >;
```
The **real** `Flags` field needs to be customized beyond the current capabilities of the 
[CommsDSL](https://github.com/commschamp/CommsDSL-Specification). It requires defining &lt;custom&gt; layer:
```xml
<custom name="Flags" field="Flags" />
```
The actual code, defined in [dsl_src/include/howto10/frame/layer/Flags.h](dsl_src/include/howto10/frame/layer/Flags.h) and
copied to [include/howto10/frame/layer/Flags.h](include/howto10/frame/layer/Flags.h) by the code generator, extends the
[comms::protocol::TransportValueLayer](https://commschamp.github.io/comms_doc/classcomms_1_1protocol_1_1TransportValueLayer.html).
```cpp
template<typename TField, typename TNextLayer, typename... TOptions>
class Flags : public
    comms::protocol::TransportValueLayer<
        TField,
        Interface<>::TransportFieldIdx_flags,
        TNextLayer,
        TOptions...,
        comms::option::def::ProtocolLayerSuppressReadUntilDataSplitForcing,
        comms::option::def::ExtendingClass<Flags<TField, TNextLayer, TOptions...> >
    >
{

public:
    template <typename TMsg>
    bool reassignFieldValueToMsg(const Field& field, TMsg* msgPtr)
    {
        assert(msgPtr == nullptr); // The message object hasn't been created yet
        static_cast<void>(msgPtr);
        auto& idLayer = Base::nextLayer();
        auto& psedoFlagsLayer = idLayer.nextLayer();

        // Re-assign the field to the pseudo layer, which is going to 
        // assign it to the message object
        psedoFlagsLayer.pseudoField().value() = field.value();
        return true;
    }
};
```
Note usage of the `comms::option::def::ProtocolLayerSuppressReadUntilDataSplitForcing` option is forcefully passed to the 
base class to suppress the described earlier attempt to split the read operation into two stages. The class definition also overrides
the default implementation of the `reassignFieldValueToMsg()` to assign the read field's value to the pseudo layer, 
which follows the `ID` instead of assigning the value to the message object, which doesn't exist at this stage yet. 
The pseudo layer will assign the read value to the message object when its turn comes.

