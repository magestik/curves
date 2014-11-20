cmake_minimum_required(VERSION 2.8.11)

FILE(GLOB src *.cpp *.h)

add_library(curves ${src})
