###############################################################################
#   @file   openserial_config_build.pri
#   @brief  Contains build configuration for openserial
#           (build directories, destination directory,...)
#   @author GOM
###############################################################################


# ##############################################################################
##  Global definitions about this project
# ##############################################################################
TARGET  = openserial
TEMPLATE = app

CONFIG  += c++11



# ##############################################################################
## Declaration of Qt modules used in the project
# ##############################################################################
QT  +=  core
QT  +=  gui
QT  +=  serialport
#QT  +=  xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets



# ##############################################################################
##  Destination directories configuration
# ##############################################################################

##  @brief  The DESTDIR variable defines where the generated target will be made
##          available.
DESTDIR = $$PWD/out


##  This section defines the prefix of build directories depending on the build
##  mode. It also adds a suffix to the target in debug mode.
CONFIG(release, debug|release) {
    BUILDDIR    = build/release
}else{
    BUILDDIR    = build/debug
    TARGET = $$join(TARGET,,,_d)
}


##  This section defines the build subdirs to group generated objects of the
##  same type in the same directory instead of putting all generated objects in
##  a common directory.
MOC_DIR     = $$BUILDDIR/moc
OBJECTS_DIR = $$BUILDDIR/obj
RCC_DIR     = $$BUILDDIR/rcc
UI_DIR      = $$BUILDDIR/ui
