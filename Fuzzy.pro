TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp \
    FuzzySet.cpp \
    InputFuzzySet.cpp \
    OutputFuzzySet.cpp \
    InputFuzzySetTriangular.cpp \
    OutputFuzzySetTriangular.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    FuzzySet.h \
    InputFuzzySet.h \
    OutputFuzzySet.h \
    InputFuzzySetTriangular.h \
    OutputFuzzySetTriangular.h \
    FuzzyLogic.h \
    Defuzzification.h

