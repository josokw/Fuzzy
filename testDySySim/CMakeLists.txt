find_library(UNITTESTPP_LIB UnitTest++)
find_path(UNITTESTPP_INC UnitTest++/UnitTest++.h)

add_executable(testDySySim main.cpp)

target_link_libraries(testDySySim PRIVATE DySySim ${UNITTESTPP_LIB})
target_include_directories(testDySySim PRIVATE ${UNITTESTPP_INC})

add_test(NAME testDySySim COMMAND testDySySim)
