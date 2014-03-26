
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

# This file sets basic D flags, and loads compiler-specific settings.

# DMD uses the C compiler for linking on Unix systems
# We tell it to use whatever C compiler CMake finds
if(UNIX AND CMAKE_D_COMPILER_ID MATCHES "DigitalMars")
  if(NOT CMAKE_C_COMPILER_LOADED)
    #message(STATUS "DigitalMars D requires a C compiler for linking on Unix")
    enable_language(C)
  endif()
  set(ENV{CC} "${CMAKE_C_COMPILER}" INTERNAL STRING "" PARENT_SCOPE)
endif()

if(WIN32
   AND CMAKE_SYSTEM_PROCESSOR STREQUAL "x86"
   AND CMAKE_D_COMPILER_ID STREQUAL "DigitalMars"
  )
  if( (DEFINED CMAKE_C_COMPILER
       AND NOT CMAKE_C_COMPILER_ID STREQUAL "DigitalMars")
      OR
      (DEFINED CMAKE_CXX_COMPILER
       AND NOT CMAKE_CXX_COMPILER_ID STREQUAL "DigitalMars")
    )
    message(FATAL_ERROR "DMD on Win32 uses OMF instead of COFF object format.
It is known to have linking problems with non-DigitalMars C/C++ compilers.
Please use dmc, which can be found at http://digitalmars.com
Hint: set CMAKE_C_COMPILER and/or CMAKE_CXX_COMPILER accordingly.")
  endif()
endif()

if(UNIX)
  set(CMAKE_D_OUTPUT_EXTENSION .o)
else()
  set(CMAKE_D_OUTPUT_EXTENSION .obj)
endif()

set(_INCLUDED_FILE 0)

if(CMAKE_D_COMPILER_ID)
  include(Compiler/${CMAKE_D_COMPILER_ID}-D OPTIONAL)
endif()

set(CMAKE_BASE_NAME)
get_filename_component(CMAKE_BASE_NAME ${CMAKE_D_COMPILER} NAME_WE)
if(CMAKE_COMPILER_IS_GNUD)
  set(CMAKE_BASE_NAME gdc)
endif()

if(CMAKE_SYSTEM_PROCESSOR)
  if(CMAKE_D_COMPILER_ID)
    include(Platform/${CMAKE_SYSTEM_NAME}-${CMAKE_D_COMPILER_ID}-D-${CMAKE_SYSTEM_PROCESSOR} OPTIONAL RESULT_VARIABLE _INCLUDED_FILE)
  endif()

  if(NOT _INCLUDED_FILE)
    include(Platform/${CMAKE_SYSTEM_NAME}-${CMAKE_BASE_NAME}-${CMAKE_SYSTEM_PROCESSOR} OPTIONAL)
  endif()
endif()

if(CMAKE_D_COMPILER_ID)
  include(Platform/${CMAKE_SYSTEM_NAME}-${CMAKE_D_COMPILER_ID}-D
    OPTIONAL RESULT_VARIABLE _INCLUDED_FILE)
endif()

if(NOT _INCLUDED_FILE)
  include(Platform/${CMAKE_SYSTEM_NAME}-${CMAKE_BASE_NAME}
    OPTIONAL RESULT_VARIABLE _INCLUDED_FILE)
endif()

if(NOT _INCLUDED_FILE)
  include(${CMAKE_ROOT}/Modules/Platform/${CMAKE_SYSTEM_NAME} OPTIONAL)
endif()

if(CMAKE_D_SIZEOF_DATA_PTR)
  foreach(f ${CMAKE_D_ABI_FILES})
    include(${f})
  endforeach()
  unset(CMAKE_D_ABI_FILES)
endif()

if(CMAKE_USER_MAKE_RULES_OVERRIDE)
  include(${CMAKE_USER_MAKE_RULES_OVERRIDE} RESULT_VARIABLE _override)
  set(CMAKE_USER_MAKE_RULES_OVERRIDE "${_override}")
endif()

if(CMAKE_USER_MAKE_RULES_OVERRIDE_D )
  include(${CMAKE_USER_MAKE_RULES_OVERRIDE_D} RESULT_VARIABLE _override)
  set(CMAKE_USER_MAKE_RULES_OVERRIDE_D "${_override}")
endif()

if(NOT CMAKE_MODULE_EXISTS)
  set(CMAKE_SHARED_MODULE_D_FLAGS ${CMAKE_SHARED_LIBRARY_D_FLAGS})
  set(CMAKE_SHARED_MODULE_CREATE_D_FLAGS ${CMAKE_SHARED_LIBRARY_CREATE_D_FLAGS})
endif()

set(CMAKE_D_FLAGS_INIT $ENV{DFLAGS} ${CMAKE_D_FLAGS_INIT})

if(CMAKE_D_FLAGS_INIT STREQUAL " ")
  set(CMAKE_D_FLAGS_INIT)
endif()
set(CMAKE_D_FLAGS "${CMAKE_D_FLAGS_INIT}" CACHE STRING
  "Flags used by the D compiler during all build types.")

if(NOT CMAKE_NOT_USING_CONFIG_FLAGS)
  if(NOT CMAKE_NO_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE_INIT} CACHE STRING
      "Choose the type of build, options are: None, Debug, Release, RelWithDebInfo, MinSizeRel.")
  endif()
  set(CMAKE_D_FLAGS_DEBUG "${CMAKE_D_FLAGS_DEBUG_INIT}" CACHE STRING
    "Flags used by the D compiler during debug builds.")
  set(CMAKE_D_FLAGS_MINSIZEREL "${CMAKE_D_FLAGS_MINSIZEREL_INIT}" CACHE STRING
    "Flags used by the D compiler during release minsize builds.")
  set(CMAKE_D_FLAGS_RELEASE "${CMAKE_D_FLAGS_RELEASE_INIT}" CACHE STRING
    "Flags used by the D compiler during release builds.")
  set(CMAKE_D_FLAGS_RELWITHDEBINFO "${CMAKE_D_FLAGS_RELWITHDEBINFO_INIT}" CACHE STRING
    "Flags used by the D compiler during Release with Debug Info builds.")
