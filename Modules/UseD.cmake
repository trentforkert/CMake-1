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
#    add_d_conditions(
#       [TARGETS <target1> [<target2> ...] ]
#       [VERSION <ident1> [<ident2> ...] ]
#       [DEBUG <ident1> [<ident2> ...] ]
#    )
#
# This command adds the specified identifiers to D's version/debug flags.
# These are used to control conditional compilation similar to (but distinct
# from) C's -Dfoo=bar flags. If any targets are specified, the identifiers
# will only be added for those targets. Otherwise, they follow usual CMake
# scope rules.
#
# These conditions are added to :prop_tgt:`COMPILE_OPTIONS` for targets
# or :prop_dir:`COMPILE_OPTIONS` if no target is specified. This allows
# an executable target to link to a library target that required version
# flags, with the executable automatically picking up the version flags
# so that the D compiler can generate code correctly.
#
# ::
#
#    add_d_unittests(<unittest_target>
#       TARGET <target>
#       [PARAMETERS <param_string1> [<param_string2> ...] ]
#       [SOURCES <extra_source1> [<extra_source2> ...] ]
#    )
#
# Adds a unittest target. The executable target will be named
# ``<unittest_target>``, so that you can add additional flags
# or link libraries to it as needed.
#
# The set of sources, flags and libraries used for ``<unittest_target>``
# is determined by those on the provided ``<target>``. At least two
# test targets are added, called ``<unittest_target>_build`` and
# ``<unittest_target>_run``, which build and run the target respectively.
#
# By providing strings to ``PARAMETERS``, you can specify that the
# ``<unittest_target>`` should be run with said flags. Each set of flags
# must be its own string, so if you want multiple flags on a single
# test call, you need to write them as follows:
#
#    add_d_unittests(test_example
#       TARGET example
#       PARAMETERS
#           "--run-test 1 --quiet"
#           "--run-test 2 --quiet"
#           "--run-test 3 --quiet"
#    )
#
# This will produce three tests which call ``test_example``, once for each
# of the sets of parameters. Without the double-quotes, this would be
# interpreted as 9 tests which call ``test_example``.
#
# All test running targets are name ``<unittest_target>_run_<num>`` where
# ``<num>`` is an integer that begins at zero, and increments for each test
# added within this command. No attempt to pad the number with leading
# zeroes is made.
#
# ``SOURCES`` allows you to specify additional source files needed to build
# ``<unittest_target>``, if any. You may instead wish to add a library
# containing these sources, and link ``<unittest_target>`` to it
# using :command:`target_link_libraries`.
#
# Note: the executable target will be generated as long as this
# function is called, but the test targets will only be enabled
# if testing is enabled (for example, by calling :command:`enable_testing`).
# Tests will also not be generated when cross compiling.
#
# ::
#
#    add_ddoc(<doc_target>
#       TARGETS <target> [<target2> ...]
#       [EXCLUDE_FROM_ALL]
#       [OUTPUT_DIRECTORY <dir>]
#       [PACKAGE_SEPARATOR <sep>]
#       [EXTENSION <ext>]
#       [MACROS <macro_file1> [<macro_file2> ...] ]
#       [ASSETS <asset_file1> [<asset_file2> ...] ]
#       [SOURCES <extra_source1> [<extra_source2> ...] ]
#       [VERSION <ident1> [<ident2> ...] ]
#       [EXCLUDE_SOURCES <source1> [<source2> ...] ]
#       [EXCLUDE_MODULES <regex>]
#    )
#
# Adds a Ddoc generating target (named ``<doc_target>``) for the specified
# targets. Compiler parameters and initial source list are derived from
# ``<target>``. A Ddoc file containing a ``MODULES`` macro is automatically
# generated and used based on the modules include in the target.
#
# Additional targets, if specified, will be generated as part of the same
# documentation target. That is, all D modules from each listed target
# will be included in the same generated ``MODULES`` macro file.
# from the default target.
#
# By default, ``add_ddoc`` adds ``<doc_target>`` to the default build.
# This can be prevented by specifying ``EXCLUDE_FROM_ALL``. Note that
# if ``EXCLUDE_FROM_ALL`` is set, the documentation cannot be installed.
# It is recommended to configure this such that it is an option for
# the user whether or not to generate (and install) documentation.
#
# The output directory can be specified via ``OUTPUT_DIRECTORY``.
# The default output directory, if that parameter is omitted, is
# ``${PROJECT_BINARY_DIR}/ddoc``.
#
# The separator used in the names of the generated files can be specified
# via ``PACKAGE_SEPARATOR``. If left unspecified, it defaults to a period.
# For example, given a module ``pkg.sub.mod`` (in file ``pkg/sub/mod.d``),
# The default is to generate a ``pkg.sub.mod.<ext>`` file. Providing
# a ``PACKAGE_SEPARATOR`` of "_" would put the same file in
# ``pkg_sub_mod.<ext>``. This also determines the names used in the
# generated ``MODULES`` macro file. This should be set to the same thing your
# other Ddoc macros expect.
#
# The generated file extension can be specified via the ``EXTENSION`` argument.
# It defaults to "html", which is the usual output format for Ddoc.
# Note that this only determines the output extension; the contents
# of the file depend on how your macros are defined.
#
# With the ``MACROS`` flag, additional macro files can be specified to define
# more macros. This is useful, for instance, to generate Ddoc using bootDoc:
# simply point to the ``bootdoc.ddoc`` and ``settings.ddoc`` files.
# These files must have an extension of "ddoc". Remember that a macro file
# containing a definition of ``MODULES`` is automatically generated and used.
#
# Asset files and directories can be specified via ``ASSETS``. The files
# will be copied to the ``OUTPUT_DIRECTORY`` as is, from where they can
# be installed easily. These files can then be used by the generated
# Ddoc. For instance, you might add JavaScript, CSS and images with this.
#
# If needed, additional sources may be processed alongside the targets'
# sources by providing the ``SOURCES`` argument. This is primarily useful
# if you have a D source that only contains documentation, and that you
# do not include in any of your targets' sources. These sources will
# take on the same flags as the first specified target.
#
# Additional conditional compilation flags may be passed to via ``VERSION``.
# This works by calling ``add_d_conditions(VERSION ...)``, and thus will
# apply to every D compiler call by add_ddoc.
#
# If desired, modules can be excluded from Ddoc generation, either by
# giving sources manually to ``EXCLUDE_SOURCES``, or a regex against module
# names provided to ``EXCLUDE_MODULES``. The module names here are the
# canonical form before the separator is modified.
#
# This command can be called multiple times on the same targets, so that
# you can generate different forms of documentation (HTML, man pages, etc.)
# Further processing (such as compiling generated LaTeX to a PDF) is
# beyond the scope of this command. Note, however, that different
# ``<doc_target>`` will be needed for each call to ``add_ddoc``.
#
# ::
#
#    add_d_headers(
#       TARGETS <target> [<target2> ...]
#       [OUTPUT_DIRECTORY <dir>]
#    )
#
# Adds rules responsible for generating D headers from the sources
# of all the specified targets. These rules are added to the targets
# themselves as a post-build step. When using this, remember that
# this is not always a bug-free process. For instance, DMD v2.065 does
# not properly handle "auto" functions, instead dropping the return
# type all together. Older versions of D will leave implementations
# intact. These are also not appropriate for documentation,
# as all comments are stripped. Use ``add_ddoc`` for creating documentation.
#
# The output directory can be specified via ``OUTPUT_DIRECTORY``. If not
# specified, it defaults to ``${PROJECT_BINARY_DIR}/import``.
#
# ::
#
#    d_enforce_property(
#       [TARGETS <target1> [<target2> ...] ]
#    )
#
# Instructs the D compiler to enforce D's property semantics. This is
# (currently) disabled by default in D, and makes it so that methods
# annotated with ``@property`` are the only methods that can be used
# as properties.
#
# As with ``add_d_conditions``, this appends to :prop_tgt:`COMPILE_OPTIONS`
# for targets and :prop_dir:`COMPILE_OPTIONS` if no targets are specified.
# As such, linking to a library target that uses property enforcement
# will automatically instruct the linking target to also use property
# enforcement.

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

