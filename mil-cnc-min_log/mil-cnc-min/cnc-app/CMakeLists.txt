# CMakeList.txt : CMake project for milteksan-cnc, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.8)

project(cnc-app VERSION 1.0)

# configure_file(version.h.in version.h)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB APP_HEADER *.h)
file(GLOB APP_SOURCE *.cpp)

## TODO(batuhan): -SOEM- Need to change how we handle these, find_package?
message(DEBUG "SOEM Include root: ${CMAKE_SOURCE_DIR}/thirdparty/SOEM-master")
include_directories(${CMAKE_SOURCE_DIR}/thirdparty/SOEM-master/soem)
include_directories(${CMAKE_SOURCE_DIR}/thirdparty/SOEM-master/osal)
include_directories(${CMAKE_SOURCE_DIR}/thirdparty/SOEM-master/oshw)
include_directories(${CMAKE_SOURCE_DIR}/thirdparty/cli/include)
## TODO(batuhan): Target/Platform selection
include_directories(${CMAKE_SOURCE_DIR}/thirdparty/SOEM-master/osal/linux)
include_directories(${CMAKE_SOURCE_DIR}/thirdparty/SOEM-master/oshw/linux)
# link_directories(${CMAKE_SOURCE_DIR}/thirdparty/SOEM-master/Release)
find_package(Threads REQUIRED)
find_library(soem REQUIRED)
find_library(cli REQUIRED)

add_executable(cnc-app ${APP_HEADER} ${APP_SOURCE} "global_data_area.h" "servo_master.h" "servo_faker.h")
target_link_libraries(cnc-app Threads::Threads)
target_link_libraries(cnc-app soem)
target_link_libraries(cnc-app cli)
