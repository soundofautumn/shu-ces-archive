cmake_minimum_required(VERSION 3.23)
project(MIDIexample)

link_libraries(winmm)
link_directories(${PROJECT_SOURCE_DIR}/lib)

include_directories(${PROJECT_SOURCE_DIR}/include)
aux_source_directory(${PROJECT_SOURCE_DIR}/src DIR_SRCS)

set(CMAKE_CXX_STANDARD 14)

#add_executable(main main.cpp MIDIexample.cpp MIDIexample.h)
add_executable(main ${DIR_SRCS} main.cpp MIDIPlayer.h MIDIPlayer.cpp)