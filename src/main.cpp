#include <QApplication>
#include <QDir>
#include <QStandardPaths>

#include "Version.h"
#include "core/plugins/management/CPluginsManagerSingleton.h"
#include "ui/CMainWindow.h"

/* ########################################################################## */
/* ########################################################################## */

static const QString    C_DIRNAME_PLUGINS( "openserial-plugins" );

/* ########################################################################## */
/* ########################################################################## */

void    init_plugins(void)
{
    /* Search plugins in the application's binary directory */
    CPluginsManagerSingleton::getInstance()
            ->addSearchPath( QCoreApplication::applicationDirPath()
                             + QDir::separator() + C_DIRNAME_PLUGINS
                             + QDir::separator() );

    /* Search plugins in the working directory */
    CPluginsManagerSingleton::getInstance()
            ->addSearchPath( QDir::currentPath()
                             + QDir::separator() + C_DIRNAME_PLUGINS
                             + QDir::separator() );

    CPluginsManagerSingleton::getInstance()
            ->addSearchPath( QStandardPaths::standardLocations(
                                 QStandardPaths::DataLocation ).at( 0 )
                             + QDir::separator() + C_DIRNAME_PLUGINS
                             + QDir::separator() );
}

/* ########################################################################## */
/* ########################################################################## */

void    init_qCoreApplication(void)
{
    QString str_version
            = VERSION_MAJOR
            + "." + VERSION_MINOR
            + "." + VERSION_PATCH
            + "_" + VERSION_CVS
            + "_" + VERSION_BUILD;


#ifdef QT_DEBUG
    str_version.append( "-debug" );
#else
    str_version.append( "-release" );
#endif


    QCoreApplication::setOrganizationName( "Aloïké" );
    QCoreApplication::
            setOrganizationDomain( "http://aloike.github.io/openserial/" );
    QCoreApplication::setApplicationName( "OpenSerial" );
    QCoreApplication::setApplicationVersion( str_version );
}

/* ########################################################################## */
/* ########################################################################## */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    init_qCoreApplication();
    init_plugins();


    CMainWindow::getInstance()->show();

    int retVal  = a.exec();

    CMainWindow::freeInstance();


    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */
