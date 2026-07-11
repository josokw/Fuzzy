add_library(DySySim STATIC
    Connecting.cpp
    DySySimControl.cpp
    DySySim.cpp
    DySySimHC.cpp
    DySySimLogic.cpp
    DySySimMath.cpp
    ErrorCodes.cpp
    Model.cpp
    SimBlock.cpp
    SimBlockFactory.cpp
    SimBlockHC.cpp
    SimModel.cpp
    SimModelTime.cpp
)

target_include_directories(DySySim PUBLIC ${PROJECT_SOURCE_DIR}/libDySySim)
