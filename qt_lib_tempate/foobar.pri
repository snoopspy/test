#------------------------------------------------------------------------------
# debug and release
#------------------------------------------------------------------------------
CONFIG(debug, debug|release)   DEFINES += _DEBUG
CONFIG(release, debug|release) DEFINES += _RELEASE NDEBUG

#------------------------------------------------------------------------------
# library name
#------------------------------------------------------------------------------
FOOBAR_NAME = foobar
android-g++:                 FOOBAR_NAME = $${FOOBAR_NAME}_android
contains(QT, gui)            FOOBAR_NAME = $${FOOBAR_NAME}_gui
CONFIG(GTEST)                FOOBAR_NAME = $${FOOBAR_NAME}_test
CONFIG(debug, debug|release) FOOBAR_NAME = $${FOOBAR_NAME}_d
message($${FOOBAR_NAME})

#------------------------------------------------------------------------------
# foobar
#------------------------------------------------------------------------------
FOOBAR_PATH  = $${PWD}
INCLUDEPATH += $${FOOBAR_PATH}/src
!CONFIG(FOOBAR_BUILD) {
  PRE_TARGETDEPS +=  $${FOOBAR_PATH}/lib/lib$${FOOBAR_NAME}.a
  LIBS           += -L$${FOOBAR_PATH}/lib -l$${FOOBAR_NAME}
}
