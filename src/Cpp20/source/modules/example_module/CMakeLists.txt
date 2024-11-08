cmake_minimum_required(VERSION 3.18)

add_library(example_module STATIC example_module.cppm)

target_include_directories(example_module PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Set compiler settings - standard in that case
target_compile_features(example_module PRIVATE
    cxx_std_20
)

# Set compiler flags
target_compile_options(example_module PRIVATE
    -fconcepts
    -g
    -fmodules-ts
    -x c++
)
