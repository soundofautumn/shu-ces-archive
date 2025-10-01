cmake_minimum_required(VERSION 3.25)
project(LinkList)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(LinkList
        AddressBook.cpp
        Banking.cpp
        Banking.h
        BankingTest.cpp
        LinkList.h
        Main.cpp
        Test.cpp)
