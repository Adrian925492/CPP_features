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
add_subdirectory(algorithms)
add_subdirectory(advanced_algorithms)
add_subdirectory(strings)
add_subdirectory(traits)
add_subdirectory(parallel_processing)
add_subdirectory(file_systems)

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
        algorithm_recepies
        advanced_algorithm_recepies
        string_recepies
        traits_recepies
        parallell_processing_recepies
        file_systems_recepies
)

add_custom_command(
    TARGET Cpp17
    COMMAND ${CMAKE_OBJCOPY} ARGS --only-keep-debug ${EXECUTABLE_OUTPUT_PATH}/Cpp17 ${EXECUTABLE_OUTPUT_PATH}/Cpp17.debug
    COMMAND strip ARGS -g ${EXECUTABLE_OUTPUT_PATH}/Cpp17
    COMMAND ${CMAKE_OBJCOPY} ARGS --add-gnu-debuglink=${EXECUTABLE_OUTPUT_PATH}/Cpp17.debug ${EXECUTABLE_OUTPUT_PATH}/Cpp17
    DEPENDS ${EXECUTABLE_OUTPUT_PATH}/Cpp17
)
