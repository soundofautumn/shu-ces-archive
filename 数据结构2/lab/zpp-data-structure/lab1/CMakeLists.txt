cmake_minimum_required(VERSION 3.26)

project(Tree)

set(CMAKE_CXX_STANDARD 11)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/tree.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(Tree main.cpp
        Tree.cpp
        Tree.h
        Assistant.cpp)