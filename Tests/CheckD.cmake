
#=============================================================================
# Copyright 2014 Kitware, Inc.
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distribute this file outside of CMake, substitute the full
#  License text for the above reference.)

if(NOT DEFINED CMAKE_D_COMPILER)
  set(_desc "Looking for a D compiler")
  message(STATUS ${_desc})
  file(REMOVE_RECURSE ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/CheckD)
  file(WRITE "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/CheckD/CMakeLists.txt"
    "cmake_minimum_required(VERSION 3.0)
project(CheckD D)
file(WRITE \"\${CMAKE_CURRENT_BINARY_DIR}/result.cmake\"
  \"set(CMAKE_D_COMPILER \\\"\${CMAKE_D_COMPILER}\\\")\\n\"
  \"set(CMAKE_D_FLAGS \\\"\${CMAKE_D_FLAGS}\\\")\\n\"
  )
")
  execute_process(
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/CheckD
    COMMAND ${CMAKE_COMMAND} . -G ${CMAKE_GENERATOR}
    OUTPUT_VARIABLE output
    ERROR_VARIABLE output
    RESULT_VARIABLE result
    )
  include(${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/CheckD/result.cmake OPTIONAL)
  if(CMAKE_D_COMPILER AND "${result}" STREQUAL "0")
    file(APPEND ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeOutput.log
      "${_desc} passed with the following output:\n"
      "${output}\n")
  else()
    set(CMAKE_D_COMPILER NOTFOUND)
    file(APPEND ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeError.log
      "${_desc} failed with the following output:\n"
      "${output}\n")
  endif()
  message(STATUS "${_desc} - ${CMAKE_D_COMPILER}")
  set(CMAKE_D_COMPILER "${CMAKE_D_COMPILER}" CACHE FILEPATH "D compiler")
  mark_as_advanced(CMAKE_D_COMPILER)
  set(CMAKE_D_FLAGS "${CMAKE_D_FLAGS}" CACHE STRING "D flags")
  mark_as_advanced(CMAKE_D_FLAGS)
endif()
