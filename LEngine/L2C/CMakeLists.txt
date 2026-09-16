cmake_minimum_required(VERSION 3.12)
project(l2c DESCRIPTION "L-system compiler l2c implementetation")
message(STATUS "LEngine/L2C")
include(CMakePrintHelpers)
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  cmake_print_variables(CMAKE_SOURCE_DIR)
  cmake_print_variables(CMAKE_BINARY_DIR)
  cmake_print_variables(PROJECT_SOURCE_DIR)
  cmake_print_variables(PROJECT_BINARY_DIR)
  cmake_print_variables(CMAKE_CURRENT_LIST_DIR)
  cmake_print_variables(CMAKE_CURRENT_SOURCE_DIR)
  cmake_print_variables(CMAKE_CURRENT_BINARY_DIR)
endif()
  
include(FindFLEX)
include(FindBISON)
find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)
if (FLEX_FOUND)
  message(STATUS "Found Flex: ${FLEX_VERSION}")
endif()
if (BISON_FOUND)
  message(STATUS "Found Bison: ${BISON_VERSION}")
endif()

flex_target(L2CScanner l2c.l ${CMAKE_CURRENT_LIST_DIR}/lex_l.cpp COMPILE_FLAGS "-8 -Pl --noline")
bison_target(L2CParser l2c.y ${CMAKE_CURRENT_LIST_DIR}/l2c_tab.cpp COMPILE_FLAGS "-d --no-lines -p l")
add_flex_bison_dependency(L2CScanner L2CParser)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
cmake_print_variables(FLEX_L2CScanner_OUTPUTS)
cmake_print_variables(BISON_L2CParser_OUTPUTS)
endif()

set(SOURCE_FILES main.cpp
  ${FLEX_L2CScanner_OUTPUTS}
  ${BISON_L2CParser_OUTPUTS}
  module.cpp
  production.cpp
)

include_directories("${CMAKE_CURRENT_LIST_DIR}" "." "${CMAKE_CURRENT_LIST_DIR}/../include"
"${CMAKE_CURRENT_LIST_DIR}/../Global"
"${CMAKE_CURRENT_LIST_DIR}/../Common"
)

add_executable(l2c ${SOURCE_FILES})
add_executable(l2c::l2c ALIAS l2c)
