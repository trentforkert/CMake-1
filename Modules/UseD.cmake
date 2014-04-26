#.rst:
# UseD
# ----
#
# Use Module for D
#
# This module provides functions for D to complement core CMake functions.
#
# ::
#
#    add_d_target(<target>
#        [EXECUTABLE | STATIC_LIBRARY | SHARED_LIBRARY]
#        [SOURCES] <source1> [<source2> ...]
#        [VERSION_IDENTS <ident1> [<ident2> ...]]
#        [DEBUG_IDENTS <ident1> [<ident2> ...]]
#        [IMPORT_DIRS <dir1> [<dir2> ...]]
#        [TEXT_IMPORT_DIRS <dir1> [<dir2> ...]]
#        [FLAGS <flag1> [<flag2> ...]]
#        [COVERAGE <pct>]
#        [DEPRECATED ALLOW | WARN | ERROR]
#        [ENFORCE_PROPERTY TRUE|FALSE]
#        [WARNINGS_ARE_ERRORS TRUE|FALSE]
#        [STRICT]
#        [GENERATE_UNITTESTS]
#        [GENERATE_DDOC]
#        [GENERATE_INSTALL]
#        [EXCLUDE_FROM_ALL]
#    )
#
# In its simplest form,
#
# ::
#
#    add_d_target(<target>)
#
# this command will create a target based on the source file <target>.d in
# the current source directory. It will automatically compile as an
# executable if it has a main method, or a static library otherwise.
# It automatically infers needed sources and libraries based on information
# from the D compiler.
#
# For automatic library dependency resolution to work, the library must
# be referenced from the D source code with pragma(lib). The name specified
# in the pragma must then be mapped to the libraries as follows:
#
# ::
#
#    set(_d_link_target_<libname> ${LIBNAME_LIBRARIES})
#
# This is not necessary for in-project libraries whose "pragma" name and
# "target" name are the same.
#
# ::
#
#    include_text_directories(
#       <dir1> [<dir2> ...]
#       [TARGET <target>]
#    )
#
# This command adds the specified directories to the text import search
# path. If a target is specified, the directories will only be added for
# that target. Otherwise, they follow usual CMake scope rules.
#
# ::
#
#    add_d_conditions(
#       [TARGET <target>]
#       [VERSION <ident1> [<ident2> ...] ]
#       [DEBUG <ident1> [<ident2> ...] ]
#    )
#
# This command adds the specified identifiers to D's version/debug flags.
# If a target is specified, the identifiers will only be added for that target.
# Otherwise, they follow usual CMake scope rules.
#
# ::
#
#    create_ddoc(
#       <target>
#       BASED_ON <base_target>
#       [OUTPUT_DIRECTORY <dir>]
#       [MACRO_FILES <macro_file1> [<macro_file2> ...]]
#    )
#
# Adds a DDoc generating target for the specified target, and makes it a
# dependency of a global ddoc target. Compiler parameters and initial
# source list are derived from <base_target>. A DDoc file containing a
# MODULES macro is automatically generated and used based on the modules
# include in the target.
#
# Additional macro files can be specified to define more macros. The
# default output directory, if that parameter is omitted, is
# ${CMAKE_CURRENT_BINARY_DIR}/ddoc.
#
# ::
#
#    add_d_unittests(
#       <target>
#       BASED_ON <base_target>
#       [COVERAGE <pct>]
#    )
#
# Adds a unittest target. This will use <base_target> to determine
# the initial set of compiler flags and source files to include.
# COVERAGE, if specified, will enforce that level of test coverage,
# provided the compiler support it.
#

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

enable_language(D)
include(CMakeParseArguments)

# Notable functions:
#   create_ddoc                 done
#   add_d_unittests             done
#   examine_d_source            done
#   add_d_conditions            done
#   add_d_target                done?

function(include_text_directories)
    cmake_parse_arguments(ARG "" "TARGET" "" ${ARGN})
    foreach(dir IN LISTS ARG_UNPARSED_ARGUMENTS)
        get_filename_component(dir "${dir}" ABSOLUTE)
        if(ARG_TARGET)
            set_property(TARGET ${ARG_TARGET} APPEND_STRING PROPERTY COMPILE_FLAGS " ${CMAKE_TEXT_INCLUDE_FLAG_D}${dir}")
        else()
            set(CMAKE_D_FLAGS "${CMAKE_D_FLAGS} ${CMAKE_TEXT_INCLUDE_FLAG_D}${dir}")
        endif()
    endforeach()
    set(CMAKE_D_FLAGS "${CMAKE_D_FLAGS}" PARENT_SCOPE)
