#include "CConsole.h"

#include "core/comm/interface/CInterfaceSerialSingleton.h"


/* ########################################################################## */
/* ########################################################################## */

CConsole::CConsole(QWidget* argParent)
    :   QPlainTextEdit(argParent)
    ,   m_printTx( true )
{
    CInterfaceSerial*   p_interfaceSerial
            = CInterfaceSerialSingleton::instance();


    this->setReadOnly( true );
    this->setWordWrapMode( QTextOption::WrapAnywhere );
    this->document()->setMaximumBlockCount( 500 );

    QFont font = this->font();
    font.setFamily( "Monospace" );
    font.setFixedPitch( true );
    this->setFont( font );


    connect( p_interfaceSerial, SIGNAL(connectStateChanged(bool)),
             this, SLOT(on_serialPort_connectStateChanged(bool)) );
    this->on_serialPort_connectStateChanged( p_interfaceSerial->isOpen() );

    connect( p_interfaceSerial, SIGNAL(dataReceived(QByteArray)),
             this, SLOT(on_serialPort_dataReceived(QByteArray)) );

    connect( p_interfaceSerial, SIGNAL(dataSent(QByteArray)),
             this, SLOT(on_serialPort_dataSent(QByteArray)) );
}

/* ########################################################################## */
/* ########################################################################## */

void    CConsole::appendData(const QByteArray& argdata)
{
    this->moveCursor( QTextCursor::End );
    this->textCursor().insertText( argdata );
}

/* ########################################################################## */
/* ########################################################################## */

void    CConsole::keyPressEvent(QKeyEvent* e)
{
    if( ! e->text().isEmpty() )
    {
        e->accept();

        if( this->isEnabled() )
        {
            CInterfaceSerialSingleton::instance()
                    ->sendData( e->text().toLatin1() );
        }
    }
    else
    {
        QPlainTextEdit::keyPressEvent( e );
    }
}

/* ########################################################################## */
/* ########################################################################## */
/**
 *  @brief  This slot is called whenever the connection state of the serial port
 *          changes.
 *
 *  @param  argIsOpen   The new serial port state :
 *                      + \c true means the port is open ;
 *                      + \c false means the port is closed.
 */
void    CConsole::on_serialPort_connectStateChanged(const bool &argIsOpen)
{
    this->setEnabled( argIsOpen );
}

/* ########################################################################## */
/* ########################################################################## */

void    CConsole::on_serialPort_dataReceived(const QByteArray &argReceivedData)
{
    this->appendData( argReceivedData );
}

/* ########################################################################## */
/* ########################################################################## */

void    CConsole::on_serialPort_dataSent(const QByteArray &argReceivedData)
{
    if( this->printTxEnabled() )
    {
        this->appendData( argReceivedData );
    }
}

/* ########################################################################## */
/* ########################################################################## */

bool    CConsole::printTxEnabled(void) const
{
    return this->m_printTx;
}

/* ########################################################################## */
/* ########################################################################## */

void    CConsole::setPrintTxEnabled(const bool &argEnabled)
{
    this->m_printTx = argEnabled;
}

/* ########################################################################## */
/* ########################################################################## */
