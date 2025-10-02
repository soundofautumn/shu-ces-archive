cmake_minimum_required(VERSION 3.26)

project(Graph)

set(CMAKE_CXX_STANDARD 11)

# Qt6

find_package(Qt6 COMPONENTS Widgets Core Gui REQUIRED)

qt_standard_project_setup()

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/大中国乡.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(Graph main.cpp
        Graph.h
        Assistant.h
        UnionFind.h
        graphview.cpp
        graphview.h
        graphview.ui
        mainview.cpp
        mainview.h
        mainview.ui
)

target_link_libraries(Graph PRIVATE Qt6::Widgets Qt6::Core Qt6::Gui)

set_target_properties(Graph PROPERTIES
        WIN32_EXECUTABLE ON
        MACOSX_BUNDLE ON
)

install(TARGETS Graph
        BUNDLE  DESTINATION .
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_generate_deploy_app_script(
        TARGET Graph
        OUTPUT_SCRIPT deploy_script
        NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})