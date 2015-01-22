#-------------------------------------------------
#
# Project created by QtCreator 2014-12-23T10:06:48
#
#-------------------------------------------------

QT += core
QT += gui widgets
#QT -= gui

include(../../../vdream/vdream91/lib/vdream.pri)
include(../../../google/gtest/gtest.pri)

TARGET = serialize_test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

#QMAKE_CXXFLAGS += -Wc++0x-compat

SOURCES += main.cpp \
    vip.cpp \
    vserializable.cpp \
    vrep.cpp \
    vtcpclient.cpp \
    vobject.cpp \
    vlog.cpp \
    vcommon.cpp \
    vstate.cpp \
    vmetadump.cpp \
    other.cpp \
    vmac.cpp \
    vwidget.cpp \
    vserializer.cpp

HEADERS += \
    vip.h \
    vserializable.h \
    vrep.h \
    vtcpclient.h \
    vobject.h \
    vlog.h \
    vcommon.h \
    vstate.h \
    vmetadump.h \
    other.h \
    vmac.h \
    vwidget.h \
    vserializer.h

OTHER_FILES += \
    to_do_list.txt
