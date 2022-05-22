# Overview
This repository is a combination of tutorials and various how-to(s) for
[CommsChampion Ecosystem](https://commschamp.github.io). It is important to
understand the available components and their respective roles. Please
read the [introduction](https://commschamp.github.io) if you haven't done
so yet.

The tutorials are organized as a combination **tutorials/tutorialX** folders. They 
gradually introduce various concepts as well as explain various nuances for specific
use cases. The tutorials are expected to be read **sequentially**
one by one. Be patient and try to follow them through even if a tutorial subject seems
irrelevant to a particular use case you are trying to implement. It might
still introduce a concept relevant for further tutorials.

The how-to(s) on the other hand, do not have any particular organization. They
reside in **howtos/howtoX** folders and can be read independently. **HOWEVER**, it is
paramount to understand the core ideas explained in tutorials before attempting
to understand a particular howto example. The howto(s) are
there to provide some extra examples or cover some specific nuances which are
not explained properly in the tutorials. If you encounter a sutuation where it is 
not 100% clear how to define and/or implement some logic please open an issue for this 
project or send a direct [e-mail](https://commschamp.github.io/contact/). 
Maybe your question will end up as one of the **howtos**.

It is highly recommended to open 
a source code with your favourite IDE to be able to easily navigate it and 
have a full code listing visible, while reading the README files of the tutorials from this
github repository using your browser.

The [CommsChampion Ecosystem](https://commschamp.github.io) was built to be easy to use 
while providing sensible behavioural defaults suitable for most of C++ applications. It 
is also very flexible when it comes to application specific configurations. However, it 
is very difficult to cover all the capabilities in a set of introductory tutorials.
It is highly recommended to read through the [CommsDSL](https://commschamp.github.io/commsdsl_spec/)
specification in order to understand the full capabilities of the schema definition
as well as [COMMS Library documentation](https://commschamp.github.io/comms_doc/)
(especially [How to Use Defined Custom Protocol](https://commschamp.github.io/comms_doc/page_use_prot.html)
page) in order to understand application specific configuration, after finishing the whole set
of the tutorials from this repository.

# Repository Organization
Every **tutorials/tutorialX** and **howotos/howtoX** folder may contain the following files / directories:

- **README.md** - Actual tutorial / how-to explanation markdown text that is 
intended to be made available for online reading by the repository hosting service
(github).
- **dsl** - Folder containing [CommsDSL](https://github.com/commschamp/CommsDSL-Specification)
schema file(s) relevant for the tutorial / how-to.
- **include** - Folder that contains protocol definition code 
**generated** by the [commsdsl2comms](https://github.com/commschamp/commsdsl)
tool and relevant for the tutorial.
- **src** - Folder containing code relevant to the tutorial / how-to.
- **dsl_src** - Optional folder containing extra code snippets which are 
picked up by the [commsdsl2comms](https://github.com/commschamp/commsdsl) tool
and find their way into the generated protocol definition code.

**IMPORTANT EMPHASIS**: The **include** folder of each and every **tutorials/tutorialX**
and **howtows/howtoX** is the **generated** code produced by the **commsdsl2comms** code
generation tool during the build process. Note, that it is a bad practice to
keep generated code as sources of the repository and should not be done in 
real life projects. It was done here to allow easy generated code demonstration and
references to it from the tutorial text. Also note that **commsdsl2comms** 
generates a full CMake project while only its **include** folder is copied to
the tutorial.

This whole repository is also a CMake project which builds code of all the 
tutorials and how-to(s). Every tutorial and how-to implements both **client** 
and **server** side of the same protocol and produces **X_client** and **X_server**
binary executables (where **X** is the name of the tutorial / how-to). In most
cases the **server** is an _echo_ one, it parses the received output, creates 
appropriate message object, then serializes and sends it back to the **client**.
The **client**-s usually send multiple messages to the **server** and then 
process and print the received messages. After exchanging all the planned
messages with the **server**, the connection session is terminated.

The I/O handling framework used for all the applications is 
**Boost.Asio** and TCP/IP communication was chosen for all the built client / server
applications. The relevant code is common for all the applications and is abstracted away into the
common static library (residing in the [lib](../../tree/master/lib) folder). Note, that
protocol handling and management code is completely I/O link independent and can
be used in the same way with any I/O link type.

To test the binaries of the specific tutorial, first run the **server** application
in your terminal window. It is expected to run indefinitely until manually terminated
with CTRL+C. In the second terminal window run the **client** application. In most
cases it will exchange several messages with the **server** and exit. 

# Updates to the Tutorial(s)
Any future updates to the [COMMS Library](https://github.com/commschamp/comms) and/or
[commsdsl2comms](https://github.com/commschamp/commsdsl) code generator will probably
result in updates to this tutorial. All the new updates can be viewed on
the [releases](https://github.com/commschamp/cc_tutorial/releases) page. The 
releases are all date based for easier tracking when an update was introduced.

# References
The core component of the [CommsChampion Ecosystem](https://commschamp.github.io) is
[COMMS Library](https://github.com/commschamp/comms). Its full
tutorial and API reference can be viewed [online](https://commschamp.github.io/comms_doc) or
downloaded from latest [release artifacts](https://github.com/commschamp/comms/releases).
The full tutorial on how to use the [COMMS Library](https://github.com/commschamp/comms)
resides in
[How to Use Defined Custom Protocol](https://commschamp.github.io/comms_doc/page_use_prot.html)
page of the documentation.

The **commsdsl2comms** code generator requires schema file(s) to be written in
[CommsDSL](https://github.com/commschamp/CommsDSL-Specification). The full specification
can be viewed [online](https://commschamp.github.io/commsdsl_spec/) or
downloaded as PDF from latest [release artifacts](https://github.com/commschamp/CommsDSL-Specification/releases).

# How to Build
This project uses CMake as its build system. Please open main
[CMakeLists.txt](CMakeLists.txt) file and review available options as well as
mentioned available parameters, which can be used in addition to standard 
ones provided by CMake itself, to modify the default build. 

**NOTE**, that [Boost](https://www.boost.org) libraries are also required.
In case Boost libraries are not installed in expected default location
(mostly happens on Windows systems), use variables described in 
[CMake documentation](https://cmake.org/cmake/help/v3.8/module/FindBoost.html) 
to help CMake find required libraries and headers.
It is recommended to use `-DBoost_USE_STATIC_LIBS=ON` parameter to force
linkage with static Boost libraries.

### Linux Build
```
$> cd /source/of/this/project
$> mkdir build && cd build
$> cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$PWD/install ..
$> make install
```
### Windows Build
```
$> cd C:\source\of\this\project
$> mkdir build
$> cd build
$> cmake -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=Release \ 
    -DCMAKE_INSTALL_PREFIX=%cd%/install \
    -DBOOST_ROOT="C:\Libraries\boost_1_65_1" -DBoost_USE_STATIC_LIBS=ON ..
$> nmake install
```

# Tutorials

- [tutorial1](../../tree/master/tutorials/tutorial1) - Introducing basic protocol definition, polymorphic message 
  interfaces, and dispatching message object into appropriate handling function.
- [tutorial2](../../tree/master/tutorials/tutorial2) - Introduction to message fields definitions and their usage.
- [tutorial3](../../tree/master/tutorials/tutorial3) - Working with scaling and units in numeric fields.
- [tutorial4](../../tree/master/tutorials/tutorial4) - Working with **&lt;variant&gt;** fields and defining heterogeneous
  lists.
- [tutorial5](../../tree/master/tutorials/tutorial5) - Deeper understanding of **&lt;frame&gt;**-ing and working 
  with multiple **&lt;frame&gt;**-s.
- [tutorial6](../../tree/master/tutorials/tutorial6) - Deeper understanding of message dispatch.
- [tutorial7](../../tree/master/tutorials/tutorial7) - Dispatching single message object to multiple handlers.
- [tutorial8](../../tree/master/tutorials/tutorial8) - Returning values from message handling functions.
- [tutorial9](../../tree/master/tutorials/tutorial9) - Dealing with multiple uni-directional messages.
- [tutorial10](../../tree/master/tutorials/tutorial10) - Dealing with small number of uni-directional messages.
- [tutorial11](../../tree/master/tutorials/tutorial11) - Avoiding virtual functions.
- [tutorial12](../../tree/master/tutorials/tutorial12) - Avoiding dynamic memory allocation.
- [tutorial13](../../tree/master/tutorials/tutorial13) - Supporting multiple message forms with the same numeric ID.
- [tutorial14](../../tree/master/tutorials/tutorial14) - Custom checksum and other custom code injections.
- [tutorial15](../../tree/master/tutorials/tutorial15) - Avoiding unnecessary decoding of messages.
- [tutorial16](../../tree/master/tutorials/tutorial16) - Extra values in transport framing.
- [tutorial17](../../tree/master/tutorials/tutorial17) - Custom transport framing layers.
- [tutorial18](../../tree/master/tutorials/tutorial18) - How to access transport framing fields.
- [tutorial19](../../tree/master/tutorials/tutorial19) - Introduction to protocol version support.
- [tutorial20](../../tree/master/tutorials/tutorial20) - Reporting protocol version in one of the messages.
- [tutorial21](../../tree/master/tutorials/tutorial21) - Cast between different field types.


# How-Tos
- [howto1](../../tree/master/howtos/howto1) - Custom remaining size framing information preceding **&lt;id&gt;**.
- [howto2](../../tree/master/howtos/howto2) - Having single field for message ID and remaining size in message framing.
- [howto3](../../tree/master/howtos/howto3) - Using message termination suffix instead of message length prefix.
- [howto4](../../tree/master/howtos/howto4) - Single message protocol without message ID in framing.
- [howto5](../../tree/master/howtos/howto5) - Custom transport value containing protocol version and extra flags.
- [howto6](../../tree/master/howtos/howto6) - Multiple run-time determined checksum algorithms in the same protocol.
- [howto7](../../tree/master/howtos/howto7) - Alternating values in synchronization framing prefix.
- [howto8](../../tree/master/howtos/howto8) - Optional fields in message framing.
- [howto9](../../tree/master/howtos/howto9) - Frame with checksum of the header.
- [howto10](../../tree/master/howtos/howto10) - Dealing with "Read split is disallowed by at least one of the inner layers" static assertion.

`
