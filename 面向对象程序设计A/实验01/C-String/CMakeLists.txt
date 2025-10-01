cmake_minimum_required(VERSION 3.23)
project(C_String)

set(CMAKE_CXX_STANDARD 14)

include_directories(C-String)

add_executable(C_String
        C-String/C-String.cpp
        C-String/C-String.h
        C-String/Main.cpp
        C-String/SortStrings.cpp
        C-String/SortStrings.h)
