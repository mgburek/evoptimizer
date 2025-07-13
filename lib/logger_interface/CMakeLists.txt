set(
        HEADERS
        "includes/logger_interface.h"
)

add_library(${LOGGER_INTERFACE_NAME} INTERFACE)

target_include_directories(${LOGGER_INTERFACE_NAME} INTERFACE "includes")