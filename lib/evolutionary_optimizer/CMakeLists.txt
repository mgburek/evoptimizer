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
        ${LOGGER_INTERFACE_NAME}
)