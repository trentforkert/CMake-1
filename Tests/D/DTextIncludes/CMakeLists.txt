cmake_minimum_required(VERSION 3.0)
project(DTextIncludes C D)

include_directories(TEXT ${CMAKE_CURRENT_SOURCE_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Confirm that C is not broken by include_directories(TEXT)
add_library(foo foo.c)

add_executable(DTextIncludes main.d)

target_link_libraries(DTextIncludes foo)
