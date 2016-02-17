TEMPLATE = app
CONFIG += console
CONFIG += c++11
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
        LIBS += -L$$OUT_PWD/../../FuzzyDebug/FuzzyEngine -lFuzzyEngineDebug
        PRE_TARGETDEPS += $$OUT_PWD/../../FuzzyDebug/FuzzyEngine/libFuzzyEngineDebug.a
        LIBS += -L$$OUT_PWD/../../FuzzyDebug/DySySim -lDySySimDebug
        PRE_TARGETDEPS += $$OUT_PWD/../../FuzzyDebug/DySySim/libDySySimDebug.a
    }
    CONFIG(release, debug|release) {
        LIBS += -L$$OUT_PWD/../../FuzzyRelease/FuzzyEngine -lFuzzyEngine
        PRE_TARGETDEPS += $$OUT_PWD/../../FuzzyRelease/FuzzyEngine/libFuzzyEngine.a
        LIBS += -L$$OUT_PWD/../../FuzzyRelease/DySySim -lDySySim
        PRE_TARGETDEPS += $$OUT_PWD/../../FuzzyRelease/DySySim/libDySySim.a
    }
}