endfunction()

function(add_d_conditions)
    cmake_parse_arguments(ARG "" "TARGET" "VERSION;DEBUG" ${ARGN})
    foreach(vers IN LISTS ARG_VERSION)
        if(ARG_TARGET)
            set_property(TARGET ${ARG_TARGET} APPEND_STRING PROPERTY COMPILE_FLAGS " ${CMAKE_D_VERSION_FLAG}${vers}")
        else()
            set(CMAKE_D_FLAGS "${CMAKE_D_FLAGS} ${CMAKE_D_VERSION_FLAG}${vers}")
        endif()
    endforeach()

    foreach(dbg IN LISTS ARG_DEBUG)
        if(ARG_TARGET)
            set_property(TARGET ${ARG_TARGET} APPEND_STRING PROPERTY COMPILE_FLAGS " ${CMAKE_D_DEBUG_FLAG}${dbg}")
        else()
            set(CMAKE_D_FLAGS "${CMAKE_D_FLAGS} ${CMAKE_D_DEBUG_FLAG}${dbg}")
        endif()
    endforeach()

    set(CMAKE_D_FLAGS "${CMAKE_D_FLAGS}" PARENT_SCOPE)
endfunction()

function(create_ddoc _target)
    if(NOT TARGET ddoc)
        add_custom_target(ddoc)
    endif()
    cmake_parse_arguments(ARG "" "BASED_ON;OUTPUT_DIRECTORY" "MACRO_FILES" ${ARGN})
    if(NOT ARG_BASED_ON)
        message(FATAL_ERROR "create_ddoc called without BASED_ON target specified")
    endif()

    get_target_property(flags "${ARG_BASED_ON}" COMPILE_FLAGS)
    get_target_property(sources "${ARG_BASED_ON}" SOURCES)

    if(NOT ARG_OUTPUT_DIRECTORY)
        set(ARG_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/ddoc)
    endif()
    file(MAKE_DIRECTORY "${ARG_OUTPUT_DIRECTORY}")
    list(APPEND ARG_MACRO_FILES "${ARG_OUTPUT_DIRECTORY}/${ARG_BASED_ON}_modules.ddoc")

    get_directory_property(imps DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} INCLUDE_DIRECTORIES)
    foreach(dir IN LISTS imps ITEMS ${CMAKE_CURRENT_SOURCE_DIR})
        get_filename_component(loc "${dir}" ABSOLUTE)
        list(APPEND _includes "${CMAKE_INCLUDE_FLAG_D}${loc}")
    endforeach()

    if(flags)
        set(CMAKE_D_FLAGS "${flags} ${CMAKE_D_FLAGS}")
    endif()
    examine_d_source(srcs libs isexe ${sources})

    separate_arguments(d_flags UNIX_COMMAND "${CMAKE_D_FLAGS}")

    add_custom_target(${_target})
    foreach(srcfile IN LISTS srcs)
        get_source_file_property(modname "${srcfile}" D_MODULE_NAME)
        if(NOT modname OR modname STREQUAL "NOTFOUND")
            message(FATAL_ERROR "${srcfile} didn't parse properly. Report bug, please!")
        endif()

        foreach(mf IN LISTS ARG_MACRO_FILES)
            list(APPEND macro_flags ${CMAKE_D_DDOC_MACRO_FLAG}${mf})
        endforeach()

        add_custom_command(TARGET ${_target}
            POST_BUILD
            COMMAND ${CMAKE_D_COMPILER}
            ${d_flags}
            ${_includes}
            ${CMAKE_D_NO_OUTPUT_FLAG}
            "${CMAKE_D_DDOC_FILE_FLAG}${modname}.html"
            "${srcfile}"
            ${macro_flags}
            WORKING_DIRECTORY ${ARG_OUTPUT_DIRECTORY}
            )
        set_property(SOURCE ${ARG_OUTPUT_DIRECTORY}/${ARG_BASED_ON}_modules.ddoc APPEND PROPERTY DDOC_MODULES ${modname})
    endforeach()
    get_source_file_property(mods ${ARG_OUTPUT_DIRECTORY}/${ARG_BASED_ON}_modules.ddoc DDOC_MODULES)
    list(SORT mods)
    file(WRITE "${ARG_OUTPUT_DIRECTORY}/${ARG_BASED_ON}_modules.ddoc" "MODULES = \n")
    foreach(mod IN LISTS mods)
        file(APPEND "${ARG_OUTPUT_DIRECTORY}/${ARG_BASED_ON}_modules.ddoc" "\t$(MODULE ${mod})\n")
    endforeach()
    add_dependencies(ddoc ${_target})
