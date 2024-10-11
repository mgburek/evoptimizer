add_subdirectory("lib")

if(COMPILE_EXAMPLE)
    message("Compiling with example executable")
    add_subdirectory("example")
else()
    message("Compiling without example executable")
endif()