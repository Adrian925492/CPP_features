# Defines version of the CMake - some of features are not backward compatiblem thus it is needed here. 
# At least one for project, in top-level CMake lists.txt required.
# It is good practice to keep it in all CMakeLists.txt files in the structure
cmake_minimum_required(VERSION 3.14)

add_library(vetor_recepies STATIC vector.cpp vector.h)

# Link config library
target_link_libraries(
    vetor_recepies
    PRIVATE
        cpp17_config
)