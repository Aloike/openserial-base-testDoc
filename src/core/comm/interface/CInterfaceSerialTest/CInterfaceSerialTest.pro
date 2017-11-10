# ##############################################################################
##  @project    CInterfaceSerialTest
##  @brief      This is the test project for the CInterfaceSerial class.
##
##  @author GOM
##  @date   2016-11-08
# ##############################################################################



TARGET = CInterfaceSerialManagerSingletonTest
TEMPLATE = app


CONFIG   += console
CONFIG   -= app_bundle

QT  -= gui
QT  += testlib
QT  +=  serialport



# ##############################################################################
## Include build configuration
# ##############################################################################
include( $$PWD/../../../../../openserial_config_build.pri )



# ##############################################################################
## Source files
# ##############################################################################
SOURCES += \
    ../CInterfaceSerial.cpp \
    ../CInterfaceSerialSingleton.cpp \
    src/CInterfaceSerialTest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../CInterfaceSerial.h \
    ../CInterfaceSerialSingleton.h
