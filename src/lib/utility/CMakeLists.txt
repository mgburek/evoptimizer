set(
    HEADERS
    random_generator.h
)

set(
    SOURCES
    random_generator.cpp
)

add_library(${UTILITY_LIB_NAME} STATIC ${HEADERS} ${SOURCES})

target_include_directories(${UTILITY_LIB_NAME} PUBLIC "./")