set(
    HEADERS
    global_engine.h
    generators.h
)


add_library(${RANDOM_LIB_NAME} STATIC ${HEADERS})
set_target_properties(${RANDOM_LIB_NAME} PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(${RANDOM_LIB_NAME} PUBLIC "./")