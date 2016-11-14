#include <QApplication>

#include "Version.h"
#include "ui/CMainWindow.h"

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

    CMainWindow w;
    w.show();

    return a.exec();
}

/* ########################################################################## */
/* ########################################################################## */
