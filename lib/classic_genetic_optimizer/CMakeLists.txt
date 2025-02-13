set(
    HEADERS
    "population/classic_gene.h"
    "population/classic_individual.h"
    "population/classic_generation.h"
    "population/classic_fitness_evaluator.h"
    "algorithm/classic_selector.h"
    "algorithm/classic_cross_breeder.h"
    "algorithm/classic_mutator.h"
    "algorithm/classic_rank_selector.h"
    "algorithm/classic_single_point_cross_breeder.h"
    "algorithm/classic_single_bit_mutator.h"
    "includes/classic_evoptimizer.h"
)

add_library(${EVOPTIMIZER_CLASSIC_LIB_NAME} STATIC ${HEADERS})
set_target_properties(${EVOPTIMIZER_CLASSIC_LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(
    ${EVOPTIMIZER_CLASSIC_LIB_NAME} 
    PUBLIC 
    "includes"
    "population"
    "algorithm"
)

target_link_libraries(
    ${EVOPTIMIZER_CLASSIC_LIB_NAME} 
    PUBLIC 
    ${RANDOM_LIB_NAME}
    ${OPTIMIZER_INTERFACE_NAME}
)