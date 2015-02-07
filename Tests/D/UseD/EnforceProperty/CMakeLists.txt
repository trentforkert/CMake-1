cmake_minimum_required(VERSION 3.0)

project(EnforceProperty D)
include(UseD)

# Older versions had a bug that would break this
if(CMAKE_D_COMPILER_VERSION VERSION_GREATER 2.056)
  d_enforce_property()
endif()

add_library(enforceProperty enforceProperty.d)
