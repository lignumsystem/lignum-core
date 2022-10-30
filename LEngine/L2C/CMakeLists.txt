cmake_minimum_required(VERSION 3.12)
project(l2c DESCRIPTION "L-system implementetation")

set(SOURCE_FILES l2c_tab.cpp 
lex_l.cpp 
main.cpp 
module.cpp 
production.cpp
)

include_directories("." "${CMAKE_CURRENT_LIST_DIR}/../include"
"${CMAKE_CURRENT_LIST_DIR}/../Global"
"${CMAKE_CURRENT_LIST_DIR}/../Common"
)

add_executable(l2c ${SOURCE_FILES})
install(TARGETS l2c DESTINATION "${CMAKE_CURRENT_LIST_DIR}/../bin")
