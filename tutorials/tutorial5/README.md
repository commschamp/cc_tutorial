# Tutorial 5
Deeper understanding of **&lt;frame&gt;**-ing and working with multiple **&lt;frame&gt;**-s.

Many embedded systems have multiple I/O interfaces for communication with external world. It is also
not uncommon for new I/O interfaces being added in the future versions of the hardware. Many developers
make a prudent choice and try to reuse the same communication protocol for multiple available I/O links.
However, every type of I/O has different reliability built-in and may require different message framing.

For example the TCP/IP link uses checksum in its packets to insure that data is not corrupted and 
automatically re-requests packets to be sent again if needed. As the result simple framing below is
suitable in most cases.
```
SIZE | ID | PAYLOAD
```

With RS-232 link (or similar) there is a need to take extra measures to identify where the message packet 
starts and whether the message data was not corrupted on the way with a checksum. It many cases it looks
something like this:
```
SYNC (predefined header) | SIZE | ID | PAYLOAD | CHECKSUM
```

The whole [CommsChampion Ecosystem](https://arobenko.github.io/cc/) was designed with clean separation
of message definitions with their payloads and the actual framing. It also allows definition of multiple
frames in the same protocol schema file(s) and allows the end application to pick one that is needed at
compile time.

In this tutorial we will use two different frames: one for messages sent from **client** to **server** 
and another for the opposite direction. In the process we'll get a deeper understanding of **&lt;frame&gt;**
definition options.

The [schema](dsl/schema.xml) defines two frames. One is for messages being sent by the **server** to the 
**client**.
```xml
<frame name="ServerToClientFrame">
    <size name="Size">
        <int name="SizeField" type="uint16" />
    </size>
    <id name="ID" field="MsgId" />
    <payload name="Data" />
</frame>
```
This is the framing that has been seen in all the previous tutorials. It is simply:
```
SIZE (2 bytes) | ID (1 byte) | PAYLOAD
```

The other one for messages being sent from the **client** to the **server** is:
```xml
<frame name="ClientToServerFrame">
    <sync name="Sync">
        <int name="SyncField" type="uint16" defaultValue="0xabcd" />
    </sync>
    <size name="Size">
        <int name="SizeField" type="uint16" serOffset="2" displayOffset="2" />
    </size>
    <id name="ID" field="MsgId" />
    <payload name="Data" />
    <checksum name="Checksum" alg="crc-ccitt" from="Size" >
        <int name="ChecksumField" type="uint16" />
    </checksum>        
</frame>
```
It represents the following framing:
```
SYNC (0xabcd - 2 bytes) | SIZE (up until and including CHECKSUM - 2 bytes) | ID (1 byte) | PAYLOAD | CHECKSUM (crc-ccitt - 2 bytes)
```

To properly understand the schema definition above and the implementation implications let's go through the
important points one by one.

First of all, all every **&lt;frame&gt;** must define internal so called **layers** (**&lt;sync&gt;**, 
**&lt;size&gt;**, etc...). Every such layer handles only one specific value inside the message frame. To
properly describe the length and type of such value, the **field** definition is used:
```xml
<sync name="Sync">
    <int name="SyncField" type="uint16" defaultValue="0xabcd" />
</sync>
```

----

**SIDE NOTE**: In case the **&lt;frame&gt;** XML node has properties other than **layers** defined as XML children,
then the layers themselves need to be defined inside **&lt;layers&gt;** XML node.
```xml
<frame name="ClientToServerFrame">
    <description>
        This frame is used for messages being sent from client to server.
    </description>
    <layers>
        <sync name="Sync">
            <int name="SyncField" type="uint16" defaultValue="0xabcd" />
        </sync>
        ...
    </layers>
</frame>
```

Similar with the definition of the layer itself. If it has some other non inner field definition properties
defined as XML children, then the field definition needs to be defined as a child of **&lt;field&gt;** XML
node:
```xml
<sync name="Sync">
    <description>
        Synchronization bytes to mark beginning of the message.
    </description>
    <field>
        <int name="SyncField" type="uint16" defaultValue="0xabcd" />
    </field>
</sync>
```

----

[Read Previous Tutorial](../tutorial4) &lt;-----------------------&gt; [Read Next Tutorial](../tutorial6) 
