# Defines version of the CMake - some of features are not backward compatiblem thus it is needed here. 
# At least one for project, in top-level CMake lists.txt required.
# It is good practice to keep it in all CMakeLists.txt files in the structure
cmake_minimum_required(VERSION 3.10)

# Create a library for the ChaiScript functionality
add_library(chaiscript_lib STATIC chai.cpp)

target_include_directories(chaiscript_lib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${chaiscript_SOURCE_DIR}/include
)

# Link config library
target_link_libraries(
    chaiscript_lib
    PRIVATE
        cpp20_config
)

# Create a separate executable for ChaiScript example
add_executable(chaiscript_example main.cpp)

target_include_directories(chaiscript_example PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${chaiscript_SOURCE_DIR}/include
)

target_link_libraries(
    chaiscript_example
    PRIVATE
        chaiscript_lib
        cpp20_config
        -lpthread
)