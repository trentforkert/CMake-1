macro(add_d_test_macro NAME)
  string(REPLACE "." "/" dir "D.${NAME}")
  add_test(NAME "D.${NAME}" COMMAND "${CMAKE_CTEST_COMMAND}"
    --build-and-test
    "${CMake_SOURCE_DIR}/Tests/${dir}"
    "${CMake_BINARY_DIR}/Tests/${dir}"
    --build-two-config
    ${build_generator_args}
    --build-project ${NAME}
    ${${NAME}_CTEST_OPTIONS}
    --build-options ${build_options}
    ${${NAME}_BUILD_OPTIONS}
    --test-command ${NAME} ${ARGN})
  list(APPEND TEST_BUILD_DIRS "${CMake_BINARY_DIR}/Tests/${dir}")
endmacro()

add_d_test_macro(DOnly)
add_d_test_macro(DC)
add_d_test_macro(UseD)
add_d_test_macro(DTextIncludes)
add_subdirectory(DDeps)
