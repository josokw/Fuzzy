TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += C++11

INCLUDEPATH += ../../FuzzyEngine
DEPENDPATH += ../../FuzzyEngine

SOURCES += \
   main.cpp

HEADERS += \
   AppInfo.h

include(deployment.pri)
qtcAddDeployment()

unix {
    CONFIG(debug, debug|release) {
        LIBS += -L../../FuzzyDebug/FuzzyEngine -lFuzzyEngineDebug
        #PRE_TARGETDEPS += ../../FuzzyDebug/FuzzyEngine/libFuzzyEngineDebug.a
    }
    CONFIG(release, debug|release) {
        LIBS += -L../../FuzzyRelease/FuzzyEngine -lFuzzyEngine
        #PRE_TARGETDEPS += ../../FuzzyRelease/FuzzyEngine/libFuzzyEngine.a
    }
}
