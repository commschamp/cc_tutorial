# Tutorial 24
Extra validity verification of message payload.

Many protocols specify extra validity conditions of the message payload. For example,
some fields require having (or not having) certain values base on the value of other fields.
The [CommsDSL](https://github.com/commschamp/CommsDSL-Specification) allows specify such conditions
using **validCond** property. It works in exactly the same way as **construct** and/or **readCond** ones
described in the [tutorial16](../tutorial23) (including referencing the interface fields if needed).

The [schema](dsl/schema.xml) of this tutorial has `Msg1` defined as below:

```xml
<message name="Msg1" id="MsgId.M1" ...>
    <fields>
        <int name="F1" type="uint8" />
        <int name="F2" type="uint8" />
    </fields>
    <validCond>
        <or>
            <validCond value="$F1 != 0" />
            <validCond value="$F2 = 0" />
        </or>
    </validCond>
</message>
```
In this example `F2` must be `0` in case `F1` is `0`.

The generated [Msg1](include/tutorial24/message/Msg1.h) implements its `doValid()` member function accordingly:
```cpp
template <typename TMsgBase, typename TOpt = tutorial24::options::DefaultOptions>
class Msg1 : public
    comms::MessageBase<...>
{
   ...

    // Generated validity check functionality
    bool doValid() const
    {
        if (!Base::doValid()) {
            return false;
        }

        return
            ((field_f1().getValue() != static_cast<typename Field_f1::ValueType>(0U)) ||
             (field_f2().getValue() == static_cast<typename Field_f2::ValueType>(0U)));
    }
};
```

In some cases the protocol specification demands the message to be discarded if its contents are invalid.
The [CommsDSL](https://github.com/commschamp/CommsDSL-Specification) provides **failOnInvalid** property that
can be used for messages, not only fields.

```xml
<message name="Msg1" id="MsgId.M1" failOnInvalid="true" displayName="^Msg1Name">
    ...
</message>
```

The generated [Msg1](include/tutorial24/message/Msg1.h) class uses **comms::option::def::FailOnInvalid** option in the
message class definition.
```
template <typename TMsgBase, typename TOpt = tutorial24::options::DefaultOptions>
class Msg1 : public
    comms::MessageBase<
        TMsgBase,
        comms::option::def::StaticNumIdImpl<tutorial24::MsgId_M1>,
        comms::option::def::FieldsImpl<typename Msg1Fields<TOpt>::All>,
        comms::option::def::MsgType<Msg1<TMsgBase, TOpt> >,
        comms::option::def::HasName,
        comms::option::def::FailOnInvalid<>
    >
{...};
```

The code which prepares and sends `Msg1` inside the [src/ClientSession.cpp](src/ClientSession.cpp) looks like this:
```cpp
void ClientSession::sendMsg1()
{
    Msg1 msg;
    assert(msg.doValid());

    msg.field_f2().value() = 2;
    assert(!msg.doValid());
    sendMessage(msg); // Invalid message can be sent, but should be ignored on reception

    msg.field_f1().value() = 1;
    sendMessage(msg); // Should get received and echoed back
}
```
Note that `Msg1` is sent twice. When the message contents are invalid the object gets discarded on the server side and only
the valid one is echoes back to the client.

The **failOnInvalid** property assigned to the `<message>` works also without any extra validity conditions (**validCond**) in
case any of the fields contain invalid values:
```xml
<message name="Msg2" id="MsgId.M2" failOnInvalid="true" displayName="^Msg2Name">
    <int name="F1" type="uint8" validRange="[0, 10]" />
    <int name="F2" type="uint8" validRange="[10, 20]" />
</message>
```

The code which sends/receives `Msg2` demonstrates it:
```cpp
void ClientSession::sendMsg2()
{
    Msg2 msg;
    assert(!msg.doValid()); // F2 is invalid when default constructed
    sendMessage(msg); // Invalid message can be sent, but should be ignored on reception

    msg.field_f1().value() = 5;
    msg.field_f2().value() = 10;
    assert(msg.doValid());
    sendMessage(msg); // Should get received and echoed back
}
```

## Summary
- To specify extra validity condition(s) use **validCond** property (or `<validCond>` child node).
- The **validCond** property uses the same syntax / rules as **construct** and **readCond** described in [tutorial16](../tutorial16).
- To discard message on invalid contents use **failOnInvalid** property.

[Read Previous Tutorial](../tutorial23) &lt;-----------------------&gt; [Read Next Tutorial](../tutorial25) 
