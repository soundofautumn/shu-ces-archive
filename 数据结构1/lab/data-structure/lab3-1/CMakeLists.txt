cmake_minimum_required(VERSION 3.26)

project(KMP_verify)

set(CMAKE_CXX_STANDARD 11)

add_executable(KMP_verify
        Assistance.h
        KMP.h
        LinkList.h
        Node.h
        String.h
        TestKMP.cpp
)