#include "CMainWindow.h"

#include <QCoreApplication>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>

#include "core/comm/interface/CInterfaceSerialSingleton.h"
#include "ui/configuration/CDialogConfig.h"
#include "ui/console/CConsole.h"
#include "ui/toolbars/CToolBarSerialPortConfig.h"
#include "ui/toolbars/CToolBarSerialPortStatus.h"

#include "CMainWindowStatusBar.h"


/* ########################################################################## */
/* ########################################################################## */

CMainWindow*    CMainWindow::s_m_instance   = nullptr;

/* ########################################################################## */
/* ########################################################################## */

CMainWindow::CMainWindow(QWidget *parent)
    :   QMainWindow(parent)
    ,   m_console( new CConsole( this ) )
{
    this->setWindowIcon(QIcon(":/icons/app"));
    this->setWindowIconText(QCoreApplication::applicationName());
    this->setWindowTitle(QCoreApplication::applicationName());

    this->_createUi();

    this->_createConnections();

    this->resize( 800, 600 );
}

/* ########################################################################## */
/* ########################################################################## */

CMainWindow::~CMainWindow()
{
    if( CInterfaceSerialSingleton::instance()->isOpen() )
    {
        CInterfaceSerialSingleton::instance()->close();
    }

    CInterfaceSerialSingleton::freeInstance();

    qDebug( "MainWindow's width : %d", this->width() );
}

/* ########################################################################## */
/* ########################################################################## */

void    CMainWindow::_createConnections(void)
{
    CInterfaceSerialSingleton*  p_interface
                = CInterfaceSerialSingleton::instance();

    connect( p_interface, SIGNAL(errorOccured(QString)),
             this, SLOT(on_serialPort_errorOccured(QString)) );
}

/* ########################################################################## */
/* ########################################################################## */

void    CMainWindow::_createUi(void)
{
    this->_createUi_menus();

    this->addToolBar( new CToolBarSerialPortConfig( this ) );
    this->addToolBar( new CToolBarSerialPortStatus( this ) );

    this->setStatusBar( new CMainWindowStatusBar(this) );

    this->setCentralWidget( this->m_console );
}

/* ########################################################################## */
/* ########################################################################## */

void    CMainWindow::_createUi_menus(void)
{
    QMenu*  p_menuOptions   = this->menuBar()->addMenu( tr("Options") );
    connect( p_menuOptions, SIGNAL(aboutToShow()),
             this, SLOT(on_menuOptions_aboutToShow()) );


    QMenu*  p_menuPlugins   = this->menuBar()->addMenu( tr("Plugins") );
    connect( p_menuPlugins, SIGNAL(aboutToShow()),
             this, SLOT(on_menuPlugins_aboutToShow()) );


    QMenu*  p_menuView  = this->menuBar()->addMenu( tr("View") );
    connect( p_menuView, SIGNAL(aboutToShow()),
             this, SLOT(on_menuView_aboutToShow()) );


    QMenu*  p_menuHelp   = this->menuBar()->addMenu( tr("Help") );
    connect( p_menuHelp, SIGNAL(aboutToShow()),
             this, SLOT(on_menuHelp_aboutToShow()) );
}

/* ########################################################################## */
/* ########################################################################## */

void    CMainWindow::freeInstance(void)
{
    if( CMainWindow::s_m_instance != nullptr )
    {
        delete CMainWindow::s_m_instance;
        CMainWindow::s_m_instance   = nullptr;
    }
}

/* ########################################################################## */
/* ########################################################################## */

CMainWindow*    CMainWindow::getInstance(void)
{
    if( CMainWindow::s_m_instance == nullptr )
    {
        CMainWindow::s_m_instance   = new CMainWindow;
    }

    return CMainWindow::s_m_instance;
}

/* ########################################################################## */
/* ########################################################################## */

void    CMainWindow::on_actionAboutThisApp_triggered()
{
    QString text
            = "<h2>"
            + tr( "The %1 application" )
              .arg( QCoreApplication::applicationName() )
            + "</h2>";

    text.append( "<h3><font color=gray>"
                 + tr( "Version %1" )
                   .arg( QCoreApplication::applicationVersion() )
                 + "</font></h3>" );


    text.append( "\n\n" );

    text.append( "<p>" + tr( "Hello !" ) + "</p>" );
    text.append( "<p>" +
                 tr( "Welcome on the OpenSerial software !<br>"
                     "The aim of this project is to provide a free,"
                     " open-source, cross-platform, modular program to"
                     " communicate through serial interfaces." )
                 + "</p>" );

    text.append( "<p>" +
                 tr( "It uses the Qt library (see Help->About Qt for details)"
                     " and " )
                 + "</p>" );

    text.append( "<p>" +
                 tr( "If you want to be involved in this software development,"
                     " have any whishes on how this app should evolve,"
                     " found a bug, get in touch with Aloike through Github on"
                     " <a href='https://github.com/Aloike/openserial/'>This"
                     " project's Github page</a> ! :)" )
                 + "</p>" );

    text.append( "<p>" +
                 tr( "Thanks for your support! :)<br>"
                     "The SerialCommunicator Team" )
                 + "</p>" );


    QMessageBox::about(this, tr("About this software"), text);
}

