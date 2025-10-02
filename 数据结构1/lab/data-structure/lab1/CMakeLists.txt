cmake_minimum_required(VERSION 3.26)

project(SeqList)

set(CMAKE_CXX_STANDARD 11)

add_executable(SeqList
        SeqList.h
        main.cpp
        Point2D.cpp)