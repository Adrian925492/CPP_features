# Defines version of the CMake - some of features are not backward compatiblem thus it is needed here. 
# At least one for project, in top-level CMake lists.txt required.
# It is good practice to keep it in all CMakeLists.txt files in the structure
cmake_minimum_required(VERSION 3.14)

# project
project(CppFeatures)

# add subdirs
add_subdirectory(Cpp14)
add_subdirectory(Cpp17)