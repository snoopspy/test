QT += core
QT -= gui

CONFIG += FOOBAR_BUILD
include(../foobar.pro)

TARGET   = $${FOOBAR_NAME}
TEMPLATE = lib
CONFIG  += staticlib
DESTDIR  = $${PWD}
