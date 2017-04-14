#-------------------------------------------------
#
# Project created by QtCreator 2016-11-04T11:34:13
#
#-------------------------------------------------


# ##############################################################################
##  Global definitions about this project
# ##############################################################################
TARGET = openserial
TEMPLATE = app



# ##############################################################################
## Declaration of Qt modules used in the project
# ##############################################################################
QT  +=  core
QT  +=  gui
QT  +=  serialport
#QT  +=  xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets



# ##############################################################################
## Include build configuration
# ##############################################################################
include( $$PWD/openserial_config_build.pri )

include( $$PWD/src/version_git.pri )



# ##############################################################################
## Source files
# ##############################################################################
INCLUDEPATH += $$PWD/src/

SOURCES +=\
    src/main.cpp \
    src/core/comm/interface/CInterfaceSerial.cpp \
    src/core/comm/interface/CInterfaceSerialSingleton.cpp \
    src/ui/CMainWindow.cpp \
    src/ui/common/CComboBox.cpp \
    src/ui/CMainWindowStatusBar.cpp \
    src/ui/common/CLed.cpp \
    src/ui/toolbars/CToolBarSerialPortConfig.cpp \
    src/ui/toolbars/CToolBarSerialPortStatus.cpp \
    src/ui/toolbars/CToolbarAbstract.cpp \
    src/ui/console/CConsole.cpp \
    src/ui/configuration/CDialogConfig.cpp \
    src/ui/configuration/CGroupBoxConfigConsole.cpp



HEADERS  += \
    src/core/comm/interface/CInterfaceSerial.h \
    src/core/comm/interface/CInterfaceSerialSingleton.h \
    src/ui/CMainWindow.h \
    src/ui/common/CComboBox.h \
    src/ui/CMainWindowStatusBar.h \
    src/ui/common/CLed.h \
    src/ui/toolbars/CToolBarSerialPortConfig.h \
    src/ui/toolbars/CToolBarSerialPortStatus.h \
    src/ui/toolbars/CToolbarAbstract.h \
    src/ui/console/CConsole.h \
    src/ui/configuration/CDialogConfig.h \
    src/ui/configuration/CGroupBoxConfigConsole.h



RESOURCES += \
    rsrc/resources.qrc
