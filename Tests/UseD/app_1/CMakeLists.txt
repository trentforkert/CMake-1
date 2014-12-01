file(GLOB files RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.d")

include(UseD)

enable_testing()

foreach(file IN LISTS files)
    get_filename_component(executable ${file} NAME_WE)
    add_library(${executable} ${file})
    add_d_unittests("test_${executable}"
        TARGET ${executable}
        SOURCES ${file})
endforeach()
