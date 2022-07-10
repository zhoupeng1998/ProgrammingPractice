cmake_minimum_required (VERSION 3.9 FATAL_ERROR)

project(programming_practice LANGUAGES CXX)
add_definitions(-std=c++11)
add_subdirectory(sorting)
add_subdirectory(data_structure)
add_subdirectory(smart_pointer)

add_executable(${PROJECT_NAME} main.cc)

target_link_libraries(${PROJECT_NAME}
    sorting
    data_structure
    smart_pointer
)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)