cmake_minimum_required(VERSION 3.0)

project(AddConditions D)

include(UseD)

add_d_conditions(VERSION Condition1)

add_library(conditions STATIC conditions.d)
add_d_conditions(TARGETS conditions VERSION Condition2)

