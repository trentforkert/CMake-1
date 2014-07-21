cmake_minimum_required(VERSION 3.0)
project(DC C D)

add_library(clib clib.c)

add_executable(DC main.d)

target_link_libraries(DC clib)

