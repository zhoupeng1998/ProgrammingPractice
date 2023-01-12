cmake_minimum_required (VERSION 3.9 FATAL_ERROR)

project(multi_exec LANGUAGES C CXX)
add_definitions(-std=c++11)
add_subdirectory(exec_a)
add_subdirectory(exec_b)
add_subdirectory(shared_mod)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)