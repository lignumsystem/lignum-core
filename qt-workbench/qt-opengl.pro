######################################################################
# Automatically generated by qmake (2.00a) Ti Kes 20 12:39:50 2006
######################################################################

TEMPLATE = app
TARGET += 
DEPENDPATH += .
INCLUDEPATH += . ../stl-lignum/include ../c++adt/include ../Firmament/include ../LEngine/include ../stl-voxelspace/include ../Graphics ../Pine ../Lig-Crobas/include ..
CONFIG += qt
QT += opengl
LIBS	+= -L/usr/freeware/lib32 -L../c++adt/lib -L../stl-lignum/lib -L../Firmament/lib -L../LEngine/lib -L../Lig-Crobas -L../stl-voxelspace/lib -L../Graphics -lVisual  -lglut -lXmu  -lsky -lpine -llsys -lL -lvoxel -lLGM  -lc++adt

# Input
HEADERS += GLDrawer.h BSPPolygon.h BSPTree.h SceneObject.h BSPPolygonMaterial.h
SOURCES += GLDrawer.cpp main.cpp BSPPolygon.cpp BSPTree.cpp SceneObject.cpp BSPPolygonMaterial.cpp
