#-------------------------------------------------
#
# Project created by QtCreator 2014-12-18T00:26:31
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = sizeof_test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    ../common/vperson.cpp \
    ../common/vip.cpp \
	../common/vmetatype.cpp \
	../common/vvariant.cpp

HEADERS += \
    ../common/vperson.h \
    ../common/vip.h \
	../common/vmetatype.h \
	../common/vvariant.h
