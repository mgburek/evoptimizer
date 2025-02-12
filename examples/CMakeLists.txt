set(ClASSIC_ALGORITHM_EXAMPLE_NAME "evoptimizer_classic_example")
add_executable(${ClASSIC_ALGORITHM_EXAMPLE_NAME} "classic/main.cpp")
target_link_libraries(${ClASSIC_ALGORITHM_EXAMPLE_NAME} ${EVOPTIMIZER_CLASSIC_LIB_NAME})

set(EVOPTIMIZER_EXAMPLE_NAME "evoptimizer_example")
add_executable(${EVOPTIMIZER_EXAMPLE_NAME} "evoptimizer/main.cpp")
target_link_libraries(${EVOPTIMIZER_EXAMPLE_NAME} ${EVOPTIMIZER_LIB_NAME})