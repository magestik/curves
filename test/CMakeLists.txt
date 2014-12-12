cmake_minimum_required(VERSION 2.8.11)

include_directories(../src)

add_executable(spline spline.cpp)
target_link_libraries(spline curves)

add_executable(patch patch.cpp)
target_link_libraries(patch curves)

add_executable(lagrange lagrange.cpp)
target_link_libraries(lagrange curves)

add_executable(benchmark benchmark.cpp)
target_link_libraries(benchmark curves)
