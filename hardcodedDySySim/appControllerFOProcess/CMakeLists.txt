add_executable(ControllerFOProcess
    FuzzyController.cpp
    main.cpp
)

target_link_libraries(ControllerFOProcess PRIVATE FuzzyEngine DySySim)
