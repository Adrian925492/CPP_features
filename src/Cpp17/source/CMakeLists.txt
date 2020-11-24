# Defines version of the CMake - some of features are not backward compatiblem thus it is needed here. 
# At least one for project, in top-level CMake lists.txt required.
# It is good practice to keep it in all CMakeLists.txt files in the structure
cmake_minimum_required(VERSION 3.14)

add_subdirectory(new_features_cpp17)
add_subdirectory(vector)
add_subdirectory(map)
add_subdirectory(unordered_map)
add_subdirectory(stack)
add_subdirectory(set)
add_subdirectory(multimap)
add_subdirectory(queue)
add_subdirectory(iterators)
add_subdirectory(lambda)

# Define project name
project(Cpp17 VERSION 1.0.0)

# Add executable
add_executable(Cpp17 
    main.cpp
)

# Link config library
target_link_libraries(
    Cpp17
    PRIVATE
        cpp17_config
        vetor_recepies
        map_recepies
        unordered_map_recepies
        stack_recepies
        set_recepies
        multimap_recepies
        queue_recepies
        iterators_recepies
        lambda_recepies
)
