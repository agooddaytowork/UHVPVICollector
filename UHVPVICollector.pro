QT += core sql network serialport serialbus
QT -= gui

CONFIG += c++11

TARGET = UHVPVICollectorExec
CONFIG += -std=c++11 console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    binaryprotocol.cpp \
    windowprotocol.cpp \
    UHVPVICollector/emitreadi.cpp \
    UHVPVICollector/emitreadp.cpp \
    UHVPVICollector/emitreadv.cpp \
    UHVPVICollector/idle.cpp \
    UHVPVICollector/uhvpvicollector.cpp \
    UHVPVICollector/uhvpvicollectordb.cpp \
    UHVPVICollector/wait4i.cpp \
    UHVPVICollector/wait4p.cpp \
    UHVPVICollector/wait4v.cpp \
    SerialPortWorker/serialportworkerproperty.cpp \
    piLocalDBWorker/pilocaldbworkervarset.cpp \
    canprotocol.cpp \
    UHVPVICollector/directtransitionforuhvpvicollectorstate.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    anlogger.h \
    binaryprotocol.h \
    commonthings.h \
    windowprotocol.h \
    UHVPVICollector/emitreadi.h \
    UHVPVICollector/emitreadp.h \
    UHVPVICollector/emitreadv.h \
    UHVPVICollector/idle.h \
    UHVPVICollector/uhvpvicollector.h \
    UHVPVICollector/uhvpvicollectordb.h \
    UHVPVICollector/wait4i.h \
    UHVPVICollector/wait4p.h \
    UHVPVICollector/wait4v.h \
    SerialPortWorker/serialportworkerproperty.h \
    piLocalDBWorker/pilocaldbworkervarset.h \
    canprotocol.h \
    UHVPVICollector/directtransitionforuhvpvicollectorstate.h
