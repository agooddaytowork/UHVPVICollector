QT += core sql network serialport
QT -= gui

CONFIG += c++11

TARGET = UHVPVICollectorExec
CONFIG += -std=c++11 console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    anLogger/src/anlogger.cpp \
    shared/abstractstatemachinebasis.cpp \
    shared/commonthings.cpp \
    shared/directtransition.cpp \
    BinaryProtocol/src/binaryprotocol.cpp \
    WindowProtocol/src/windowprotocol.cpp \
    SerialPortWorker/src/serialportworkerbasis.cpp \
    piLocalDBWorker/src/pilocaldbworkerbasis.cpp \
    src/emitreadi.cpp \
    src/emitreadp.cpp \
    src/emitreadv.cpp \
    src/idleuhvpvicollector.cpp \
    src/uhvpvicollector.cpp \
    src/uhvpvicollectordb.cpp \
    src/wait4i.cpp \
    src/wait4p.cpp \
    src/wait4v.cpp

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
    shared/abstractstatemachinebasis.h \
    shared/commonthings.h \
    shared/directtransition.h \
    BinaryProtocol/src/binaryprotocol.h \
    WindowProtocol/src/windowprotocol.h \
    SerialPortWorker/src/serialportworkerbasis.h \
    piLocalDBWorker/src/pilocaldbworkerbasis.h \
    src/emitreadi.h \
    src/emitreadp.h \
    src/emitreadv.h \
    src/idleuhvpvicollector.h \
    src/uhvpvicollector.h \
    src/uhvpvicollectordb.h \
    src/wait4i.h \
    src/wait4p.h \
    src/wait4v.h
