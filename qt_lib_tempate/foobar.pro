CONFIG += FOOBAR_BUILD
include(foobar.pri)

SOURCES += \
	$${PWD}/src/foobar/bar.cpp \
	$${PWD}/src/foobar/foo.cpp

HEADERS += \
	$${PWD}/src/foobar/bar.h \
	$${PWD}/src/foobar/foo.h
