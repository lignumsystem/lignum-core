# lignum-core

Welcome to the lignum-core repository. The lignum-core implements the ubiquitous classes in The LIGNUM System

	+ c++adt: basic ubiquitous (abstract) classes
	+ Firmamanet: Implementation of the hemispheren standard overcast sky (SOC) 
	+ stl-lignum: Implementatetation of the elementry tree units in LIGNUM
	+ stl-voxelspace: VoxelSpace implementation
	+ LEngine: L-system implementation
 	+ XMLTree: XML representation of the Lignum tree
	+ qt-workbench: The LignumWB GUI implementation

# Requirements

## CMake

CMake  [CMake](https://cmake.org) is a popular cross-platform build tool perhaps
becoming *de facto* standard  to control the software  build and compilation process 
using platform and compiler independent configuration files called *CMakeLists.txt*. 

In short the binary `cmake` reads *CMakeLists.txt* configuration files and builds 
the required build system on the target system, for example Unix Makefile system 
or Xcode project files, to then actually compile the project. There are only 
*CMakeLists.txt* configuration files. If necessary for the build process a CMakeLists.txt 
has instructions for `cmake` to read other CMakeLists.txt files.

CMake may feel overwhelming with steep learning curve at first. The best way to 
learn it is to look at the examples with [tutorials](https://cmake.org/getting-started/).
The *lignum-project* has CMakeLists.txt files to build libraries and binaries. 
The actual modelling projects like *CrownDensity* show how to use and link these dependency 
libraries and binaries as well as how to use external libraries (e.g. HDF5 and Qt4/Qt5). 

Simple programming language in CMake allows conditional (e.g. platform
specific) execution of configuration definitions in  CMakeLists. CMake has also many 
(hundreds of) variables and built-in functions that can be used to control the software build process.

It is custom that all build processes with `cmake` and the actual compilation of a project
takes place in one build directory. There `cmake` is given necessary command line options including 
the directory of the first main CMakeLists.txt file, traditionally one directory level above 
the build directory.

## System requrements
System requirements to follow. In short, we develop on macOS and run simulations also on Linux servers.

# Documentation

## Compilation with CMake

The *lignum-core* project  and its subprojects (directories) have *CMakeLists.txt* files to build 
lignum-core libraries and binaries.  The CMake build process is as follows:

	mkdir build #Immediately under lignum-core directory
	cd build
	cmake ..
	make
	make install
	      
This generates Unix Makefile build system and instructs compiler to add Debug information. 
The `cmake ..` command assumes that the *CMakeLists.txt* is in the immediate directory above. 
Note also that all build products are under *build* directory. To move them to proper locations
defined in CMakeLists.txt files `make install` is needed.

Each lignum-core subdirectory and the main project have had Qt project (pro) files to compile.
The main project must tell in its Qt project file the location of the lignum-core. We have traditionally
had the main project at the same level as lignum-core directories.

>[!IMPORTANT]
>Qt4 seems to be ever more difficult to maintain in MacPorts. 

Apple Silicon processors (M1, M2, etc.), macOS Ventura and later require Qt5  with XMLTree. *qt-workbench* cannot be compiled 
and used with Qt5 because of the backward incompatibilites between the Qt4 and Qt5 versions. To install Qt5 Toolkit 
from MacPorts type:

	    sudo port install qt5

## Projects using lignum-core

As an example clone CrownDensity and LignumForest projects immediately under lignum-core and compile. CrownDensity has CMakeLists.txt that
defines how to use lignum-core projects and well known libraries (Qt, HDF5) to build the project. To build Xcode project files for debugging:

	git clone https://github.com/lignumsystem/CrownDensity.git #Immediately under lignum-core directory
	git clone https://github.com/lignumsystem/LignumForest.git #Immediately under lignum-core directory
	mkdir xcode #Immediately under CrownDensity directory
	cd xcode
	cmake .. -G Xcode

Open the *xcode/crowndens.xcodeproj* file in Xcode. If in Xcode &#8594; Product &#8594; Run is disabled 
check Xcode &#8594; Product  &#8594; Scheme that the binary `crowndens` is selected, not for example ALL_BUILD. 

The binary `crowndens` is located in xcode/Debug directory. It has for example hard coded locations 
for function file (*.fun*) names and configuration (*.txt*) files. Such files must be copied 
to xcode/Debug directory in order to let `crowndens` to fine them. Another option is to manually
move the binary *xcode/Debug/`crowndens`* to CrownDens directory and explicitely set the binary in
XCode &#8594; Debug &#8594; Debug Executable. There are no Unix Makefiles available 
in the generated Xcode build system.

As the third example to create CrownDensity Release version Unix Makefile build system 
(optimization, no debug information):

	mkdir release #Immediately under CrownDensity directory
	cd release
	cmake .. -DCMAKE_BUILD_TYPE=Release
	make
	make install 

Use different directories for different build types (degub, release) because they cannot coexists under the same directory.
The CMAKE_BUILD_TYPE is just one of the many (a hundred or so)
[CMake system built-in variables](https://cmake.org/cmake/help/latest/manual/cmake-variables.7.html) 
that can describe the operating system,  control the build process, provide information during the build etc.

## Doxygen
Software is usually under constant development and frequent changes. Detailed documentation of the lignum-core 
and projects using it will be done with Doxygen using extensive commenting directly in the software.
An outline of the lignum-core model structure can be found in the publications listed below.

# Publications 

**Core model**:

To cite, please use: Perttunen *et al.* (1996), *Annals of Botany*, https://doi.org/10.1006/anbo.1996.0011

**Applictions**:

Perttunen *et al.* (2001), *Annals of Botany*, https://doi.org/10.1006/anbo.2001.1489

Sievänen *et al.* (2008), *Functional Plant Biology*, https://doi.org/10.1071/FP08077