# Set compiler-specific flags this module will use
# Not intended for use outside this module
if(CMAKE_D_COMPILER_ID MATCHES "DigitalMars")
    set(_USED_DDOC_FILE_FLAG "-Df")
    set(_USED_DDOC_MACRO_FLAG "")

    set(_USED_HEADER_FILE_FLAG "-Hf")

    set(_USED_UNITTEST_FLAG "-unittest")

    set(_USED_VERSION_FLAG "-version=")
    set(_USED_DEBUG_FLAG "-debug=")

    set(_USED_ENFORCE_PROPERTY_FLAG "-property")
elseif(CMAKE_D_COMPILER_ID MATCHES "GNU")
    set(_USED_DDOC_FILE_FLAG "-fdoc-file=")
    set(_USED_DDOC_MACRO_FLAG "-fdoc-inc=")

    set(_USED_HEADER_FILE_FLAG "-fintfc-file=")

    set(_USED_UNITTEST_FLAG "-funittest")

    set(_USED_VERSION_FLAG "-fversion=")
    set(_USED_DEBUG_FLAG "-fdebug=")

    set(_USED_ENFORCE_PROPERTY_FLAG "-fproperty")
elseif(CMAKE_D_COMPILER_ID MATCHES "LLVM")
    set(_USED_DDOC_FILE_FLAG "-Df=")
    set(_USED_DDOC_MACRO_FLAG "")

    set(_USED_HEADER_FILE_FLAG "-Hf=")

    set(_USED_UNITTEST_FLAG "-unittest")

    set(_USED_VERSION_FLAG "-d-version=")
    set(_USED_DEBUG_FLAG "-d-debug=")

    set(_USED_ENFORCE_PROPERTY_FLAG "-property")
