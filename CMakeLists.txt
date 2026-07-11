cmake_minimum_required(VERSION 3.12)

project(Fuzzy LANGUAGES CXX)
message(STATUS "==== Project: ${PROJECT_NAME}")
message(STATUS "==== Source dir: ${PROJECT_SOURCE_DIR}")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

add_compile_options(-Wall -Wextra -pedantic -g)

enable_testing()

add_subdirectory(libFuzzyEngine)
add_subdirectory(libDySySim)

add_subdirectory(appDySySim)
add_subdirectory(appTipping)

add_subdirectory(hardcodedDySySim/appControllerFOProcess)
add_subdirectory(hardcodedDySySim/appRC-OnOff)

add_subdirectory(testDySySim)
add_subdirectory(testFuzzyEngine)
