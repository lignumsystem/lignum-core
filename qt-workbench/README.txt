To avoid problems  in compiling LignumWb, make sure  you have done the
following

1. Download and install Qt SDK from qt-project.org for your platform.

2. For  Windows operating  system use the  command line of  Dos window
provided by  Qt (locate  this window  in the Qt  SDK menu  by browsing
e.g. Start->Programs).


To compile LignumWb program in debug mode type in the command line:

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


LignumWb  (The Lignum Workbench)  is the  Graphical User  Interface to
visualize and inspect  trees simulated by tree or  forest stand models
based on the LIGNUM model. It does not take any command line arguments.

In general, for  the ease of implementation, the  tree or forest stand
models  based on  the  LIGNUM model  look  for files  required by  the
application specific  command line arguments at  the current directory
(where the program was started) unless otherwise stated.

Mac OS  X Notes 

Note  1:  The  qt-opengl-main.pro  is  configured to  make  Mac  OS  X
application bundle LignumWb.app.

Windows Notes

Note 1:  On Windows the  make program comes  with mingw system  and is
called mingw32-make

Note 2: On Windows use the  Dos window provided by Qt. When started it
will set paths to Qt tools SDK tools and libraries.

Note 3: On Windows the  LignumWb binary is generated either into debug
or release subdirectory depending on the CONFIG option to qmake.  This
is the default behaviour with Qt compilation tools on Windows.
          
Linux Notes

Note   1:  The   LignumWb   binary  is   created   into  the   current
(i.e. qt-workbench)  directory. This is the default  behaviour with Qt
compilation tools on Linux.




