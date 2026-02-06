# The LIGNUM System
Welcome to The LIGNUM System. The *lignum-core* project 
consist of the following seven subprojects that implement 
the ubiquitous libraries and binaries in The LIGNUM System
that are used to build applications within The LIGNUM System:

+ c++adt: Basic ubiquitous classes
+ Firmament: Standard overcast sky (SOC) implementation
+ stl-lignum: Implementation of the elementary tree units and generic algorithms in The LIGNUM System
+ stl-voxelspace: VoxelSpace implementation
+ LEngine: L-system implementation
+ XMLTree: XML representation of a LIGNUM tree
+ qt-workbench: The LignumWb GUI application

The *qt-workbench* implements `LignumWb`, a separate application to visualize simulated trees 
and to inspect the content of a LIGNUM XML file.

## Operating system  requirements
The LIGNUM System and applications are developed with macOS. We use the most recent version 
pragmatically available. Ubuntu Linux is used as a secondary operating system to confirm the 
flawless use of C++ as mentioned in 
[PROGRAMMING_GUIDELINES](https://github.com/lignumsystem/lignum-core/blob/master/PROGRAMMING_GUIDELINES.md).

## CMake system and LIGNUM applications
The CMake software build system  [CMake](https://cmake.org) is used to compile
the *lignum-core* project as well as the LIGNUM applications depending on it. 

CMake  projects   are   configured  with   *CMakeLists.txt*
files. For  this CMake  has an  extensive set  of CMake  variables and
built-in functions that can be set in *CMakeLists.txt* files or given in
command line.

In short the binary `cmake` in CMake reads the *CMakeLists.txt* configuration files and creates
the required build system on the target system, for example Unix Makefile system 
or Xcode project files, to actually compile the project. See [tutorials](https://cmake.org/getting-started/) 
for CMake and CMakeLists.txt files.

The best way to  learn CMake is by studying examples.
*lignum-core* and for example *LignumForest* provide
*CMakeLists.txt* examples how to create libraries, 
find and integrate external libraries (Qt, HDF5),
create and use external binaries (for axample `l2c` to compile L-system files) 
and setup the final product with its dependenices.

### CMake for lignum-core
First, download *lignum-core*, create the CMake build directory for it and build 
the libraries and binaries in *lignum-core*.

The step by step CMake build process for Unix Makefile system is as follows:

	git clone https://github.com/lignumsystem/lignum-core.git #Download the software
	cd lignum-core
	mkdir release                       #Build directory 
	cd release
	cmake .. -DCMAKE_BUILD_TYPE=Release #Makefile release build system, no debugging
	make                                #Compilation
	make install                        #Install software components

The *Release* build type results optimized code. To generate build system for debugging 
either for Makefile system or for Xcode:

	cmake .. -DCMAKE_BUILD_TYPE=Debug #Makefile debug build system
	cmake .. -G Xcode                 #Xcode build system

The CMake software build process is analog for LIGNUM pojects depending on *lignum-core*.
For each LIGNUM application, for example *LignumForest*, download the software under the *lignum-core* 
directory, create the CMake build directory and build the software. Each appplication 
has an accompanying *README* file and necessary *CMakeList.txt* files including 
detailed instructions for compilation.

To remove all CMake configurations and compilation work simply remove the build directory and recreate it.

>[!NOTE]
>A CMake build directory can have only one build system. This means that for example 
>release and debug build types must be in their own separate build directories.

>[!NOTE] 
>The name for a build directory is chosen by the user but names like *release*, *debug* or
>*xcode* are descriptive.

## LignumWb
The `LignumWb` GUI is an independent application to visualize LIGNUM trees and inspect their status.
To build `LignumWb` see the *README.md* file in the *qt-workbench* project.

>[!IMPORTANT]
>Qt4 does not install on Apple Silicon since fall 2025.

>[!NOTE]
>`LignumWb` is becoming obsolete. Also the Qt `qmake` build tool is becoming obsolete. 
>The Qt project has switched to CMake since Qt6.

## LignumVTK
To upgrade `LignumWb` from Qt4 to modern Qt5 or Qt6 application would require substantial amount of time and work. 
Instead we are making a transition to the *LignumVTK* project to visualize trees and forest plots with
[ParaView](https://www.paraview.org). See LignumVTK for details.

## Installing the necessary software
The LIGNUM System software is being developed with C++ together 
with non-proprietary software packages available from the Internet.

[MacPorts](https://www.macports.org) can be used to install and update 
most of the necessary additional software. The MacPorts installations 
are made with the `port` command in macOS Terminal.

### Xcode
Install Xcode from App Store in macOS.

### CMake
To install CMake:

	sudo port install cmake-gui

### Qt5 and HDF5 
Simulated trees can be saved in XML format implemented with the Qt5 XML package.

HDF5 is a file format designed to store and organise large datasets. 
It is used to save simulation results including the simulated trees. 

To install Qt5 and HDF5:

	sudo port install qt5
	sudo port install hdf5

### Qt6
The current version of Qt6 6.10.1, specifically qt6-qtwebengine, uses Metal toolchain 
which is no longer bundled in Xcode 26. Install first Metal from the command line 
before installing Qt6 from MacPorts:

	sudo port selfupdate
	sudo xcodebuild -downloadComponent MetalToolchain
	sudo xcodebuild -showComponent MetalToolchain
	sudo rm -f "$(sudo --user=macports getconf DARWIN_USER_TEMP_DIR)/xcrun_db"
	
To install Qt6:
	
	sudo port install qt6
	
If the Qt6 installation fails macOS restart may be necessary to clear `xcrun` cache in Xcode.
For details see the article for [Metal toolchain](https://trac.macports.org/wiki/TahoeProblems#MetaltoolchainisnolongerbundledinXcode).

>[!NOTE]
>The XMLTree subproject is being ported to Qt6 and is not yet available.

### Qt4 
The `LignumWb` workbench has been implemented with Qt4. MacPorts has only Intel binary.
For that reason Rosetta2 must be installed for Apple Silicon processors:
	
	sudo softwareupdate --install-rosetta
	sudo port install qt4-mac
	
>[!IMPORTANT]
>Qt4 does not install on Apple Silicon fall 2025.

### Doxygen 
Documentation of the *lignum-core* and The LIGNUM System applications 
is done with Doxygen documentation blocks in the software.  LaTeX is used to 
typeset mathematical equations and notations:

	sudo port install doxygen +qt5          #doxygen with Qt5 dependency
	sudo port install doxygen-launcher      #doxygen and doxywizard GUI
	sudo port install graphviz              #Graphviz and dot for Doxygen
	sudo port install texlive +full         #LaTeX full installation
	

The `doxygen-launcher` installs both `doxygen` and `doxywizard` the latter being 
a GUI editor for Doxygen configuration files called *Doxyfiles*. `doxygen`
uses the layout program `dot` from the `graphviz` port to produce visual information 
as graphs and network diagrams for example for function call dependencies 
and inverse dependencies, class hierarchies and interdependencies as well
as file interconnections due to include statements. 

Doxygen documentations use the built-in LaTeX mathematical environment only. 
Auxiliary packages such as *amstex* are not used.

To produce Doxygen software documentation use the project Doxyfile:

	doxygen Doxyfile 2> errors.txt
	open  DoxygenDoc/html/index.html

Project Doxyfiles are configured so that the final document appears under
the *DoxygenDoc* directory. 

### Emacs
Emacs is a popular text editor in software engineering.

	sudo port install emacs-app -nativecomp #Emacs text editor without nativecomp 
	
>[!NOTE]
>MacPorts emacs-app is broken fall 2025. 
>MacPorts emacs-mac-app with better macOS integration is broken fall 2025.
>Download and install Emacs from the [official web site](https://www.gnu.org/software/emacs/).

### Python
Some LIGNUM projects implement Python packages from C++ software and use 
for example Python `matplotlib`  package to visualize results or data structures. 

To install Python type the following:

	sudo port install python312
	/opt/local/bin/python3.12 -m venv ~/venv/lignumsystem #Create virtual environment
	source ~/venv/lignumsystem/bin/activate               #Activate the virtual environment
	(lignumsystem) pip install -r requirements.txt        #In lignum-core directory

These instructions install python3.12, create Python virtual environment and install additional
Python software specified in the [requirements.txt](https://github.com/lignumsystem/lignum-core/blob/master/requirements.txt) 
file. The Terminal prompt prefix *(lignumsystem)* tells the corresponding 
Python virtual environment is active. 

Create a Python package from a C++ software defined in a *setup.py* file found in a working directory:
	
	(lignumsystem) python3 setup.py build_ext --inplace
	
See instructions for each use case.

> [!TIP]
> The *lignumsystem* Python virtual environment is installed under home directory in the *venv* directory
> where additional virtual environments can be installed and found in one place.

### R
[RStudio](https://posit.co/products/open-source/rstudio/) is a popular choice for R GUI
and has instructions for R system installation.

The [tidyverse](https://www.tidyverse.org) is a collection of R packages 
for data science. To install `tidyverse` in R:
	
	install.packages("tidyverse")

R is used in data analysis in The LIGNUM System. See instructions for each use case.

### Git
XCode installs `git`. However, it usually lacks behind the mainstream version
or close to it available in MacPorts:
	
		sudo port install git
		
See the [.gitignore](https://github.com/lignumsystem/lignum-core/blob/master/.gitignore) file 
in *lignum-core* that can be used with The LIGNUM System projects. 

### ParaView
MacPorts shows poor port health for ParaView (i.e. it is likely not in working order).
Install ParaView from [ParaView](https://www.paraview.org) home page.

## Litterature to cite the LIGNUM model

### Core model
To refer to the LIGNUM model in general:

Perttunen *et al.* (1996), *Annals of Botany*, https://doi.org/10.1006/anbo.1996.0011

### Applictions
Choose the relevant publication, for example:

Perttunen *et al.* (2001), *Annals of Botany*, https://doi.org/10.1006/anbo.2001.1489<br>
Sievänen *et al.* (2008), *Functional Plant Biology*, https://doi.org/10.1071/FP08077<br>








