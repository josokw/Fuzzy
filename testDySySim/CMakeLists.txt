cmake_minimum_required(VERSION 3.12)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

find_library(UnitTest++ REQUIRED)

file(
    GLOB_RECURSE DYSYSIMTESTS_SOURCES
    # RELATIVE ${CMAKE_SOURCE_DIR}
    *.cpp 
)

file(
    GLOB_RECURSE DYSYSIMTESTS_INCLUDES
    # RELATIVE ${CMAKE_SOURCE_DIR}
    *.h
)

message("==== DySiSimTests includes: ${DYSYSIMTESTS_INCLUDES}")
message("==== DySySImTests sources : ${DYSYSIMTESTS_SOURCES}")

add_executable(DySySimTests ${DYSYSIMTESTS_SOURCES} ${DYSYSIMTESTS_INCLUDES})

target_include_directories(DySySimTests PUBLIC ../libDySySim)
target_link_libraries(DySySimTests DySySim)
target_link_libraries(DySySimTests UnitTest++)
