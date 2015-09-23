TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

include(deployment.pri)
qtcAddDeployment()

INCLUDEPATH += ../../Fuzzy
DEPENDPATH += ../../Fuzzy

SOURCES += \
    main.cpp
#HEADERS += \
#    OutputFuzzySet.h

LIBS += -lunittest++

CONFIG(debug, debug|release) {
#LIBS += ../FuzzyDebug/*.o
  LIBS += ../FuzzyDebug/FuzzySet.o
  LIBS += ../FuzzyDebug/InputFuzzySet.o
  LIBS += ../FuzzyDebug/OutputFuzzySet.o
  LIBS += ../FuzzyDebug/InputFuzzySetTrapezoidal.o
  LIBS += ../FuzzyDebug/InputFuzzySetTriangular.o
  LIBS += ../FuzzyDebug/OutputFuzzySetTrapezoidal.o
  LIBS += ../FuzzyDebug/OutputFuzzySetTriangular.o
}
CONFIG(release, debug|release) {
  LIBS += ../FuzzyRelease/OutputFuzzySetTraiangular.o
}
