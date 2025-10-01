cmake_minimum_required(VERSION 3.26)
project(MyVector)

set(CMAKE_CXX_STANDARD 11)

add_executable(MyVector
        MyVector.h
        MyVectorTest.cpp
        my_assert.h
)
