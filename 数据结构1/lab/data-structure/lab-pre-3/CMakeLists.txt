cmake_minimum_required(VERSION 3.26)

project(Median)

set(CMAKE_CXX_STANDARD 11)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/median.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(Median
        Heap.h
        main.cpp
        Median.h
)