cmake_minimum_required(VERSION 3.26)

project(DictRandom)

set(CMAKE_CXX_STANDARD 20)

add_definitions(-Wall)

if (MSVC)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
endif ()

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/dictrandom.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(DictRandom main.cpp
        DictReader.cpp
        DictReader.h
        sorts.cpp
        sorts.h
)