endif()

if(CMAKE_D_STANDARD_LIBRARIES_INIT)
  set(CMAKE_D_STANDARD_LIBRARIES "${CMAKE_D_STANDARD_LIBRARIES_INIT}"
    CACHE STRING "Libraries linked by default with all D applications.")
  mark_as_advanced(CMAKE_D_STANDARD_LIBRARIES)
endif()

include(CMakeCommonLanguageInclude)

if(NOT CMAKE_D_CREATE_SHARED_LIBRARY)
  set(CMAKE_D_CREATE_SHARED_LIBRARY
    "<CMAKE_D_COMPILER> <CMAKE_SHARED_LIBRARY_D_FLAGS> <LANGUAGE_COMPILE_FLAGS> <LINK_FLAGS> <CMAKE_SHARED_LIBRARY_CREATE_D_FLAGS> <SONAME_FLAG><TARGET_SONAME> -of<TARGET> <OBJECTS> <LINK_LIBRARIES>")
endif()

if(NOT CMAKE_D_CREATE_SHARED_MODULE)
  set(CMAKE_D_CREATE_SHARED_MODULE ${CMAKE_D_CREATE_SHARED_LIBRARY})
endif()

if(NOT DEFINED CMAKE_D_CREATE_STATIC_LIBRARY)
  set(CMAKE_D_CREATE_STATIC_LIBRARY "<CMAKE_D_COMPILER> -lib -of<TARGET> <LINK_FLAGS> <OBJECTS>")
endif()

if(NOT DEFINED CMAKE_D_ARCHIVE_CREATE)
  set(CMAKE_D_ARCHIVE_CREATE "<CMAKE_AR> cr <TARGET> <LINK_FLAGS> <OBJECTS>")
endif()
if(NOT DEFINED CMAKE_D_ARCHIVE_APPEND)
  set(CMAKE_D_ARCHIVE_APPEND "<CMAKE_AR> r  <TARGET> <LINK_FLAGS> <OBJECTS>")
endif()
if(NOT DEFINED CMAKE_D_ARCHIVE_FINISH)
  set(CMAKE_D_ARCHIVE_FINISH "<CMAKE_RANLIB> <TARGET>")
endif()

if(NOT CMAKE_D_COMPILE_OBJECT)
  set(CMAKE_D_COMPILE_OBJECT
    "<CMAKE_D_COMPILER> <FLAGS> -I=<CMAKE_CURRENT_SOURCE_DIR> -of<OBJECT> -c <SOURCE>")
endif()

if(NOT CMAKE_D_LINK_EXECUTABLE)
  set(CMAKE_D_LINK_EXECUTABLE
    "<CMAKE_D_COMPILER> <FLAGS> <CMAKE_D_LINK_FLAGS> <LINK_FLAGS> <OBJECTS> -of<TARGET> <LINK_LIBRARIES>")
endif()

if(NOT CMAKE_EXECUTABLE_RUNTIME_D_FLAG)
  set(CMAKE_EXECUTABLE_RUNTIME_D_FLAG ${CMAKE_SHARED_LIBRARY_RUNTIME_D_FLAG})
endif()

if(NOT CMAKE_EXECUTABLE_RUNTIME_D_FLAG_SEP)
  set(CMAKE_EXECUTABLE_RUNTIME_D_FLAG_SEP ${CMAKE_SHARED_LIBRARY_RUNTIME_D_FLAG_SEP})
endif()

if(NOT CMAKE_EXECUTABLE_RPATH_LINK_D_FLAG)
  set(CMAKE_EXECUTABLE_RPATH_LINK_D_FLAG ${CMAKE_SHARED_LIBRARY_RPATH_LINK_D_FLAG})
endif()

mark_as_advanced(
  CMAKE_D_FLAGS
  CMAKE_D_FLAGS_DEBUG
  CMAKE_D_FLAGS_MINSIZEREL
  CMAKE_D_FLAGS_RELEASE
  CMAKE_D_FLAGS_RELWITHDEBINFO
  )

set(CMAKE_D_INFORMATION_LOADED 1)
