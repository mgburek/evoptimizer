cmake_minimum_required(VERSION 3.10)

project(
    Evoptimzer
    VERSION 0.0.1
    LANGUAGES CXX 
)

set(CMAKE_CXX_STANDARD 17) 
set(CMAKE_CXX_STANDARD_REQUIRED ON) 
set(CMAKE_CXX_EXTENSIONS OFF)

set(LIBRARY_NAME "evoptimizer")
set(EXAMPLE_EXECUTABLE_NAME "lib_example")

option(COMPILE_EXAMPLE OFF)

if(BUILD_TESTING)
    enable_testing()
endif()

add_subdirectory("lib")

if(BUILD_TESTING)
    message("Tests enabled")
    add_subdirectory("tests")
else()
    message("Tests not enabled")
endif()

if(COMPILE_EXAMPLE)
    message("Compiling with example executable")
    add_subdirectory("example")
else()
    message("Compiling without example executable")
endif()