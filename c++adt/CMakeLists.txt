cmake_minimum_required(VERSION 3.12)
project(cxxadtlib DESCRIPTION "Generic utility classes")
message("c++adt")
find_package(HDF5 COMPONENTS C CXX HL REQUIRED)
if (HDF5_FOUND)
  message(STATUS "Found HDF5: ${HDF5_VERSION}")
endif()
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

add_library(cxxadt STATIC src/Bernoulli.cc
src/Bisection.cc
src/CString.cc
src/DList.cc
src/DListElement.cc
src/Ellipse.cc
src/Ellipsis.cc
src/Gauss.cc
src/HDF5example.cc
src/HRMatrix.cc
src/InvNorm.cc
src/LGMGeometry.cc
src/LGMHDF5File.cc
src/LGMHistogram.cc
src/Lex.cc
src/Parallelogram.cc
src/ParallelogramExample.cc
src/ParametricCurve.cc
src/ParseCommandLine.cc
src/Poisson.cc
src/Polygon.cc
src/PositionVector.cc
src/RMatrix.cc
src/Triangle.cc
src/Uniform.cc
src/hrmatrix-test.cc
src/normal.cc
src/rand3.cc
src/Kite.cc
src/RectangularCuboid.cc
)
add_library(cxxadt::cxxadt ALIAS cxxadt)
if(CMAKE_HOST_SYSTEM_NAME MATCHES "Darwin")
  message(STATUS "Using the C++14 standard for the HDF5 library")
  message(STATUS "The C++17 standard (-std=c++17), XCode clang default) will cause error")
  #Keep the C++14 standard PRIVATE to this compilation,
  #otherwise the language standard may propagate unintentionally.
  #Many software packages like VTK and QT6 require C++17.
  # Forces C++14 for the cxxadt library compilation only
  target_compile_features(cxxadt PRIVATE cxx_std_14)
  set_target_properties(cxxadt PROPERTIES
    CXX_STANDARD_REQUIRED ON
  )
  get_target_property(TARGET_FEATURES cxxadt COMPILE_FEATURES)
  message(STATUS "cxxadt compile features: ${TARGET_FEATURES}")
endif()
target_include_directories(cxxadt PRIVATE ${HDF5_INCLUDE_DIRS} "include" "/opt/local/include")
set(CMAKE_INSTALL_PREFIX ".")
install(TARGETS cxxadt DESTINATION "${CMAKE_CURRENT_LIST_DIR}/lib")
export(TARGETS cxxadt  NAMESPACE cxxadt:: FILE ${CMAKE_CURRENT_LIST_DIR}/lib/cxxadt.cmake)
