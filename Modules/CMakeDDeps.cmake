
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

# Dependency resolution for D is handled in a separate bundled program
# in order to minimize code duplication between Makefile and Ninja
# generators.

if(CMAKE_GENERATOR MATCHES "Ninja|Makefiles" AND CMAKE_D_COMPILER AND CMAKE_COMMAND)
  get_filename_component(bin_dir ${CMAKE_COMMAND} DIRECTORY)
  get_filename_component(bin_ext ${CMAKE_COMMAND} EXT)
  set(CMAKE_DDEPS_EXECUTABLE "${bin_dir}/ddeps${bin_ext}")

  set(predir ${CMAKE_BINARY_DIR}/CMakeFiles/ddeps_versions)

  # We need to have the compiler tell us which standard version flags are defined,
  # So that we can pass them to the parser
  file(WRITE ${predir}/versions.d "
    version(DigitalMars) pragma(msg, `version: DigitalMars`);
    version(GNU) pragma(msg, `version: GNU`);
    version(LDC) pragma(msg, `version: LDC`);
    version(SDC) pragma(msg, `version: SDC`);
    version(Windows) pragma(msg, `version: Windows`);
    version(Win32) pragma(msg, `version: Win32`);
    version(Win64) pragma(msg, `version: Win64`);
    version(linux) pragma(msg, `version: linux`);
    version(OSX) pragma(msg, `version: OSX`);
    version(FreeBSD) pragma(msg, `version: FreeBSD`);
    version(OpenBSD) pragma(msg, `version: OpenBSD`);
    version(NetBSD) pragma(msg, `version: NetBSD`);
    version(DragonFlyBSD) pragma(msg, `version: DragonFlyBSD`);
    version(BSD) pragma(msg, `version: BSD`);
    version(Solaris) pragma(msg, `version: Solaris`);
    version(Posix) pragma(msg, `version: Posix`);
    version(AIX) pragma(msg, `version: AIX`);
    version(Haiku) pragma(msg, `version: Haiku`);
    version(SkyOS) pragma(msg, `version: SkyOS`);
    version(SysV3) pragma(msg, `version: SysV3`);
    version(SysV4) pragma(msg, `version: SysV4`);
    version(Hurd) pragma(msg, `version: Hurd`);
    version(Android) pragma(msg, `version: Android`);
    version(Cygwin) pragma(msg, `version: Cygwin`);
    version(MinGW) pragma(msg, `version: MinGW`);
    version(X86) pragma(msg, `version: X86`);
    version(X86_64) pragma(msg, `version: X86_64`);
    version(ARM) pragma(msg, `version: ARM`);
    version(ARM_Thumb) pragma(msg, `version: ARM_Thumb`);
    version(ARM_SoftFloat) pragma(msg, `version: ARM_SoftFloat`);
    version(ARM_SoftFP) pragma(msg, `version: ARM_SoftFP`);
    version(ARM_HardFloat) pragma(msg, `version: ARM_HardFloat`);
    version(AArch64) pragma(msg, `version: AArch64`);
    version(PPC) pragma(msg, `version: PPC`);
    version(PPC_SoftFloat) pragma(msg, `version: PPC_SoftFloat`);
    version(PPC_HardFloat) pragma(msg, `version: PPC_HardFloat`);
    version(PPC64) pragma(msg, `version: PPC64`);
    version(IA64) pragma(msg, `version: IA64`);
    version(MIPS32) pragma(msg, `version: MIPS32`);
    version(MIPS64) pragma(msg, `version: MIPS64`);
    version(MIPS_O32) pragma(msg, `version: MIPS_O32`);
    version(MIPS_N32) pragma(msg, `version: MIPS_N32`);
    version(MIPS_N64) pragma(msg, `version: MIPS_N64`);
    version(MIPS_EABI) pragma(msg, `version: MIPS_EABI`);
    version(MIPS_SoftFloat) pragma(msg, `version: MIPS_SoftFloat`);
    version(MIPS_HardFloat) pragma(msg, `version: MIPS_HardFloat`);
    version(SPARC) pragma(msg, `version: SPARC`);
    version(SPARC_V8Plus) pragma(msg, `version: SPARC_V8Plus`);
    version(SPARC_SoftFloat) pragma(msg, `version: SPARC_SoftFloat`);
    version(SPARC_HardFloat) pragma(msg, `version: SPARC_HardFloat`);
    version(SPARC64) pragma(msg, `version: SPARC64`);
    version(S390) pragma(msg, `version: S390`);
    version(S390X) pragma(msg, `version: S390X`);
    version(HPPA) pragma(msg, `version: HPPA`);
    version(HPPA64) pragma(msg, `version: HPPA64`);
    version(SH) pragma(msg, `version: SH`);
    version(SH64) pragma(msg, `version: SH64`);
    version(Alpha) pragma(msg, `version: Alpha`);
    version(Alpha_SoftFloat) pragma(msg, `version: Alpha_SoftFloat`);
    version(Alpha_HardFloat) pragma(msg, `version: Alpha_HardFloat`);
    version(LittleEndian) pragma(msg, `version: LittleEndian`);
    version(BigEndian) pragma(msg, `version: BigEndian`);
    version(D_InlineAsm_X86) pragma(msg, `version: D_InlineAsm_X86`);
    version(D_InlineAsm_X86_64) pragma(msg, `version: D_InlineAsm_X86_64`);
    version(D_LP64) pragma(msg, `version: D_LP64`);
    version(D_X32) pragma(msg, `version: D_X32`);
    version(D_HardFloat) pragma(msg, `version: D_HardFloat`);
    version(D_SoftFloat) pragma(msg, `version: D_SoftFloat`);
    version(D_PIC) pragma(msg, `version: D_PIC`);
    version(D_SIMD) pragma(msg, `version: D_SIMD`);
    version(D_Version2) pragma(msg, `version: D_Version2`);
    version(D_NoBoundsChecks) pragma(msg, `version: D_NoBoundsChecks`);
    version(D_Coverage) pragma(msg, `version: D_Coverage`);
    version(D_Ddoc) pragma(msg, `version: D_Ddoc`);
    // assert and unittest are left out because they break older compilers

    // Legacy identifiers:
    version(LLVM) pragma(msg, `version: LLVM`);
    version(LLVM64) pragma(msg, `version: LLVM64`);
    version(darwin) pragma(msg, `version: darwin`);
    version(Thumb) pragma(msg, `version: Thumb`);
    version(mingw32) pragma(msg, `version: mingw32`);
    version(solaris) pragma(msg, `version: solaris`);
  ")

  # TODO: "-c" works for all current D compilers, but maybe isn't portable?
  execute_process(COMMAND ${CMAKE_D_COMPILER} ${CMAKE_D_COMPILER_ARG1} -c versions.d
    WORKING_DIRECTORY ${predir}
    OUTPUT_VARIABLE outLine
    ERROR_VARIABLE errLine)

  string(REGEX MATCHALL "version: [^\n]+" versions_tmp "${outLine}\n${errLine}")
  foreach(version IN LISTS versions_tmp)
    string(REPLACE "version: " "" vers ${version})
    list(APPEND CMAKE_DDEPS_DEFAULT_VERSIONS ${vers})
  endforeach()
  set(SET_CMAKE_DDEPS_EXECUTABLE "set(CMAKE_DDEPS_EXECUTABLE \"${CMAKE_DDEPS_EXECUTABLE}\")\nset(CMAKE_DDEPS_DEFAULT_VERSIONS \"${CMAKE_DDEPS_DEFAULT_VERSIONS}\")")
endif()
