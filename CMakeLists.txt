cmake_minimum_required(VERSION 3.10)

project(RubiksCube)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)


include_directories("${PROJECT_SOURCE_DIR}/source/")

add_executable(rc main.cpp ${PROJECT_SOURCE_DIR}/source/Cube.cpp)

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

  add_executable(cubeTwistTest "${PROJECT_SOURCE_DIR}/test/TestCubeTwists.cpp"
                               "${PROJECT_SOURCE_DIR}/source/Cube.cpp")

  target_link_libraries(cubeTwistTest gtest)

endif() # gtest_build_tests
