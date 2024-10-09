set(
    HEADERS
    optimizer.h
)

set(
    SOURCES
    optimizer.cpp
)

add_library(${LIBRARY_NAME} STATIC ${HEADERS} ${SOURCES})

set(
    INCLUDES
    "./"
)

target_include_directories(${LIBRARY_NAME} PUBLIC ${INCLUDES})