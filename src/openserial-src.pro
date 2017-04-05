# ##############################################################################
##  @project    openserial  https://github.com/OpenserialProject
##
##  @file   openserial-src.pro
##  @brief  Qt Project file containing declarations of all files needed by the
##          main OpenSerial software.
##
##  @author GOM
##  @date   2017-04-05  Wed.
# ##############################################################################


# ##############################################################################
## Include build configuration
# ##############################################################################
include( $$PWD/../openserial_config_build.pri )

include( $$PWD/version_git.pri )



DEFINES +=  TRACE_CPluginContainer_DEBUG
DEFINES +=  TRACE_CPluginsSearchPathsManager_DEBUG



# ##############################################################################
## Git Subtrees includes
# ##############################################################################
# Plugins interface
HEADERS     += core/plugins/interface/COpenserialPluginInterface.h
INCLUDEPATH += core/plugins/interface/



# ##############################################################################
## Source files
# ##############################################################################
INCLUDEPATH += $$PWD/


HEADERS += core/comm/interface/CInterfaceSerial.h
HEADERS += core/comm/interface/CInterfaceSerialSingleton.h
HEADERS += core/plugins/management/CPluginContainer.h
HEADERS += core/plugins/management/CPluginsManagerSingleton.h
HEADERS += core/plugins/management/CPluginsSearchPathsManager.h
HEADERS += core/trace/trace.h
HEADERS += ui/CMainWindow.h
HEADERS += ui/CMainWindowStatusBar.h
HEADERS += ui/common/CComboBox.h
HEADERS += ui/common/CLed.h
HEADERS += ui/configuration/CDialogConfig.h
HEADERS += ui/configuration/CGroupBoxConfigConsole.h
HEADERS += ui/console/CConsole.h
HEADERS += ui/menuPlugins/CMenuPlugins.h
HEADERS += ui/toolbars/CToolbarAbstract.h
HEADERS += ui/toolbars/CToolBarSerialPortConfig.h
HEADERS += ui/toolbars/CToolBarSerialPortStatus.h


RESOURCES   += ../rsrc/resources.qrc


SOURCES += core/comm/interface/CInterfaceSerial.cpp
SOURCES += core/comm/interface/CInterfaceSerialSingleton.cpp
SOURCES += core/plugins/management/CPluginContainer.cpp
SOURCES += core/plugins/management/CPluginsManagerSingleton.cpp
SOURCES += core/plugins/management/CPluginsSearchPathsManager.cpp
SOURCES += main.cpp
SOURCES += ui/CMainWindow.cpp
SOURCES += ui/CMainWindowStatusBar.cpp
SOURCES += ui/common/CComboBox.cpp
SOURCES += ui/common/CLed.cpp
SOURCES += ui/configuration/CDialogConfig.cpp
SOURCES += ui/configuration/CGroupBoxConfigConsole.cpp
SOURCES += ui/console/CConsole.cpp
SOURCES += ui/menuPlugins/CMenuPlugins.cpp
SOURCES += ui/toolbars/CToolbarAbstract.cpp
SOURCES += ui/toolbars/CToolBarSerialPortConfig.cpp
SOURCES += ui/toolbars/CToolBarSerialPortStatus.cpp
