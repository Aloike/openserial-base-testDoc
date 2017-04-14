#ifndef CINTERFACESERIAL_H
#define CINTERFACESERIAL_H

#include <QSerialPort>


class CInterfaceSerial : public QSerialPort
{
    Q_OBJECT

public:

    static QStringList      portsAvailable(void);


    explicit CInterfaceSerial(QObject *argParent = 0);


    QString     portNameSystem(void) const;

    bool    open(void);
    void    close(void);

    bool    setBaudRate(qint32 baudRate, Directions directions = AllDirections);
    bool    setDataBits(DataBits dataBits);
    bool    setParity(Parity parity);
    bool    setStopBits(StopBits stopBits);
    bool    setFlowControl(FlowControl flowControl);

    Q_SLOT  qint64  sendData(const QByteArray& argData);



protected:

    bool    open(OpenMode mode);



private slots:

    void    on_this_readyRead(void);



signals:

    void    connectStateChanged(const bool& argIsOpen);
    void    errorOccured(const QString& argErrorString);
    void    dataReceived(const QByteArray& argReceivedData);
    void    dataSent(const QByteArray& argEmittedData);



};

#endif /*< CINTERFACESERIAL_H */
