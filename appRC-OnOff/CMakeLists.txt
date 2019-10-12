cmake_minimum_required(VERSION 3.12)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

file(
        GLOB_RECURSE RC-ONOFF_SOURCES
        # RELATIVE ${CMAKE_SOURCE_DIR}
        *.cpp 
        *.h
)

message("==== RC-OnOff sources: ${RC-ONOFF_SOURCES}")

add_executable(RC-OnOff ${RC-ONOFF_SOURCES})

target_include_directories(RC-OnOff PUBLIC ../libFuzzyEngine)
target_link_libraries(RC-OnOff FuzzyEngine)

target_include_directories(RC-OnOff PUBLIC ../libDySySim)
target_link_libraries(RC-OnOff DySySim)
