# Defines version of the CMake - some of features are not backward compatiblem thus it is needed here. 
# At least one for project, in top-level CMake lists.txt required.
# It is good practice to keep it in all CMakeLists.txt files in the structure
cmake_minimum_required(VERSION 3.14)

add_library(unordered_map_recepies STATIC unordered_map.cpp unordered_map.h)

# Link config library
target_link_libraries(
    unordered_map_recepies
    PRIVATE
        cpp17_config
)