# The LIGNUM System
The following six projects implement *lignum-core* libraries and binaries 
that are used to build applications in the LIGNUM system:

+ c++adt: Basic general purpose classes
+ Firmament: Standard overcast sky (SOC)
+ stl-lignum: LIGNUM tree, tree parts and generic algorithms
+ stl-voxelspace: Voxel space 
+ LEngine: L-system 
+ XMLTree: XML representation of a LIGNUM tree

The qt-workbench and `LignumWb` application, for visualizing simulated trees,
are now obsolete. Because `LignumWb` relies on Qt4 - which lacks support for Apple Silicon - 
it has been incompatible with macOS since the release of macOS Tahoe.
`LignumWb` has been superseded by LignumVTK.

## Operating system requirements
The LIGNUM system is developed for macOS, with Ubuntu Linux used to verify software portability.

## Install required software
The LIGNUM system and its applications require third-party software, which is 
freely available from the respective developer websites or software package managers. 
The installation examples are for macOS and the package manager is 
[MacPorts](https://www.macports.org). 

### Xcode
Xcode is the integrated development environment (IDE) for macOS. 
Download and install Xcode from App Store. Install also command line tools:

	sudo xcode-select --install

### MacPorts
Install from [MacPorts](https://www.macports.org) website. Once installed
use the `port` command line interface in Terminal for package management.

### CMake
Use CMake to manage the configuration and build process for lignum-core and 
its associated LIGNUM applications. In MacPorts, CMake is available in 
two main versions:

	sudo port install cmake       #CMake 3.x
	sudo port install cmake-devel #CMake 4.x

`cmake` is the standard, stable release version and `cmake-devel` tracks the latest features and changes.

### HDF5
[HDF5](https://www.hdfgroup.org) is a file format designed to store and organise large datasets. 
It is used to save simulation configuration and results including the simulated trees:

	sudo port install hdf5
	
### Qt
[Qt](https://www.qt.io) and its QtXML module is used to save and read simulated trees in XML format. 
Both Qt5 and Qt6 can be used.

#### Qt5 
Qt5 installation is straightforward:

	sudo port install qt5
	
#### Qt6
Qt6 installation is more complex because the `qt6-qtwebengine` uses Metal toolchain,
which is no longer bundled with Xcode 26. First, install Metal:

	sudo port selfupdate
	sudo xcodebuild -downloadComponent MetalToolchain
	sudo xcodebuild -showComponent MetalToolchain
	sudo rm -f "$(sudo --user=macports getconf DARWIN_USER_TEMP_DIR)/xcrun_db"
	
To install Qt6:
	
	sudo port install qt6
	
If Qt6 installation fails, try restarting Mac; this clears the `xcrun` cache in Xcode, 
which often resolves the issue. The instructions for Qt6 are from the article for 
[Metal toolchain](https://trac.macports.org/wiki/TahoeProblems#MetaltoolchainisnolongerbundledinXcode).

### LignumVTK and VTK
LignumVTK now replaces `LignumWb` for visualization. The VTK Visualization Toolkit converts 
LIGNUM trees and voxel space data into VTK files for final visualization in [ParaView](https://www.paraview.org).
To install VTK:

	sudo port install vtk

### ParaView
ParaView is the open source post-processing visualization program. 
Install from [ParaView](https://www.paraview.org) home page.

### Doxygen 
Documentation of the *lignum-core* and the LIGNUM system applications 
is done with Doxygen documentation blocks in the software.  LaTeX is used to 
typeset mathematical equations and notations:

	sudo port install doxygen +qt5     #doxygen with Qt5 dependency
	sudo port install doxygen-launcher #doxygen and doxywizard GUI
	sudo port install graphviz         #Graphviz and dot for Doxygen figures
	sudo port install texlive +full    #LaTeX full installation 

Doxygen documentation uses the built-in LaTeX mathematical environment only. 
Auxiliary packages such as *amstex* are not used.

To produce Doxygen software documentation use the project Doxyfile:

	doxygen Doxyfile 2> errors.txt
	open  DoxygenDoc/html/index.html   #Final documentation

Project Doxyfiles specify *DoxygenDoc* as the destination for final documents. 

### Python
Some projects expose C++ software as Python packages. Install Python,
create Python virtual environment and install Python packages:

	sudo port install python312                           #Python 3.12 example
	/opt/local/bin/python3.12 -m venv ~/venv/lignumsystem #Create virtual environment
	source ~/venv/lignumsystem/bin/activate               #Activate the virtual environment
	(lignumsystem) pip install -r requirements.txt        #Install required python packages

For the LIGNUM system, the [requirements.txt](https://github.com/lignumsystem/lignum-core/blob/master/requirements.txt) 
file defines the commonly used packages. 

The build process for C++ extensions is in *setup.py* files:
	
	(lignumsystem) python3 setup.py build_ext --inplace
	
See instructions for each use case.

> [!TIP]
> The *lignumsystem* virtual environment is in the *~/venv* directory, where
> the tilde (~) denotes home directory. Centralizing environments this way makes 
> them easier to manage and locate.

### R
R is used in data analysis in the LIGNUM system. [RStudio](https://posit.co/products/open-source/rstudio/) 
is a popular choice and it has instructions for R system installation.

The [tidyverse](https://www.tidyverse.org) is a collection of R packages 
for data science:
	
	install.packages("tidyverse") #Function in R

RStudio features a built-in GUI that simplifies package management and installation.

## Building The LIGNUM System applications
The lignum-core project and its applications are built using the [CMake](https://cmake.org) 
build system. The CMake build process consists of four phases:

+ Create a build directory: This keeps the source tree clean.
+ Generate the build system: CMake inspects the CMakeLists.txt files.
+ Compile the project: Create binaries and libraries.
+ Install the project (optional): Copy binaries and libraries to install locations.

CMake features hundreds of built-in functions and variables for customizing build systems.
It also integrates popular software packages, making it easy to incorporate external dependencies.
See [tutorials](https://cmake.org/getting-started/) for CMake and CMakeLists.txt files.

### CMake example for lignum-core
To build lignum-core using Unix Makefiles, follow these steps:

	git clone https://github.com/lignumsystem/lignum-core.git #Download the software
	cd lignum-core
	mkdir release                       #Build directory 
	cd release
	cmake .. -DCMAKE_BUILD_TYPE=Release #Makefile release build system.
	make                                #Compile
	make install                        #Install software components

The *Release* build system results optimized code. To generate *Debug* build system
either for Makefile system or for Xcode:

	cmake .. -DCMAKE_BUILD_TYPE=Debug #Makefile debug build system
	cmake .. -G Xcode                 #Xcode build system

The `make clean` command clears the build environment to ensure all changes 
are captured during recompilation. To reset the build, simply remove the build 
directory and recreate it.

> [!NOTE]
> Each CMake build directory is limited to one build configuration. This means that
> different build configurations must be in separate build directories.
> Choose descriptive names like *release*, *debug* or *xcode* for these directories.

### Emacs
Emacs is a popular text editor in software engineering. Download and install
from the [official web site](https://www.gnu.org/software/emacs/).

## Programming guidelines
The concise [PROGRAMMING_GUIDELINES](https://github.com/lignumsystem/lignum-core/blob/master/PROGRAMMING_GUIDELINES.md)
highlights key aspects for implementing LIGNUM applications. 

## Litterature to cite the LIGNUM model

### Core model
To refer to the LIGNUM model in general:

Perttunen *et al.* (1996), *Annals of Botany*, https://doi.org/10.1006/anbo.1996.0011

### Applictions
Choose the relevant publication, for example:

Perttunen *et al.* (2001), *Annals of Botany*, https://doi.org/10.1006/anbo.2001.1489<br>
Sievänen *et al.* (2008), *Functional Plant Biology*, https://doi.org/10.1071/FP08077<br>








