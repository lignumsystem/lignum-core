# The LIGNUM System
At the heart of the LIGNUM system is *lignum-core*. It currently consists of seven projects, 
providing the foundational libraries and binaries necessary to build LIGNUM applications.

```
lignum-core
├── Firmament:      Standard overcast sky (SOC) 
├── LEngine:        Lindenmayer system 
├── XMLTree:        LIGNUM tree XML representation 
├── c++adt:         General purpose classes
├── qt-workbench:   LignumWb application for tree visualization
├── stl-lignum:     LIGNUM tree and generic algorithms
└── stl-voxelspace: Voxel space

7 directories
```
macOS 27 Golden Gate marks the final stop for Intel apps. As a result, qt-workbench and its `LignumWb` 
application will be removed; they rely on Qt4, which does not support Apple silicon. `LignumWb` has been
superseded by LignumVTK.

## Operating system requirements
The LIGNUM system is developed for macOS, with Ubuntu Linux used to verify software portability.

## Install required software
The LIGNUM system and its applications require third-party software, which is 
freely available from the respective developer websites or software package managers. 
The installation examples are for macOS and the package manager is 
[MacPorts](https://www.macports.org). 

### Xcode
Xcode is the integrated development environment (IDE) for macOS
and provides C++ toolchain. Download and install Xcode from App Store. 
Install also command line tools:

	sudo xcode-select --install

Xcode is a mandatory dependency for the MacPorts system.

### MacPorts
Install MacPorts from [MacPorts](https://www.macports.org) website. Once installed
use the `port` command line interface in Terminal for package management.

To list available ports for a specific program or library use the following template,
for example list all Python versions supported:

	 port search --name --line --regex '^python\d*$'
	 
Query *notes* or *info* for quick package details, for example:

	port notes python314
	port info python314

Each major macOS release requires new macOS-specific MacPorts version and updated packages.
Fortunately, existing installed ports remain functional and usable during this transition,
allowing this migration to be made at a more convenient or appropriate time. Indeed, waiting
allows some time for package compatibility updates.

To remove all installed packages and compilation work:

	sudo port uninstall installed
	sudo port reclaim
	
This leaves only the MacPorts  installation and configuration on the system.

### CMake
Use CMake to manage the configuration and build process for lignum-core and 
its associated LIGNUM applications. In MacPorts, CMake is available in 
two main versions:

	sudo port install cmake       #CMake 3.x
	sudo port install cmake-devel #CMake 4.x

`cmake` is the stable release version and `cmake-devel` tracks the latest features and changes.
These packages are mutually exclusive; you can only install one.

### HDF5
[HDF5](https://www.hdfgroup.org) files act like a file system within a single file,
using a hierarchical structure to store large self-documenting datasets. This standardized
storage format is used to save simulation configuration and results, including the
simulated trees:

	sudo port install hdf5
	
HDF5 facilitates seamless data analysis for high-level languages like R or Python. 
Both offer dedicated packages — `rhdf5` and `h5py`, respectively — that implement the 
HDF5 API for reading, writing, and inspecting data.

### Qt Toolkit
Simulated trees are saved and read in XML format implemented with the [Qt XML module](https://doc.qt.io/qt-6/qtxml-index.html),
ensuring compatibility with both Qt5 and Qt6. The Qt XML module module is part of the foundational ports
`qt5-qtbase` and `qt6-qtbase`:

	sudo port install qt5-qtbase #Qt5 version
	sudo port install qt6-qtbase #Qt6 version

MacPorts allows both Qt5 and Qt6 to co-exists.

Optionally, both Qt5 and Qt6 have *meta-ports* that will trigger the installation of the whole
Qt library system. The Qt5 installation is straightforward:

	sudo port install qt5 #Qt5 libraries and headers
	
Qt6 installation is more complex because the `qt6-qtwebengine` uses Metal toolchain,
which is no longer bundled with Xcode 26. First, install Metal:

	sudo port selfupdate
	sudo xcodebuild -downloadComponent MetalToolchain
	sudo xcodebuild -showComponent MetalToolchain
	sudo rm -f "$(sudo --user=macports getconf DARWIN_USER_TEMP_DIR)/xcrun_db"

To install Qt6:

	sudo port install qt6 #Qt6 libraries and headers

If Qt6 installation fails, try restarting Mac; this clears the `xcrun` cache in Xcode, 
which may resolve the issue (see [Metal toolchain](https://trac.macports.org/wiki/TahoeProblems#MetaltoolchainisnolongerbundledinXcode)).

#### Failed to build qt5-qtwebengine: command execution failed
This error can occur because of an incompatibility between modern Apple Clang compilers
and older Chromium source code embedded inside qt5-qtwebengine. Use an older `clang-17`
bundled with MacPorts. 

	sudo port install clang-17
	sudo port clean qt5-qtwebengine
	sudo port install qt5-qtwebengine

#### Error: Failed to destroot qt6-qtwebengine: xinstall:
This error occurs because MacPorts' staging system (`xinstall`) attempts to copy compiled files into
the destination directory (destroot) before the required nested folder path for QtWebEngineCore.framework
resources has been created. MacPorts does not generate this directory structure automatically.

Solution: create the necessary folder path in the error message manually, for example:

	sudo mkdir -p /opt/local/var/macports/build/qt6-qtwebengine-e1fa6a31/work/destroot/opt/local/libexec/qt6/lib/QtWebEngineCore.framework/Resources/

### LignumVTK and VTK
LignumVTK now replaces `LignumWb` for visualization. The [VTK](https://vtk.org) Visualization Toolkit converts 
LIGNUM trees and voxel space data into VTK files for final visualization in [ParaView](https://www.paraview.org).
To install VTK:

	sudo port install vtk

### ParaView
ParaView is the open source post-processing visualization software. 
Install from [ParaView](https://www.paraview.org) home page.

> [!IMPORTANT]
> Choose the right processor architecture for macOS: Intel or Apple Silicon.

### Doxygen 
Documentation of the lignum-core and the LIGNUM system applications 
is done with Doxygen documentation blocks in the software. LaTeX is used to 
typeset mathematical equations and notations:

	sudo port install doxygen +qt5     #doxygen with Qt5 dependency
	sudo port install doxygen-launcher #doxygen and doxywizard GUI
	sudo port install graphviz         #Graphviz and dot for Doxygen figures
	sudo port install texlive [+full]  #LaTeX [full] installation 

The `doxygen` port provides the stable version, whereas the `doxygen-devel` package
tracks the latest Doxygen development releases.

To produce Doxygen software documentation use the project Doxyfile:

	doxygen Doxyfile 2> errors.txt
	open  DoxygenDoc/html/index.html   #Final documentation

Each project's Doxyfile sets the *DoxygenDoc* directory as the destination for final documents.

Doxygen documentations use the built-in LaTeX mathematical environment only. 
Auxiliary packages such as *amstex* are not used.

#### LaTeX installation issues 
The default `texlive` installation is sufficient for writing academic journal articles. 
Upgrading to the *+full* variant consumes an additional 8+ GB of disk space for packages
rarely needed. Furthermore, the *+full* variant introduces a complex dependency tree that can force
hours of local source file compilation. These builds are  prone to errors, particularly following
the launch of a major macOS version when package compatibility is still being updated.

#### jxrlib installation fails
LaTeX installation or ugrade can fail because the CMake configuration for `jxrlib` is
incompatible with CMake 4. Temporarily downgrade to CMake 3 and reinstall `texlive`:

	sudo port uninstall cmake-devel #CMake 4
	sudo port install cmake         #CMake 3
	sudo port install texlive       #Alternatively: sudo port upgrade texlive
	
Finally, replace CMake 3 with CMake 4. 

### Python
Some C++ projects use Cython to expose their software as Python packages. 
To set up Python environment: 

+ Install Python
+ Create a Python virtual environment
+ Install Cython 
+ Install the required packages

Follow the Terminal command line sequence:

	sudo port install python312                               #Python 3.12
	/opt/local/bin/python3.12 -m venv ~/venv/lignumsystem     #Create a Python virtual environment
	source ~/venv/lignumsystem/bin/activate                   #Activate the virtual environment
	(lignumsystem) pip install --upgrade pip setuptools wheel #Core packaging tools for Python 3.12
	(lignumsystem) pip install Cython                         #Cython for Python 3.12
	(lignumsystem) pip install -r requirements.txt            #Install the required python packages

The [requirements.txt](https://github.com/lignumsystem/lignum-core/blob/master/requirements.txt) 
file is available in the *lignum-core* directory.

The build processes for C++ extensions with Cython are in *setup.py* files:
	
	(lignumsystem) python3 setup.py build_ext --inplace
	
See detailed instructions for each use case.

> [!TIP]
> In the example the *lignumsystem* virtual environment is in the *~/venv* directory, where
> the tilde (~) denotes home directory. Centralizing environments this way makes them 
> easier to locate and manage.

### R
`R` is used in data analysis in the LIGNUM system. Download `R` from [CRAN](https://cran.r-project.org).
`RStudio` is a popular choice to replace the built-in `R GUI`. Download `RStudio` from 
[Posit](https://posit.co/products/open-source/rstudio/).

[tidyverse](https://www.tidyverse.org) is a collection of `R` libraries 
for data science:
	
	install.packages("tidyverse") #Function call in the R console

### Emacs
Emacs is a popular text editor in software engineering. Download and install
from the [official web site](https://www.gnu.org/software/emacs/).

## Building the LIGNUM system applications
The lignum-core project and its applications are built using the [CMake](https://cmake.org) 
build system. The CMake build process consists of four phases:

+ Create a build directory: This keeps the source tree clean.
+ Generate the build system: CMake inspects the CMakeLists.txt files.
+ Compile the project: Create binaries and libraries.
+ Install the project (optional): Copy binaries and libraries to install locations.

CMake offers hundreds of built-in variables and functions while supporting custom definitions 
for complete build system tailoring. It also integrates popular software packages, making it easy
to incorporate external dependencies.

> [!TIP]
> [The CMake tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html) 
> is an excellent starting point, while the CMakeLists.txt files within LIGNUM
> provide practical, system-specific examples.

### CMake example for lignum-core
To build lignum-core using Unix Makefiles, follow these steps:

	git clone https://github.com/lignumsystem/lignum-core.git #Download the software
	cd lignum-core
	mkdir release                       #Build directory 
	cd release
	cmake .. -DCMAKE_BUILD_TYPE=Release #Makefile release build system.
	make                                #Compile
	make install                        #Install software components

The *Release* build system results optimized, production-ready code. 
To debug, switch to the *Debug* build configuration in Makefile system 
or generate Xcode project:

	cmake .. -DCMAKE_BUILD_TYPE=Debug #Makefile debug build system
	cmake .. -G Xcode                 #Xcode build system

The `make clean` command in the Makefile system clears the build environment 
to ensure all changes are captured during recompilation. To reset the build
system, simply remove the build directory and recreate it.

> [!NOTE]
> Each CMake build directory is limited to one build configuration. This means that
> different build configurations must be in separate build directories.
> Choose descriptive names like *release*, *debug* or *xcode* for these directories.

### Setting up a new project
Setting up a LIGNUM project involves both lignum-core and the new project. 
For instance, the LignumForest development environment uses the following top-level 
directory structure:

```
lignum-core/
├── CMakeLists.txt
├── Firmament
├── Graphics
├── LEngine
├── LignumForest
│   └── CMakeLists.txt
├── Pine
├── XMLTree
├── c++adt
├── qt-workbench
├── stl-lignum
└── stl-voxelspace
10 directories, 2 files
```
The root CMakeLists.txt for LignumForest specifies lignum-core as a build-time dependency.

The [PROGRAMMING_GUIDELINES](PROGRAMMING_GUIDELINES.md) outline recommended practices for LIGNUM application development.

## Litterature to cite the LIGNUM model

### Core model
To refer to the LIGNUM model in general:

Perttunen *et al.* (1996), *Annals of Botany*, https://doi.org/10.1006/anbo.1996.0011

### Applictions
Choose the relevant publication, for example:

Perttunen *et al.* (2001), *Annals of Botany*, https://doi.org/10.1006/anbo.2001.1489<br>
Sievänen *et al.* (2008), *Functional Plant Biology*, https://doi.org/10.1071/FP08077<br>








