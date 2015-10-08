TEMPLATE = app
CONFIG += console
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += ../../FuzzyEngine
DEPENDPATH += ../../FuzzyEngine

SOURCES += main.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    RCcircuit.h \
    AppInfo.h

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
