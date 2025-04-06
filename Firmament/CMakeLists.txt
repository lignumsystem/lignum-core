cmake_minimum_required(VERSION 3.12)
project(skylib DESCRIPTION "Implementation of Standard Overcast Sky")
message("---------")
message("Firmament")
message("---------")
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
