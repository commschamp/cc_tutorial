# Tutorial 4
Working with **&lt;variant&gt;** fields and defining heterogeneous lists.

## Heterogeneous Fields
Some protocols in some cases don't _hardcode_ type of the field value which is supposed to
be in a specific place. It puts some kind of (usually) numeric **ID** 
(sometimes referred as **key** or **type**) which determines the value type that follows.
It makes it ideal to define various _properties_ (or list of _properties_) which can be
or any type and reported in any order.

The [CommsDSL](https://github.com/arobenko/CommsDSL-Specification) supports such constructs
using **&lt;variant&gt;** fields. Let's take a look inside [dsl/schema.xml](dsl/schema.xml) 
and see how the following table of properties is implemented.

|ID (1 byte)|Type|
|:---:|:---:|
|0|Property1 - 2 bytes unsigned integer (uint16)|
|2|Property2 - 4 bytes floating point value (float)|
|5|Property3 - string prefixed with 1 bytes of its length|

First of all the numeric property ID (**key**) is convenient to define
as stand-alone **&lt;enum&gt;** first.
```xml
<enum name="PropKey" type="uint8">
    <validValue name="K1" val="0" />
    <validValue name="K2" val="2" />
    <validValue name="K3" val="5" />
    ...
</enum>
```
The definition of a heterogeneous field that can hold **any** (but one at a time) of the properties listed
above looks like this:
```xml
<int name="PropKeyCommon" type="uint8" failOnInvalid="true"/>

<variant name="KeyValueProp">
    <bundle name="Prop1">
        <int reuse="PropKeyCommon" name="Key" defaultValue="PropKey.K1" validValue="PropKey.K1" />
        <int name="Val" type="uint16" />
    </bundle>
    
    <bundle name="Prop2">
        <int reuse="PropKeyCommon" name="Key" defaultValue="PropKey.K2" validValue="PropKey.K2" />
        <float name="Val" type="float" defaultValue="nan" />
    </bundle>            
    
    <bundle name="Prop3">
        <int reuse="PropKeyCommon" name="Key" defaultValue="PropKey.K3" validValue="PropKey.K3" />
        <string name="Val">
            <lengthPrefix>
                <int name="Length" type="uint8" />
            </lengthPrefix>
        </string>
    </bundle>            
</variant>
```
There are multiple important aspects that require a closer look and deeper understanding.

- Every property is a **key**-**value** pair, which are bundled together by the **&lt;bundle&gt;** 
  field definition to represent a **single** member field of the **&lt;variant&gt;**.
- Every first (**key**) field inside such **&lt;bundle&gt;** must be of the same size and share
  come common property. That's why external **PropKeyCommon** field was defined and all other
  **key** ones reuse (using **reuse** property) the common definition and then apply extra changes / modifications
  on top.
- The **logical** (not necessarily actually implemented in the same way) code flow when
  reading such field is to attempt reading of the defined members (**&lt;bundle&gt;**-s) one
  by one **in order** of their definition and stop reading once the read operation of the 
  member is successful. For that purpose there is a need to **fail** reading of the property if
  its **key** is not as expected. That's how the right one is found.
- To fail reading of the property on different **key** value the latter sets the **validValue**
  property to appropriate one and has **failOnInvalid** property set to **true** as well 
  (defined in and reused from **PropKeyCommon** field).
- In order to default construct a property with the correct key value without any need to implement
  boilerplate code that does so the **defaultValue** property is used to set the same value as a valid one.
- The definition of the key valid values as a separate **&lt;enum&gt;** (PropKey) allows referencing its
  values by a name (instead of hard-coded numeric value) in the **defaultValue** and **validValue** properties.



[Read Previous Tutorial](../tutorial3) &lt;-----------------------&gt; [Read Next Tutorial](../tutorial5) 
