
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

# This file finds and determines which D compiler to use.


include(${CMAKE_ROOT}/Modules/CMakeDetermineCompiler.cmake)
include(Platform/${CMAKE_SYSTEM_NAME}-D OPTIONAL)

#if("${CMAKE_GENERATOR}" MATCHES "Visual Studio")
    #find_program(CMAKE_D_COMPILER "${CMAKE_GENERATOR_DC}")
if("${CMAKE_GENERATOR}" MATCHES "Xcode")
  set(CMAKE_D_COMPILER_XCODE_TYPE sourcecode.d.d)
else()
  if(NOT CMAKE_D_COMPILER)
    set(CMAKE_D_COMPILER_INIT NOTFOUND)

    if($ENV{DC} MATCHES ".+")
      get_filename_component(CMAKE_D_COMPILER_INIT $ENV{DC} PROGRAM PROGRAM_ARGS CMAKE_D_FLAGS_ENV_INIT)
      if(CMAKE_D_FLAGS_ENV_INIT)
        set(CMAKE_D_COMPILER_ARG1 "${CMAKE_D_FLAGS_ENV_INIT}" CACHE STRING "First argument to D compiler")
      endif()
      if(NOT EXISTS ${CMAKE_D_COMPILER_INIT})
        message(FATAL_ERROR "Could not find compiler set in environment variable DC:\n$ENV{DC}.")
      endif()
    endif()

    #if(CMAKE_GENERATOR_DC)
      #if(NOT CMAKE_D_COMPILER_INIT)
        #set(CMAKE_D_COMPILER_INIT ${CMAKE_GENERATOR_DC})
      #endif()
    #endif()

    if(NOT CMAKE_D_COMPILER_INIT)
      # TODO: Add toolchain prefix
      set( CMAKE_D_COMPILER_LIST dmd gdc ldc2 )
    endif()

    _cmake_find_compiler(D)
  else()
    list(LENGTH CMAKE_D_COMPILER _CMAKE_D_COMPILER_LIST_LENGTH)
    if("${_CMAKE_D_COMPILER_LIST_LENGTH}" EQUAL 2)
      list(GET CMAKE_D_COMPILER 1 CMAKE_D_COMPILER_ARG1)
      list(GET CMAKE_D_COMPILER 0 CMAKE_D_COMPILER)
    endif()

    get_filename_component(_CMAKE_USER_D_COMPILER_PATH "${CMAKE_D_COMPILER}" PATH)
    if(NOT _CMAKE_USER_D_COMPILER_PATH)
      find_program(CMAKE_D_COMPILER_WITH_PATH NAMES ${CMAKE_D_COMPILER})
      mark_as_advanced(CMAKE_D_COMPILER_WITH_PATH)
      if(CMAKE_D_COMPILER_WITH_PATH)
        set(CMAKE_D_COMPILER ${CMAKE_D_COMPILER_WITH_PATH} CACHE STRING "D compiler" FORCE)
      endif()
    endif()
  endif()
  mark_as_advanced(CMAKE_D_COMPILER)
endif()

if(NOT CMAKE_D_COMPILER_ID_RUN)
  set(CMAKE_D_COMPILER_ID_RUN 1)

  set(CMAKE_D_COMPILER_ID)
  include(${CMAKE_ROOT}/Modules/CMakeDetermineCompilerId.cmake)

  cmake_determine_compiler_id(D DFLAGS "CMakeDCompilerId.d")

  #file(WRITE ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeTmp/checkFrontend.d
  #"void main(){ pragma(msg, __VERSION__); }\n")
  #exec_program("${CMAKE_D_COMPILER}"
  #ARGS "${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/CMakeTmp/checkFrontend.d"
  #OUTPUT_VARIABLE CMAKE_D_COMPILER_OUTPUT)
  #message(STATUS "checkFrontend: ${CMAKE_D_COMPILER_OUTPUT}")

  if("${CMAKE_D_COMPILER_ID}" MATCHES "GNU")
    set(CMAKE_COMPILER_IS_GNUDC 1)
  endif()

  if("${CMAKE_D_PLATFORM_ID}" MATCHES "MinGW")
    set(CMAKE_COMPILER_IS_MINGW 1)
  elseif("${CMAKE_D_PLATFORM_ID}" MATCHES "Cygwin")
    set(CMAKE_COMPILER_IS_CYGWIN 1)
  endif()
endif()

if(NOT _CMAKE_TOOLCHAIN_LOCATION)
  get_filename_component(_CMAKE_TOOLCHAIN_LOCATION "${CMAKE_D_COMPILER}" PATH)
endif()

if(CMAKE_CROSSCOMPILING
    AND "${CMAKE_D_COMPILER_ID}" MATCHES "GNU"
    AND NOT _CMAKE_TOOLCHAIN_PREFIX)
  get_filename_component(COMPILER_BASENAME "${CMAKE_D_COMPILER}" NAME)
  if(COMPILER_BASENAME MATCHES "^(.+-)gdc(-[0-9]+\\.[0-9]+\\.[0-9]+)?(\\.exe)?$")
    set(_CMAKE_TOOLCHAIN_PREFIX ${CMAKE_MATCH_1})
  endif()

  if("${_CMAKE_TOOLCHAIN_PREFIX}" MATCHES "(.+-)?llvm-$")
    set(_CMAKE_TOOLCHAIN_PREFIX ${CMAKE_MATCH_1})
  endif()
endif()

include(${CMAKE_ROOT}/Modules/CMakeClDeps.cmake)
include(${CMAKE_ROOT}/Modules/CMakeDDeps.cmake)
include(CMakeFindBinUtils)
if(MSVC_D_ARCHITECTURE_ID)
  set(SET_MSVC_D_ARCHITECTURE_ID
    "set(MSVC_D_ARCHITECTURE_ID ${MSVC_D_ARCHITECTURE_ID})")
endif()

get_filename_component(COMPILER_LOCATION "${CMAKE_D_COMPILER}" PATH)
find_program(CMAKE_AR NAMES ar PATHS ${COMPILER_LOCATION})
find_program(CMAKE_RANLIB NAMES ranlib)
if(NOT CMAKE_RANLIB)
  set(CMAKE_RANLIB : CACHE INTERNAL "noop for ranlib")
endif()
mark_as_advanced(CMAKE_RANLIB)


configure_file(${CMAKE_ROOT}/Modules/CMakeDCompiler.cmake.in
  ${CMAKE_PLATFORM_INFO_DIR}/CMakeDCompiler.cmake
  @ONLY IMMEDIATE
  )
set(CMAKE_D_COMPILER_ENV_VAR "DC")
