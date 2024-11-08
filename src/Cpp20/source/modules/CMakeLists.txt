# Defines version of the CMake - some of features are not backward compatiblem thus it is needed here. 
# At least one for project, in top-level CMake lists.txt required.
# It is good practice to keep it in all CMakeLists.txt files in the structure
cmake_minimum_required(VERSION 3.18)

add_subdirectory(example_module)

add_library(modules STATIC modules.cpp)

target_include_directories(modules PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Link config library
target_link_libraries(
    modules
    PRIVATE
        cpp20_config
)