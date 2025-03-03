set(
    HEADERS
    "population/individual.h"
    "population/generation.h"
    "population/fitness_evaluator.h"
    "algorithm/selector.h"
    "algorithm/selector_rank.h"
    "algorithm/cross_breeder.h"
    "algorithm/cross_breeder_single_point_mean.h"
    "algorithm/mutator.h"
    "algorithm/mutator_single_gene_additive.h"
    "includes/evoptimizer.h"
)

add_library(${EVOPTIMIZER_LIB_NAME} INTERFACE)

target_include_directories(
    ${EVOPTIMIZER_LIB_NAME} 
    INTERFACE
    "includes"
    "population" 
    "algorithm")

target_link_libraries(
    ${EVOPTIMIZER_LIB_NAME} 
    INTERFACE
    ${RANDOM_LIB_NAME}
    ${OPTIMIZER_INTERFACE_NAME}
)