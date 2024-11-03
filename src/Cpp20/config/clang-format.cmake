# additional target to perform clang-tidy run, requires clang-tidy
# Usage: make clang-tidy

# Defines version of the CMake - some of features are not backward compatiblem thus it is needed here. 
# At least one for project, in top-level CMake lists.txt required.
# It is good practice to keep it in all CMakeLists.txt files in the structure
cmake_minimum_required(VERSION 3.14)

# Find (using glob :( ) all source files for check)
file(
        GLOB_RECURSE 
        ALL_SOURCE_FILES 
                ${CMAKE_SOURCE_DIR}/Cpp20/source/*.cpp 
                ${CMAKE_SOURCE_DIR}/Cpp20/source/*.h
                ${CMAKE_SOURCE_DIR}/Cpp20/tests/*.cpp 
                ${CMAKE_SOURCE_DIR}/Cpp20/tests/*.h
)

message(STATUS "ClangTidy enabled")
message(STATUS "Source files for clang-tidy processing: ${ALL_SOURCE_FILES}")

# And add cppcheck target
add_custom_target(
        clang-format
        COMMAND /usr/bin/clang-format
        -style=WebKit
        -i
        ${ALL_SOURCE_FILES}
)
