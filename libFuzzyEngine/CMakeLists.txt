add_library(FuzzyEngine STATIC
    FuzzyEngine.cpp
    FuzzyLogic.cpp
    FuzzySet.cpp
    InputFuzzySet.cpp
    InputFuzzySetTrapezoidal.cpp
    InputFuzzySetTriangular.cpp
    OutputFuzzySet.cpp
    OutputFuzzySetSingleton.cpp
    OutputFuzzySetTrapezoidal.cpp
    OutputFuzzySetTriangular.cpp
)

target_include_directories(FuzzyEngine PUBLIC ${PROJECT_SOURCE_DIR}/libFuzzyEngine)