endfunction()

function(add_d_unittests _target)
    cmake_parse_arguments(ARG "" "BASED_ON;COVERAGE" "" ${ARGN})
    if(DEFINED ARG_COVERAGE AND CMAKE_D_COVERAGE_FLAG)
        set(_cov ${CMAKE_D_COVERAGE_FLAG}${ARG_COVERAGE})
    else()
        unset(_cov)
    endif()
    get_target_property(flags "${ARG_BASED_ON}" COMPILE_FLAGS)
    if(flags)
        set(CMAKE_D_FLAGS "${CMAKE_D_FLAGS} ${flags}")
    endif()
    get_target_property(sources "${ARG_BASED_ON}" SOURCES)
    set(CMAKE_D_FLAGS "${CMAKE_D_FLAGS} ${CMAKE_D_UNITTEST_FLAG} ${_cov}")
    examine_d_source(srcs libs isexe ${sources})
    if(NOT ${isexe})
        message(FATAL_ERROR "Trying to unittest ${_target}, but it isn't an executable")
    endif()
    add_executable(${_target} EXCLUDE_FROM_ALL ${srcs})
    target_link_libraries(${_target} ${libs})
    set_property(TARGET ${_target} PROPERTY COMPILE_FLAGS "${CMAKE_D_FLAGS}")
    add_test(NAME ${_target}_build COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_BINARY_DIR}" --target ${_target})
    add_test(NAME ${_target}_run COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${_target})
    set_tests_properties(${_target}_run PROPERTIES DEPENDS ${_target}_build)
endfunction()

