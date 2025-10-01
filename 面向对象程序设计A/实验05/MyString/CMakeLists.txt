cmake_minimum_required(VERSION 3.26)
project(MyString)

set(CMAKE_CXX_STANDARD 11)

add_executable(MyString
        MyString.h
        MyStringTest.cpp
        MyString.cpp
        my_assert.h)
