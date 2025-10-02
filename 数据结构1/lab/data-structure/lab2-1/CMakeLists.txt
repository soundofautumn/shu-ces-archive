cmake_minimum_required(VERSION 3.26)

project(LinkQueue)

set(CMAKE_CXX_STANDARD 11)

add_executable(LinkQueue
        Point2D.cpp
        Point2D.h
        LinkQueue.h
        main.cpp)