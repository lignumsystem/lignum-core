# lignum-core

Welcome to the lignum-core repository. The lignum-core implements the ubiquitous classes in The LIGNUM System

+ c++adt: basic ubiquitous (abstract) classes
+ Firmamanet: Implementation of the hemisphere
+ stl-lignum: Implementatetation of the elementry tree units in LIGNUM
+ stl-voxelspace: VoxelSpace implementation
+ LEngine: L-system implementation
+ qt-workbench: The GUI implementation

# Requirements

System requirements to follow

# Documentation

## Compilation

Each lignum-core subdirectory and the main project have had Qt project (pro) files to compile.
The main project must tell in its Qt project file the location of the lignum-core. We have traditionally
had the main project at the same level as lignum-core directories.

[CMake](https://cmake.org) cross-platform build tool has gained popularity recent years. 
One of the reasons is that it supports many IDE tools including Xcode. The lignum-core project 
and its subprojects (directories) have *CMakeLists.txt* files to build lignum-core libraries and binaries. 
Traditionally the CMake build process has been as follows:

	      mkdir build #Immediately under lignum-core directory
	      cd build
	      cmake ..
	      make
	      make install
	      
This generates Unix Makefile build system and instructs compiler to add Debug information. 
The `cmake ..` command assumes that the *CMakeLists.txt* is in the immediate directory above. 
Note also that all build products are under *build* directory. To move them to proper locations
defined in CMakeLists.txt files `make install` is needed.

CrownDensity project has CMakeLists.txt that uses lignum-core projects and well known libraries (Qt, HDF5)
to build the project. To build Xcode project files for debugging:

   	      mkdir xcode #Immediately under CrownDensity directory
	      cd xcode
	      cmake .. -G Xcode

Use different directory names for different build types because they cannot coexists under the same directory.
Open the *xcode/crowndens.xcodeproj* file in Xcode. If in Xcode &#8594; Product &#8594; Run is disabled 
check Xcode &#8594; Product  &#8594; Scheme that the binary `crowndens` is selected, not for example ALL_BUILD. 

The binary `crowndens` is located in xcode/Debug directory. It has for example hard coded locations 
for function file (*.fun*) names and configuration (*.txt) files. Such files must be copied 
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

The CMAKE_BUILD_TYPE is just one of the many (a hundred or so)
[CMake system built-in variables](https://cmake.org/cmake/help/latest/manual/cmake-variables.7.html) 
that can describe the operating system,  control the build process, provide information during the build etc.


## Doxygen
Sofwtare is usually under constant development and frequent changes. Detailed documentation of the lignum-core 
and projects using it will be done with Doxygen using extensive commenting directly in the software.
An outline of the lignum-core model structure can be found in the publications listed below.

# Publications 

**Core model**:

To cite, please use: Perttunen *et al.* (1996), *Annals of Botany*, https://doi.org/10.1006/anbo.1996.0011

**Applictions**:

Perttunen *et al.* (2001), *Annals of Botany*, https://doi.org/10.1006/anbo.2001.1489

Sievänen *et al.* (2008), *Functional Plant Biology*, https://doi.org/10.1071/FP08077








