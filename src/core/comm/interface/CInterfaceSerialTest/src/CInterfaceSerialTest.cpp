#include <QString>
#include <QtTest>

#include "../CInterfaceSerialSingleton.h"


/* ########################################################################## */
/* ########################################################################## */

class CInterfaceSerialTest  :   public QObject
{
    Q_OBJECT

public:
    CInterfaceSerialTest();

private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    void    testSingletonCreation(void);

    void    test_portsAvailable(void);
    void    test_portName(void);

    void    test_openClose(void);

//    void    test_configStruct(void);

    void testCase1_data();
    void testCase1();
};

/* ########################################################################## */
/* ########################################################################## */

CInterfaceSerialTest::CInterfaceSerialTest()
{
}

/* ########################################################################## */
/* ########################################################################## */

void CInterfaceSerialTest::initTestCase()
{
}

/* ########################################################################## */
/* ########################################################################## */

void CInterfaceSerialTest::cleanupTestCase()
{
}

/* ########################################################################## */
/* ########################################################################## */

void CInterfaceSerialTest::testCase1_data()
{
    QTest::addColumn<QString>("data");
    QTest::newRow("0") << QString();
}

/* ########################################################################## */
/* ########################################################################## */

void CInterfaceSerialTest::testCase1()
{
    QFETCH(QString, data);
    QVERIFY2(true, "Failure");
}

/* ########################################################################## */
/* ########################################################################## */

//void    CInterfaceSerialManagerSingletonTest::test_configStruct(void)
//{
//    TsInterfaceSerialConfig lConfigStruct
//            = CInterfaceSerialManagerSingleton::instance()->configStruct();

//    qInfo( "+-- lConfigStruct (raw !) :" );
//    qInfo( "    +-- databits \t: %d",   lConfigStruct.dataBits );
//    qInfo( "    +-- flowCtrl \t: %d",   lConfigStruct.flowCtrl );
//    qInfo( "    +-- parity \t: %d",     lConfigStruct.parity );
//    qInfo( "    +-- rate \t: %d",       lConfigStruct.rate );
//    qInfo( "    +-- stopBits \t: %d",   lConfigStruct.stopBits );

//    CInterfaceSerialManagerSingleton::freeInstance();
//}

/* ########################################################################## */
/* ########################################################################## */

void    CInterfaceSerialTest::test_openClose(void)
{
    const QString   c_portName( "/dev/ttyUSB0" );


    QVERIFY2( CInterfaceSerialSingleton::instance()->isOpen() != true,
              "Serial port should not be opened !" );


    CInterfaceSerialSingleton::instance()->setPortName( c_portName );
    qInfo( "Current port name : '%s'",
           CInterfaceSerialSingleton::instance()->portNameSystem()
           .toStdString().c_str() );

    QVERIFY2( CInterfaceSerialSingleton::instance()->open(),
              "An error occured while opening serial port" );
    QVERIFY2( CInterfaceSerialSingleton::instance()->isOpen(),
              "isOpen returned false whereas port should be opened" );

    CInterfaceSerialSingleton::instance()->close();
    QVERIFY2( CInterfaceSerialSingleton::instance()->isOpen() != true,
              "isOpen returned `true` whereas port should be closed" );


    CInterfaceSerialSingleton::freeInstance();
}

/* ########################################################################## */
/* ########################################################################## */

void    CInterfaceSerialTest::test_portName(void)
{
    const QString   c_portName( "/dev/ttyUSB0" );

    QVERIFY2( CInterfaceSerialSingleton::instance()->portNameSystem().isEmpty(),
              "Port name is not empty !" );


//    CInterfaceSerialManagerSingleton::instance()->setPortName( "/dev/ttyS0" );
//    QVERIFY2( CInterfaceSerialManagerSingleton::instance()->open(),
//              "Can't open port" );

    CInterfaceSerialSingleton::instance()->setPortName( c_portName );
    qInfo( "Current port name : '%s'",
           CInterfaceSerialSingleton::instance()->portNameSystem()
           .toStdString().c_str() );

    QVERIFY2(       CInterfaceSerialSingleton::instance()->portNameSystem()
              ==    c_portName,
              "Port name is not the expected one !" );


    CInterfaceSerialSingleton::freeInstance();
}

/* ########################################################################## */
/* ########################################################################## */

void    CInterfaceSerialTest::test_portsAvailable(void)
{
    qInfo( "+-- List of available ports :" );
    foreach( QString lPortName,
             CInterfaceSerialSingleton::portsAvailable() )
    {
        qInfo( "    +-- `%s`", lPortName.toStdString().c_str() );
    }
}

/* ########################################################################## */
/* ########################################################################## */
/**
 *  @brief  This test case validates the singleton's creation/destruction.
 */
void    CInterfaceSerialTest::testSingletonCreation()
{
    CInterfaceSerialSingleton*   p_ifaceSerial   = 0;
    QVERIFY2( p_ifaceSerial == 0,
              "p_ifaceSerial has not been initialized correctly" );

    p_ifaceSerial   = CInterfaceSerialSingleton::instance();
    QVERIFY2( p_ifaceSerial != 0,
              "The singleton has not been created successfully" );

    CInterfaceSerialSingleton::freeInstance();
}

/* ########################################################################## */
/* ########################################################################## */

QTEST_APPLESS_MAIN(CInterfaceSerialTest)

#include "CInterfaceSerialTest.moc"

/* ########################################################################## */
/* ########################################################################## */
