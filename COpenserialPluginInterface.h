#ifndef COPENSERIALPLUGININTERFACE_H
#define COPENSERIALPLUGININTERFACE_H

#include <QObject>

#include <QString>

class QDialog;
class QMenu;
class QToolBar;


class   COpenserialPluginInterface
        :   public  QObject
{
    Q_OBJECT

public:

    COpenserialPluginInterface(const QString& argName)
        :   QObject()
        ,   m_name( argName )
    {}

    QString name(void) const { return this->m_name; }


    virtual QDialog*    floatingWidget(void)    { return nullptr; }
    virtual QMenu*      menu(void)              { return nullptr; }
    virtual QToolBar*   toolBar(void)           { return nullptr; }


    /* -------------------------------------------------------------------------
     * Sginals declaration
     * ---------------------------------------------------------------------- */
    Q_SIGNAL qint64  toIfaceSerial_sendData(const QByteArray& argData);


    /* -------------------------------------------------------------------------
     * Slots declaration
     * ---------------------------------------------------------------------- */
    Q_SLOT virtual void on_interfaceSerial_connectStateChanged(
                                const bool& argIsOpen )
    {
        Q_UNUSED( argIsOpen )
    }

    Q_SLOT virtual void on_interfaceSerial_dataReceived(
                                const QByteArray& argReceivedData)
    {
        Q_UNUSED( argReceivedData )
    }

    Q_SLOT virtual void on_interfaceSerial_dataSent(
                                const QByteArray& argEmittedData)
    {
        Q_UNUSED( argEmittedData )
    }



public:
protected:
private:

    QString m_name;



};

Q_DECLARE_INTERFACE( COpenserialPluginInterface,
                     "openserial.COpenserialPluginInterface" )

#endif  /*< COPENSERIALPLUGININTERFACE_H */
