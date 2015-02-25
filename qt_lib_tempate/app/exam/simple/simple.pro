QT += core
QT -= gui

include(../../../foobar.pri)

TARGET = simple
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
DESTDIR = $${PWD}/../../../bin

SOURCES += main.cpp
