cmake_minimum_required(VERSION 2.8.11)

FILE(GLOB src *.cpp *.h)

include_directories(../src)

add_executable(test ${src})

target_link_libraries(test curves)
