# FuzzyEngine 2015-09-21

QT -= core gui
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++11

CONFIG(debug, debug|release) {
    TARGET = FuzzyEngineDebug
}
CONFIG(release, debug|release) {
    TARGET = FuzzyEngine
    DEFINES += NDEBUG
}

SOURCES += \
   FuzzyEngine.cpp \
   FuzzySet.cpp \
   InputFuzzySet.cpp \
   InputFuzzySetTrapezoidal.cpp \
   InputFuzzySetTriangular.cpp \
   OutputFuzzySet.cpp \
   OutputFuzzySetTrapezoidal.cpp \
   OutputFuzzySetTriangular.cpp

HEADERS += \
   FuzzyEngine.h \
   Defuzzification.h \
   FuzzyLogic.h \
   FuzzySet.h \
   InputFuzzySet.h \
   InputFuzzySetTrapezoidal.h \
   InputFuzzySetTriangular.h \
   OutputFuzzySet.h \
   OutputFuzzySetTrapezoidal.h \
   OutputFuzzySetTriangular.h

#unix {
#    target.path = /usr/lib
#    INSTALLS += target
#}
