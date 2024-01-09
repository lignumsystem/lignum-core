# The Lignum Workbench
`LignumWb`  (The Lignum Workbench)  is the  Graphical User  Interface to
visualize and inspect  trees simulated with the LIGNUM model. 
It does not take any command line arguments. LignumWb is implemented
with Qt4 Toolkit.

It seems Qt4 is becoming ever more difficult to maintain in MacPorts.
So far Qt4 can used to compile LignumWb on Apple Silicon on Sonoma. Qt5 breaks
the Meta Object Compiler (`moc`) interface and cannot be used to compile
LignumWb. However, XMLTree template library writing and reading trees 
(XML format) simulated with LIGNUM can be used with both Qt4 and Qt5.

## Qt Toolkit installation 
For Macs both Qt4 and Qt5  Toolkits can be installed from MacPorts:

Qt4: 
	
	sudo port install qt4-mac

Qt5: 

	sudo port install qt5
	
Note that these installations don't include QtCreator.

## Compilation
First, make sure that `qmake` points to Qt version:
	 
	ls -Flah /opt/local/bin/qmake
	/opt/local/bin/qmake@ -> /opt/local/libexec/qt4/bin/qmake 
	
If not, use the explicit directory path to `qmake` or create for example the soft link:
	
	cd  /opt/local/bin/
	sudo ln -s /opt/local/libexec/qt4/bin/qmake 
	

To compile LignumWb in debug mode type in the command line.

	qmake -r qt-opengl.pro
	make

or defining explicitely the debug option:

	qmake -r "CONFIG+=debug" qt-opengl.pro
	make

To compile with optimization (faster, no debug) type:

	qmake -r "CONFIG+=release" qt-opengl.pro
	make

To remove all compilation work type:

	make distclean


## CMake
CMake has become a popular software build system and LIGNUM projects
in general have transferred to CMake to manage software build process.
Note that even Qt Toolkit (since Qt6) has done that.

## Mac OS  X Notes 

+ Note  1:  The  qt-opengl-main.pro  is  configured to  make  Mac  OS  X
application bundle LignumWb.app.

## Windows Notes

+ Note 1:  On Windows the  make program comes  with mingw system  and is
called mingw32-make

+ Note 2: On Windows use the  Dos window provided by Qt. When started it
will set paths to Qt tools SDK tools and libraries.

+ Note 3: On Windows the  LignumWb binary is generated either into debug
or release subdirectory depending on the CONFIG option to qmake.  This
is the default behaviour with Qt compilation tools on Windows.

+ Note 4: You  may need to update paths to GLU  (GL utility) library and
glu.h header  file depending the Qt  installation directory. Currently
the  path  to  Qt  installation  directory is  assumed  to  begin  with
C:\prog\QtSDK.
          
## Linux Notes

+ Note   1:  The   LignumWb   binary  is   created   into  the   current
(i.e. qt-workbench)  directory. This is the default  behaviour with Qt
compilation tools on Linux.

Note 2: To compile under Ubuntu, it may be necessary
to add -LGLU to the libraries in qt-opengl-main.pro (line 19):

	LIBS	+= -L../c++adt/lib -L../stl-lignum/lib -L../Firmament/lib -L../LEngine/lib -lL -lsky -lLGM  -lcxxadt -lGLU
