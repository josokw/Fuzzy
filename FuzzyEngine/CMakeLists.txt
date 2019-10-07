cmake_minimum_required(VERSION 3.12)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

file(
    GLOB_RECURSE FUZZYENGINE_SOURCES
    # RELATIVE ${CMAKE_SOURCE_DIR}
    *.cpp 
)

file(
    GLOB_RECURSE FUZZYENGINE_INCLUDES
    # RELATIVE ${CMAKE_SOURCE_DIR}
    *.h
)

message("==== FyzzyEngine includes: ${FUZZYENGINE_INCLUDES}")
message("==== FuzzyEngine sources : ${FUZZYENGINE_SOURCES}")

add_library(FuzzyEngine STATIC ${FUZZYENGINE_SOURCES} ${FUZZYENGINE_INCLUDES})
# target_include_directories(FuzzyEngine PUBLIC ${FUZZYENGINE_INCLUDES})
# install(TARGETS FuzzyEngine DESTINATION "${PROJECT_SOURCE_DIR}/lib")
