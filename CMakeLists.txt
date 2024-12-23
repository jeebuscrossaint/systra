cmake_minimum_required(VERSION 3.31.3)

project(initmgr)

set(CMAKE_CXX_STANDARD 23)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

add_executable(initmgr
        src/main.cc
)

target_link_libraries(initmgr Qt6::Widgets)