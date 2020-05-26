# Overview
This repository is a combination of tutorials and various how-to(s) for
[CommsChampion Ecosystem](https://arobenko.github.io/cc). 

The tutorials are organized as a combination **tutorials/tutorialX** folders. They 
gradually introduce various concepts as well as explain various nuances for specific
use cases. The tutorials are expected to be read **sequentially**
one by one. Be patient and try to follow them through.

The how-to(s) on the other hand, do not have any particular organization. They
reside in **howtos/howtoX** folders and can be read independently. **HOWEVER**, it is
paramount to understand the core ideas explained in tutorials before attempting
to understand a particular howto example. The howto(s) are
there to provide some extra examples or cover some specific nuances which are
not explained properly in the tutorials. 

# Repository Organization
Every **tutorials/tutorialX** and **howotos/howtoX** folder may contain the following files / directories:

- **README.md** - Actual tutorial / how-to explanation markdown text that is 
intended to be made available for online reading by the repository hosting service
(github).
- **dsl** - Folder containing [CommsDSL](https://github.com/arobenko/CommsDSL-Specification)
schema file(s) relevant for the tutorial / how-to.
- **include** - Folder that contains protocol definition code 
**generated** by the [commsdsl2comms](https://github.com/arobenko/commsdsl)
tool and relevant for the tutorial.
- **src** - Folder containing code relevant to the tutorial / how-to.
- **dsl_src** - Optional folder containing extra code snippets which are 
picked up by the [commsdsl2comms](https://github.com/arobenko/commsdsl) tool
and find their way into the generated protocol definition code.

**IMPORTANT EMPHASIS**: The **include** folder of each and every **tutorials/tutorialX**
and **howtows/howtoX** is the **generated** code produced by the **commsdsl2comms** code
generation tool during the build process. Note, that it is a bad practice to
keep generated code as sources of the repository and should not be done in 
real life projects. It was done here to allow easy generated code demonstration and
references to it from the tutorial text.

The whole repository is also a CMake project which builds code of all the 
tutorials and how-to(s). Every tutorial and how-to implements both **client** 
and **server** side of the same protocol and produce **X_client** and **X_server**
binary executables (where **X** is the name of the tutorial / how-to). 
The I/O handling framework used for all the applications is 
**Boost.Asio** and TCP/IP communication was chosen for all the built client / server
applications. The relevant code is common for all the applications and is abstracted away into the
common static library (residing in the [lib](../../tree/master/lib) folder). Note, that
protocol handling and management code is completely I/O link independent and can
be used in the same way with any I/O link type.

To test the binaries of the specific tutorial, first run the **server** application
in your terminal window. It is expected to run indefinitely until manually terminated
with CTRL+C. In the second terminal window run the **client** application. In most
cases it will exchange several messages with the **server** and exit. Also in most
cases (unless specified explicitly in the tutorial/howto) is an **echo** server, it
decodes the message, re-encodes it and sends it back to the client, which does the
proper processing and display of the message contents.

# References
The core component of the [CommsChampion Ecosystem](https://arobenko.github.io/cc) is
[COMMS Library](https://github.com/arobenko/comms_champion#comms-library). Its full
tutorial and API reference can be viewed [online](https://arobenko.github.io/comms_doc) or
downloaded from latest [release artifacts](https://github.com/arobenko/comms_champion/releases).
The full tutorial on how to use the [COMMS Library](https://github.com/arobenko/comms_champion#comms-library)
resides in
[How to Use Defined Custom Protocol](https://arobenko.github.io/comms_doc/page_use_prot.html)
page of the documentation.

The **commsdsl2comms** code generator requires schema file(s) to be written in
[CommsDSL](https://github.com/arobenko/CommsDSL-Specification). The full specification
can be viewed [online](https://arobenko.gitbooks.io/commsdsl-specification/content/) or
downloaded as PDF from latest [release artifacts](https://github.com/arobenko/CommsDSL-Specification/releases).

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
