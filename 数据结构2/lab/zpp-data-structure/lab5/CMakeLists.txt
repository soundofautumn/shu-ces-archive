cmake_minimum_required(VERSION 3.26)

project(Test)

set(CMAKE_CXX_STANDARD 20)

add_definitions(-Wall)

if (MSVC)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif ()

add_executable(Test main.cpp
)