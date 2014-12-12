cmake_minimum_required(VERSION 2.8.11)

project(Curves)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(USE_RECURSIVE_EVAL FALSE CACHE BOOL "Use recursive function for BSpline evaluation")

include_directories(external/linear-algebra/include)

add_subdirectory(src)
add_subdirectory(test)
