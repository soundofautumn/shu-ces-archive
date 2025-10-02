cmake_minimum_required(VERSION 3.26)

project(Tri_spare_matrix)

set(CMAKE_CXX_STANDARD 11)

add_executable(TriSparseMatrix
        Assistance.h
        TestTriSparseMatrix.cpp
        Triple.h
        TriSparseMatrix.h
)