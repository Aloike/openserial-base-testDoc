#ifndef CTOOLBARSERIALPORTSTATUS_H
#define CTOOLBARSERIALPORTSTATUS_H

#include "CToolbarAbstract.h"

class QLabel;

class CLed;


class   CToolBarSerialPortStatus
        :   public CToolbarAbstract
{
    Q_OBJECT

public:

    CToolBarSerialPortStatus(QWidget *argParent=nullptr);



protected:
private:

    void    _createConnections(void);
    void    _createUi(void);



public slots:
protected slots:
private slots:

    void    on_serialPort_connectStateChanged(bool argIsConnected);
//    void    on_serialPort_errorOccured(QString argErrorString);



public:
protected:
private:

    CLed*   m_ledPortStatus;
    QLabel* m_lPortStatus;
};

#endif /*< CTOOLBARSERIALPORTSTATUS_H */
