cmake_minimum_required(VERSION 3.12)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

file(
    GLOB_RECURSE LIBDYSYSIM_SOURCES
    # RELATIVE ${CMAKE_SOURCE_DIR}
    *.cpp 
)

file(
    GLOB_RECURSE LIBDYSYSIM_INCLUDES
    # RELATIVE ${CMAKE_SOURCE_DIR}
    *.h
)

message("==== libDySiSim includes: ${LIBDYSYSIM_INCLUDES}")
message("==== libDySySIm sources : ${LIBDYSYSIM_SOURCES}")

add_library(DySySim STATIC ${LIBDYSYSIM_SOURCES} ${LIBDYSYSIM_INCLUDES})
