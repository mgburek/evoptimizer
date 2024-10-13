set(
    HEADERS
    int_random_generator.h
    real_random_generator.h
)


add_library(${UTILITY_LIB_NAME} STATIC ${HEADERS})
set_target_properties(${UTILITY_LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(${UTILITY_LIB_NAME} PUBLIC "./")