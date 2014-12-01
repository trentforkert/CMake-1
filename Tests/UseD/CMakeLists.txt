cmake_minimum_required(VERSION 3.0)

project(UseD D)

include_directories(AddConditions Ddoc EnforceProperty HeaderGen)

add_subdirectory(AddConditions)
add_subdirectory(Ddoc)
add_subdirectory(EnforceProperty)
add_subdirectory(HeaderGen)

include_directories(${DDOC_CHECKER_INCLUDE_DIR})
include_directories(${HEADER_CHECKER_INCLUDE_DIR})

add_executable(UseD main.d)
target_link_libraries(UseD conditions ddocChecker enforceProperty headerChecker)

# # extra tests from cmake-d
# add_subdirectory(app_1)
