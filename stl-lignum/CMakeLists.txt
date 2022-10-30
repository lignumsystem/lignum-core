cmake_minimum_required(VERSION 3.12)
project(LGM DESCRIPTION "LIGNUM tree with generic algorithms")

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
