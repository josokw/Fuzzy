cmake_minimum_required(VERSION 3.12)

set(PROJECT_NAME Fuzzy)
project(${PROJECT_NAME})
message("==== Projectname: ${PROJECT_NAME}")
message("==== Project dir: ${PROJECT_SOURCE_DIR}")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -g")

# set(CMAKE_VERBOSE_MAKEFILE ON)

add_subdirectory(libFuzzyEngine)
add_subdirectory(libDySySim)
add_subdirectory(appDySySim)
add_subdirectory(appTipping)
add_subdirectory(appControllerFOProcess)
add_subdirectory(appRC-OnOff)
add_subdirectory(testDySySim)
add_subdirectory(testFuzzyEngine)
