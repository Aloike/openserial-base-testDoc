#include "CToolBarSerialPortConfig.h"

#include <QLineEdit>
#include <QPushButton>
#include <QTimer>

#include "core/comm/interface/CInterfaceSerialSingleton.h"
#include "ui/common/CComboBox.h"


/* ########################################################################## */
/* ########################################################################## */

CToolBarSerialPortConfig::CToolBarSerialPortConfig(QWidget *argParent)
    :   CToolbarAbstract( argParent )
    ,   m_cbDataBits( new CComboBox( this ) )
    ,   m_cbFlowControl( new CComboBox( this ) )
    ,   m_cbParity( new CComboBox( this ) )
    ,   m_cbPortName( new CComboBox( this, true ) )
    ,   m_cbRate( new CComboBox( this ) )
    ,   m_cbStopBits( new CComboBox( this ) )
    ,   m_pbPortStateToggle( new QPushButton( "[[Unknown state]]", this ) )
//    ,   m_pbRefreshPortsList( new QPushButton( QIcon(":/icons/refresh" ), "",
//                                               this ) )
{
    this->setWindowTitle( tr("Serial port configuration") );

    this->_createUi();
    this->_createConnections();
}

/* ########################################################################## */
/* ########################################################################## */

void    CToolBarSerialPortConfig::_createConnections(void)
{
    CInterfaceSerialSingleton*  p_interface
                = CInterfaceSerialSingleton::instance();


    connect( p_interface, SIGNAL(connectStateChanged(bool)),
             this, SLOT(on_serialPort_connectStateChanged(bool)) );

    connect(p_interface,SIGNAL(baudRateChanged(qint32,QSerialPort::Directions)),
            this, SLOT(on_serialPort_configChanged()) );

    connect(p_interface,SIGNAL(dataBitsChanged(QSerialPort::DataBits)),
            this, SLOT(on_serialPort_configChanged()) );

    connect(p_interface,SIGNAL(flowControlChanged(QSerialPort::FlowControl)),
            this, SLOT(on_serialPort_configChanged()) );

    connect(p_interface,SIGNAL(parityChanged(QSerialPort::Parity)),
            this, SLOT(on_serialPort_configChanged()) );

    connect(p_interface,SIGNAL(stopBitsChanged(QSerialPort::StopBits)),
            this, SLOT(on_serialPort_configChanged()) );


    connect( this->m_cbDataBits, SIGNAL(currentIndexChanged(int)),
             this, SLOT(on_m_cbDataBits_currentIndexChanged(int)) );

    connect( this->m_cbFlowControl, SIGNAL(currentIndexChanged(int)),
             this, SLOT(on_m_cbFlowControl_currentIndexChanged(int)) );

    connect( this->m_cbParity, SIGNAL(currentIndexChanged(int)),
             this, SLOT(on_m_cbParity_currentIndexChanged(int)) );

    connect( this->m_cbRate, SIGNAL(currentIndexChanged(int)),
             this, SLOT(on_m_cbRate_currentIndexChanged(int)) );

    connect( this->m_cbStopBits, SIGNAL(currentIndexChanged(int)),
             this, SLOT(on_m_cbStopBits_currentIndexChanged(int)) );

    connect( this->m_pbPortStateToggle, SIGNAL(clicked(bool)),
             this, SLOT(on_m_pbPortStateToggle_clicked(bool)) );
}

/* ########################################################################## */
/* ########################################################################## */

