# Defines version of the CMake - some of features are not backward compatiblem thus it is needed here. 
# At least one for project, in top-level CMake lists.txt required.
# It is good practice to keep it in all CMakeLists.txt files in the structure
cmake_minimum_required(VERSION 3.18)

add_subdirectory(constant_expressions)
add_subdirectory(move_semantic)
add_subdirectory(multilang_string)
add_subdirectory(spaceship)
add_subdirectory(modules)
add_subdirectory(concepts)

# Define project name
project(Cpp20 VERSION 1.0.0)

# Add executable
add_executable(Cpp20 
    main.cpp
)

# Link config library
target_link_libraries(
    Cpp20
    PRIVATE
        cpp20_config
        constant_expressions
        move_semantic
        multilang_string
        spaceship
        modules
        concepts
)

add_custom_command(
    TARGET Cpp20
    COMMAND ${CMAKE_OBJCOPY} ARGS --only-keep-debug ${EXECUTABLE_OUTPUT_PATH}/Cpp20 ${EXECUTABLE_OUTPUT_PATH}/Cpp20.debug
    COMMAND strip ARGS -g ${EXECUTABLE_OUTPUT_PATH}/Cpp20
    COMMAND ${CMAKE_OBJCOPY} ARGS --add-gnu-debuglink=${EXECUTABLE_OUTPUT_PATH}/Cpp20.debug ${EXECUTABLE_OUTPUT_PATH}/Cpp20
    DEPENDS ${EXECUTABLE_OUTPUT_PATH}/Cpp20
)
