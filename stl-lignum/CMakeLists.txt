cmake_minimum_required(VERSION 3.12)
project(LGMlib DESCRIPTION "LIGNUM tree with generic algorithms")
message("------")
message("Lignum")
message("------")
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

add_library(LGM STATIC Axis/AxisFriend.cc
BranchingPoint/BranchingPointFriend.cc
Bud/Bud.cc
Bud/BudFriend.cc
Tree/TreeFriend.cc
TreeCompartment/TreeCompartmentFriend.cc
TreeMetaFileParser/TreeMetaFileParser.cc
TreeSegment/BeamShading.cc
TreeSegment/BroadLeaf.cc
TreeSegment/BroadLeafMetabolism.cc
TreeSegment/CfTreeSegment.cc
TreeSegment/MyTreeSegment.cc
TreeSegment/TreeSegment.cc
TreeSegment/TreeSegmentFriend.cc 
)

target_include_directories(LGM PUBLIC "include" 
"${CMAKE_CURRENT_LIST_DIR}/../c++adt/include"
"${CMAKE_CURRENT_LIST_DIR}/../Firmament/include"
"${CMAKE_CURRENT_LIST_DIR}/../stl-lignum/include"
)
set(CMAKE_INSTALL_PREFIX ".")
install(TARGETS LGM DESTINATION "${CMAKE_CURRENT_LIST_DIR}/lib")
export(TARGETS LGM  FILE ${CMAKE_CURRENT_LIST_DIR}/lib/LGM.cmake)
