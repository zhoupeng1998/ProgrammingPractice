project(exec_b)

add_executable(${PROJECT_NAME} exec_b.cc)

target_link_libraries(${PROJECT_NAME}
    multi_exec::mod_shared
)