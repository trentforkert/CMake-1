
#=============================================================================
# Copyright 2013-2014 Kitware, Inc.
# Copyright 2013-2014 Trent Forkert
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

# This file tests the D compiler, and determines its ABI.

if( CMAKE_D_COMPILER_FORCED )
  set(CMAKE_D_COMPILER_WORKS TRUE)
  return()
endif()

include(CMakeTestCompilerCommon)

unset(CMAKE_D_COMPILER_WORKS CACHE)

if(NOT CMAKE_D_COMPILER_WORKS )
  PrintTestCompilerStatus("D" "")
  file(WRITE ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeTmp/testDCompiler.d
    "module testDCompiler; int main(string[] args){ return cast(int) args.length - 1; }\n")
  try_compile(CMAKE_D_COMPILER_WORKS ${CMAKE_BINARY_DIR}
    ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeTmp/testDCompiler.d
    OUTPUT_VARIABLE __CMAKE_D_COMPILER_OUTPUT)
  set(CMAKE_D_COMPILER_WORKS ${CMAKE_D_COMPILER_WORKS})
  unset(CMAKE_D_COMPILER_WORKS CACHE)
  set(D_TEST_WAS_RUN 1)
endif()

if(NOT CMAKE_D_COMPILER_WORKS)
  PrintTestCompilerStatus("D" " -- broken")
  file(APPEND ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeError.log
    "Determining if the D compiler works failed with "
    "the following output:\n${__CMAKE_D_COMPILER_OUTPUT}\n\n"
    "CMake will not be able to correctly generate this project.")
  message(FATAL_ERROR "The D compiler \"${CMAKE_D_COMPILER}\" "
    "is not able to compile a simple test program.\nIt fails "
    "with the following output:\n ${__CMAKE_D_COMPILER_OUTPUT}\n\n"
    "CMake will not be able to correctly generate this project.")
else()
  if(D_TEST_WAS_RUN)
    PrintTestCompilerStatus("D" " -- works")
    file(APPEND ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeOutput.log
      "Determining if the D compiler works passed with "
      "the following output:\n${__CMAKE_D_COMPILER_OUTPUT}\n\n")
  endif()

  include(CMakeDetermineCompilerABI)
  cmake_determine_compiler_abi(D ${CMAKE_ROOT}/Modules/CMakeDCompilerABI.d)

  configure_file(
    ${CMAKE_ROOT}/Modules/CMakeDCompiler.cmake.in
    ${CMAKE_PLATFORM_INFO_DIR}/CMakeDCompiler.cmake
    @ONLY IMMEDIATE)
  include(${CMAKE_PLATFORM_INFO_DIR}/CMakeDCompiler.cmake)

  if(CMAKE_D_SIZEOF_DATA_PTR)
    foreach(f ${CMAKE_D_ABI_FILES})
      include(${f})
    endforeach()

    unset(CMAKE_D_ABI_FILES)
  endif()
endif()

unset(__CMAKE_D_COMPILER_OUTPUT)