void    CToolBarSerialPortConfig::_createUi()
{
    QString lToolTipText;


    this->addWidget( this->m_cbPortName );
    this->m_cbPortName->setMinimumWidth( 150 );
    this->m_cbPortName->setToolTip( tr( "Name of the port to use" ) );
    connect( this->m_cbPortName, SIGNAL(aboutToShowPopup()),
             this, SLOT(on_m_cbPortName_aboutToShowPopup()) );


    this->addWidget( this->m_cbRate );
    this->m_cbRate->setAlignment(Qt::AlignRight);
    this->m_cbRate->addItem( "1200",    QSerialPort::Baud1200   );
    this->m_cbRate->addItem( "2400",    QSerialPort::Baud2400   );
    this->m_cbRate->addItem( "4800",    QSerialPort::Baud4800   );
    this->m_cbRate->addItem( "9600",    QSerialPort::Baud9600   );
    this->m_cbRate->addItem( "19200",   QSerialPort::Baud19200  );
    this->m_cbRate->addItem( "38400",   QSerialPort::Baud38400  );
    this->m_cbRate->addItem( "57600",   QSerialPort::Baud57600  );
    this->m_cbRate->addItem( "115200",  QSerialPort::Baud115200 );
    this->m_cbRate->setToolTip( "<p><b>" + tr( "Baud Rate" ) + "</b></p>"
                                + "<p>" + tr( "Data transmission speed,"
                                              " expressed as bits per second." )
                                + "</p>" );


    this->addWidget( this->m_cbDataBits );
    this->m_cbDataBits->setAlignment(Qt::AlignRight);
    this->m_cbDataBits->addItem( "5",   QSerialPort::Data5  );
    this->m_cbDataBits->addItem( "6",   QSerialPort::Data6  );
    this->m_cbDataBits->addItem( "7",   QSerialPort::Data7  );
    this->m_cbDataBits->addItem( "8",   QSerialPort::Data8  );
    this->m_cbDataBits->setToolTip( "<p><b>" + tr( "Data Bits" ) + "</b></p>"
                                    + "<p>" + tr( "The number of data bits in"
                                                  " each character." )
                                    + "</p>" );


    this->addWidget( this->m_cbParity );
    this->m_cbParity->setAlignment(Qt::AlignRight);
    this->m_cbParity->addItem(  "N",    QSerialPort::NoParity   );
    this->m_cbParity->addItem(  "E",    QSerialPort::EvenParity );
    this->m_cbParity->addItem(  "O",    QSerialPort::OddParity  );
    this->m_cbParity->addItem(  "M",    QSerialPort::MarkParity );
    this->m_cbParity->addItem(  "S",    QSerialPort::SpaceParity);
    lToolTipText
            = "<p><b>" + tr( "Parity" ) + "</b></p>"
            + "<p>" + tr( "This is a method of detecting errors in"
                          " transmission." )
            + "</p>"
            + "<p>" + tr( "When parity is used with a serial port, an extra"
                          " data bit is sent with each data character, arranged"
                          " so that the number of 1 bits in each character"
                          " matches to one of the following :" )
            + "<ul>"
            + "<li>"
                + tr( "<b><u>N</u>one :</b> No parity bit is sent at all." )
            + "</li>"
            + "<li>"
                + tr( "<b><u>E</u>ven :</b> The number of '1' bits in each"
                      " character, including the parity bit, is always even." )
            + "</li>"
            + "<li>"
                + tr( "<b><u>O</u>dd :</b> The number of '1' bits in each"
                      " character, including the parity bit, is always odd."
                      " More useful than even, since it"
                      " ensures that at least one state transition occurs in"
                      " each character, which makes it more reliable." )
            + "</li>"
            + "<li>"
                + tr( "<b><u>M</u>ark :</b> The parity bit is always set to the"
                      " mark signal condition (logical 1)." )
            + "</li>"
            + "<li>"
                + tr( "<b><u>S</u>pace :</b> The parity bit is always set to"
                      " the space signal condition (logical 0)." )
            + "</li>"
            + "</ul>"
            + tr( "If a byte is received with the wrong number of 1s, then it"
                  " must have been corrupted. However, an even number of errors"
                  " can pass the parity check." )
            + "</p>";
    this->m_cbParity->setToolTip( lToolTipText );


    this->addWidget( this->m_cbStopBits );
    this->m_cbStopBits->setAlignment(Qt::AlignRight);
    this->m_cbStopBits->addItem( "1",   QSerialPort::OneStop        );
    this->m_cbStopBits->addItem( "1.5", QSerialPort::OneAndHalfStop );
    this->m_cbStopBits->addItem( "2",   QSerialPort::TwoStop        );
    lToolTipText
            = "<p><b>" + tr( "Stop Bits" ) + "</b></p>"
            + "<p>"
            + tr( "Stop bits sent at the end of every character allow the"
                  " receiving signal hardware to detect the end of a character"
                  " and to resynchronise with the character stream." )
            + "</p>";
    this->m_cbStopBits->setToolTip( lToolTipText );


    this->addWidget( this->m_cbFlowControl );
    this->m_cbFlowControl->setAlignment(Qt::AlignRight);
    this->m_cbFlowControl->addItem( tr("None"),
                                    QSerialPort::NoFlowControl );
    this->m_cbFlowControl->addItem( tr("Hardware"),
                                    QSerialPort::HardwareControl );
    this->m_cbFlowControl->addItem( tr("Software"),
                                    QSerialPort::SoftwareControl );
    lToolTipText
            = "<p><b>" + tr( "Flow Control" ) + "</b></p>"
            + "<p>"
            + tr( "A serial port may use signals in the interface to pause and"
                  " resume the transmission of data." )
            + "</p>";
    this->m_cbFlowControl->setToolTip( lToolTipText );


    this->addWidget( this->m_pbPortStateToggle );


    this->uiUpdate();
}

/* ########################################################################## */
/* ########################################################################## */

