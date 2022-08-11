# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required(VERSION 3.8)

project(cnc-app VERSION 1.0)

# Include sub-projects.
add_subdirectory(cnc-app)
add_subdirectory(thirdparty/SOEM-master)
add_subdirectory(thirdparty/cli)
