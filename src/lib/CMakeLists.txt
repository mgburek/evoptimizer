set(
    HEADERS
    rank_selector.h
    single_point_cross_breeder.h
    single_bit_mutator.h
)

set(POPULATION_LIB_NAME "population_lib")
set(RANDOM_LIB_NAME "random_lib")

add_subdirectory("random")
add_subdirectory("population")

add_library(${LIBRARY_NAME} STATIC ${HEADERS})
set_target_properties(${LIBRARY_NAME} PROPERTIES LINKER_LANGUAGE CXX)

set(
    INCLUDES
    "./"
)

target_include_directories(${LIBRARY_NAME} PUBLIC ${INCLUDES})

target_link_libraries(
    ${LIBRARY_NAME} 
    PUBLIC 
    ${POPULATION_LIB_NAME}
    ${RANDOM_LIB_NAME}
)