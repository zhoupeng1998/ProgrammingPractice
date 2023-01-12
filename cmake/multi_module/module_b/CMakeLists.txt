project(mod_b)

aux_source_directory(src DIR_SRCS)

add_library(${PROJECT_NAME} ${DIR_SRCS})
add_library(multi_module::mod_b ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME}
    multi_module::mod_a
)