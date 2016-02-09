TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += C++11

include(deployment.pri)
qtcAddDeployment()

INCLUDEPATH += $$PWD/../FuzzyEngine
DEPENDPATH += $$PWD/../FuzzyEngine

SOURCES += \
   main.cpp \
   TippingFIS.cpp

HEADERS += \
   AppInfo.h \
   TippingFIS.h

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
