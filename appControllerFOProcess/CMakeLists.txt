cmake_minimum_required(VERSION 3.12)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/_bin)

file(
        GLOB_RECURSE CONTROLLERFOPROCESS_SOURCES
        # RELATIVE ${CMAKE_SOURCE_DIR}
        *.cpp 
        *.h
)

message("==== ControllerFOProcess sources: ${CONTROLLERFOPROCESS_SOURCES}")

add_executable(ControllerFOProcess ${CONTROLLERFOPROCESS_SOURCES})

target_include_directories(ControllerFOProcess PUBLIC ../FuzzyEngine)
target_link_libraries(ControllerFOProcess FuzzyEngine)

target_include_directories(ControllerFOProcess PUBLIC ../DySySim)
target_link_libraries(ControllerFOProcess DySySim)
