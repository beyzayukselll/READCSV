cmake_minimum_required(VERSION 3.16.3)
project(test)  

find_package(Python3 REQUIRED
COMPONENTS Interpreter Development NumPy)
find_package(PythonLibs     3.8     REQUIRED)
find_package(PythonInterp   3.8     REQUIRED)
find_package (Eigen3 3.4 REQUIRED NO_MODULE)

# find_package(Catch2 CONFIG REQUIRED)

include_directories(${CMAKE_SOURCE_DIR}
                    ${CMAKE_SOURCE_DIR}/include
                    ${Python3_INCLUDE_DIRS} include
                    ${Python3_NumPy_INCLUDE_DIRS} include
                    /usr/include/python3.8
                    )

file(GLOB  APP_SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")
file(GLOB  TEST_SOURCES "${CMAKE_SOURCE_DIR}/test/*.cpp")
# file(GLOB TEST_SOURCES "*.cpp")


list(APPEND      APP_SOURCES  ${TEST_SOURCES})
list(REMOVE_ITEM APP_SOURCES "${CMAKE_SOURCE_DIR}/src/main.cpp")

add_executable(test ${APP_SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR})
                                                   

target_link_libraries(test ${Python3_LIBRARIES})
target_link_libraries (test Eigen3::Eigen)