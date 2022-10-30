cmake_minimum_required(VERSION 3.12)
project(sky DESCRIPTION "Implementation of Standard Overcast Sky")
add_library(sky STATIC Firmament.cc
FirmamentWithMask.cc
Interlen.cc
MineSet.cc
sky-dump.cc 
)
target_include_directories(sky PUBLIC "include" 
"${CMAKE_CURRENT_LIST_DIR}/../c++adt/include"
"${CMAKE_CURRENT_LIST_DIR}/../stl-lignum/include"
)
set(CMAKE_INSTALL_PREFIX ".")
install(TARGETS sky  DESTINATION "${CMAKE_CURRENT_LIST_DIR}/lib")
export(TARGETS sky  FILE ${CMAKE_CURRENT_LIST_DIR}/lib/sky.cmake)
