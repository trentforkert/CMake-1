# a simple D only test case
cmake_minimum_required(VERSION 3.0)
project(DOnly D)

# TODO: Support shared on compilers that support it
set(_SHARED STATIC)

add_library(hello STATIC hello.d)
add_library(world ${_SHARED} world.d)
add_executable(DOnly donly.d aux.d)
target_link_libraries(DOnly hello world)

# TODO: Adds unsupported compiler flags
# add_library(testDModule MODULE testDModule.d)
