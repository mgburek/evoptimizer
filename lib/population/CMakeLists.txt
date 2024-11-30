set(
    HEADERS
    "includes/gene.h"
    "includes/individual.h"
    "includes/generation.h"
    "includes/fitness_evaluator.h"
)

add_library(${POPULATION_LIB_NAME} STATIC ${HEADERS})
set_target_properties(${POPULATION_LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(${POPULATION_LIB_NAME} PUBLIC "includes")

target_link_libraries(${POPULATION_LIB_NAME} PUBLIC ${RANDOM_LIB_NAME})