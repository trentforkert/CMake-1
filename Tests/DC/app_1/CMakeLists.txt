# This is a D app that links a C library.
#
# The linker preference of D is higher than C (or CXX), so after
# the objects are created, the D toolchain will drive linking.
#
include_directories(app_1 ${PROJECT_SOURCE_DIR})

add_executable(app_1 app_1.d)
target_link_libraries(app_1 lib_1)

add_test(app_1 app_1)
