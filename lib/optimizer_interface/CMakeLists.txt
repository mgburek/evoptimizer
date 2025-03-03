set(
    HEADERS
    "includes/optimizer.h"
)

add_library(${OPTIMIZER_INTERFACE_NAME} INTERFACE)

target_include_directories(${OPTIMIZER_INTERFACE_NAME} INTERFACE "includes")