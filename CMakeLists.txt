# CMAKE file that builds lignum-core libraries and binaries.
# -----------------------------------------
# For Unix Makefile build system for Debug:
# mkdir debug
# cd  debug
# cmake .. -DCMAKE_BUILD_TYPE=Debug
# make install
#
# Optionally set for example C/C++ compiler in command line
# cmake ..  -DCMAKE_BUILD_TYPE=Debug  -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_CXX_FLAGS=-stdlib=libc++
# make install
# ------------------------------------------
# For Unix Makefile build system for Release:
# mkdir release
# cd release
# cmake .. -DCMAKE_BUILD_TYPE=Release
# make install
# ---------------------------------------------
# For Xcode IDE first create Xcode project file:
# mkdir xcode
# cd xcode
# cmake .. -G Xcode
# -------------------------------------
# Open Xcode IDE:
# open lignum-core.xcodeproj
# -------------------------------------
# In Xcode select Product (from menu bar) -> Scheme -> install to compile lignum-core libriaries
# and binaries.
#
# To use  'lignum-core' in other projects see for example LignumForest and its CMakeLists.txt.
cmake_minimum_required(VERSION 3.30)
# cmake 3.23 for Xcode 13 recommends the policy CMP0114 (warning output)
#cmake_policy(SET CMP0114 NEW)
project(lignum-core DESCRIPTION "Lignum project core models")
add_subdirectory(c++adt)
add_subdirectory(Firmament)
add_subdirectory(LEngine)
add_subdirectory(stl-lignum)
add_subdirectory(stl-voxelspace)
if(CMAKE_HOST_SYSTEM_NAME MATCHES "Darwin")
  add_subdirectory(Graphics)
endif()
