# How-To 1
Custom remaining size framing information preceding **&lt;id&gt;**.

This howto demonstrates having remaining size information in message framing sharing its 2 bytes with
extra flags which influence the way message payload is read. 

Having values (flags) in the message framing which influence how message payload is read and/or how 
message is processed requires definition of common message interface:
```xml
<fields>
    <set name="InterfaceFlags" length="1">
        <bit name="B0" idx="0" />
        <bit name="B1" idx="1" />
    </set>        
    
</fields>

<interface name="Interface" description="Common Interface for all the messages.">
    <ref field="InterfaceFlags" name="Flags" />
</interface>    
```

When remaining message length information in the message framing is split into multiple
values, the default **&lt;size&gt;** cannot be used, the **&lt;custom&gt;** one needs to be used 
instead:
```xml
    <frame name="Frame">
        <custom name="SizeWithFlags">
            <bitfield name="Field">
                <int name="Size" type="uint16" bitLength="12"/>
                <ref field="InterfaceFlags" name="Flags" bitLength="4" />
            </bitfield>
        </custom>        
        <id name="Id" field="MsgId" />
        <value name="Flags" interfaceFieldName="Flags" pseudo="true" field="InterfaceFlags" />
        <payload name="Data" />
    </frame>
```
When _size_ layer precedes **&lt;id&gt;** it is not possible to assign flags to message object 
(because the latter is not allocated yet) and then forward the `read()` operation to the next 
layer. In order to solve the problem the **pseudo** (marked with **pseudo="true"** property) 
**&lt;value&gt;** layer is added right before the **&lt;payload&gt;**.

---

**REMINDER**: The **pseudo** **&lt;value&gt;** layer does not produce any output or consumes any input, it just 
contains its field as a private data member (value of which can be assigned externally) and 
pretends to read the value when its `read()` member function is invoked.

---

When the `SizeWithFlags` reads its value it needs to access the `Flags` **&lt;value&gt;** layer and 
assign the pseudo field value, see [dsl_src/include/howto1/frame/layer/SizeWithFlags.h](dsl_src/include/howto1/frame/layer/SizeWithFlags.h)
for details:
```cpp
template<typename TField, typename TNextLayer, typename... TOptions>
class SizeWithFlags : public
    comms::protocol::MsgSizeLayer<...>
{

public:
    // Repeat some types from the base class
    using Field = typename Base::Field;    

    template<typename TMsg> 
    void beforeRead(const Field& field, TMsg* msg)
    {
        static_cast<void>(msg);
        COMMS_ASSERT(msg == nullptr); // The message object is not created yet
        Base::nextLayer().nextLayer().pseudoField().value() = field.field_flags().value();
    } 

    ...
};
```
**Note** that `nextLayer()` function is called twice: first time gives an access to the `Id` layer 
that follows, and second time gives an access to the `Flags` one. After that the 
**&lt;value&gt;** layer will do its job of re-assigning its field to the **&lt;interface&gt;** the 
normal way it's designed to do.

Also for more details please read [Defining Custom Message Size Protocol Stack Layer](https://commschamp.github.io/comms_doc/page_custom_size_layer.html)
tutorial page.
