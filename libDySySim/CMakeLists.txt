cmake_minimum_required(VERSION 3.12)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

file(
    GLOB_RECURSE DYSYSIM_SOURCES
    # RELATIVE ${CMAKE_SOURCE_DIR}
    *.cpp 
)

file(
    GLOB_RECURSE DYSYSIM_INCLUDES
    # RELATIVE ${CMAKE_SOURCE_DIR}
    *.h
)

message("==== DySiSim includes: ${DYSYSIM_INCLUDES}")
message("==== DySySIm sources : ${DYSYSIM_SOURCES}")

add_library(DySySim STATIC ${DYSYSIM_SOURCES} ${DYSYSIM_INCLUDES})
# target_include_directories(FuzzyEngine PUBLIC ${FUZZYENGINE_INCLUDES})
# install(TARGETS FuzzyEngine DESTINATION "${PROJECT_SOURCE_DIR}/lib")
