QT += core
QT -= gui

include(../../../foobar.pro)

TARGET = simple_build
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
DESTDIR = $${PWD}/../../../bin

SOURCES += main.cpp
