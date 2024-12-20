cmake_minimum_required(VERSION 3.0)
project(initui VERSION 1.0)

# C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# find ncurses
find_package(Curses REQUIRED)

#include directories
include_directories(${CURSES_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/src/include)

# collect source files
file (GLOB_RECURSE SOURCES
    "src/initui/*.cpp"
    "src/openrc/*cpp"
    "src/runit/*cpp"
    "src/systemd/*cpp"    
)

add_executable(initui ${SOURCES})

# link ncurses
target_link_libraries(initui ${CURSES_LIBRARIES})