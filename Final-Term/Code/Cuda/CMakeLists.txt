cmake_minimum_required(VERSION 3.10)
project(Cuda_DES)

set(CMAKE_CXX_STANDARD 11)

add_executable(Cuda_DES main.cu utils.h des.h)