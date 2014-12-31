#-------------------------------------------------
#
# Project created by QtCreator 2014-12-23T10:06:48
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = serialize_test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    vip.cpp \
    vserializable.cpp \
    vvar.cpp \
    vrep.cpp \
    vtcpclient.cpp \
    vobject.cpp \
    vlog.cpp

HEADERS += \
    vip.h \
    vserializable.h \
    vvar.h \
    vrep.h \
    vtcpclient.h \
    vobject.h \
    vlog.h

OTHER_FILES += \
    to_do_list.txt
