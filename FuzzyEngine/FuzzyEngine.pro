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
   FuzzyEngine.cpp

HEADERS += \
   FuzzyEngine.h

#unix {
#    target.path = /usr/lib
#    INSTALLS += target
#}
