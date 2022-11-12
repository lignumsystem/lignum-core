# cmake file that builds all lignum-core projects.
# To build, compile and install type
# mkdir build    # Create build directory
# cd build
# cmake ..       # Create Unix Makefile build system
# make           # Compile
# make install   # Install products, libraries to 'lib' directories, binaries to 'bin'
# To use  'lignum-core' in other projects see as an example CrownDensity and its CMakeLists.txt
cmake_minimum_required(VERSION 3.12)
# cmake 3.23 for Xcode 13 recommends the policy CMP0114 (warning output)
cmake_policy(SET CMP0114 NEW)
project(lignum-core DESCRIPTION "Lignum project core models")
add_subdirectory(c++adt)
add_subdirectory(Firmament)
add_subdirectory(LEngine)
add_subdirectory(stl-lignum)
add_subdirectory(stl-voxelspace)
add_subdirectory(Graphics)
