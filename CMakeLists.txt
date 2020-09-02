cmake_minimum_required(VERSION 3.16)
project(OSExp03)

set(CMAKE_CXX_STANDARD 14)

add_executable(OSExp03 main.cpp myrandom.h instruction.h page.h ram.h)