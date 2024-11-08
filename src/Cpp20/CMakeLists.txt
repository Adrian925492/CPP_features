# Defines version of the CMake - some of features are not backward compatiblem thus it is needed here. 
# At least one for project, in top-level CMake lists.txt required.
# It is good practice to keep it in all CMakeLists.txt files in the structure
cmake_minimum_required(VERSION 3.18)

# Include the FetchContent module
include(FetchContent)

# Define project name
project(Cpp20 VERSION 1.0.0)

# Add testing
include(CTest)

# Include config for Cpp11
include(config/config.cmake)

# Include cppcheck
include(config/cppcheck.cmake)

# Include cppcheck
include(config/clang-tidy.cmake)

# Include cppcheck
include(config/clang-format.cmake)

# Add source subdir
add_subdirectory(source)

# Include test subdirectory
if(BUILD_TESTING)
    # Declare and fetch GoogleTest
    FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1
    )
    FetchContent_MakeAvailable(googletest)

    add_subdirectory(tests)
endif()