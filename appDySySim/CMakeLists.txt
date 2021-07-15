cmake_minimum_required(VERSION 3.12)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

file(
        GLOB_RECURSE DYSYSIM_SOURCES
        # RELATIVE ${CMAKE_SOURCE_DIR}
        *.cpp 
        *.h
)

message("==== DySySim sources: ${DYSYSIM_SOURCES}")

add_executable(dss ${DYSYSIM_SOURCES})

target_include_directories(dss PUBLIC ../libDySySim)
target_link_libraries(dss DySySim)
