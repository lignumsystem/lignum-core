TEMPLATE	= app
CONFIG		+= qt warn_on debug
QT              += xml opengl
HEADERS		= 
SOURCES		= pine.cc XMLDomTreeBuilder.h XMLDomTreeReader.h XMLDomTreeWriterI.h
INCLUDEPATH	+=  ../stl-lignum/include ../c++adt/include ../Firmament/include ../LEngine/include ../stl-voxelspace/include ../Graphics ../Pine ../Lig-Crobas/include 
LIBS	+= -L../c++adt/lib -L../stl-lignum/lib -L../Firmament/lib -L../LEngine/lib -L../stl-voxelspace/lib -L../Graphics -lglut -L../Lig-Crobas -llsys -lVisual -lpine -lsky -lL -lvoxel -lLGM -lc++adt

TARGET		= scotspine
QTDIR_build:REQUIRES="contains(QT_CONFIG, small-config)"

# install
target.path = $$[QT_INSTALL_EXAMPLES]/tutorial/t1
sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS t1.pro
sources.path = $$[QT_INSTALL_EXAMPLES]/tutorial/t1
INSTALLS += target sources
