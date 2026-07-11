add_executable(Tipping
    main.cpp
    TippingFIS.cpp
)

target_link_libraries(Tipping PRIVATE FuzzyEngine)
