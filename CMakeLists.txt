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

# Boost stuff.
set(BOOST_ROOT "/usr/local/Cellar/boost/1.76.0/")
set(Boost_NO_BOOST_CMAKE on)
set(Boost_NO_SYSTEM_PATHS on)
set(Boost_USE_STATIC_LIBS on)
unset(Boost_INCLUDE_DIR CACHE)
unset(Boost_LIBRARY_DIRS CACHE)
find_package(Boost 1.75.0 REQUIRED
                          COMPONENTS
                          program_options) # Commandline/configuration file parsing.
                          #system          # Needed for boost::timer.
                          #timer           # CPU timer.
                          #chrono          # another CPU timer.
                          #filesystem)     # basename/extension extraction etc.

if (Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  link_directories(${Boost_LIBRARY_DIRS})
  #message(STATUS "Boost include directory: " ${Boost_INCLUDE_DIR})
  #message(STATUS "Boost include directories: " ${Boost_INCLUDE_DIRS})
  #message(STATUS "Boost library directory: " ${Boost_LIBRARY_DIR})
  #message(STATUS "Boost library directories: " ${Boost_LIBRARY_DIRS})
  #message(STATUS "Boost libraries: " ${Boost_LIBRARIES})
endif()

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")

# Kociemba stuff
include_directories(${CMAKE_SOURCE_DIR}/kociemba/kociemba/ckociemba/include)
link_directories(${CMAKE_SOURCE_DIR}/kociemba/kociemba/ckociemba/lib)

include_directories(${PROJECT_SOURCE_DIR}
                    "${PROJECT_SOURCE_DIR}/utils/"
                    "${PROJECT_SOURCE_DIR}/source/")

add_executable(rc main.cpp ${PROJECT_SOURCE_DIR}/source/Cube.cpp
                  ${PROJECT_SOURCE_DIR}/source/CubeSolve.cpp
                  ${PROJECT_SOURCE_DIR}/source/CubeManipulateFace.cpp
                  ${PROJECT_SOURCE_DIR}/source/CubeRotations.cpp
                  ${PROJECT_SOURCE_DIR}/utils/Utils.cpp
                  ${PROJECT_SOURCE_DIR}/utils/CubeParams.cpp)

add_dependencies(rc git-version)
target_link_libraries(rc boost_program_options.a) # boost::program_options
target_link_libraries(rc libkociemba.a) # kociemba library

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
                          "${PROJECT_SOURCE_DIR}/utils/Utils.cpp"
                          "${PROJECT_SOURCE_DIR}/source/CubeManipulateFace.cpp"
                          "${PROJECT_SOURCE_DIR}/source/CubeRotations.cpp")

  target_link_libraries(cubeTest gtest)

  # Test face twist logic.
  add_executable(cubeTwistTest "${PROJECT_SOURCE_DIR}/test/TestCubeTwists.cpp"
                               "${PROJECT_SOURCE_DIR}/source/Cube.cpp"
                               "${PROJECT_SOURCE_DIR}/utils/Utils.cpp"
                               "${PROJECT_SOURCE_DIR}/source/CubeManipulateFace.cpp"
                               "${PROJECT_SOURCE_DIR}/source/CubeRotations.cpp")

  target_link_libraries(cubeTwistTest gtest)

  # Test cube rotation logic.
  add_executable(cubeRotationTest "${PROJECT_SOURCE_DIR}/test/TestCubeRotations.cpp"
                                  "${PROJECT_SOURCE_DIR}/source/Cube.cpp"
                                  "${PROJECT_SOURCE_DIR}/utils/Utils.cpp"
                                  "${PROJECT_SOURCE_DIR}/source/CubeManipulateFace.cpp"
                                  "${PROJECT_SOURCE_DIR}/source/CubeRotations.cpp")

  target_link_libraries(cubeRotationTest gtest)

endif() # gtest_build_tests