void    CToolBarSerialPortConfig::on_m_cbDataBits_currentIndexChanged(
                int argNewIndex )
{
    CInterfaceSerialSingleton::instance()
            ->setDataBits( (QSerialPort::DataBits)
                           this->m_cbDataBits->itemData(argNewIndex).toInt());
}

/* ########################################################################## */
/* ########################################################################## */

void    CToolBarSerialPortConfig::on_m_cbFlowControl_currentIndexChanged(
                int argNewIndex )
{
    CInterfaceSerialSingleton::instance()
            ->setFlowControl( (QSerialPort::FlowControl)
                              this->m_cbFlowControl
                              ->itemData(argNewIndex).toInt() );
}

/* ########################################################################## */
/* ########################################################################## */

void    CToolBarSerialPortConfig::on_m_cbParity_currentIndexChanged(
                int argNewIndex )
{
    CInterfaceSerialSingleton::instance()
            ->setParity( (QSerialPort::Parity)
                         this->m_cbParity->itemData(argNewIndex).toInt() );
}

/* ########################################################################## */
/* ########################################################################## */

void    CToolBarSerialPortConfig::on_m_cbPortName_aboutToShowPopup(void)
{
    this->portNames_update();
}

/* ########################################################################## */
/* ########################################################################## */

void    CToolBarSerialPortConfig::on_m_cbRate_currentIndexChanged(
                int argNewIndex )
{
    CInterfaceSerialSingleton::instance()
            ->setBaudRate( this->m_cbRate->itemData(argNewIndex).toInt() );
}

/* ########################################################################## */
/* ########################################################################## */

void    CToolBarSerialPortConfig::on_m_cbStopBits_currentIndexChanged(
                int argNewIndex )
{
    CInterfaceSerialSingleton::instance()
            ->setStopBits( (QSerialPort::StopBits)
                           this->m_cbStopBits->itemData(argNewIndex).toInt() );
}

/* ########################################################################## */
/* ########################################################################## */

void    CToolBarSerialPortConfig::on_m_pbPortStateToggle_clicked(bool)
{
    CInterfaceSerialSingleton*  p_interface
            = CInterfaceSerialSingleton::instance();

    if( p_interface->isOpen() )
    {
        p_interface->close();
    }
    else
    {
        p_interface->setPortName( this->m_cbPortName->currentText() );
        p_interface->open();
    }
}

/* ########################################################################## */
/* ########################################################################## */

void    CToolBarSerialPortConfig::on_serialPort_configChanged()
{
    this->uiUpdate();
}

/* ########################################################################## */
/* ########################################################################## */

void    CToolBarSerialPortConfig::on_serialPort_connectStateChanged(
                const bool &argIsOpen)
{
    this->m_cbPortName->setEnabled( ! argIsOpen );

    this->uiUpdate();
}

/* ########################################################################## */
/* ########################################################################## */

void    CToolBarSerialPortConfig::portNames_update(void)
{
    QString lText = this->m_cbPortName->currentText();

    this->m_cbPortName->clear();

    QStringList lPortsListAlphabetical  = CInterfaceSerial::portsAvailable();
    qSort( lPortsListAlphabetical );

    foreach( QString lPortName, lPortsListAlphabetical )
    {
        this->m_cbPortName->addItem( lPortName );
    }

    this->m_cbPortName->setEditText( lText );
}

/* ########################################################################## */
/* ########################################################################## */

void    CToolBarSerialPortConfig::uiUpdate(void)
{
    CInterfaceSerialSingleton*  p_ifaceSerial
            = CInterfaceSerialSingleton::instance();


    this->m_cbPortName->setCurrentText( p_ifaceSerial->portNameSystem() );

    this->m_cbRate->setCurrentIndex( this->m_cbRate
                                     ->findData( p_ifaceSerial->baudRate() ) );

    this->m_cbDataBits->setCurrentIndex( this->m_cbDataBits
                                         ->findData( p_ifaceSerial
                                                     ->dataBits() ) );

    this->m_cbParity->setCurrentIndex( this->m_cbParity
                                       ->findData( p_ifaceSerial->parity() ) );

    this->m_cbStopBits->setCurrentIndex( this->m_cbStopBits
                                         ->findData( p_ifaceSerial
                                                     ->stopBits() ) );

    this->m_cbFlowControl->setCurrentIndex( this->m_cbFlowControl
                                            ->findData( p_ifaceSerial
                                                        ->flowControl() ) );

    if( p_ifaceSerial->isOpen() )
    {
        this->m_pbPortStateToggle->setText( tr( "Close" ) );
    }
    else
    {
        this->m_pbPortStateToggle->setText( tr( "Open" ) );
    }
}

/* ########################################################################## */
/* ########################################################################## */