else()
    message(FATAL_ERROR "UseD does not support ${CMAKE_D_COMPILER_ID} ${CMAKE_D_COMPILER_VERSION}: ${CMAKE_D_COMPILER}")
endif()


function(add_d_conditions)
    cmake_parse_arguments(ARG "" "" "TARGETS;VERSION;DEBUG;" ${ARGN})
    foreach(vers IN LISTS ARG_VERSION)
        if(ARG_TARGETS)
            foreach(tgt IN LISTS ARG_TARGETS)
                target_compile_options(${tgt} PUBLIC "$<$<STREQUAL:$<TARGET_PROPERTY:LINKER_LANGUAGE>,D>:${_USED_VERSION_FLAG}${vers}>")
            endforeach()
        else()
            add_compile_options("$<$<STREQUAL:$<TARGET_PROPERTY:LINKER_LANGUAGE>,D>:${_USED_VERSION_FLAG}${vers}>")
        endif()
    endforeach()

    foreach(dbg IN LISTS ARG_DEBUG)
        if(ARG_TARGETS)
            foreach(tgt IN LISTS ARG_TARGETS)
                target_compile_options(${tgt} PUBLIC "$<$<STREQUAL:$<TARGET_PROPERTY:LINKER_LANGUAGE>,D>:${_USED_DEBUG_FLAG}${dbg}>")
            endforeach()
        else()
            add_compile_options("$<$<STREQUAL:$<TARGET_PROPERTY:LINKER_LANGUAGE>,D>:${_USED_DEBUG_FLAG}${dbg}>")
        endif()
    endforeach()
endfunction()

function(d_enforce_property)
    cmake_parse_arguments(ARG "" "" "TARGETS" ${ARGN})
    if(ARG_TARGETS)
        foreach(tgt IN LISTS ARG_TARGETS)
            target_compile_options(${tgt} PUBLIC "$<$<STREQUAL:$<TARGET_PROPERTY:LINKER_LANGUAGE>,D>:${_USED_ENFORCE_PROPERTY_FLAG}>")
        endforeach()
    else()
        add_compile_options("$<$<STREQUAL:$<TARGET_PROPERTY:LINKER_LANGUAGE>,D>:${_USED_ENFORCE_PROPERTY_FLAG}>")
    endif()
endfunction()

