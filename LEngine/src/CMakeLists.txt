cmake_minimum_required(VERSION 3.12)
project(L DESCRIPTION "L system library")
message(STATUS "LEngine/src")
add_library(L STATIC Turtle.cc)
add_library(L::L ALIAS L)
target_include_directories(L PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../include
"${CMAKE_CURRENT_LIST_DIR}/../../c++adt/include"
)