# Internal function
function(examine_d_source _src_result _lib_result _exe_result)
    get_directory_property(imps DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} INCLUDE_DIRECTORIES)
    foreach(dir IN LISTS imps ITEMS ${CMAKE_CURRENT_SOURCE_DIR})
        get_filename_component(loc "${dir}" ABSOLUTE)
        list(APPEND _includes "${CMAKE_INCLUDE_FLAG_D}${loc}")
    endforeach()

    foreach(source IN LISTS ARGN)
        get_filename_component(loc "${source}" ABSOLUTE)
        list(APPEND RESOLVED_SRCS "${loc}")
    endforeach()

    separate_arguments(d_flags UNIX_COMMAND "${CMAKE_D_FLAGS}")

    if(CMAKE_D_COMPILER_ID MATCHES "LLVM")
        set(_json_output "${CMAKE_D_JSON_FILE_FLAG}temporary.json")
    endif()

    execute_process(COMMAND ${CMAKE_D_COMPILER}
        ${d_flags}
        ${_includes}
        ${CMAKE_D_DVERBOSE_FLAG}
        ${CMAKE_D_NO_OUTPUT_FLAG}
        ${CMAKE_D_DEPS_FILE_FLAG}temporary.deps
        ${_json_output}
        ${RESOLVED_SRCS}
        WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles"
        RESULT_VARIABLE _success
        OUTPUT_VARIABLE dep_listing
        ERROR_VARIABLE err_listing
        )

    string(REPLACE "\n" ";" verbose_listing "${dep_listing}\n${err_listing}")
    foreach(item IN LISTS verbose_listing)
        if(item MATCHES "^library[ ]+([^\n]+)$")
            set(libname "${CMAKE_MATCH_1}")
            if(NOT libname MATCHES "advapi32|shell32")
                if(_d_link_target_${libname})
                    list(APPEND RESOLVED_LIBS ${_d_link_target_${libname}})
                elseif(TARGET ${libname})
                    list(APPEND RESOLVED_LIBS ${libname})
                else()
                    message(FATAL_ERROR
                        "D source \"${sourcefile}\" wants to link \"${libname}\"")
                endif()
            endif()
        elseif(item MATCHES "^file[ ]+[^()]+\\(([^()]+)\\)$")
            set_property(SOURCE ${RESOLVED_SRCS} APPEND PROPERTY OBJECT_DEPENDS ${CMAKE_MATCH_1})
        elseif(item MATCHES "^entry[ ]+" OR item MATCHES "^function[ ]+D main$")
            set(IS_EXECUTABLE true)
        endif()
    endforeach()

    file(STRINGS "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/temporary.deps" moddeps)
    get_property(_d_all_libraries GLOBAL PROPERTY D_ALL_LIBRARIES)
    foreach(mod IN LISTS moddeps)
        if(mod MATCHES "([^ \n]+) \\(([^()]+)\\) : (private|public|package|protected) : ([^ ]+) \\(([^()]+)\\)")
            set(srcmod "${CMAKE_MATCH_1}")
            set(src "${CMAKE_MATCH_2}")
            set(depmod "${CMAKE_MATCH_4}")
            set(dep "${CMAKE_MATCH_5}")

            # Don't consider standard library / runtime modules as sources
            if(NOT srcmod MATCHES "^(__main|object|std\\.|core\\.|etc\\.|ldc\\.|gcc\\.)")
                get_property(named SOURCE "${src}" PROPERTY D_MODULE_NAME SET)
                if(NOT named)
                    set_property(SOURCE "${src}" PROPERTY D_MODULE_NAME "${srcmod}")
                endif()
                set_property(SOURCE "${src}" APPEND PROPERTY OBJECT_DEPENDS "${dep}")
                list(FIND RESOLVED_SRCS "${src}" idx)
                if(idx EQUAL -1)
                    set(src_in_lib FALSE)
                    foreach(lib IN LISTS _d_all_libraries)
                        get_target_property(lib_srcs ${lib} SOURCES)
                        list(FIND lib_srcs "${src}" idx2)
                        if(idx2 GREATER -1)
                            set(src_in_lib TRUE)
                            list(FIND RESOLVED_LIBS ${lib} lib_idx)
                            if(lib_idx EQUAL -1)
                                list(APPEND RESOLVED_LIBS ${lib})
                            endif()
                            break()
                        endif()
                    endforeach()
                    if(NOT src_in_lib)
                        file(TO_CMAKE_PATH "${src}" cmsrc)
                        list(APPEND RESOLVED_SRCS "${cmsrc}")
                    endif()
                endif()
            endif()
        endif()
    endforeach()

    # LDC doesn't expose "entry" line in DVERBOSE output
    # So, we get json output for all sources and check that for a main function
    if(EXISTS "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/temporary.json")
        file(READ "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/temporary.json" jsonstr)
        if(jsonstr MATCHES "\"name\" : \"main\",[ \n\r\t]*\"kind\" : \"function\"")
            set(IS_EXECUTABLE true)
        endif()
    endif()

    # Instead of depending on objects (we can't), we recursively depend
    # on the whole source tree in question
    function(recurse_deps src)
        list(FIND recursed "${src}" idx)
        if(idx EQUAL -1)
            list(APPEND recursed "${src}")
            get_source_file_property(deps "${src}" OBJECT_DEPENDS)
            foreach(dep IN LISTS deps)
                if(NOT dep STREQUAL "NOTFOUND")
                    recurse_deps("${dep}")
                    get_source_file_property(redep "${dep}" OBJECT_DEPENDS)
                    if(NOT redep STREQUAL "NOTFOUND")
                        list(APPEND deps "${redep}")
                    endif()
                endif()
            endforeach()
            list(REMOVE_DUPLICATES deps)
            set_property(SOURCE "${src}" PROPERTY OBJECT_DEPENDS "${deps}")
        endif()
        set(recursed "${recursed}" PARENT_SCOPE)
    endfunction()
    foreach(src IN LISTS ${_target})
        recurse_deps("${src}")
    endforeach()

    set(${_src_result} "${RESOLVED_SRCS}" PARENT_SCOPE)
    set(${_lib_result} "${RESOLVED_LIBS}" PARENT_SCOPE)
    set(${_exe_result} "${IS_EXECUTABLE}" PARENT_SCOPE)
endfunction()

