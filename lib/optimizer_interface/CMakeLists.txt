set(
    HEADERS
    "includes/optimizer.h"
)

add_library(${OPTIMIZER_INTERFACE_NAME} STATIC ${HEADERS})
set_target_properties(${OPTIMIZER_INTERFACE_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(${OPTIMIZER_INTERFACE_NAME} PUBLIC "includes")