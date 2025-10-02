cmake_minimum_required(VERSION 3.26)

project(AirwayBillSystem)

set(CMAKE_CXX_STANDARD 11)

add_executable(AirwayBillSystem
        AirwayBillSystem.cpp
        AirwayBillSystem.h
        main.cpp
        Flight.cpp
        Flight.h
        common_exception.h
        Queue.h
        SeqList.h
        Passenger.cpp
        Passenger.h
        LinkedMap.h
        datetime.cpp
        datetime.h
        AirwayBillSystemMain.cpp
)