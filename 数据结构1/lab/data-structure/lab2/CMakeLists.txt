cmake_minimum_required(VERSION 3.26)

project(SeqStack)

set(CMAKE_CXX_STANDARD 11)

add_executable(SeqStack
        main.cpp
        SeqStack.h
        Point2D.cpp
        Point2D.h
)