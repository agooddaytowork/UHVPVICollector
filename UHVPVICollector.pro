QT += core sql network serialport serialbus
QT -= gui

CONFIG += c++11

TARGET = UHVPVICollectorExec
CONFIG += -std=c++11 console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    anLogger/src/anlogger.cpp \
    BinaryProtocol/src/binaryprotocol.cpp \
    CanProtocol/src/canprotocol.cpp \
    WindowProtocol/src/windowprotocol.cpp \
    shared/commonthings.cpp \
    src/directtransitionforuhvpvicollectorstate.cpp \
    src/emitreadi.cpp \
    src/emitreadp.cpp \
    src/emitreadv.cpp \
    src/idleuhvpvicollector.cpp \
    src/uhvpvicollector.cpp \
    src/uhvpvicollectordb.cpp \
    src/wait4i.cpp \
    src/wait4p.cpp \
    src/wait4v.cpp \
    piLocalDBWorker/src/pilocaldbworkervarset.cpp \
    SerialPortWorker/src/serialportworkerproperty.cpp

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
    anLogger/src/anlogger.h \
    BinaryProtocol/src/binaryprotocol.h \
    CanProtocol/src/canprotocol.h \
    WindowProtocol/src/windowprotocol.h \
    shared/commonthings.h \
    src/directtransitionforuhvpvicollectorstate.h \
    src/emitreadi.h \
    src/emitreadp.h \
    src/emitreadv.h \
    src/idleuhvpvicollector.h \
    src/uhvpvicollector.h \
    src/uhvpvicollectordb.h \
    src/wait4i.h \
    src/wait4p.h \
    src/wait4v.h \
    piLocalDBWorker/src/pilocaldbworkervarset.h \
    SerialPortWorker/src/serialportworkerproperty.h
