#-------------------------------------------------
#
# Project created by QtCreator 2016-02-13T07:16:45
#
#-------------------------------------------------

QT -= core gui

TARGET = DySySim
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++17

CONFIG(debug, debug|release) {
    TARGET = DySySimDebug
}
CONFIG(release, debug|release) {
    TARGET = DySySim
    DEFINES += NDEBUG
}

SOURCES += \
    DySySim.cpp \
    SimBlock.cpp \
    Connecting.cpp \
    Model.cpp \
    SimBlockIO.cpp \
    SimBlockI.cpp \
    SimBlockO.cpp
HEADERS += \
    DySySim.h \
    SimBlock.h \
    LibInfoDySySim.h \
    Connecting.h \
    Model.h \
    SimBlockIO.h \
    SimBlockI.h \
    SimBlockO.h

#unix {
#    target.path = /usr/lib
#    INSTALLS += target
#}
