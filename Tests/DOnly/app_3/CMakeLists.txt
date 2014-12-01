include_directories(app_3 ${PROJECT_SOURCE_DIR})

add_executable(app_3 app_3.d)
target_link_libraries(app_3 lib_1)

add_test(app_3 app_3)
