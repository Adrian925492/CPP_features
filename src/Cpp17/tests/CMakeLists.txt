# Defines version of the CMake - some of features are not backward compatiblem thus it is needed here. 
# At least one for project, in top-level CMake lists.txt required.
# It is good practice to keep it in all CMakeLists.txt files in the structure
cmake_minimum_required(VERSION 3.14)

# Set test exec output path
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/test)

# Add test project
project(Cpp17_tests)

# Add executable
add_executable(
    Cpp17_tests
    test.cpp

)

target_link_libraries(
    Cpp17_tests
    PRIVATE
        gtest
        gmock
        gmock_main
        cpp17_config   
)

# add_test()