cmake_minimum_required(VERSION 2.8.11)

FILE(GLOB_RECURSE src *.cpp *.h)

if(USE_RECURSIVE_EVAL)
add_definitions(-DUSE_RECURSIVE_EVAL=1)
message("Will use recursive function for BSpline evaluation")
else()
add_definitions(-DUSE_RECURSIVE_EVAL=0)
message("Will use iterative function for BSpline evaluation")
endif()

add_library(curves ${src})
