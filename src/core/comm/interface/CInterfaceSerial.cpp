#include "CInterfaceSerial.h"

#include <QSerialPortInfo>


/* ########################################################################## */
/* ########################################################################## */
/**
 *  @brief Constructor of the CInterfaceSerial class.
 *
 *  @param argParent    The parent object.
 */
CInterfaceSerial::CInterfaceSerial(QObject *argParent)
    :   QSerialPort( argParent )
{
    connect( this, SIGNAL(readyRead()),
             this, SLOT(on_this_readyRead()) );
}

/* ########################################################################## */
/* ########################################################################## */

void    CInterfaceSerial::close(void)
{
    QSerialPort::close();

    emit this->connectStateChanged( this->isOpen() );
}

/* ########################################################################## */
/* ########################################################################## */

void    CInterfaceSerial::on_this_readyRead(void)
{
    QByteArray  lReceivedData;

    while( ! this->atEnd() )
    {
        if( lReceivedData.count() >= 200 )
        {
            emit this->dataReceived( lReceivedData );
            lReceivedData.clear();
        }

        lReceivedData.append( this->readAll() );
    }

    emit this->dataReceived( lReceivedData );
}

/* ########################################################################## */
/* ########################################################################## */
/**
 *  @brief  This method opens the serial port's interface for read and write
 *          access.
 *
 *  @retval true    If the port has successfully been opened ;
 *  @retval false   otherwise.
 */
bool    CInterfaceSerial::open(void)
{
    return this->open( QSerialPort::ReadWrite );
}

/* ########################################################################## */
/* ########################################################################## */
/**
 *  @brief  Overload of the QSerialPort::open method, adding signal emissions.
 *
 *  When successfull, it emits the \ref connectStateChanged signal. If an error
 *  occured, the \ref connectStateChanged and the \ref openError signals are
 *  emitted.
 *
 *  @param mode See \ref QSerialPort::open(QIODevice::OpenMode mode).
 *
 *  @retval true    on success;
 *  @retval false   otherwise.
 */
bool    CInterfaceSerial::open(QIODevice::OpenMode mode)
{
    bool    retVal  = false;

    retVal  = QSerialPort::open(mode);

    if( retVal == true )
    {
        emit this->connectStateChanged( true );
    }
    else
    {
        emit this->connectStateChanged( false );
        emit this->errorOccured( this->errorString() );
    }

    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */
/**
 *  @brief  Accessor to get the current port's name as a system location.
 *
 *  @return The system location of the port.
 */
QString CInterfaceSerial::portNameSystem(void) const
{
    return QSerialPortInfo( this->portName() ).systemLocation();
}

/* ########################################################################## */
/* #### STATIC METHODS ###################################################### */
/* ########################################################################## */
/**
 *  @brief  This method returns a list of serial ports that have been found on
 *          the system.
 *
 *  @return A QStringList containing a list of ports names.
 */
QStringList CInterfaceSerial::portsAvailable(void)
{
    QStringList retVal;

    foreach( QSerialPortInfo lPortInfo,
             QSerialPortInfo::availablePorts() )
    {
        retVal.append( lPortInfo.systemLocation() );
    }

    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */

qint64      CInterfaceSerial::sendData(const QByteArray &argData)
{
    qint64  retVal  = this->write( argData );


    if( retVal == argData.count() )
    {
        emit this->dataSent( argData );
    }
    else if( retVal > 0 )
    {
        emit this->dataSent( argData.left( retVal ) );
    }
    else
    {
        /* An error occured / no data has been emitted */
    }


    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */

bool    CInterfaceSerial::setBaudRate( qint32 baudRate,
                                       QSerialPort::Directions directions)
{
    bool    retVal  = false;

    retVal  = QSerialPort::setBaudRate( baudRate, directions );

    if( retVal == false )
    {
        emit this->errorOccured( this->errorString() );
    }

    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */

bool    CInterfaceSerial::setDataBits(DataBits dataBits)
{
    bool    retVal  = false;

    retVal  = QSerialPort::setDataBits( dataBits );

    if( retVal == false )
    {
        emit this->errorOccured( this->errorString() );
    }

    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */

bool    CInterfaceSerial::setParity(Parity parity)
{
    bool    retVal  = false;

    retVal  = QSerialPort::setParity( parity );

    if( retVal == false )
    {
        emit this->errorOccured( this->errorString() );
    }

    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */

bool    CInterfaceSerial::setStopBits(StopBits stopBits)
{
    bool    retVal  = false;

    retVal  = QSerialPort::setStopBits( stopBits );

    if( retVal == false )
    {
        emit this->errorOccured( this->errorString() );
    }

    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */

bool    CInterfaceSerial::setFlowControl(FlowControl flowControl)
{
    bool    retVal  = false;

    retVal  = QSerialPort::setFlowControl( flowControl );

    if( retVal == false )
    {
        emit this->errorOccured( this->errorString() );
    }

    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */
