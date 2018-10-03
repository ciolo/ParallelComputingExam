cmake_minimum_required(VERSION 3.10)
project(DesCpp)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_COMPILER "/usr/local/bin/g++-7")
set(CMAKE_CXX_FLAGS "-fopenmp")

add_executable(DesCpp main.cpp des.h des.cpp utils.h utils.cpp)