add_executable(dss
    Builder.cpp
    main.cpp
    Parser.cpp
)

target_link_libraries(dss PRIVATE DySySim)
