include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest
    GIT_TAG v1.15.2
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(googletest)

set(
    TESTS
    single_point_cross_breeder_test
    single_bit_mutator_test
)

include(GoogleTest)
foreach(test IN LISTS TESTS)
    message("Test: ${test}")
    add_executable(${test} "${test}.cpp")
    target_link_libraries(${test} ${EVOPTIMIZER_CLASSIC_LIB_NAME} GTest::gtest_main)

    # automatically detect and add tests found in the target, alternative to add_test
    gtest_discover_tests(${test})
endforeach(test in TESTS)