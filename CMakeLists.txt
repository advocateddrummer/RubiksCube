cmake_minimum_required(VERSION 3.10)

project(RubiksCube)

# Find git for version number generation.
find_package(Git)

# This is where cmake modules will live.
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

# Find git for version number generation.
find_package(Git)

# this custom target generates the version string from the git repository.
add_custom_target(git-version
                  ${CMAKE_COMMAND} -D SRC=${CMAKE_SOURCE_DIR}/Version.hpp.in
                                   -D DEST=${CMAKE_SOURCE_DIR}/Version.hpp
                                   -P ${CMAKE_MODULE_PATH}/GenerateGitVersion.cmake)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

include_directories("${PROJECT_SOURCE_DIR}/source/")

add_executable(rc main.cpp ${PROJECT_SOURCE_DIR}/source/Cube.cpp
                  ${PROJECT_SOURCE_DIR}/source/CubeManipulateFace.cpp
                  ${PROJECT_SOURCE_DIR}/source/CubeRotations.cpp)

add_dependencies(rc git-version)

###############################################################################
#                         Google's gtest unit testing                         #
###############################################################################
option(gtest_build_tests "build all gtest tests." on)

# define where gtest lives.
set(gtest_dir /Users/ehereth/local CACHE PATH "location of gtest.")

if(gtest_build_tests)
  add_definitions(-DGTEST)
  enable_testing()

  # gtest includes for unit tests.
  include_directories(${gtest_dir}/include)

  # gtest library.
  link_directories(${gtest_dir}/lib)

  # Test general cube logic.
  add_executable(cubeTest "${PROJECT_SOURCE_DIR}/test/TestCube.cpp"
                          "${PROJECT_SOURCE_DIR}/source/Cube.cpp"
                          "${PROJECT_SOURCE_DIR}/source/CubeManipulateFace.cpp"
                          "${PROJECT_SOURCE_DIR}/source/CubeRotations.cpp")

  target_link_libraries(cubeTest gtest)

  add_executable(cubeTwistTest "${PROJECT_SOURCE_DIR}/test/TestCubeTwists.cpp"
                               "${PROJECT_SOURCE_DIR}/source/Cube.cpp"
                               "${PROJECT_SOURCE_DIR}/source/CubeManipulateFace.cpp"
                               "${PROJECT_SOURCE_DIR}/source/CubeRotations.cpp")

  target_link_libraries(cubeTwistTest gtest)

endif() # gtest_build_tests
