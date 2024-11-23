# lignum-core

Welcome to the *lignum-core* repository. The *lignum-core* implements the ubiquitous libraries and binaries 
in The LIGNUM System in seven projects:

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

## System requirements
The Lignum model is developed on macOS and simulations are also made on Linux servers.
The *lignum-core* base requires HDF5 and Qt5 libraries. With [MacPorts](https://www.macports.org) 
installations are straightforward:

	sudo port install hdf5
	sudo port install qt5

Simulation results can be saved in HDF5 files including Lignum trees in XML format. 
See *LignumForest* as an example. In addition the *Doxygen* system is used 
for software  documentation:

	sudo port install doxygen +qt5
	sudo port install doxygen-launcher
	sudo port install graphviz 
	
The LignumWB workbench has been implemented with Qt4. *MacPorts* has only Intel binary.
Therefore Rosetta2 must be installed for Apple Silicon processors:
	
	sudo softwareupdate --install-rosetta
	sudo port install qt4-mac
	
Emacs is a popular text editor in software engineering and LateX common document preparation system,
especially in engineering sciences.

	sudo port install emacs-mac-app
	sudo port install texlive +full
	
The *+full* variant for *texlive* means full installation that will take several gigabytes of disk space.
Naturally, there are other ways to install the required software.

# Documentation

## Compilation with CMake

The *lignum-core* repository  and its projects (directories) have *CMakeLists.txt* files to build 
*lignum-core* libraries and binaries.  The CMake build process for Unix Makefile systen is as follows:

	cd lignum-core
	mkdir release #Immediately under lignum-core directory
	cd release
	cmake .. -DCMAKE_BUILD_TYPE=Release
	make
	make install
	      
The  `cmake`  program  instructs  compiler to  create  Release  version,
i.e. without debugging information. To corresponding option to create 
Debug version is `-DCMAKE_BUILD_TYPE=Debug` . The `cmake ..` command expects to
find the top level *CMakeLists.txt*  in the immediate directory above.
Note also that *all* build  products are under *release* directory. To
move them  to proper locations  defined in CMakeLists.txt  files `make
install` is needed.

Different directories for different build types (Degub, Release) must be used because they cannot 
coexists under the same directory. CMake has hundred or so
[CMake system built-in variables](https://cmake.org/cmake/help/latest/manual/cmake-variables.7.html) 
that describe the operating system,  control the build process, provide information during the build etc.

>[!NOTE]
>The `make` or `make install` commands are necessary to allow projects depending on *lignum-core* to 
>find and use libraries and binaries in *lignum-core* via their CMakeLists.txt files.

>[!CAUTION]
>Qt4 seems to be ever more difficult to maintain in MacPorts. 

>[!WARNING]
>Apple Silicon processors (M1, M2, etc.), macOS Ventura and later require Qt5  with XMLTree. *qt-workbench* cannot be compiled 
>and used with Qt5 because of the backward incompatibilites between the Qt4 and Qt5 versions. 

To install Qt5 Toolkit from MacPorts type:

	    sudo port install qt5

## Projects using lignum-core

To create LignumForest Release version Unix Makefile build system type:

	cd lignum-core
	git clone https://github.com/lignumsystem/LignumForest.git #Immediately under lignum-core directory
	cd LignumForest
	mkdir release #Immediately under LignumForest directory
	cd release
	cmake .. -DCMAKE_BUILD_TYPE=Release
	make
	make install 

To build Xcode project files for debugging:

	mkdir xcode #Immediately under LignumForest directory
	cd xcode
	cmake .. -G Xcode

Open the *xcode/lignum-forest.xcodeproj* file in Xcode. If  Xcode &#8594; Product &#8594; Run is disabled 
check Xcode &#8594; Product  &#8594; Scheme that the binary `crowndens` is selected, not for example ALL_BUILD. 

The  binary `lignum-forest`  is located  in xcode/Debug  directory. It
needs  function files  (*.fun*) and  configuration (*.txt*)  files for
simulations. Such  files must  be copied  to xcode/Debug  directory in
order  to let  `lignum-forest` to  find  them.  Another  option is  to
manually move the  binary *xcode/Debug/`lignum-forest`* to LignumForest
directory  and explicitely  set  the binary  in  XCode: XCode  &#8594;
Debug&#8594; Debug  Executable. 

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








