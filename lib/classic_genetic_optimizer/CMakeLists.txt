set(
    HEADERS
    "population/gene.h"
    "population/individual.h"
    "population/generation.h"
    "population/fitness_evaluator.h"
    "algorithm/selector.h"
    "algorithm/cross_breeder.h"
    "algorithm/mutator.h"
    "algorithm/rank_selector.h"
    "algorithm/single_point_cross_breeder.h"
    "algorithm/single_bit_mutator.h"
    "includes/evoptimizer.h"
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
)