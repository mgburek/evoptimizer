set(
    HEADERS
    "includes/selector.h"
    "includes/cross_breeder.h"
    "includes/mutator.h"
    "includes/rank_selector.h"
    "includes/single_point_cross_breeder.h"
    "includes/single_bit_mutator.h"
    "includes/evoptimizer.h"
)

add_library(${LIBRARY_NAME} STATIC ${HEADERS})
set_target_properties(${LIBRARY_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(${LIBRARY_NAME} PUBLIC "includes")

target_link_libraries(
    ${LIBRARY_NAME} 
    PUBLIC 
    ${POPULATION_LIB_NAME}
    ${RANDOM_LIB_NAME}
)