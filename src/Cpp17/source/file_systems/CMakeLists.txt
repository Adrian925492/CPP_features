# Defines version of the CMake - some of features are not backward compatiblem thus it is needed here. 
# At least one for project, in top-level CMake lists.txt required.
# It is good practice to keep it in all CMakeLists.txt files in the structure
cmake_minimum_required(VERSION 3.14)

add_library(file_systems_recepies STATIC file_systems.cpp file_systems.h)
add_executable(file_systems_grep grep.cpp)
add_executable(file_systems_changer file_changer.cpp)
add_executable(file_systems_ls ls_tool.cpp)
add_executable(file_systems_sizer_stats filesizes_stats.cpp)

# Link config library
target_link_libraries(
    file_systems_recepies
    PRIVATE
        cpp17_config
)

target_link_libraries(
    file_systems_grep
    PRIVATE
        cpp17_config
)

target_link_libraries(
    file_systems_changer
    PRIVATE
        cpp17_config
)

target_link_libraries(
    file_systems_ls
    PRIVATE
        cpp17_config
)

target_link_libraries(
    file_systems_sizer_stats
    PRIVATE
        cpp17_config
)