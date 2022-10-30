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

Traditionally each lignum-core subdirectory and the main project have had Qt project (pro) files to compile.
The main project must tell in its Qt project file the location of the lignum-core. We have traditionally
had the main project at the same level as lignum-core directories.

CMake build tool has gained popularity recent years. One of the reasons is that it supports many IDE tools
including Xcode. lignum-core projects (directories) have *CMakeLists.txt* files to build the projects.
Traditionally the CMake build process has been as follows:

	      mkdir build
	      cd build
	      cmake ..
	      make

The `cmake ..` command assumes that the *CMakeLists.txt* is in the immediate directory above. To build Xcode project files:

   	      mkdir xcode
	      cd xcode
	      cmake .. -G Xcode

Use different directory because configuration files for traditional builld and Xcode build cannot exist in the same directory.
Open the *xcodeproj* file in Xcode. If in Xcode Product &#8594; Run is disabled check Product  &#8594; Scheme
that the binary is selected, not for example ALL_BUILD. The binary is in xcode/Debug. Depending on the implementation
the binary might have for example hard coded function file (*.fun*) names. Such files must be copied accordingly related to xcode/Debug directory.

As an example CrownDensity project has CMakeLists.txt that uses lignum-core projects and well known libraries (Qt, HDF5)
to build the project. So far downsize is that each lignum-core project must be built one at a time. Yours truly
haven't learnt (yet) how to create build rules for imported (lignum-core) projects.

Detailed documentation to follow. An outline of model structure can be found in the publications listed below.

Doxygen will be used to document software. 

# Publications 

**Core model**:

To cite, please use: Perttunen *et al.* (1996), *Annals of Botany*, https://doi.org/10.1006/anbo.1996.0011

**Applictions**:

Perttunen *et al.* (2001), *Annals of Botany*, https://doi.org/10.1006/anbo.2001.1489

Sievänen *et al.* (2008), *Functional Plant Biology*, https://doi.org/10.1071/FP08077








