set(
    HEADERS
    "includes/global_engine.h"
    "includes/generators.h"
)

add_library(${RANDOM_LIB_NAME} STATIC ${HEADERS})
set_target_properties(${RANDOM_LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(${RANDOM_LIB_NAME} PUBLIC "includes")