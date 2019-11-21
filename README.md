# Overview
This repository is a combination of tutorials and various how-to(s) for
[CommsChampion Ecosystem](https://arobenko.github.io/cc). 

The tutorials are organized as a combination **tutorialX** folders. They 
gradually introduce various concepts and expected to be read sequentially 
one by one. 

The how-to(s) on the other hand, do not have any particular organization. They
reside in **howtoX** folders and can be read independently. The howto(s) are
there to provide some extra examples or cover some specific nuances which are
not explained properly in the tutorials. 

# Repository Organization
Every **tutorialX** and **howtoX** folder may contain the following files / directories:

- **README.md** - Actual tutorial / how-to explanation markdown text that is 
intended to be made available for online reading by the repository hosting service
(github).
- **dsl** - Folder containing [CommsDSL](https://github.com/arobenko/CommsDSL-Specification)
schema file(s) relevant for the tutorial / how-to.
- **include** - Folder that contains protocol definition code 
**generated** (by the [commsdsl2comms](https://github.com/arobenko/commsdsl)
tool and relevant for the tutorial.
- **src** - Folder containing code relevant to the tutorial / how-to.
- **dsl_src** - Optional folder containing extra code snippets which are 
picked up by the [commsdsl2comms](https://github.com/arobenko/commsdsl) tool
and find their way into the generated protocol definition code.

**IMPORTANT EMPHASIS**: The **include** folder of each and every **tutorialX**
and **howtoX** is the **generated** code produced by the **commsdsl2comms** code
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
common static library (residing in the [lib](tree/master/lib) folder).

To test the binaries of the specific tutorial, first run the **server** application
in your terminal window. It is expected to run indefinitely until manually terminated
with CTRL+C. In the second terminal window run the **client** application. In most
cases it will exchange several messages with the **server** and exit.

