cmake_minimum_required(VERSION 3.25)
project(03_LinkList_code02)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(03_LinkList_code02
        Assistance.h
        LinkList.h
        Node.h
        TestLinkList.cpp)
