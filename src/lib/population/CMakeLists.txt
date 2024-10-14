set(
    HEADERS
    gene.h
    individual.h
    generation.h
    fitness_evaluator.h
)

add_library(${POPULATION_LIB_NAME} STATIC ${HEADERS})
set_target_properties(${POPULATION_LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(${POPULATION_LIB_NAME} PUBLIC "./")

target_link_libraries(${POPULATION_LIB_NAME} PUBLIC ${UTILITY_LIB_NAME})