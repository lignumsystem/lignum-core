cmake_minimum_required(VERSION 3.12)
project(cxxadtlib DESCRIPTION "Generic utility classes")

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
src/Parallelogramexample.cc
src/ParametricCurve.cc
src/ParseCommandLine.cc
src/Poisson.cc
src/Polygon.cc
src/PositionVector.cc
src/RMatrix.cc
src/Triangle.cc
src/Uniform.cc
src/hrmatrix-test.cc
src/matrix3d.cc
src/normal.cc
src/rand3.cc
src/Kite.cc
src/RectangularCuboid.cc
)

if(CMAKE_HOST_SYSTEM_NAME MATCHES "Darwin")
  message("c++adt")
  message("------")
  message("Using C++14 standard (-std=c++14)  because of HDF5 library")
  message("XCode with C++17 standard (-std=c++17, default) will cause error")
  target_compile_options(cxxadt PUBLIC -std=c++14)
endif()
target_include_directories(cxxadt PRIVATE "include" "/opt/local/include")
set(CMAKE_INSTALL_PREFIX ".")
install(TARGETS cxxadt DESTINATION "${CMAKE_CURRENT_LIST_DIR}/lib")
export(TARGETS cxxadt  FILE ${CMAKE_CURRENT_LIST_DIR}/lib/cxxadt.cmake)
