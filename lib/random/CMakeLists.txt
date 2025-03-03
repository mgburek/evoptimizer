set(
    HEADERS
    "includes/global_engine.h"
    "includes/generators.h"
)

add_library(${RANDOM_LIB_NAME} INTERFACE)

target_include_directories(${RANDOM_LIB_NAME} INTERFACE "includes")