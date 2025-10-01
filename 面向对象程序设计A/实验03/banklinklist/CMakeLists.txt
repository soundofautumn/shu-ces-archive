cmake_minimum_required(VERSION 3.26)
project(banklinklist)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(banklinklist
        Account.cpp
        Account.h
        main.cpp
        UserList.cpp
        UserList.h
        LinkList.h
)
