cmake_minimum_required(VERSION 3.12)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/_bin)

file(
        GLOB_RECURSE TIPPING_SOURCES
        # RELATIVE ${CMAKE_SOURCE_DIR}
        *.cpp 
        *.h
)

message("==== Tipping sources: ${TIPPING_SOURCES}")

add_executable(Tipping ${TIPPING_SOURCES})
target_include_directories(Tipping PUBLIC ../libFuzzyEngine)
target_link_libraries(Tipping FuzzyEngine)





