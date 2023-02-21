cmake_minimum_required(VERSION 3.20)
project(scene-data)

file(GLOB_RECURSE SRCS "src/*.cpp")
include_directories(src/)

add_library(scene-data ${SRCS})