find_library(UNITTESTPP_LIB UnitTest++)
find_path(UNITTESTPP_INC UnitTest++/UnitTest++.h)

add_executable(testFuzzyEngine main.cpp)

target_link_libraries(testFuzzyEngine PRIVATE FuzzyEngine ${UNITTESTPP_LIB})
target_include_directories(testFuzzyEngine PRIVATE ${UNITTESTPP_INC})

add_test(NAME testFuzzyEngine COMMAND testFuzzyEngine)
