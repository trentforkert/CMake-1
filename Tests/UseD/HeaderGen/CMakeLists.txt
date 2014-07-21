cmake_minimum_required(VERSION 3.0)

project(HeaderGen D)
include(UseD)

add_library(HeaderGenLib1 STATIC hgl1.d)
add_library(HeaderGenLib2 STATIC hgl2.d)

add_d_headers(TARGETS HeaderGenLib1 HeaderGenLib2)

add_d_headers(TARGETS HeaderGenLib1 HeaderGenLib2
  OUTPUT_DIRECTORY headers)

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/headerChecker.d.in"
  "${CMAKE_CURRENT_BINARY_DIR}/headerChecker.d" @ONLY ESCAPE_QUOTES)

set(HEADER_CHECKER_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}" PARENT_SCOPE)

include_directories(${HEADER_CHECKER_INCLUDE_DIR})

add_library(headerChecker "${CMAKE_CURRENT_BINARY_DIR}/headerChecker.d")
