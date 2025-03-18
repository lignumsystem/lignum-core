# The LIGNUM System
Welcome to The LIGNUM System. The *lignum-core* project 
consist of the following seven subprojects that implement 
the ubiquitous libraries and binaries in The LIGNUM System :

+ c++adt: basic ubiquitous classes
+ Firmamanet: Standard overcast sky (SOC) implementation
+ stl-lignum: Implementatetation of the elementary tree units in The LIGNUM System
+ stl-voxelspace: VoxelSpace implementation
+ LEngine: L-system implementation
+ XMLTree: XML representation of the LIGNUM tree
+ qt-workbench: The LignumWb GUI application

These seven subprojects are used to build applications in The LIGNUM System.

### Building lignum-core with CMake
The *lignum-core* repository  and its subprojects (directories) have *CMakeLists.txt* files to build 
*lignum-core* libraries and binaries.  The CMake build process for Unix Makefile system is as follows:

	git clone https://github.com/lignumsystem/lignum-core.git
	cd lignum-core
	mkdir release 
	cd release
	cmake .. -DCMAKE_BUILD_TYPE=Release
	make
	make install
	    
The build process for the applications is the same. Download the software, create the build directory and
build the software.

## Operating system  requirements
The LIGNUM System applications are  developed with on macOS. 
Simulations are also made on Linux servers. We keep the 
macOS up to date, using the most recent version practicably available.

## Software requirements
The LIGNUM System software is being developed with C++ together 
with non-proprietary software packages available from the Internet.
The *lignum-core* subprojects require Xcode IDE, HDF5 and Qt5 libraries. 
In addition the *qt-workbench* requires Qt4 library. The software documentation
is uses Doxygen document generator.

[MacPorts](https://www.macports.org) is used to install and update 
necessary software to build applications. The software installation 
instructions that follow are given with the `port` command 
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

### Qt4 
The `LignumWb` workbench has been implemented with Qt4. MacPorts has only Intel binary.
Therefore Rosetta2 must be installed for Apple Silicon processors:
	
	sudo softwareupdate --install-rosetta
	sudo port install qt4-mac

To build `LignumWb` see the README.md file in qt-workbench.

### Doxygen 
Documentation of the *lignum-core* and applications  will be done directly in the software 
and typsetted with Doxygen. The documentation uses also LaTeX for typesetting 
mathematical notations.

	sudo port install doxygen +qt5
	sudo port install doxygen-launcher
	sudo port install graphviz 
	sudo port install texlive
	sudo port install emacs-mac-app

The `doxygen-launcher` installs `doxywizard` which is a GUI editor for Doxygen 
configuration files called *Doxyfile*s. Emacs is a popular text editor in software engineering. 

The documentation uses plain LaTeX mathematical environment only, not external packages such as *amstex*. 

To produce Doxygen software documentation for lignum-core:

	doxygen Doxyfile 2> errors.txt
	open  DoxygenDoc/html/index.html

Doxyfiles are configured so that the HTML version of the document appears under
DoxygenDoc directory. This convention applies to The LIGNUM System applications too. 

### Python and R
#### Python
Some projects implement Python packages and can use for example Python `matplotlib`  
to visualize results. From the Terminal command line type:

	sudo port install python312
	/opt/local/bin/python3.12 -m venv ~/venv/lignumsystem
	source ~/venv/lignumsystem/bin/activate
	(lignumsystem) pip install -r requirements.txt

These instructions install python3.12, create Python virtual environment and install
Python software in *requirements.txt*. The Terminal prompt prefix *(lignumsystem)* tells the 
Python virtual envronment is active. In general to create a Python package from a C++ software 
defined in *setup.py* file:
	
	(lignumsystem) python3 setup.py build_ext --inplace
	
See instructions for each use case.

> [!TIP]
> The Python virtual environment is installed in *venv* directory under home directory.
> In this way the virtual environments are collected in one place.

#### R
[RStudio](https://posit.co/products/open-source/rstudio/) is a popular choice for R installation.
R has its own package management system. The [tidyverse](https://www.tidyverse.org) is collection of R packages 
for data science. To install tidyverse in R:
	
	install.packages("tidyverse")

R is used in data analysis in The Lignum System. See instructions for each use case.

### Git
See the .gitignore file that can be used with The LIGNUM System projects. 

## Publications 
To cite, please use:

### Core model

Perttunen *et al.* (1996), *Annals of Botany*, https://doi.org/10.1006/anbo.1996.0011

### Applictions

Perttunen *et al.* (2001), *Annals of Botany*, https://doi.org/10.1006/anbo.2001.1489<br>
Sievänen *et al.* (2008), *Functional Plant Biology*, https://doi.org/10.1071/FP08077<br>








