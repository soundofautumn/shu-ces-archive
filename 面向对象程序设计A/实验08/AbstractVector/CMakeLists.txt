cmake_minimum_required(VERSION 3.26)
project(AbstractVector)

set(CMAKE_CXX_STANDARD 17)

add_executable(AbstractVector main.cpp
        MyVector.h
        MyString.h
        MyMathVector.h
        MyString.cpp
        my_assert.h
)
