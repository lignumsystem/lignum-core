# MacPorts
[MacPorts](https://www.macports.org) is an open source initiative on Macs to install and maintain 
Linux/Unix open-source software packages called *ports*.  Detailed MacPorts and Xcode 
installation instructions are in [MacPorts Guide](https://guide.macports.org).

MacPorts port installations and removals are done with `port` command in Terminal. Start Terminal from
*/Applications/Utilities/Terminal.app* in Finder. Installations and removals require administrative rights. 
On macOS administrator users can use `sudo` command ("super user do") to gain necessary privileges. 

MacPorts is not the only package management system for Macs. Another popular system is [Homebrew](https://brew.sh). 

In the `port` command examples the '[]' and '\< \>' are not part of `port` command but denote a placeholder for
`port` action, port name or regular expression.

# Xcode commands
Xcode installation is mandatory for MacPorts. Remember also to install command line tools and the licence agreement:

	sudo xcode-select --install #Install command line tools
	sudo xcodebuild -license    #Licence agreement

To view developer kits:

	xcodebuild -showsdks  #Show developer kits available
	xcrun --show-sdk-path #Software developer kit location
	
# MacPorts for Lignum
The following ports are used to implement and to compile Lignum projects:
	
		sudo port install cmake-gui #CMake software build system
		sudo port install qt5       #Qt5 software libraries
		sudo port install hdf5      #HDF5 data management and storage suite libraries and software
		sudo port install vtk       #VTK data model library for ParaView
		sudo port install doxygen-launcher +qt5 #Doxygen documentation system, qt5 variant installs Qt5
		auso port install graphviz              #Graph visualization software for Doxygen
		sudo port install cgal6                 #CGAL6 computer geometry algorithms library
		sudo port install texlive +full         #LaTeX documentation preparation system, full installation

Note the ports install their dependencies including useful software like Python.

## Broken and non-functional ports
Regarding Lignum the following ports cannot be installed on macOS Tahoe or are unstable.

### qt4-mac
qt4-mac port does not install on macOS Tahoe. It is needed to compile *qt-workbench*. 
Use LignumVTK for visualization.

### emacs-mac-app
Emacs port seem to be unstable for macOS Tahoe. Download precompiled [Emacs](https://emacsformacosx.com)
or [Aquamacs](https://aquamacs.org).

### R-app
Port for R has been unstable. [RStudio](https://posit.co/download/rstudio-desktop/) 
is a popular choice for R and R GUI.

# Port installations
MacPorts uses local *ports tree*, catalogue of available ports accompanied 
by installation instructions in *Portfiles* to organise and administer 
port installations, updates and removals. 

Port installations sort out and install required dependencies between ports. 
Successful port installation will become *active*. 

For ordinary users there is always  one port version to install, the latest. 
Advanced users can set active version between installed port versions.
Wizard users can install required port version from GitHub.

	sudo port install <port1> <port2>                  #Install one or more ports
	sudo port install <port> [+<variant1> -<variant2>] #Use '+/-' to add/remove port variant 

A port may also provide post installation commands. See `port notes` after installation.

# Port upgrades
Update ports regurlarly for example once a month.

	sudo port selfupdate       #First, upgrade MacPorts itself and port definition files
	sudo port upgrade outdated #Upgrade outdated ports found in port definition files 
	sudo port upgrade <port>   #Upgrade a single port
	sudo port upgrade --enforce-variants <port> +<variant1> -<variant2> #Upgrade port with or without variants

Successful port update will become *active*, previous installation will remain installed as *inactive*. 
If the port upgrade fails previous installation  remains *active* and can be used.

Note there is a difference between software versions and port versions. For example Python 3.9 and 3.13
have ports *python39* and *python313* respectively, both ports having several port versions.

>[!CAUTION]
>Perform port installations, updates and removals strictly sequentially. If you for example try to speed things up and install new 
>ports in one Terminal window and use another one for removals, this most likely results corrupted ports tree and Portfiles.

# Port migration
MacPorts is macOS specific. Each major macOS update requires migrations procedure. 
This is now automated with `migrate`:

	sudo port migrate
	
A snapshot of installed ports before migration is also taken. Ports that fail to install can be tried later when fixed:

	sudo port restore --last
	
>|!NOTE]
>After macOS major update you should be able to use existing ports. Seldom does a new macOS break the software itself.
>It is the MacPorts that is designed to be macOS and CPU architecture specific.

>[!CAUTION]
>It is common that some ports fail to install right after new macOS release. Fixes are usually provided
>within weeks. The [Support page](https://trac.macports.org) gives details for migration process and maintains
>tickets for ports failing migration. 

# Useful MacPorts port commands

## Help

	port help [<port_command>]
	port help #Generic 'port' help, manual page
	port help install #Help for 'port install' 

## Pseudo port names
The `port` command can operate on a set of ports with the same status 
or *pseudo port names*. These include for example *installed*, *requested*,
*active*, *inactive*, *outdated* and *obsolete*:

	port installed           #List all installed ports
	port installed active    #List active installed ports
	port installed outdated  #List ports requiring update 
	port installed requested #List ports installed explicitely with `port install`
	port installed 'gcc*'    #List installed ports matching wild card search, note mandatory hyphens

The `port`command comes with the manual page (`man port`).

## Query ports

	port search <keyword>         #Search ports with port name or by topic
	port search 'gcc*'            #Search matching wild card search, note mandatory hyphens
	port search --exact <keyword> #Search with exact keyword match
	port info <port>              #Display useful information for the port
	port variants <port>          #Ports may have diverse installation options, a.k.a variants
	port notes <port>             #Query for example post installation actions

### Port information page
Most likely the required port and its exact name for installation can be found with `port search`. 
Ports page provides more detailed port information:

  + Go to [Ports page](https://ports.macports.org)
  + Search for a port
  + See for example port health for macOS versions

## Reclaim space after installation
Interactive `reclaim` finds files in the port system that can be removed:

	sudo port reclaim #Uninstall inactive ports, remove unnecessary files and directories
  
Files and directories are in three parts. The first part presents
unnecessary unrequested ports (i.e. ports without dependencies). The second part
contains inactive ports. Third part has unnecessary files and directories. 
Remove inactive ports and unnecessary files. Unnecessary unrequested ports can include useful programs.

Port `clean` removes temporary files and compilation work:

	sudo port clean installed #Remove compilation work
	sudo port clean python39  #Clean python39 only
	sudo port clean active    #Clean all active ports

`port install` calls `clean` as the last step in port installation. Manual `clean` is needed
if the port installation fails.

## Uninstall ports
Port removals are straightforward. The `uninstall` command will issue warnings for ports with
dependents.

	sudo port uninstall <port1> <port2> #Remove list of installed ports
	sudo port uninstall [--follow-dependencies] <port> #Remove a single port and ports it dependens on
	sudo port uninstall [--follow-dependents <port>    #Remove a single port and ports depending on it
	sudo port uninstall inactive  #Remove inactive ports
	sudo port uninstall installed #Remove all installed ports

# Some useful port installations
Note that if you have no prior port installations some installations will take a very long time, several hours,
including all port dependencies.

## cheat
Community effort to provide program usage examples.

	sudo port install cheat #Cheat sheets for Unix/Linux commmands

For example:

	cheat cheat
	cheat tar
	cheat zip
	cheat find

## GNU compiler collection 
Each GCC version has its own port. GNU compiler collection includes `gfortran` Fortran compiler.

	sudo port install gcc15
	sudo port select --set gcc mp-gcc15 #Active version, 'gfortran' ready to use

## Qt libraries

	sudo port install qt4-mac #Qt4 developer
	sudo port install qt5     #Qt5 developer
	sudo port install qt6     #Qt6 developer
	
Optionally set in *.zprofile*: 

	alias qmake4='/opt/local/libexec/qt4/bin/qmake' #Explicitely Qt4 qmake
	alias qmake5='/opt/local/libexec/qt5/bin/qmake' #Explicitely Qt5 qmake
	alias qmake6='/opt/local/libexec/qt6/bin/qmake' #Explicitely Qt6 qmake
	
Qt libraries are mutually exclusive conficting each other.

## Programming libraries

	sudo port install libomp #The OpenMP subproject of LLVM, parallel programming with threads and tasks
	sudo port install openmpi #The MPI library, parallel programming with independent processes
	sudo port select --set mpi openmpi-mp-fortran #Activate mpi compilers 'mpi[xxx], 'mpiexec' and 'mprun'
	sudo port install cgal6 #New version, conflicts cgal4 and cgal5
	sudo port install hdf5 #Libraries and command line tools for HDF5 files
	sudo port install h5utils #Utilities for visualization and conversion of HDF5 files
	sudo port install vtk #VTK 3D computer graphics library for ParaView file formats
	
For hdf5 port Mac users may need to add `export HDF5_USE_FILE_LOCKING=FALSE` in *.zprofile* for network mounted files.

## Image processing

	sudo port install ImageMagick #Command line tools suite to create, convert and edit pdf files and raster images
	sudo port install ffmpeg #Create, convert, play and stream audio/video

## Text file formatting 
GNU `enscript` can be used to format source code text files. `enscript-color` is an example for two column landscape 
PostScript output.

	sudo port install enscript +mediaA4 -mediaLetter #GNU enscript text files to PostScript formatting for printing or file output
	alias enscript-color='enscript --line-numbers --columns=2 --landscape --pretty-print --fancy-header --borders --color'#In .zprofile 
	
Use `convert` from ImageMagick to convert PostScript to PDF.

	enscript-color -o <file.cc> -p <file.ps> #Command line 
	convert [input-options] file.ps [output-options] file.pdf #Use convert in ImageMagick suite to convert between file formats
     
`enscript` does not support UTF-8. Use for example `iconv` to convert UTF-8 to ISO_8859-1:

	iconv -f UTF-8 -t ISO-8859-1 <file.txt> #Convert from UTF-8 to ISO-8859-1 character encoding
	
## Convert version control systems to Git
To convert from CVS or Mercurial to Git the following ports are needed. 
See also the [VC_Conversion](https://github.com/jariperttunen/VC_Conversion) repository.

	sudo port install cvs           #CVS version control
	sudo port install mercurial     #Mercurial version control
	sudo port install cvs2svn       #CVS to SVN convenrsion, contains cvs2git program
	sudo port install git-remote-hg #Bidirectional conversion between Git and Mercurial

## Miscellaneous

	sudo port install gh      #GitHub command line interface
	sudo port install mpstats #Submit anonymous statistics about port installations to MacPorts)

## Broken ports 
A port that fails `port install` is *broken*. Try first `sudo port clean <broken_port>`, then 
`sudo port selfupdate` followed by `sudo port upgrade outdated` before one more try with 
the broken port installation. The ports tree may be outdated.

## Bug reports
You may submit port bug report concerning *compiling and installation* via [Trac](https://trac.macports.org/wiki/Tickets). 
GitHub login is required (upper right hand corner of the Trac page). Add port maintainers to ticket recipients:

	port info <port> --maintainers 
  
To avoid submitting duplicate bugs read the  [Advisory](https://guide.macports.org/#project.tickets) first. 

# Uninstall MacPorts
If you have decided to do this the step-by-step instructions are in 
[MacPorts Guide](https://guide.macports.org/#installing.macports.uninstalling). 

