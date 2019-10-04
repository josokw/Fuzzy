TEMPLATE = app
CONFIG += console
CONFIG += c++17
CONFIG -= app_bundle
CONFIG -= qt

include(deployment.pri)
qtcAddDeployment()

INCLUDEPATH += $$PWD/../FuzzyEngine
INCLUDEPATH += $$PWD/../DySySim
DEPENDPATH += $$PWD/../FuzzyEngine
DEPENDPATH += $$PWD/../DySySim

SOURCES += \
main.cpp \
    FuzzyController.cpp

HEADERS += \
    AppInfo.h \
    FuzzyController.h

unix {
    CONFIG(debug, debug|release) {
        LIBS += -L/home/jos/Projects/Github/build-Fuzzy-Desktop_Qt_5_9_2_GCC_64bit-Debug/FuzzyEngine -lFuzzyEngineDebug
        #LIBS += -L$$OUT_PWD/FuzzyEngine -lFuzzyEngineDebug
        #PRE_TARGETDEPS += $$OUT_PWD/../../FuzzyDebug/FuzzyEngine/libFuzzyEngineDebug.a
        #PRE_TARGETDEPS += -L/home/jos/Projects/Github/build-Fuzzy-Desktop_Qt_5_9_2_GCC_64bit-Debug/FuzzyEngine/libFuzzyEngineDebug.a
        LIBS += -L/home/jos/Projects/Github/build-Fuzzy-Desktop_Qt_5_9_2_GCC_64bit-Debug/DySySim -lDySySimDebug
        #LIBS += -L$$OUT_PWD/DySySim -lDySySimDebug
        #PRE_TARGETDEPS += $$OUT_PWD/../../FuzzyDebug/DySySim/libDySySimDebug.a
    }
    CONFIG(release, debug|release) {
       #LIBS += -L$$OUT_PWD/../../FuzzyRelease/FuzzyEngine -lFuzzyEngine
       #PRE_TARGETDEPS += $$OUT_PWD/../../FuzzyRelease/FuzzyEngine/libFuzzyEngine.a
       #LIBS += -L$$OUT_PWD/../../FuzzyRelease/DySySim -lDySySim
       #PRE_TARGETDEPS += $$OUT_PWD/../../FuzzyRelease/DySySim/libDySySim.a
    }
}
