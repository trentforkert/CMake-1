
#=============================================================================
# Copyright 2002-2014 Kitware, Inc.
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

if(NOT DEFINED CMAKE_LINKER)
  # This will be optlink on 32bit, MSVC link on 64bit.
  set(CMAKE_LINKER link)
endif()

# Set these to spaces to prevent MSVC's flags from being passed to DMD
set(CMAKE_D_CREATE_CONSOLE_EXE " ")
set(CMAKE_D_CREATE_WIN32_EXE " ")
set(CMAKE_D_EXE_LINKER_FLAGS " ")

