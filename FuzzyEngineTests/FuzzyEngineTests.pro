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
LIBS += ../FuzzyDebug/*.o
#  LIBS += ../FuzzyDebug/OutputFuzzySetTriangular.o
#  LIBS += ../FuzzyDebug/OutputFuzzySet.o
#  LIBS += ../FuzzyDebug/FuzzySet.o
}
CONFIG(release, debug|release) {
  LIBS += ../FuzzyRelease/OutputFuzzySetTraiangular.o
}
