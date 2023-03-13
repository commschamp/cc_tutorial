# Tutorial 23
Reusing definitions from other schemas.

Sometimes a need may arise to reuse some elements (usually fields) of one schema / protocol in the definition of another.
It can be useful when common complex encoding rules, like [ASN.1](https://en.wikipedia.org/wiki/ASN.1) requiring
custom code injection need to be reused in multiple independent protocols. Version **v5.0** of the
[CommsDSL Specification](https://commschamp.github.io/commsdsl_spec) allow use of multiple independent
schema names when processing multiple schema files and referencing fields of one in another.

Version **v5.0** of the **commsdsl2comms** code generator supports this multi-schema feature, but
requires extra command line parameter `-s` to allow
use of multiple schemas names in the definition of the protocol.

This tutorial uses two schema files:

- [dsl/schema_ext.xml](dsl/schema_ext.xml) which defines external schema with name (and main namespace) "t23_ext".
- [dsl/schema.xml](dsl/schema.xml) which defines schema of this tutorial.

The inter-schema field reference is prefixing the usual field reference with `@ + schema name`.
```xml
<ref field="@t23_ext.ns1.I1" />
```
The generated code (in [include/tutorial23/field/I1.h](include/tutorial23/field/I1.h)) defines
the field (which inherits the name of the referenced field) as an alias type to the field in the `t23_ext` namespace:
```cpp
template <typename TOpt = tutorial23::options::DefaultOptions, typename... TExtraOpts>
using I1 =
    t23_ext::ns1::field::I1<
        TOpt,
        TExtraOpts...
    >;
```
The definition of the `t23_ext::ns1::field::I1` field itself is generated in
[include/t23_ext/ns1/field](include/t23_ext/ns1/field) folder, i.e. the [include](include)
folder has two sub-folders for the different namespaces.

The member field of the `Msg` message definition also references field in the external schema.
```xml
<message name="Msg1" id="MsgId.M1" displayName="^Msg1Name">
    <ref field="I1" name="F1" />
    <ref field="@t23_ext.ns1.S1" name="F2" />
</message>
```

The definition of the `Length` field in the external `t23_ext` schema is taken from the
previous [tutorial22](../tutorial22). Instead of referencing it with the **&lt;ref&gt;**
field definition (which is also possible) the schema just copies its definition using **reuse**
property:
```xml
<bundle reuse="@t23_ext.ns1.Length" reuseCode="true" />
```
Please note the usage of the **reuseCode** property. The **reuse** one just copies the XML definition of the
field without copying any of the custom injected code of the field. Setting **reuseCode** boolean property
ensures that the custom code is also copied. As the result, the `Length` field definition can be
found in the `tutorial23` namespace ([include/tutorial23/field/Length.h](include/tutorial23/field/Length.h)) and
cannot be found in `t23_ext` because it's not really referenced. The `Length` in the `tutorial23` namespace
is referenced by the frame:
```xml
<frame name="Frame">
    <sync name="Sync">
        <int name="SyncField" type="uint16" defaultValue="0xabdc" />
    </sync>
    <size name="Size" field="Length" />
    <id name="Id" field="MsgId" />
    <payload name="Data" />
</frame>
```

Also note that the custom injected code of the `Length` field is located in the folder specifying its
original location ([dsl_src/include/t23_ext/ns1/field](dsl_src/include/t23_ext/ns1/field)).

Using multiple schemas requires extra attention to specifying protocol options
(the classes defined in the [include/tutorial23/options](include/tutorial23/options) folder).
The option classes are designed to be folded and outer classes may extend or override options defined
by the inner ones. Every schema defines its own independent set of options:

- [include/t23_ext/options](include/t23_ext/options) - Options for the elements inside `t23_ext` schema.
- [include/tutorial23/options](include/tutorial23/options) - Options for the elements inside `tutorial23` schema.

In order to combine them the `DefaultOptions` of the protocol (`tutorial23`) schema are expected to wrap and extend
the external (`t23_ext`) one. As the result the [ClientSession](src/ClientSession.h) defines its
options in the following way:
```cpp
using ClientProtocolOptions =
    tutorial23::options::ClientDefaultOptionsT<
        tutorial23::options::DefaultOptionsT<
            t23_ext::options::ClientDefaultOptions
        >
    >;
```

The [ServerSession](src/ServerSession.h) used even more complex definition:
```cpp
using ExtProtocolOptions = 
    t23_ext::options::DataViewDefaultOptionsT<
        t23_ext::options::ServerDefaultOptions
    >;

using ServerProtocolOptions = 
    tutorial23::options::DataViewDefaultOptionsT<
        tutorial23::options::ServerDefaultOptionsT<
            tutorial23::options::DefaultOptionsT<
                ExtProtocolOptions
            >   
        >
    >;
```

Without using options from the `t23_ext::options` the compilation will fail because
`t23_ext::ns1::field::S1` [field](include/t23_ext/ns1/field/S1.h) attempts to
access the options referencing `typename TOpt::t23_ext::ns1::field::S1`, which
does not existing in the options provided by the `tutorial23`.

```cpp
template <typename TOpt = t23_ext::options::DefaultOptions, typename... TExtraOpts>
class S1 : public
    comms::field::String<
        t23_ext::field::FieldBase<>,
        TExtraOpts...,
        typename TOpt::t23_ext::ns1::field::S1,
        comms::option::def::SequenceSerLengthFieldPrefix<typename S1Members<TOpt>::LengthPrefix>
    >
```

In addition to the complications around the protocol options definitions, which if not done right may
result in difficult to understand compilation errors, referencing the fields in another schema may
cause problems in different build or packaging systems when multiple independent schemas (protocols) reusing the
common one may attempt to generate and overwrite the same common files.
To cope with this problem the code generation utilities (**commsdsl2comms** and others) allow
renaming different namespaces to avoid clashing.

However, as was shown in this tutorial the fields which are **reuse**-ed rather than
**&lt;ref&gt;**-erenced don't generate code in the external namespace. In case the **all**
the schema fields defined this way, the external namespace will be empty and no code for it
will be generated. As the result the definition of the protocol options are also getting
much simpler.

The bottom line, it is highly recommended to **reuse** the fields from the external schema rather
than **&lt;ref&gt;**-erence them.

## Summary

- External schema definitions reuse is supported since **v5.0** of the [CommsDSL](https://commschamp.github.io/commsdsl_spec)
  and [commsdsl](https://github/commschamp/commsdsl) code generators.
- Inter-schema referencing is allowed using `@<schema_name>.` prefix.
- When using multiple schemas it is highly recommended to **reuse** the fields  rather
than **&lt;ref&gt;**-erence them.


[Read Previous Tutorial](../tutorial22) &lt;-----------------------&gt; [Read Next Tutorial](../tutorial24) 
