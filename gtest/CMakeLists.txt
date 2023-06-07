cmake_minimum_required(VERSION 3.12)

# Project name
project(MyProject)

# Locate the Google Test libraries
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add the executable and link against the Google Test libraries
add_executable(MyTests tests.cc my_math.cc)
target_link_libraries(MyTests GTest::GTest GTest::Main)

include_directories(${PROJECT_SOURCE_DIR})