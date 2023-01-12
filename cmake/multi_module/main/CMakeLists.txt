project(main)

add_executable(${PROJECT_NAME} main.cc)

target_link_libraries(${PROJECT_NAME}
    multi_module::mod_a
    multi_module::mod_b
)