cmake_minimum_required(VERSION 3.26)

project(MineHeap)

set(CMAKE_CXX_STANDARD 11)

add_executable(MineHeap
        MineHeap.h
        Assistance.h
        TestMineHeap.cpp
        MaxHeap.h)