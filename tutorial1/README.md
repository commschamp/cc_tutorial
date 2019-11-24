# Tutorial 1
Introducing basic protocol definition, polymorphic message interfaces, and dispatching message object into appropriate handling function.

## CommsDSL Schema
The [schema](dsl/schema.xml) file contains very simple protocol definition.
There are two messages without any internal fields. The enum `MsgId` field
is used to define numeric IDs of the messages. The framing is also very
simple, it just prefixes message payload (empty in this specific case) with
numeric message ID.
