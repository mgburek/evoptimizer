cmake_minimum_required(VERSION 3.20)

project(
    Evoptimzer
    VERSION 0.0.1
    LANGUAGES CXX 
)

set(CMAKE_CXX_STANDARD 20) 
set(CMAKE_CXX_STANDARD_REQUIRED ON) 
set(CMAKE_CXX_EXTENSIONS OFF)

set(LIBRARY_NAME "evoptimzer")
set(EXAMPLE_EXECUTABLE_NAME "lib_example")

option(COMPILE_EXAMPLE OFF)

if(BUILD_TESTING)
    enable_testing()
endif()

add_subdirectory("src")