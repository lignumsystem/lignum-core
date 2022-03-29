######################################################################
# Automatically generated by qmake (2.00a) Fri Aug 18 17:24:43 2006
######################################################################
CONFIG += staticlib
CONFIG -= qt
TEMPLATE = lib
DESTDIR = .
TARGET = Visual 
DEPENDPATH += .
DEFINES += GL_SILENCE_DEPRECATION
QMAKE_CXXFLAGS += -Wno-deprecated -Wno-deprecated-declarations 
INCLUDEPATH += . ../c++adt/include ../stl-lignum/include ../stl-voxelspace/include ../Firmament/include 

# Input
HEADERS += CTexture.h \
           GLSettings.h \
           LGMVisualization.h \
           LGMVisualizationI.h \
           LGMVoxelVisualization.h \
           OpenGL.h \
           OpenGLfunctions.h \
           OpenGLFunctor.h \
           OpenGLFunctorI.h \
           OpenGLHFiles.h \
           OpenGLinterface.h \
           OpenGLinterfaceI.h \
           OpenGLSymbols.h \
           OpenGLUnix.h \
           OpenGLUnixI.h \
           texture.h \
           tga.h \
           TreeVariables.h \
           WrapperBase.h \
           WrapperBaseI.h
SOURCES += GLSettings.cc \
           LGMVisualization.cc \
           LGMVoxelVisualization.cc \
           OpenGL.cc \
           OpenGLfunctions.cc \
           OpenGLinterface.cc \
           OpenGLUnix.cc \
           texture.cc \
           tga.cc \
           WrapperBase.cc
