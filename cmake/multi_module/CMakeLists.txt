cmake_minimum_required (VERSION 3.9 FATAL_ERROR)

project(multi_module LANGUAGES C CXX)
add_definitions(-std=c++11)
add_subdirectory(module_a)
add_subdirectory(module_b)
add_subdirectory(main)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)