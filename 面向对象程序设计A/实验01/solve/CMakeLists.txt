cmake_minimum_required(VERSION 3.23)
project(solve)

set(CMAKE_CXX_STANDARD 14)

add_executable(solve Solver.cpp Solver.h main.cpp)
