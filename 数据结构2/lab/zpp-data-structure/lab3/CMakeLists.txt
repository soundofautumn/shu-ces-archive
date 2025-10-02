cmake_minimum_required(VERSION 3.26)

project(Dictionary)

set(CMAKE_CXX_STANDARD 11)

add_definitions(-Wall)

if (MSVC)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif ()

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/dictionary.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(Dictionary
        main.cpp
        Dictionary.cpp
        Dictionary.h
        string_utils.h
        HashMap.h
        console_utils.h
)