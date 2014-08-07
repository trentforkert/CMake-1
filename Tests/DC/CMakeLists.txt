cmake_minimum_required(VERSION 3.0)
project(DC C D)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_library(clib clib.c)

add_executable(DC main.d)

target_link_libraries(DC clib)

# extra tests from cmake-d
# build lib first
add_subdirectory(lib_1)
add_subdirectory(app_1)
add_subdirectory(app_2)
