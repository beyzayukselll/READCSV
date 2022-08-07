
cmake_minimum_required(VERSION 3.16.3)

project(system_identification)  

file(GLOB APP_HEADER *.h)
file(GLOB APP_SOURCE *.cpp)

find_package(Python3 REQUIRED
COMPONENTS Interpreter Development NumPy)
find_package(PythonLibs     3.8     REQUIRED)
find_package(PythonInterp   3.8     REQUIRED)
find_package(Eigen3         3.4     REQUIRED NO_MODULE)

include_directories(${CMAKE_SOURCE_DIR}
                    ${CMAKE_SOURCE_DIR}/include
                    ${Python3_INCLUDE_DIRS} 
                    ${Python3_NumPy_INCLUDE_DIRS} 
                    /usr/include/python3.8
                    )


add_executable(${PROJECT_NAME} ${APP_HEADER} ${APP_SOURCE})

target_link_libraries(${PROJECT_NAME}  ${Python3_LIBRARIES})
target_link_libraries (${PROJECT_NAME}  Eigen3::Eigen)
