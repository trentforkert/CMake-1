cmake_minimum_required(VERSION 3.0)

project(Ddoc D)

include(UseD)

add_library(foo foo.d secret.d internal/thing.d)

add_ddoc(ddoc_foo
  TARGETS foo
  EXCLUDE_SOURCES secret.d
  EXCLUDE_MODULES "internal\\\\..*"
  VERSION DocOnly
  ASSETS asset.txt
  MACROS macro.ddoc
  SOURCES index.d
)

add_ddoc(ddoc_foo_other
  TARGETS foo
  EXCLUDE_SOURCES secret.d
  MACROS macro.ddoc
  PACKAGE_SEPARATOR /
  OUTPUT_DIRECTORY otherDocs
)

add_ddoc(ddoc_foo_noall
  TARGETS foo
  OUTPUT_DIRECTORY noDocsHere
  EXCLUDE_FROM_ALL
)

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/ddocChecker.d.in"
  "${CMAKE_CURRENT_BINARY_DIR}/ddocChecker.d" @ONLY ESCAPE_QUOTES)

set(DDOC_CHECKER_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}" PARENT_SCOPE)

include_directories(${DDOC_CHECKER_INCLUDE_DIR})

add_library(ddocChecker "${CMAKE_CURRENT_BINARY_DIR}/ddocChecker.d")
