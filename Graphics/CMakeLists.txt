cmake_minimum_required(VERSION 3.12)
project(Visual DESCRIPTION "Simple LIGNUM tree visualization")

add_library(Visual STATIC GLSettings.cc
LGMVisualization.cc
LGMVoxelVisualization.cc
OpenGL.cc
OpenGLUnix.cc
OpenGLfunctions.cc
OpenGLinterface.cc
WrapperBase.cc
texture.cc
tga.cc
)

target_compile_options(Visual PRIVATE -DGL_SILENCE_DEPRECATION)
target_include_directories(Visual PUBLIC "."
"${CMAKE_CURRENT_LIST_DIR}/../c++adt/include"
"${CMAKE_CURRENT_LIST_DIR}/../stl-lignum/include"
"${CMAKE_CURRENT_LIST_DIR}/../Firmament/include" 
"${CMAKE_CURRENT_LIST_DIR}/../stl-voxelspace/include" 
)
set(CMAKE_INSTALL_PREFIX ".")
install(TARGETS Visual DESTINATION "${CMAKE_CURRENT_LIST_DIR}/lib")
export(TARGETS Visual  FILE ${CMAKE_CURRENT_LIST_DIR}/lib/Visual.cmake)
