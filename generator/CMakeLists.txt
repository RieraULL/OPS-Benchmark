project(OPS_benchmark_generator)


file(GLOB SOURCES 
    "src/CSU_EMIR_t.cpp"
    "src/CSU_setup_t.cpp"
    "src/EMIR_instance_t.cpp"
    "src/EMIR_set_generator_t.cpp"
    "src/EMIR_target_range_t.cpp"
    "src/EMIR_target_set_2_LaTeX.cpp"
    "src/EMIR_target_set_t.cpp"
    "src/instance_config_t.cpp" 
    "src/instance_set_config_t.cpp"
    "src/instance_type_code.cpp"
    "src/point_t.cpp"
    "src/target_generator_t.cpp"
    "src/target_range_t.cpp"
    "src/target_t.cpp"
    "src/valid_range_t.cpp"
    "src/main.cpp"
)


# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES} )

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/include
) 

# Add flags to the compiler
target_compile_options(${PROJECT_NAME} PRIVATE
  -Wall
  -Wextra
  -Wshadow
  -g
)
