#include "CToolBarSerialPortStatus.h"

#include <QLabel>

#include "core/comm/interface/CInterfaceSerialSingleton.h"
#include "ui/common/CLed.h"


/* ########################################################################## */
/* ########################################################################## */

CToolBarSerialPortStatus::CToolBarSerialPortStatus(QWidget *argParent)
    :   CToolbarAbstract(argParent)
    ,   m_ledPortStatus( new CLed( this ) )
    ,   m_lPortStatus( new QLabel( this ) )
{
    this->setWindowTitle( tr("Serial port status") );

    this->_createUi();
    this->_createConnections();

    this->on_serialPort_connectStateChanged(
                CInterfaceSerialSingleton::instance()->isOpen() );
}

/* ########################################################################## */
/* ########################################################################## */

void    CToolBarSerialPortStatus::_createConnections(void)
{
    connect( CInterfaceSerialSingleton::instance(),
             SIGNAL(connectStateChanged(bool)),
             this, SLOT(on_serialPort_connectStateChanged(bool)));
}

/* ########################################################################## */
/* ########################################################################## */

void    CToolBarSerialPortStatus::_createUi(void)
{
    this->addWidget( this->m_ledPortStatus );
    this->m_ledPortStatus->setColor( Qt::green );
    this->m_ledPortStatus->resize( 40, 40 );
    this->m_ledPortStatus
            ->setToolTip( "<p><b>"
                          + tr( "Port status" )
                          + "</b></p><p><ul>"
                          + "<li>"
                          +     tr( "Green : Serial port is connected." )
                          + "</li>"
                          + "<li>"
                          +     tr( "Grey : Serial port is not connected." )
                          + "</li>"
                          + "</ul></p>");


    this->addWidget( this->m_lPortStatus );
    this->m_lPortStatus->setAlignment( Qt::AlignCenter );
}

/* ########################################################################## */
/* ########################################################################## */

void    CToolBarSerialPortStatus::on_serialPort_connectStateChanged(
                bool    argIsConnected )
{
    this->m_ledPortStatus->setActivated( argIsConnected );

    if( argIsConnected == true )
    {
        this->m_lPortStatus->setText( tr( "Connected" ) );
    }
    else
    {
        this->m_lPortStatus->setText( tr( "Disconnected" ) );
    }
}

/* ########################################################################## */
/* ########################################################################## */
