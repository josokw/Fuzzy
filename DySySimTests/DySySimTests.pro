TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp

INCLUDEPATH += $$PWD/../DySySim
DEPENDPATH += $$PWD/../DySySim

LIBS += \
    -lunittest++

unix {
    CONFIG(debug, debug|release) {
        LIBS += -L$$OUT_PWD/../../FuzzyDebug/DySySim -lDySySimDebug
        PRE_TARGETDEPS += $$OUT_PWD/../../FuzzyDebug/DySySim/libDySySimDebug.a
    }
    CONFIG(release, debug|release) {
        LIBS += -L$$OUT_PWD/../../FuzzyRelease/DySySim -lDySySim
        PRE_TARGETDEPS += $$OUT_PWD/../../FuzzyRelease/DySySim/libDySySim.a
    }
}
