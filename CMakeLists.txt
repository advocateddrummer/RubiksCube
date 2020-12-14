cmake_minimum_required(VERSION 3.10)

project(RubiksCube)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


include_directories("${PROJECT_SOURCE_DIR}/source/")

add_executable(rc main.cpp ${PROJECT_SOURCE_DIR}/source/Cube.cpp)
