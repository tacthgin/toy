cmake_minimum_required(VERSION 3.3)
project(Rasterization)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

aux_source_directory(. DIR_SRCS)
add_executable(Rasterization ${DIR_SRCS})