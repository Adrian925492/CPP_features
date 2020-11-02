# additional target to perform cppcheck run, requires cppcheck

# Defines version of the CMake - some of features are not backward compatiblem thus it is needed here. 
# At least one for project, in top-level CMake lists.txt required.
# It is good practice to keep it in all CMakeLists.txt files in the structure
cmake_minimum_required(VERSION 3.14)

# Find (using glob :( ) all source files for check)
file(GLOB_RECURSE ALL_SOURCE_FILES ${CMAKE_SOURCE_DIR}/Cpp17/source/*.cpp ${CMAKE_SOURCE_DIR}/Cpp17/source/*.h)

message(STATUS "CppCheck enabled")
message(STATUS "Source files for cppcheck processing: ${ALL_SOURCE_FILES}")

# And add cppcheck target
add_custom_target(
        cppcheck
        COMMAND /usr/bin/cppcheck
        --enable=warning,performance,portability,information,missingInclude
        --std=c++17
        --library=qt.cfg
        --template="[{severity}][{id}] {message} {callstack} \(On {file}:{line}\)"
        --verbose
        --quiet
        ${ALL_SOURCE_FILES}
)
