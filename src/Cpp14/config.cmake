# Defines version of the CMake - some of features are not backward compatiblem thus it is needed here. 
# At least one for project, in top-level CMake lists.txt required.
# It is good practice to keep it in all CMakeLists.txt files in the structure
cmake_minimum_required(VERSION 3.14)

message(STATUS "CMAKE_SOURCE_DIR            = ${CMAKE_SOURCE_DIR}")
message(STATUS "CMAKE_BINARY_DIR            = ${CMAKE_BINARY_DIR}")
message(STATUS "CMAKE_SURRENT_SOURCE_DIR    = ${CMAKE_SURRENT_SOURCE_DIR}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR    = ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "PROJECT_SOURCE_DIR          = ${PROJECT_SOURCE_DIR}")
message(STATUS "PROJECT_BINARY_DIR          = ${PROJECT_BINARY_DIR}")

# Tell CMake to generatr compile_commands.json file
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Tekk CMake to generate Makefile with verbose ability. To get verbose output You will need to run make with "-v" flag.
set(CMAKE_VERBOSE_MAKEFILE ON)

# Compiler setting
set (CMAKE_CXX_STANDARD 14)

# Turn on error when compiler standard not satisfied
set (CMAKE_CXX_STANDARD_REQUIRED ON)

# Disable compile standard-specific extensions
set (CMAKE_CXX_EXTENSIONS OFF)

# Add INTERFACE type library - will not produce artofacts, used only to propagate properties set 
# for the libarry with INTERFACE prefixes
add_library(cpp14_config INTERFACE)

# Set compiler settings - standard in that case
target_compile_features(cpp14_config INTERFACE
    cxx_std_14
)

# Set compiler flags
target_compile_options(cpp14_config INTERFACE
    -pthread
)