function(add_ddoc _target)
    cmake_parse_arguments(ARG
        "EXCLUDE_FROM_ALL"
        "OUTPUT_DIRECTORY;PACKAGE_SEPARATOR;EXTENSION;EXCLUDE_MODULES"
        "TARGETS;MACROS;ASSETS;SOURCES;EXCLUDE_SOURCES;VERSION"
        ${ARGN})
    if(NOT ARG_EXCLUDE_FROM_ALL)
        set(ARG_EXCLUDE_FROM_ALL ALL)
    else()
        set(ARG_EXCLUDE_FROM_ALL "")
    endif()

    if(NOT DEFINED ARG_OUTPUT_DIRECTORY)
        set(ARG_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/ddoc")
    endif()

    if(NOT DEFINED ARG_EXTENSION)
        set(ARG_EXTENSION "html")
    endif()

    if(NOT DEFINED ARG_PACKAGE_SEPARATOR)
        set(ARG_PACKAGE_SEPARATOR .)
    endif()

    if(NOT DEFINED ARG_EXCLUDE_SOURCES)
        set(ARG_EXCLUDE_SOURCES)
    endif()
    foreach(src IN LISTS ARG_EXCLUDE_SOURCES)
        get_filename_component(loc "${src}" ABSOLUTE)
        list(APPEND excl_srcs "${loc}")
    endforeach()

    if(NOT DEFINED ARG_EXCLUDE_MODULES)
        set(ARG_EXCLUDE_MODULES "")
    endif()

    if(DEFINED ARG_VERSION)
        get_directory_property(_opts_old COMPILE_OPTIONS)
        add_d_conditions(VERSION ${ARG_VERSION})
        get_directory_property(_opts_new COMPILE_OPTIONS)
        foreach(_opt IN LISTS _opts_new)
            message(STATUS "{${_opt}}")
            list(FIND _opts_old ${_opt} _at)
            message(STATUS "(${_at})")
            if(_at EQUAL -1)
                if("${_opt}" MATCHES "\\$<\\$<STREQUAL:\\$<TARGET_PROPERTY:LINKER_LANGUAGE>,D>:(.+)>")
                    list(APPEND versions "${CMAKE_MATCH_1}")
                    message(STATUS "[${CMAKE_MATCH_1}]")
                endif()
            endif()
        endforeach()
    else()
        set(versions)
    endif()

    foreach(src IN LISTS ARG_SOURCES)
        get_filename_component(loc "${src}" ABSOLUTE)
        list(APPEND abs_srcs "${loc}")
    endforeach()

    foreach(ddoc_macro IN LISTS ARG_MACROS)
        get_filename_component(loc "${ddoc_macro}" ABSOLUTE)
        list(APPEND ddoc_files "${_USED_DDOC_MACRO_FLAG}${loc}")
    endforeach()

    foreach(asset IN LISTS ARG_ASSETS)
        get_filename_component(loc "${asset}" ABSOLUTE)
        list(APPEND ddoc_assets "${loc}")
    endforeach()

    set(confdir "${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/${_target}.dir")
    foreach(tgt IN LISTS ARG_TARGETS)
        _process_flags(${tgt} srcs abs_srcs lst)
        list(APPEND lst ${versions})

        # Create configure script
        configure_file(
            "${CMAKE_ROOT}/Modules/UseDConfigureDdoc.cmake.in"
            "${confdir}/${tgt}_configure_ddoc.cmake"
            @ONLY ESCAPE_QUOTES)

        # Tell our target to generate the depsfile and run the script
        add_custom_command(OUTPUT "${confdir}/${tgt}_configure_ddoc.stamp"
            COMMAND ${CMAKE_D_COMPILER} ${lst} ${CMAKE_D_NO_OUTPUT_FLAG} "${CMAKE_D_DEPS_FILE_FLAG}${confdir}/${tgt}.srcdeps" ${abs_srcs}
            COMMAND ${CMAKE_COMMAND} -P "${confdir}/${tgt}_configure_ddoc.cmake"
            COMMENT "Configuring Ddoc target ${_target} (${tgt})"
            VERBATIM
            )

        list(APPEND conf_files "${confdir}/${tgt}_configure_ddoc.stamp")

        # Cleanup
        set(srcs)
        set(abs_srcs)
        set(lst)
    endforeach()

    # Produce and call the script that actually generates the Ddoc.
    configure_file(
        "${CMAKE_ROOT}/Modules/UseDBuildDdoc.cmake.in"
        "${confdir}/${_target}_build_ddoc.cmake"
        @ONLY ESCAPE_QUOTES)
    add_custom_command(OUTPUT "${confdir}/${_target}_build_ddoc.stamp"
        COMMAND ${CMAKE_COMMAND} -P "${confdir}/${_target}_build_ddoc.cmake"
        COMMENT "Building Ddoc target ${_target}"
        DEPENDS ${conf_files}
        VERBATIM
        )
    add_custom_target(${_target} ${ARG_EXCLUDE_FROM_ALL} DEPENDS "${confdir}/${_target}_build_ddoc.stamp")

    # Remove documentation dir on make clean
    set_property(
        DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES "${ARG_OUTPUT_DIRECTORY}")
endfunction()

function(add_d_headers)
    cmake_parse_arguments(ARG "" "OUTPUT_DIRECTORY" "TARGETS" ${ARGN})
    if(NOT DEFINED ARG_OUTPUT_DIRECTORY)
        set(ARG_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/import")
    endif()

    foreach(tgt IN LISTS ARG_TARGETS)
        _process_flags(${tgt} srcs abs_srcs lst)
        foreach(src IN LISTS srcs)
            get_filename_component(loc "${src}" ABSOLUTE)
            add_custom_command(TARGET ${tgt} POST_BUILD
                COMMAND "${CMAKE_D_COMPILER}" ${lst} ${CMAKE_D_NO_OUTPUT_FLAG} "${_USED_HEADER_FILE_FLAG}${ARG_OUTPUT_DIRECTORY}/${src}i" "${loc}"
                VERBATIM
            )

            # Remove generated header files on clean
            set_property(
                DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
                APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES "${ARG_OUTPUT_DIRECTORY}/${src}i")
        endforeach()
    endforeach()
endfunction()

function(add_d_unittests _target)
    cmake_parse_arguments(ARG "" "TARGET;OUTPUT_DIRECTORY" "PARAMETERS;SOURCES" ${ARGN})

    get_target_property(sources ${ARG_TARGET} SOURCES)
    add_executable(${_target} EXCLUDE_FROM_ALL ${sources} ${ARG_SOURCES})

    get_target_property(libs ${ARG_TARGET} LINK_LIBRARIES)
    if(libs)
        target_link_libraries(${_target} ${libs})
    endif()

    get_target_property(flags ${ARG_TARGET} COMPILE_FLAGS)
    if(flags)
        set_target_properties(${_target} PROPERTIES COMPILE_FLAGS "${flags} ${_USED_UNITTEST_FLAG} ")
    else()
        set_target_properties(${_target} PROPERTIES COMPILE_FLAGS "${_USED_UNITTEST_FLAG} ")
    endif()

    get_target_property(opts ${ARG_TARGET} COMPILE_OPTIONS)
    if(opts)
        target_compile_options(${_target} PUBLIC ${opts})
    endif()

    if(CMAKE_TESTING_ENABLED AND NOT CROSS_COMPILING)
        add_test(NAME "${_target}_build" COMMAND ${CMAKE_COMMAND} --build "${CMAKE_CURRENT_BINARY_DIR}" --target ${_target})

        if(NOT DEFINED ARG_PARAMETERS)
            set(ARG_PARAMETERS " ")
        endif()
        set(num 0)
        foreach(param IN LISTS ARG_PARAMETERS)
            separate_arguments(paramlist UNIX_COMMAND "${param}")
            add_test(NAME "${_target}_run_${num}" COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${_target} ${paramlist})
            set_tests_properties(${_target}_run_${num} PROPERTIES DEPENDS ${_target}_build)
            math(EXPR num "${num}+1")
        endforeach()
    endif()
endfunction()


# Internal
function(_process_flags _target sources_var abs_sources_var flags_var)
    get_target_property(srcs ${_target} SOURCES)
    foreach(src IN LISTS srcs)
        get_filename_component(pth "${src}" ABSOLUTE)
        list(APPEND abs_srcs "${pth}")
    endforeach()

    get_target_property(flags ${_target} COMPILE_FLAGS)
    if(NOT flags)
        set(flags)
    endif()

    get_target_property(opts ${_target} COMPILE_OPTIONS)
    foreach(opt IN LISTS opts)
        if("${opt}" MATCHES "\\$<\\$<STREQUAL:\\$<TARGET_PROPERTY:LINKER_LANGUAGE>,D>:(.+)>")
            set(flags "${flags} ${CMAKE_MATCH_1}")
        endif()
    endforeach()

    separate_arguments(lst UNIX_COMMAND "${flags}")

    get_target_property(imps ${_target} INCLUDE_DIRECTORIES)
    if(imps)
        foreach(imp IN LISTS imps)
            get_filename_component(loc "${imp}" ABSOLUTE)
            list(APPEND lst "${CMAKE_INCLUDE_FLAG_D}${loc}")
        endforeach()
    endif()

    get_target_property(jimps ${_target} TEXT_INCLUDE_DIRECTORIES)
    if(jimps)
        foreach(jimp IN LISTS jimps)
            get_filename_component(loc "${jimp}" ABSOLUTE)
            list(APPEND lst "${CMAKE_TEXT_INCLUDE_FLAG_D}${loc}")
        endforeach()
    endif()

    set(${sources_var} "${srcs}" PARENT_SCOPE)
    set(${abs_sources_var} "${abs_srcs}" PARENT_SCOPE)
    set(${flags_var} "${lst}" PARENT_SCOPE)
endfunction()
