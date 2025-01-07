cmake_minimum_required(VERSION 3.12)
project(L DESCRIPTION "L system library")

add_library(L STATIC Turtle.cc)

target_include_directories(L PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../include
"${CMAKE_CURRENT_LIST_DIR}/../../c++adt/include"
)

#set(CMAKE_INSTALL_PREFIX ".")
#install(TARGETS L DESTINATION "${PROJECT_SOURCE_DIR}/lib")
