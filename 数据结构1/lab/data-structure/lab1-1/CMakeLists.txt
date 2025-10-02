cmake_minimum_required(VERSION 3.26)

project(DblLinkList)

set(CMAKE_CXX_STANDARD 11)

add_executable(DblLinkList
        DblLinkList.h
        main.cpp
        Point2D.cpp)