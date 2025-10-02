# The LIGNUM System
Welcome to The LIGNUM System. The *lignum-core* project 
consist of the following seven subprojects that implement 
the ubiquitous libraries and binaries in The LIGNUM System:

+ c++adt: basic ubiquitous classes
+ Firmament: Standard overcast sky (SOC) implementation
+ stl-lignum: Implementation of the elementary tree units and generic algorithms in The LIGNUM System
+ stl-voxelspace: VoxelSpace implementation
+ LEngine: L-system implementation
+ XMLTree: XML representation of a LIGNUM tree
+ qt-workbench: The LignumWb GUI application

These subprojects are used to build applications in The LIGNUM System. The 
*qt-workbench* implements `LignumWb` application to visualize simulated trees 
and inspect the content of a Lignum XML file.

## Building lignum-core with CMake
The *lignum-core* repository  and its subprojects (directories) have *CMakeLists.txt* files to build 
*lignum-core* libraries and binaries. The CMake build process for Unix Makefile system is as follows:

	git clone https://github.com/lignumsystem/lignum-core.git
	cd lignum-core
	mkdir release 
	cd release
	cmake .. -DCMAKE_BUILD_TYPE=Release
	make
	make install

### qt-workbench
The `LignumWb` GUI is an independent application to visualize Lignum trees and inspect their status.
To build `LignumWb` see the *README.md* file in the *qt-workbench* project.

#### Qt4 
The `LignumWb` workbench has been implemented with Qt4. MacPorts has only Intel binary.
Therefore Rosetta2 must be installed for Apple Silicon processors:
	
	sudo softwareupdate --install-rosetta
	sudo port install qt4-mac

>[!NOTE]
>`LignumWb` is becoming obsolete. We are making a transition to *LignumVTK* to visualize trees and 
>forest stands with ParaView.

## Building Lignum applications with CMake
The build process for the applications is also CMake based. Download the software from GitHub under the 
lignum-core directory, create the build directory and build the software. The applications should
have an accompanying README file and CMakeLists.txt for application specific compilation and usage details.

## LignumVTK
The `LignumWb` GUI program has become difficult to update and maintain.
To upgrade it from Qt4 to modern Qt5 or Qt6 application would require substantial amount of time and work. 
Because of these impediments we are making a transition from the *qt-workbench* to the *LignumVTK* project 
to visualize trees and forest plots with [ParaView](https://www.paraview.org). See LignumVTK for details.

## Operating system  requirements
The LIGNUM System applications are  developed with on macOS. 
Simulations are also made on Linux servers. We keep the 
macOS up to date, using and supporting the most recent version practicably available.

## Software requirements
The LIGNUM System software is being developed with C++ together 
with non-proprietary software packages available from the Internet.
The *lignum-core* subprojects require Xcode IDE, HDF5 and Qt5 libraries. 
In addition the *qt-workbench* requires Qt4 library. The software documentation
is in header file comments in Doxygen document generator format.

[MacPorts](https://www.macports.org) is used to install and update 
necessary software to build applications. The software installation 
instructions that follow in the examples are given with the `port` command 
in macOS Terminal.

### Xcode
Install Xcode from App Store in macOS.

### CMake
CMake  [CMake](https://cmake.org) is a popular cross-platform tool
to control the software  build process. To install CMake:

	sudo port install cmake-gui

In short the binary `cmake` reads *CMakeLists.txt* configuration files and builds 
the required build system on the target system, for example Unix Makefile system 
or Xcode project files to actually compile the project. See [tutorials](https://cmake.org/getting-started/) 
for CMake and also CMakeLists.txt files used in The Lignum System.

### HDF5 and Qt5 
HDF5 is a file format designed to store and organise (large) datasets. It used
to save simulation results including the simulated trees. Simulated trees
can be saved in XML format implemented with Qt5 cross-platform software development environment.

	sudo port install qt5
	sudo port install hdf5

### Doxygen 
Documentation of the *lignum-core* and The LIGNUM System applications 
will be done directly in the software and typsetted with Doxygen. 
The documentation uses LaTeX for typesetting mathematical equations and notations:

	sudo port install doxygen +qt5
	sudo port install doxygen-launcher
	sudo port install graphviz 
	sudo port install texlive
	sudo port install emacs-mac-app

The `doxygen-launcher` installs `doxywizard` which is a GUI editor for Doxygen 
configuration files called *Doxyfiles*. Doxygen documentations use plain LaTeX 
mathematical environment only, not external packages such as *amstex*. 
Emacs is a popular text editor in software engineering. 

To produce Doxygen software documentation for *lignum-core*:

	doxygen Doxyfile 2> errors.txt
	open  DoxygenDoc/html/index.html

In general project Doxyfiles are configured so that the HTML version of a document appears under
*DoxygenDoc* directory. 

### Python and R
#### Python
Some projects implement Python packages from C++ software and use 
for example Python `matplotlib`  package to visualize results or data structures. 
To install Python using Terminal command line, in the *lignum-core* 
directory type the following:

	sudo port install python312
	/opt/local/bin/python3.12 -m venv ~/venv/lignumsystem
	source ~/venv/lignumsystem/bin/activate
	(lignumsystem) pip install -r requirements.txt

These instructions install python3.12, create Python virtual environment and install
Python software enumerated in the *requirements.txt* file covering packages used in The LIGNUM System projects. 
The Terminal prompt prefix *(lignumsystem)* tells the corresponding Python virtual environment is active. 

In general to create a Python package from a C++ software 
defined in a *setup.py* file:
	
	(lignumsystem) python3 setup.py build_ext --inplace
	
See detailed instructions for each use case.

> [!TIP]
> The *lignumsystem* Python virtual environment is installed under home directory in the *venv* directory
> where additional virtual environments can be installed and found in one place.

#### R
[RStudio](https://posit.co/products/open-source/rstudio/) is a popular choice for R installation.
R has its own package management system. The [tidyverse](https://www.tidyverse.org) is a collection of R packages 
for data science. To install `tidyverse` in R:
	
	install.packages("tidyverse")

R is used in data analysis in The LIGNUM System. See instructions for each use case.

### Git
XCode installs `git`. However, it usually lacks behind the mainstream version
available (or close to it) in MacPorts:
	
		sudo port install git
		
See the *.gitignore* file in *lignum-core* that can be used with The LIGNUM System projects. 

### ParaView
MacPorts shows poor port health for ParaView (i.e. it is likely not in working order).
Install ParaView from [ParaView](https://www.paraview.org) home page.

---

## Publications 
To cite, please use:

### Core model

Perttunen *et al.* (1996), *Annals of Botany*, https://doi.org/10.1006/anbo.1996.0011

### Applictions

Perttunen *et al.* (2001), *Annals of Botany*, https://doi.org/10.1006/anbo.2001.1489<br>
Sievänen *et al.* (2008), *Functional Plant Biology*, https://doi.org/10.1071/FP08077<br>