function(add_d_target _target)
    set(options
        EXECUTABLE STATIC_LIBRARY SHARED_LIBRARY
        EXCLUDE_FROM_ALL
        STRICT # Warnings_are_errors, DEPRECATED ERROR, ENFORCE_PROPERTY
        GENERATE_DDOC GENERATE_UNITTESTS GENERATE_INSTALL)
    set(oneValueArgs
        COVERAGE
        DEPRECATED # ALLOW || WARN || ERROR
        ENFORCE_PROPERTY # true || false
        WARNINGS_ARE_ERRORS # true || false
        )
    set(multiValueArgs SOURCES VERSION_IDENTS DEBUG_IDENTS IMPORT_DIRS TEXT_IMPORT_DIRS DDOC_MACRO_FILES FLAGS)
    cmake_parse_arguments(ARG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(ARG_EXCLUDE_FROM_ALL)
        set(ARG_EXCLUDE_FROM_ALL "EXCLUDE_FROM_ALL")
        set(ARG_GENERATE_INSTALL FALSE)
    else()
        set(ARG_EXCLUDE_FROM_ALL "")
    endif()

    if(ARG_STRICT)
        set(ARG_ENFORCE_PROPERTY TRUE)
        set(ARG_WARNINGS_ARE_ERRORS TRUE)
        set(ARG_DEPRECATED ERROR)
    endif()

    if(ARG_ENFORCE_PROPERTY)
        set(CMAKE_D_FLAGS "${CMAKE_D_FLAGS} ${CMAKE_D_PROPERTY_FLAG}")
    endif()

    if(ARG_WARNINGS_ARE_ERRORS)
        set(CMAKE_D_FLAGS "${CMAKE_D_FLAGS} ${CMAKE_D_WARNING_ERROR_FLAG}")
    endif()

    if(DEFINED ARG_DEPRECATED)
        set(CMAKE_D_FLAGS "${CMAKE_D_FLAGS} ${CMAKE_D_${ARG_DEPRECATED}_DEPRECATED_FLAG}")
    endif()

    add_d_conditions(VERSION ${ARG_VERSIONS} DEBUG ${ARG_DEBUG})
    include_directories(${ARG_IMPORT_DIRS})
    include_text_directories(${ARG_TEXT_IMPORT_DIRS})

    foreach(flag IN LISTS ARG_FLAGS)
        set(CMAKE_D_FLAGS "${CMAKE_D_FLAGS} ${flag}")
    endforeach()

    list(LENGTH ARG_SOURCES len)
    if(len EQUAL 0)
        list(APPEND ARG_SOURCES "${_target}.d")
    endif()

    examine_d_source(srcs libs isexe ${ARG_SOURCES})

    if(isexe)
        add_executable(${_target} ${ARG_EXCLUDE_FROM_ALL} ${srcs})
    else()
        add_library(${_target} STATIC ${ARG_EXCLUDE_FROM_ALL} ${srcs})
    endif()
    target_link_libraries(${_target} ${libs})

    if(NOT ${_target} MATCHES "^d_unittest_" AND NOT isexe)
        set_property(GLOBAL APPEND PROPERTY D_ALL_LIBRARIES ${_target})
    endif()

    # Persist flags
    if(ARG_WARNINGS_ARE_ERRORS)
        set_property(TARGET ${_target} APPEND_STRING PROPERTY COMPILE_FLAGS ${CMAKE_D_WARNING_ERROR_FLAG})
    endif()

    if(ARG_ENFORCE_PROPERTY)
        set_property(TARGET ${_target} APPEND_STRING PROPERTY COMPILE_FLAGS ${CMAKE_D_PROPERTY_FLAG})
    endif()

    if(ARG_DEPRECATED)
        set_property(TARGET ${_target} APPEND_STRING PROPERTY COMPILE_FLAGS ${CMAKE_D_${ARG_DEPRECATED}_DEPRECATED_FLAG})
    endif()
    add_d_conditions(TARGET ${_target} VERSION ${ARG_VERSION_IDENTS} DEBUG ${ARG_DEBUG_IDENTS})

    foreach(dir IN LISTS ARG_IMPORT_DIRS)
        target_include_directories(${_target} PUBLIC ${dir})
    endforeach()
    include_text_directories(TARGET ${_target} ${ARG_TEXT_IMPORT_DIRS})
    foreach(flag IN LISTS ARG_FLAGS)
        set_property(TARGET ${_target} APPEND PROPERTY COMPILE_FLAGS "${flag}")
    endforeach()

    # Add testing target
    if(CMAKE_TESTING_ENABLED AND ARG_GENERATE_UNITTESTS)
        if(DEFINED ARG_COVERAGE)
            set(ARG_COVERAGE COVERAGE ${ARG_COVERAGE})
        else()
            set(ARG_COVERAGE)
        endif()

        add_d_unittests(d_unittest_${_target}
            BASED_ON ${_target}
            ${ARG_COVERAGE}
        )
    endif()

    if(ARG_GENERATE_DDOC)
        create_ddoc(ddoc_${_target}
            BASED_ON ${_target}
            MACRO_FILES ${ARG_DDOC_MACRO_FILES}
            )
        if(ARG_GENERATE_DDOC)
            install(FILES ${CMAKE_CURRENT_BINARY_DIR}/ddoc/* DESTINATION share/doc/${CMAKE_PROJECT_NAME})
        endif()
    endif()

    if(ARG_GENERATE_INSTALL)
        install(TARGETS ${_target}
            RUNTIME DESTINATION bin
            LIBRARY DESTINATION lib
            ARCHIVE DESTINATION lib
        )
    endif()
endfunction()
