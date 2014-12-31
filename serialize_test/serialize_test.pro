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
    vobject.cpp

HEADERS += \
    vip.h \
    vserializable.h \
    vvar.h \
    vrep.h \
    vtcpclient.h \
    vobject.h

OTHER_FILES += \
    class_list.txt
