cmake_minimum_required(VERSION 3.12)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

file(
    GLOB_RECURSE TESTFUZZYENGINE_SOURCES
    *.cpp 
)

file(
    GLOB_RECURSE TESTFUZZYENGINE_INCLUDES
    *.h
)

message("==== testFuzzyEngine includes: ${TESTFUZZYENGINE_INCLUDES}")
message("==== testFuzzyEngine sources : ${TESTFUZZYENGINE_SOURCES}")

add_executable(testFuzzyEngine ${TESTFUZZYENGINE_SOURCES}
                               ${TESTFUZZYENGINE_INCLUDES})

target_include_directories(testFuzzyEngine PUBLIC ../libFuzzyEngine)
target_link_libraries(testFuzzyEngine FuzzyEngine)
target_link_libraries(testFuzzyEngine UnitTest++)
