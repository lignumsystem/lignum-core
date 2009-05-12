To compile type

  qmake -r qt-opengl.pro
  make

To compile with optimization on 
(faster, no debug) type

  qmake -r "CONFIG+=release" qt-opengl.pro
  make

To remove all compilation work type

  make distclean

Note 1: 	
	On Windows the make program comes with 
	mingw system and is called mingw32-make
Note2:
	On Windows use the Dos window provided by Qt.
	The path to qmake and other programs are set.
	(Locate Qt menu from Start->Programs).






