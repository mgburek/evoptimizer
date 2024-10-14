set(
    HEADERS
    optimizer.h
    rank_selector.h
)

set(
    SOURCES
    optimizer.cpp
)

set(POPULATION_LIB_NAME population_lib)
set(UTILITY_LIB_NAME utility_lib)

add_subdirectory("utility")
add_subdirectory("population")

add_library(${LIBRARY_NAME} STATIC ${HEADERS} ${SOURCES})

set(
    INCLUDES
    "./"
)

target_include_directories(${LIBRARY_NAME} PUBLIC ${INCLUDES})

target_link_libraries(
    ${LIBRARY_NAME} 
    PUBLIC 
    ${POPULATION_LIB_NAME}
    ${UTILITY_LIB_NAME}
)