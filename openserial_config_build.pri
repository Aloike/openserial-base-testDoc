###############################################################################
#   @file   openserial_config_build.pri
#   @brief  Contains build configuration for openserial
#           (build directories, destination directory,...)
#   @author GOM
###############################################################################


###############################################################################
# Definition of destination directories

#DESTDIR = $$PWD/Run
#DESTDIR_MAIN    = $$PWD/out                 # destdir for the main application
#DESTDIR_PLUGINS = $$DESTDIR_MAIN/plugins    # destdir for plugins

#TARGET_MAINAPP_NAME = sercomm


# ##############################################################################
##  Destination directories configuration
# ##############################################################################

##  @brief  The DESTDIR variable defines where the generated target will be made
##          available.
DESTDIR = out


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
