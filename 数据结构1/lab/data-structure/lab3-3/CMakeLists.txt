cmake_minimum_required(VERSION 3.26)

project(Gen_List)

set(CMAKE_CXX_STANDARD 11)

add_executable(Gen_List
        Assistance.h
        GenList.h
        GenNode.h
        TestGenList.cpp
)