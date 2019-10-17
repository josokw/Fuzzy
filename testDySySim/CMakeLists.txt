cmake_minimum_required(VERSION 3.12)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

find_library(UnitTest++ REQUIRED)

file(
    GLOB_RECURSE TESTDYSYSIM_SOURCES
    # RELATIVE ${CMAKE_SOURCE_DIR}
    *.cpp 
)

file(
    GLOB_RECURSE TESTDYSYSIM_INCLUDES
    # RELATIVE ${CMAKE_SOURCE_DIR}
    *.h
)

message("==== testDySySim includes: ${TESTDYSYSIM_INCLUDES}")
message("==== testDySySim sources : ${TESTDYSYSIM_SOURCES}")

add_executable(testDySySim ${TESTDYSYSIM_SOURCES} ${TESTDYSYSIM_INCLUDES})

target_include_directories(testDySySim PUBLIC ../libDySySim)
target_link_libraries(testDySySim DySySim)
target_link_libraries(testDySySim UnitTest++)
