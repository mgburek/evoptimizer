cmake_minimum_required(VERSION 3.10)

project(
    Evoptimzer
    VERSION 0.0.1
    LANGUAGES CXX 
)

set(CMAKE_CXX_STANDARD 17) 
set(CMAKE_CXX_STANDARD_REQUIRED ON) 
set(CMAKE_CXX_EXTENSIONS OFF)

set(EVOPTIMIZER_CLASSIC_LIB_NAME "evoptimizer_classic_lib")
set(EVOPTIMIZER_LIB_NAME "evoptimizer_lib")

set(MESSAGE_PREFIX "${PROJECT_NAME}: ")

option(COMPILE_EXAMPLES OFF)

add_subdirectory("lib")

if(BUILD_TESTING)
    enable_testing()
    message(${MESSAGE_PREFIX} "Tests enabled")
    add_subdirectory("tests")
else()
    message(${MESSAGE_PREFIX} "Tests not enabled")
endif()

if(COMPILE_EXAMPLES)
    message(${MESSAGE_PREFIX} "Compiling with example executable")
    add_subdirectory("examples")
else()
    message(${MESSAGE_PREFIX} "Compiling without example executable")
endif()