/* ########################################################################## */
/* ########################################################################## */

void    CMainWindow::on_menuHelp_aboutToShow(void)
{
    Q_ASSERT( sender()->inherits( "QMenu" ) );
    QMenu *p_menuHelp   = (QMenu*) sender();


    p_menuHelp->clear();


    QAction*    p_actionAboutQt
            =   p_menuHelp->addAction( tr("About Qt"), qApp, SLOT(aboutQt()) );
    p_actionAboutQt->setIcon(QIcon(":/icons/aboutQt"));
    p_actionAboutQt->setIconVisibleInMenu(true);


    QAction*    p_actionAboutThisApp
            =   p_menuHelp->addAction(tr("About this app"),
                                      this,
                                      SLOT(on_actionAboutThisApp_triggered()) );
    p_actionAboutThisApp->setIcon(QIcon(":/icons/app"));
    p_actionAboutThisApp->setIconVisibleInMenu(true);
}

/* ########################################################################## */
/* ########################################################################## */

void    CMainWindow::on_menuOptions_aboutToShow(void)
{
    Q_ASSERT( sender()->inherits( "QMenu" ) );
    QMenu *p_menuOptions    = (QMenu*) sender();


    p_menuOptions->clear();

    /* ********** */

    p_menuOptions->addAction( QIcon(":/icons/config"),
                              tr("Configuration"),
                              this,
                              SLOT(on_menuOptions_actionConfiguration()) );

//    p_menuOptions->addMenu( this->_gbConsole->menu() );

//    p_menuOptions->addSeparator();

//    /* "Input" dock options */
//    QMenu   *menuInputDock = p_menuOptions->addMenu( tr( "Input dock" ) );
//    QAction *actionDockInputVisibilityToggle
//            = menuInputDock
//            ->addAction( tr( "Visible" ),
//                         this,
//                         SLOT(on_actionDockInputVisibilityToggle_triggered()) );
//    actionDockInputVisibilityToggle->setCheckable( true );
//    actionDockInputVisibilityToggle->setChecked( this->m_dwInput->isVisible() );
//    QAction *actionDockInputBackToDefault
//            = menuInputDock
//            ->addAction( tr( "back to default location" ),
//                         this,
//                         SLOT(on_actionDockInputBackToDefault_triggered()) );

    p_menuOptions->addSeparator();

    QAction* p_actionExit = p_menuOptions->addAction( tr("Quit"),
                                                      qApp, SLOT(quit()) );
    p_actionExit->setIcon( QIcon( ":/icons/quit" ) );
    p_actionExit->setIconVisibleInMenu( true );
}

/* ########################################################################## */
/* ########################################################################## */

void    CMainWindow::on_menuOptions_actionConfiguration(void)
{
    CDialogConfig   lDialogConfig(this);

    lDialogConfig.setPointerConsole( this->m_console );

    lDialogConfig.exec();
}

/* ########################################################################## */
/* ########################################################################## */

void    CMainWindow::on_menuPlugins_aboutToShow(void)
{
    Q_ASSERT( sender()->inherits( "QMenu" ) );
    QMenu *p_menuPlugins    = (QMenu*) sender();


    p_menuPlugins->clear();
}

/* ########################################################################## */
/* ########################################################################## */

void    CMainWindow::on_menuView_aboutToShow(void)
{
    Q_ASSERT( sender()->inherits( "QMenu" ) );
    QMenu *p_menuPlugins    = (QMenu*) sender();


    p_menuPlugins->clear();


    /* -------------------------------------------------------------------------
     *  Sub-menu "Toolbars"
     */
    QMenu*  p_menuToolbars  = p_menuPlugins->addMenu( tr("Toolbars") );

    QList<CToolbarAbstract *> lToolBarPointers
            = this->findChildren<CToolbarAbstract *>(
                QString(),
                Qt::FindDirectChildrenOnly );

    foreach( CToolbarAbstract* p_toolbar, lToolBarPointers )
    {
        QMenu*  p_menu  = p_toolbar->menu();
        if( p_menu != nullptr )
        {
            p_menuToolbars->addMenu( p_menu );
        }



//        p_action->setCheckable( true );
//        p_action->setChecked( p_toolbar->isVisible() );
//        p_action->setProperty( "p_toolbar", (qulonglong)p_toolbar );

    }
}

/* ########################################################################## */
/* ########################################################################## */

void    CMainWindow::on_serialPort_errorOccured(const QString &argErrorString)
{
    QMessageBox::warning( this,
                          tr( "Serial port error"),
                          "<p>"
                          + tr( "A serial port error occured !" )
                          + "</p><p><em>\"" + argErrorString + "\"</em></p>" );
}

/* ########################################################################## */
/* ########################################################################## */
