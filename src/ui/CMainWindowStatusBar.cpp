#include "CMainWindowStatusBar.h"

#include "core/comm/interface/CInterfaceSerialSingleton.h"
#include "ui/common/CLed.h"


CMainWindowStatusBar::CMainWindowStatusBar(QWidget* argParent)
    :   QStatusBar(argParent)
{
//    this->showMessage( "Hello World !", 2000 );

    _createUi();


    this->on_serialPort_connectStateChanged(
                CInterfaceSerialSingleton::instance()->isOpen() );


    connect( CInterfaceSerialSingleton::instance(),
             SIGNAL(connectStateChanged(bool)),
             this, SLOT(on_serialPort_connectStateChanged(bool)));

    connect( CInterfaceSerialSingleton::instance(),
             SIGNAL(errorOccured(QString)),
             this, SLOT(on_serialPort_errorOccured(QString)));
}

void CMainWindowStatusBar::_createUi()
{
}

void    CMainWindowStatusBar::on_serialPort_connectStateChanged(
                bool argIsConnected )
{
    if( argIsConnected == true )
    {
        this->showMessage( tr( "Connected" ) );
    }
    else
    {
        this->showMessage( tr( "Disconnected" ) );
    }
}

void    CMainWindowStatusBar::on_serialPort_errorOccured(QString argErrorString)
{
    this->showMessage( tr("Serial port error")
                       + " : \"" + argErrorString + "\"" );
}
