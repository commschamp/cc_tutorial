# Tutorial 12
Avoiding dynamic memory allocation.

Many embedded bare-metal systems don't use any heap and cannot use dynamic memory allocation.
The [COMMS Library](https://github.com/arobenko/comms_champion#comms-library) has several
places where dynamic memory allocation is used:

- Inside [comms::MsgFactory](https://arobenko.github.io/comms_doc/classcomms_1_1MsgFactory.html) used
  by the [comms::protocol::MsgIdLayer](https://arobenko.github.io/comms_doc/classcomms_1_1protocol_1_1MsgIdLayer.html)
  when processing message numeric ID value and creating appropriate message object.
- Default storage of **&lt;string&gt;** field (implemented by extending 
  [comms::field::String](https://arobenko.github.io/comms_doc/classcomms_1_1field_1_1String.html)) is
  `std::string`.
- Default storage of **&lt;data&gt;** field (implemented by extending
  [comms::field::ArrayList](https://arobenko.github.io/comms_doc/classcomms_1_1field_1_1ArrayList.html)) is
  `std::vector<std::uint8_t>`.
- Default storage of **&lt;list&gt;** field (implemented by extending 
  [comms::field::ArrayList](https://arobenko.github.io/comms_doc/classcomms_1_1field_1_1ArrayList.html)) is
  `std::vector<ElementField>`.
  
The dynamic allocation inside [comms::protocol::MsgIdLayer](https://arobenko.github.io/comms_doc/classcomms_1_1protocol_1_1MsgIdLayer.html)
and [comms::MsgFactory](https://arobenko.github.io/comms_doc/classcomms_1_1MsgFactory.html) can be resolved
by using [comms::option::app::InPlaceAllocation](https://arobenko.github.io/comms_doc/options_8h.html) option. 
If forces usage an array (as private data member), big
enough to hold **any** (but one at a time) message provided in the **input** messages tuple. When 
new message type is recognized, the message object is created using 
[placement](https://en.cppreference.com/w/cpp/language/new) allocation and a pointer to the used
array is returned. The message object returned by the frame 
([Frame::MsgPtr](https://arobenko.github.io/comms_doc/classcomms_1_1protocol_1_1ProtocolLayerBase.html))
is still held by `std::unique_ptr`, but with a custom deleter, which will invoke the proper message class destructor.

The problematic storage types that use dynamic memory allocation (`std::string` and `std::vector`) can also be
replaced using some [options](https://arobenko.github.io/comms_doc/options_8h.html). The 
[COMMS Library](https://github.com/arobenko/comms_champion#comms-library) provides
[comms::util::StaticString](https://arobenko.github.io/comms_doc/classcomms_1_1util_1_1StaticString.html) and
[comms::util::StaticVector](https://arobenko.github.io/comms_doc/classcomms_1_1util_1_1StaticVector.html)
which expose similar public interface as `std::string` and `std::vector` respectively, but receive
additional template parameter which specifies their **maximal** capacity and use `std::array` of
appropriate `std::aligned_storage` as their private data member. In order to replace usage of 
problematic `std::string` and/or `std::vector`, the 
[comms::option::app::FixedSizeStorage](https://arobenko.github.io/comms_doc/options_8h.html)
needs to be passed to the field definition.

The [generated](include) code contains 
[include/tutorial12/options/BareMetalDefaultOptions.h](include/tutorial12/options/BareMetalDefaultOptions.h)
options configuration. It completely disables dynamic memory allocation in all possible places.
Let's take a look inside:
```cpp
#ifndef DEFAULT_SEQ_FIXED_STORAGE_SIZE
/// @brief Define default fixed size for various sequence fields
/// @details May be defined during compile time to change the default value.
#define DEFAULT_SEQ_FIXED_STORAGE_SIZE 32
#endif

#include "tutorial12/options/DefaultOptions.h"

namespace tutorial12
{

namespace options
{

template <typename TBase = tutorial12::options::DefaultOptions>
struct BareMetalDefaultOptionsT : public TBase
{
    struct message : public TBase::message
    {
        struct Msg1Fields : public TBase::message::Msg1Fields
        {
            using F1 = 
                std::tuple<
                    comms::option::app::FixedSizeStorage<DEFAULT_SEQ_FIXED_STORAGE_SIZE>,
                    typename TBase::message::Msg1Fields::F1
                >;
            using F2 = 
                std::tuple<
                    comms::option::app::SequenceFixedSizeUseFixedSizeStorage,
                    typename TBase::message::Msg1Fields::F2
                >;
        }; // struct Msg1Fields
        
        ...
        
    }; // struct message
    
    struct frame : public TBase::frame
    {
        struct FrameLayers : public TBase::frame::FrameLayers
        {
            ...
            
            using Id = std::tuple<
                comms::option::app::InPlaceAllocation,
                typename TBase::frame::FrameLayers::Id
            >;
            
        }; // struct FrameLayers
        
    }; // struct frame
    
    
};

using BareMetalDefaultOptions = BareMetalDefaultOptionsT<>;
```
As was explained earlier, the `comms::option::app::InPlaceAllocation` option passed to
the `Id` framing layer results in placement rather than dynamic memory allocation.

All the problematic fields receive `comms::option::app::FixedSizeStorage` option. The template 
parameter specifies maximal length. The generated code forces the same maximal length for 
all such fields to be `DEFAULT_SEQ_FIXED_STORAGE_SIZE` which is defined at the beginning
of the file. The generated code allows compiled application to set a different default value
if needed.

Please also note that all the fixed length / count fields (the ones that use **length** or **count** property)
already specify the maximal length / count of the storage and it doesn't need to be repeated. 
In this  case the passed option is `comms::option::app::SequenceFixedSizeUseFixedSizeStorage`.

The used options will force usage of 
[comms::util::StaticString](https://arobenko.github.io/comms_doc/classcomms_1_1util_1_1StaticString.html) 
instead of `std::string` and [comms::util::StaticVector](https://arobenko.github.io/comms_doc/classcomms_1_1util_1_1StaticVector.html)
instead of `std::vector`.

----

**SIDE NOTE**: The `Data` layer of the protocol framing receives an option which is passed to the 
payload field. The latter is used **only** when framing fields are cached in some external structure
(see documentation of [comms::protocol::ProtocolLayerBase::readFieldsCached()](https://arobenko.github.io/comms_doc/classcomms_1_1protocol_1_1ProtocolLayerBase.html))
which is **irrelevant** for this tutorial and should be ignored.
```cpp
template <typename TBase = tutorial12::options::DefaultOptions>
struct BareMetalDefaultOptionsT : public TBase
{
    ...
    
    struct frame : public TBase::frame
    {
        struct FrameLayers : public TBase::frame::FrameLayers
        {
            using Data = std::tuple<
                comms::option::app::FixedSizeStorage<DEFAULT_SEQ_FIXED_STORAGE_SIZE * 8>,
                typename TBase::frame::FrameLayers::Data
            >;
            
            ...
            
        }; // struct FrameLayers
        
    }; // struct frame
};
```
In normal operation the payload is not copied anywhere and message's `read()` function
operates on the **input** buffer itself.

----

This tutorial reused the generated 
[include/tutorial12/options/BareMetalDefaultOptions.h](include/tutorial12/options/BareMetalDefaultOptions.h)
to define its own protocol options inside [src/BareMetalProtocolOptions.h](src/BareMetalProtocolOptions.h)
```cpp
// Expects to wrap a variant of tutorial12::options::BareMetalDefaultOptionsT
template <typename TBase = tutorial12::options::BareMetalDefaultOptions>
struct BareMetalProtocolOptionsT : public TBase
{
    struct frame : public TBase::frame
    {
        struct Msg1Fields : public TBase::message::Msg1Fields
        {
            using F1 = 
                std::tuple<
                    comms::option::app::FixedSizeStorage<8>,
                    typename TBase::message::Msg1Fields::F1
                >;
        }; // struct Msg1Fields
    }; // struct frame
};

using BareMetalProtocolOptions = BareMetalProtocolOptionsT<>;
```
The definition above assumes that the template parameter is going to be 
a variant of [tutorial12::options::BareMetalDefaultOptionsT](include/tutorial12/options/BareMetalDefaultOptions.h)
and overrides the default storage size of `Msg1Fields::F1`.

----

**SIDE NOTE**: The [COMMS Library](https://github.com/arobenko/comms_champion#comms-library) was implemented in
a way that processes the options bottom-up. As the result, the options that appear above may 
override the configuration enforced by the options listed below.

In the example above the `comms::option::app::FixedSizeStorage<8>` overrides the 
configuration enforced by the [tutorial12::options::BareMetalDefaultOptions](include/tutorial12/options/BareMetalDefaultOptions.h)
(which is `comms::option::app::FixedSizeStorage<DEFAULT_SEQ_FIXED_STORAGE_SIZE>`).

----

The protocol options used by the [ServerSession](src/ServerSession.h) of this tutorial are:
```cpp
using ServerProtocolOptions = 
    BareMetalProtocolOptionsT<
        tutorial12::options::BareMetalDefaultOptionsT<
            tutorial12::options::ServerDefaultOptions
        >
    >;
```

The [server](src/ServerSession.cpp) doesn't have any other special aspects and
everything operates normally, but without any dynamic memory allocation.

One of the **important** aspects to understand is that for sequence fields like 
**&lt;string&gt;**, or **&lt;data&gt;** the input data is constantly copied from the 
**input** buffer to the internal storage of these fields, whether it is 
`std::string`, `std::vector`, [comms::util::StaticString](https://arobenko.github.io/comms_doc/classcomms_1_1util_1_1StaticString.html),
or [comms::util::StaticVector](https://arobenko.github.io/comms_doc/classcomms_1_1util_1_1StaticVector.html).
If we think about it a bit deeper, in most of the cases (all the previous tutorials so far) 
the message object doesn't outlive the  input buffer . It would
be beneficial if the storage type of the **&lt;string&gt;** and **&lt;data&gt;**
fields is some kind of "view" on input buffer. The 
[COMMS Library](https://github.com/arobenko/comms_champion#comms-library)
provides such an ability with [comms::option::app::OrigDataView](https://arobenko.github.io/comms_doc/options_8h.html)
option. If the option is passed to the definition of 
[comms::field::String](https://arobenko.github.io/comms_doc/classcomms_1_1field_1_1String.html) then 
the storage type will be [std::string_view](https://en.cppreference.com/w/cpp/string/basic_string_view)
if C++17 is been used to compile the source and the compiler actually supports it. Otherwise 
[comms::util::StringView](https://arobenko.github.io/comms_doc/classcomms_1_1util_1_1StringView.html) is 
chosen. Similar for the definition of the 
[comms::field::ArrayList](https://arobenko.github.io/comms_doc/classcomms_1_1field_1_1ArrayList.html) with 
`std::uint8_t` as its element type (used to define **&lt;data&gt;** field). If C++20 is used 
to compile the source and the compiler supports it the 
[std::span](https://en.cppreference.com/w/cpp/container/span) is used as the storage type.
Otherwise the [comms::util::ArrayView](https://arobenko.github.io/comms_doc/classcomms_1_1util_1_1ArrayView.html)
is chosen.

**NOTE** that the data view **cannot** be used for the **&lt;list&gt;** field, because its 
element is a field, not raw data, which might use specific endian for its deserialization or 
any other special decoding operation.

To help with passing such "data view" options to the used protocol definition, the generated code
contains [include/&lt;namespace&gt;/options/DataViewDefaultOptions.h](include/tutorial12/options/DataViewDefaultOptions.h).

The **client** side of this tutorial tries to use such options in addition to 
avoiding dynamic memory allocation. To make the example even more interesting the 
virtual functions are also avoided.

To support such configuration this tutorial defines a separate options structure
([src/DataViewBareMetalProtocolOptions.h](src/DataViewBareMetalProtocolOptions.h)) which 
combines the "data view" and "bare metal" (lack of dynamic memory allocation) 
configurations.
```cpp
template <typename TBase = tutorial12::options::DataViewDefaultOptions>
struct DataViewBareMetalProtocolOptionsT : public TBase
{
    struct frame : public TBase::frame
    {
        struct Msg3Fields : public TBase::message::Msg3Fields
        {
            using F1 = 
                std::tuple<
                    comms::option::app::FixedSizeStorage<16>,
                    typename TBase::message::Msg3Fields::F1
                >;

            using F2 = 
                std::tuple<
                    comms::option::app::SequenceFixedSizeUseFixedSizeStorage,
                    typename TBase::message::Msg3Fields::F2
                >;
        }; // struct Msg3Fields

        struct FrameLayers : public TBase::frame::FrameLayers
        {
            using Id = std::tuple<
                comms::option::app::InPlaceAllocation,
                typename TBase::frame::FrameLayers::Id
            >;
            
        }; // struct FrameLayers        

    }; // struct frame
};

using DataViewBareMetalProtocolOptions = DataViewBareMetalProtocolOptionsT<>;
```
Note that it expects a variant of 
[tutorial12::options::DataViewDefaultOptionsT](include/tutorial12/options/DataViewDefaultOptions.h)
to be passed as a template parameter. The fields of the `Msg3` are a variants of 
**&lt;list&gt;** and cannot use a view on input buffer. In order to prevent the 
storage type from been `std::vector` the `comms::option::app::FixedSizeStorage` or 
`comms::option::app::SequenceFixedSizeUseFixedSizeStorage` option needs to be used.
To prevent dynamic memory allocation, when message itself is created, the 
`comms::option::app::InPlaceAllocation` option needs to be passed to the `Id` 
framing layer.

The important part of the **client** definition looks like this:
```cpp
class ClientSession : public Session
{
    using Base = Session;
public:
    using Base::Base; // Inherit constructors

    // Common interface class for all the messages
    using Message = tutorial12::Message<>;

    // Protocol options for client
    using ClientProtocolOptions = 
        DataViewBareMetalProtocolOptionsT<
            tutorial12::options::DataViewDefaultOptionsT<
                tutorial12::options::ClientDefaultOptions
            >
        >;        
        
    // Definition of all the used message classes
    using Msg1 = tutorial12::message::Msg1<Message, ClientProtocolOptions>;
    using Msg2 = tutorial12::message::Msg2<Message, ClientProtocolOptions>;
    using Msg3 = tutorial12::message::Msg3<Message, ClientProtocolOptions>;
    
private:    
    template <typename TMsg>
    void sendMessage(const TMsg& msg)
    {
        ...
    }

    // Client specific frame 
    using Frame = 
        tutorial12::frame::Frame<
            Message,
            tutorial12::input::ClientInputMessages<Message, ClientProtocolOptions>,
            ClientProtocolOptions
        >;
};
```
The important thing to realize is that the message object is held by the 
`Frame::MsgPtr` which is a variant of `std::unique_ptr` with a custom deleter.
The latter contains a special logic to determine the right type of destructor to 
call when message object is destructed.

Another interesting aspect worth mentioning is demonstrated by the 
`void ClientSession::sendMsg2()` function:
```cpp
void ClientSession::sendMsg2()
{
    static const std::uint8_t Data1[] = {0xaa, 0xbb, 0xcc, 0xdd};
    static const std::uint8_t Data2[] = {0x12, 0x34, 0x58, 0x78};
    Msg2 msg;
    comms::util::assign(msg.field_f1().value(), std::begin(Data1), std::end(Data1));
    msg.field_f2().value() = Data2;
    sendMessage(msg);
}
```
The public interface of [std::string](https://en.cppreference.com/w/cpp/string/basic_string) and 
[std::string_view](https://en.cppreference.com/w/cpp/string/basic_string_view) differ. The 
latter doesn't have `assign()` member function for example. The similar situation
can be observed with [std::vector](https://en.cppreference.com/w/cpp/container/vector) and 
[std::span](https://en.cppreference.com/w/cpp/container/span). It is difficult to write 
assignment code which is underlying storage type agnostic. Once the underlying storage type 
is assumed to be something and its known API function is used, it becomes a boilerplate code
which may fail the compilation and/or work incorrectly when the assumption is broken. The 
[COMMS Library](https://github.com/arobenko/comms_champion#comms-library) introduces
`comms::util::assign()` stand alone function (requires include of 
[comms/util/assign.h](https://arobenko.github.io/comms_doc/assign_8h.html)). It is a helper
function which allows writing storage type agnostic code to assign a range of values. It 
can be used when the two iterators (begin and end) are known and works well for any 
type, whether it is `std::string`, `std::string_view`, `comms::util::StaticString`, 
`comms::util::StringView`, `std::vector`, `std::span`, `comms::util::StaticVector`, or
`comms::util::ArrayView`.

----

**SIDE NOTE**: Most bare metal metal applications avoid using of dynamic memory 
allocation, some also avoid virtual functions (due to code size limitations). Many also 
exclude usage of standard C library altogether. 

Note that the 
[COMMS Library](https://github.com/arobenko/comms_champion#comms-library) uses various
debug code inner correctness checks (compiled in when standard `NDEBUG` is not defined). Such
checks are implemented using [COMMS_ASSERT()](https://arobenko.github.io/comms_doc/Assert_8h.html)
macro, which by default invokes standard `assert()` defined by the standard library, which 
may cause a problem if the latter is not used. To avoid usage of the standard `assert()` 
there is a need to define `COMMS_NOSTDLIB` during compilation. It will cause the default 
failure functionality of the [COMMS_ASSERT()](https://arobenko.github.io/comms_doc/Assert_8h.html)
macro to be an infinite loop. 

The [COMMS Library](https://github.com/arobenko/comms_champion#comms-library) allows run-time 
override of the default assertion failure functionality. Please read 
[Custom Assertion Failure Behaviour](https://arobenko.github.io/comms_doc/page_assert.html) page
from the documentation for more details. The 
[Error Handling](https://arobenko.github.io/comms_doc/page_use_prot.html#page_use_prot_error_handling)
section also contains useful information about the available error handling.

----

## Summary
- The default behavior of the framing is to dynamically allocate message object. 
- It can be changed by passing `comms::option::app::InPlaceAllocation` option to the `ID` framing layer
  (implemented by the [comms::protocol::MsgIdLayer](https://arobenko.github.io/comms_doc/classcomms_1_1protocol_1_1MsgIdLayer.html)).
- The default storage of the fields like **&lt;string&gt;**, **&lt;data&gt;** and **&lt;list&gt;** can
  be changed by passing certain options.
- Passing [comms::option::app::FixedSizeStorage](https://arobenko.github.io/comms_doc/options_8h.html) option
  will result in usage of [comms::util::StaticString](https://arobenko.github.io/comms_doc/classcomms_1_1util_1_1StaticString.html)
  instead `std::string` and [comms::util::StaticVector](https://arobenko.github.io/comms_doc/classcomms_1_1util_1_1StaticVector.html)
  instead of `std::vector`.
- Passing [comms::option::app::OrigDataView](https://arobenko.github.io/comms_doc/options_8h.html) option will 
  result in usage of `std::string_view` or [comms::util::StringView](https://arobenko.github.io/comms_doc/classcomms_1_1util_1_1StringView.html)
  instead of `std::string` and `std::span` or [comms::util::ArrayView](https://arobenko.github.io/comms_doc/classcomms_1_1util_1_1ArrayView.html)
  instead of `std::vector`.
- The generated code provides [include/&lt;namespace&gt;/options/BareMetalDefaultOptions.h](include/tutorial12/options/BareMetalDefaultOptions.h)
  definition to help with avoiding dynamic memory allocation.
- The generated code provides [include/&lt;namespace&gt;/options/DataViewDefaultOptions.h](include/tutorial12/options/DataViewDefaultOptions.h)
  definition to help with avoiding unnecessary data copying from input buffer to message fields' storage.
- There is [comms::util::assign()](https://arobenko.github.io/comms_doc/assign_8h.html) stand-alone function which helps
  writing storage type agnostic assignment code with a range of iterators.

[Read Previous Tutorial](../tutorial11) &lt;-----------------------&gt; [Read Next Tutorial](../tutorial13) 
