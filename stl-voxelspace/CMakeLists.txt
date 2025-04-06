cmake_minimum_required(VERSION 3.12)
project(voxellib DESCRIPTION "3D Voxel space implementation")
message("----------")
message("VoxelSpace")
message("----------")
include(CMakePrintHelpers)
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  cmake_print_variables(CMAKE_SOURCE_DIR)
  cmake_print_variables(CMAKE_BINARY_DIR)
  cmake_print_variables(PROJECT_SOURCE_DIR)
  cmake_print_variables(PROJECT_BINARY_DIR)
  cmake_print_variables(CMAKE_CURRENT_LIST_DIR)
  cmake_print_variables(CMAKE_CURRENT_SOURCE_DIR)
  cmake_print_variables(CMAKE_CURRENT_BINARY_DIR)
endif()

add_library(voxel STATIC 
src/Nearby.cc
src/VOBookKeeper.cc
src/VoxelBox.cc
src/VoxelSpace.cc
)

target_include_directories(voxel PUBLIC "include" 
"${CMAKE_CURRENT_LIST_DIR}/../c++adt/include"
"${CMAKE_CURRENT_LIST_DIR}/../Firmament/include"
"${CMAKE_CURRENT_LIST_DIR}/../stl-lignum/include"
)

set(CMAKE_INSTALL_PREFIX ".")
install(TARGETS voxel DESTINATION "${CMAKE_CURRENT_LIST_DIR}/lib")
export(TARGETS voxel  FILE ${CMAKE_CURRENT_LIST_DIR}/lib/voxel.cmake)
