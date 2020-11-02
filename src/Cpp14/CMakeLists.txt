# Defines version of the CMake - some of features are not backward compatiblem thus it is needed here. 
# At least one for project, in top-level CMake lists.txt required.
# It is good practice to keep it in all CMakeLists.txt files in the structure
cmake_minimum_required(VERSION 3.14)

# Define project name
project(Cpp14 VERSION 1.0.0)

# Include config for Cpp11
include(config.cmake)

# Add executable
add_executable(Cpp14 
    main.cpp
)

# Link config library
target_link_libraries(
    Cpp14
    PRIVATE
        cpp14_config
)
