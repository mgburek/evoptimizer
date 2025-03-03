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

function(prefixed_message text)
    set(MESSAGE_PREFIX "${PROJECT_NAME}: ")
    message(${MESSAGE_PREFIX} " " ${text})
endfunction()

option(EVOPTIMIZER_COMPILE_EXAMPLES OFF)
option(EVOPTIMIZER_BUILD_TESTING OFF)

add_subdirectory("lib")

if(EVOPTIMIZER_BUILD_TESTING)
    enable_testing()
    prefixed_message("Tests enabled")
    add_subdirectory("tests")
else()
    prefixed_message("Tests not enabled")
endif()

if(EVOPTIMIZER_COMPILE_EXAMPLES)
    prefixed_message("Compiling with example executable")
    add_subdirectory("examples")
else()
    prefixed_message("Compiling without example executable")
endif()