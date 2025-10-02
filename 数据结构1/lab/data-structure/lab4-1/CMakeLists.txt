cmake_minimum_required(VERSION 3.26)

project(BinaryTree)

set(CMAKE_CXX_STANDARD 11)

add_executable(BinaryTree
        Assistance.h
        BinaryTree.h
        BinTreeNode.h
        LinkQueue.h
        Node.h
        TestBinaryTree.cpp
        LinkStack.h)