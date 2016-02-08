TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += C++11

INCLUDEPATH += $$PWD/../FuzzyEngine
DEPENDPATH += $$PWD/../FuzzyEngine

SOURCES += \
   main.cpp

HEADERS += \
   AppInfo.h

include(deployment.pri)
qtcAddDeployment()

unix {
    CONFIG(debug, debug|release) {
        LIBS += -L$$OUT_PWD/../../FuzzyDebug/FuzzyEngine -lFuzzyEngineDebug
        PRE_TARGETDEPS += $$OUT_PWD/../../FuzzyDebug/FuzzyEngine/libFuzzyEngineDebug.a
    }
    CONFIG(release, debug|release) {
        LIBS += -L$$OUT_PWD/../../FuzzyRelease/FuzzyEngine -lFuzzyEngine
        PRE_TARGETDEPS += $$OUT_PWD/../../FuzzyRelease/FuzzyEngine/libFuzzyEngine.a
    }
}
