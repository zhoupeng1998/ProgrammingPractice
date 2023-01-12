project(exec_a)

add_executable(${PROJECT_NAME} exec_a.cc)

target_link_libraries(${PROJECT_NAME}
    multi_exec::mod_shared
)