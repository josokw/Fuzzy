cmake_minimum_required(VERSION 3.12)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

find_library(UnitTest++ REQUIRED)

file(
    GLOB_RECURSE FUZZYENGINETESTS_SOURCES
    *.cpp 
)

file(
    GLOB_RECURSE FUZZYENGINETESTS_INCLUDES
    *.h
)

message("==== FuzzyEngineTests includes: ${FUZZYENGINETESTS_INCLUDES}")
message("==== FuzzyEngineTests sources : ${FUZZYENGINETESTS_SOURCES}")

add_executable(FuzzyEngineTests ${FUZZYENGINETESTS_SOURCES} ${FUZZYENGINETESTS_INCLUDES})

target_include_directories(FuzzyEngineTests PUBLIC ../FuzzyEngine)
target_link_libraries(FuzzyEngineTests FuzzyEngine)
target_link_libraries(FuzzyEngineTests UnitTest++)
