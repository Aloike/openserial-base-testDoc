###############################################################################
#   @file version_git.pri
#   @date   2013-06-18  Tue.
#
#   @brief  To generate a header containing the version of a software using git
#
#   This file, when included to a project .pro file, will generate a header
#   containing different variables such as the GIT description, the build date,
#   etc.
#   To use it, just do a include(version_git.pri) in your .pro file.
#   When at least one build has been done, a file named Version.h (by default)
#   will appear, containing the generated constants.
#
###############################################################################

contains( CONFIG, VERSION_GIT_PRI_INCLUDED ) {
#     message( "version_git.pri already included" )
} else {

###############################################################################
###############################################################################
#   Variables that you may have to edit depending on your project / platform
###############################################################################

VER_MAJ = 0
VER_MIN = 0
VER_PAT = 0
VERSION =$${VER_MAJ}.$${VER_MIN}.$${VER_PAT}

# SVN_REVISION holds what the command "svnversion -n ." return. May depend on
# your system configuration

#SVN_REVISION = $$system("svnversion -n .") # Directly in the command line

# VERSION_OUTPUT_FILE points to the destination file where the constants will
#be written

VERSION_OUTPUT_FILE=$$PWD/Version.h

###############################################################################
###############################################################################


unix {

target_gitrev.target    =   target_gitrev

# To erase the old version file
target_gitrev.commands  =   echo \'/* Auto-generated file ! */\n\' > $$VERSION_OUTPUT_FILE

target_gitrev.commands  +=  $$escape_expand(\\n\\t) #to go to next makefile line
target_gitrev.commands  +=  (echo \"\\043ifndef VERSION_H\" >> $$VERSION_OUTPUT_FILE)
target_gitrev.commands  +=  $$escape_expand(\\n\\t) #to go to next makefile line
target_gitrev.commands  +=  (echo \"\\043define VERSION_H\\n\" >> $$VERSION_OUTPUT_FILE)

# The major version number
target_gitrev.commands  +=  $$escape_expand(\\n\\t) #to go to next makefile line
target_gitrev.commands  +=  echo \'const QString VERSION_MAJOR\(\"$$VER_MAJ\"\);\' >> $$VERSION_OUTPUT_FILE

# The minor version number
target_gitrev.commands  +=  $$escape_expand(\\n\\t) #to go to next makefile line
target_gitrev.commands  +=  echo \'const QString VERSION_MINOR\(\"$$VER_MIN\"\);\' >> $$VERSION_OUTPUT_FILE

# The patch version number
target_gitrev.commands  +=  $$escape_expand(\\n\\t) #to go to next makefile line
target_gitrev.commands  +=  echo \'const QString VERSION_PATCH\(\"$$VER_PAT\"\);\' >> $$VERSION_OUTPUT_FILE

# The GIT version
target_gitrev.commands  +=  $$escape_expand(\\n\\t) #to go to next makefile line
target_gitrev.commands  +=  echo \"const QString VERSION_CVS\(\\\"$\(shell  git describe --long --tags --always --dirty)\\\"\);\" >> $$VERSION_OUTPUT_FILE

# The Build date
target_gitrev.commands  +=  $$escape_expand(\\n\\t) #to go to next makefile line
target_gitrev.commands  +=  echo \"const QString VERSION_BUILD\(\\\"$\(shell  date +%Y%m%d%H%M%S)\\\"\);\" >> $$VERSION_OUTPUT_FILE


target_gitrev.commands  +=  $$escape_expand(\\n\\t) #to go to next makefile line
target_gitrev.commands  +=  (echo \"\\n\\043endif /*< VERSION_H */\" >> $$VERSION_OUTPUT_FILE)


#&& echo '#ifndef __VERSION_H__' >> Version.h    \
#&& echo '#define __VERSION_H__' >> Version.h    \
#&& echo '#endif'    >> Version.h


# Add the created target to the qmake ones.
QMAKE_EXTRA_TARGETS += target_gitrev
PRE_TARGETDEPS      += target_gitrev

}else:win32{
message( "Processing version_git.pri for win32" );

BIN_CMD=cmd.exe

contains( CONFIG, APPVEYOR ) {
    message( "Using AppVeyor specific configuration." );
    BIN_GIT=git
    C_STR_SEP=\"
    C_STR_SEP2=\'
    CMD_ECHO='echo '
    CMD_TIMESTAMP=$\(shell date +%Y%m%d%H%M%S\)
} else {
    BIN_GIT="C:\Program Files\Git\bin\git.exe"
    C_WIN_ESCAPECHAR=^
    CMD_ECHO=echo.
    CMD_TIMESTAMP=$(shell echo %date:~6,4%%date:~3,2%%date:~0,2%)$(shell cmd /v:on /c \"set lTime=%time: =0% && echo !lTime:~0,2!!lTime:~3,2!!lTime:~6,2!\")
}

target_gitrev.target    =   target_gitrev

# To erase the old version file
target_gitrev.commands  =   ($${CMD_ECHO}$${C_STR_SEP}/* Auto-generated file ! */$${C_STR_SEP}>$$VERSION_OUTPUT_FILE )
target_gitrev.commands  +=  $$escape_expand(\\n\\t) #to go to next makefile line
target_gitrev.commands  +=  ($${CMD_ECHO}$${C_STR_SEP}$${LITERAL_HASH}ifndef VERSION_H$${C_STR_SEP}>> $$VERSION_OUTPUT_FILE )
target_gitrev.commands  +=  $$escape_expand(\\n\\t) #to go to next makefile line
target_gitrev.commands  +=  ($${CMD_ECHO}$${C_STR_SEP}$${LITERAL_HASH}define VERSION_H$${C_STR_SEP}>> $$VERSION_OUTPUT_FILE )
target_gitrev.commands  +=  $$escape_expand(\\n\\t) #to go to next makefile line
target_gitrev.commands  +=  ($${CMD_ECHO}$${C_STR_SEP}$${C_STR_SEP}>>$$VERSION_OUTPUT_FILE)
target_gitrev.commands  +=  $$escape_expand(\\n\\t) #to go to next makefile line
target_gitrev.commands  +=  ($${CMD_ECHO}$${C_STR_SEP}$${LITERAL_HASH}include $${C_WIN_ESCAPECHAR}<QString$${C_WIN_ESCAPECHAR}>$${C_STR_SEP} >> $$VERSION_OUTPUT_FILE)
target_gitrev.commands  +=  $$escape_expand(\\n\\t) #to go to next makefile line
target_gitrev.commands  +=  ($${CMD_ECHO}$${C_STR_SEP}$${C_STR_SEP}>>$$VERSION_OUTPUT_FILE)

# The major version number
target_gitrev.commands  +=  $$escape_expand(\\n\\t) #to go to next makefile line
target_gitrev.commands  +=  ($${CMD_ECHO}$${C_STR_SEP}const QString VERSION_MAJOR = $${C_STR_SEP}$${C_STR_SEP2}\"$${C_STR_SEP2}$${C_STR_SEP}$$VER_MAJ$${C_STR_SEP}$${C_STR_SEP2}\"$${C_STR_SEP2}$${C_STR_SEP};$${C_STR_SEP}>>$$VERSION_OUTPUT_FILE)

## The minor version number
target_gitrev.commands  +=  $$escape_expand(\\n\\t) #to go to next makefile line
target_gitrev.commands  +=  ($${CMD_ECHO}$${C_STR_SEP}const QString VERSION_MINOR = $${C_STR_SEP}$${C_STR_SEP2}\"$${C_STR_SEP2}$${C_STR_SEP}$$VER_MIN$${C_STR_SEP}$${C_STR_SEP2}\"$${C_STR_SEP2}$${C_STR_SEP};$${C_STR_SEP}>>$$VERSION_OUTPUT_FILE)

## The patch version number
target_gitrev.commands  +=  $$escape_expand(\\n\\t) #to go to next makefile line
target_gitrev.commands  +=  ($${CMD_ECHO}$${C_STR_SEP}const QString VERSION_PATCH = $${C_STR_SEP}$${C_STR_SEP2}\"$${C_STR_SEP2}$${C_STR_SEP}$$VER_PAT$${C_STR_SEP}$${C_STR_SEP2}\"$${C_STR_SEP2}$${C_STR_SEP};$${C_STR_SEP}>>$$VERSION_OUTPUT_FILE)

## The GIT version
target_gitrev.commands  +=  $$escape_expand(\\n\\t) #to go to next makefile line
target_gitrev.commands  +=  ($${CMD_ECHO}$${C_STR_SEP}const QString VERSION_CVS = $${C_STR_SEP}$${C_STR_SEP2}\"$${C_STR_SEP2}$${C_STR_SEP}$(shell $${BIN_GIT} --git-dir $$PWD/../.git --work-tree $$PWD../ describe --long --tags --always --dirty)$${C_STR_SEP}$${C_STR_SEP2}\"$${C_STR_SEP2}$${C_STR_SEP};$${C_STR_SEP}>>$$VERSION_OUTPUT_FILE)

## The Build date
#target_gitrev.commands  +=  $$escape_expand(\\n\\t) #to go to next makefile line
#target_gitrev.commands  +=  export BUILD_DATE=`echo.exe %date:~6,4%%date:~3,2%%date:~0,2%`
#target_gitrev.commands  +=  $$escape_expand(\\n\\t) #to go to next makefile line
#target_gitrev.commands  +=  export BUILD_TIME=`cmd.exe /v:on /c \"set lTime=%time: =0% && echo !lTime:~0,2!!lTime:~3,2!!lTime:~6,2!\"`
target_gitrev.commands  +=  $$escape_expand(\\n\\t) #to go to next makefile line
target_gitrev.commands  +=  ($${CMD_ECHO}$${C_STR_SEP}const QString VERSION_BUILD = $${C_STR_SEP}$${C_STR_SEP2}\"$${C_STR_SEP2}$${C_STR_SEP}$${CMD_TIMESTAMP}$${C_STR_SEP}$${C_STR_SEP2}\"$${C_STR_SEP2}$${C_STR_SEP};$${C_STR_SEP}>>$$VERSION_OUTPUT_FILE)


target_gitrev.commands  +=  $$escape_expand(\\n\\t) #to go to next makefile line
target_gitrev.commands  +=  ($${CMD_ECHO}$${C_STR_SEP}$${C_STR_SEP}>>$$VERSION_OUTPUT_FILE)
target_gitrev.commands  +=  $$escape_expand(\\n\\t) #to go to next makefile line
target_gitrev.commands  +=  ($${CMD_ECHO}$${C_STR_SEP}$${LITERAL_HASH}endif /*^< VERSION_H */$${C_STR_SEP}>> $$VERSION_OUTPUT_FILE )


# Add the created target to the qmake ones.
QMAKE_EXTRA_TARGETS += target_gitrev
PRE_TARGETDEPS      += target_gitrev
}


}   #<  VERSION_GIT_PRI_INCLUDED
