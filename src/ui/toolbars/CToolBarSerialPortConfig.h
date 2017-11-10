#ifndef CTOOLBARSERIALPORTCONFIG_H
#define CTOOLBARSERIALPORTCONFIG_H

#include "CToolbarAbstract.h"

class QPushButton;
class QTimer;

class CComboBox;


class   CToolBarSerialPortConfig
        :   public CToolbarAbstract
{
    Q_OBJECT

public:

    CToolBarSerialPortConfig(QWidget* argParent=nullptr);



protected:
private:

    void    _createConnections(void);
    void    _createUi(void);

    void    portNames_update(void);

    void    uiUpdate(void);



public slots:
protected slots:
private slots:

    void    on_m_cbDataBits_currentIndexChanged(int argNewIndex);
    void    on_m_cbFlowControl_currentIndexChanged(int argNewIndex);
    void    on_m_cbParity_currentIndexChanged(int argNewIndex);
    void    on_m_cbPortName_aboutToShowPopup(void);
    void    on_m_cbRate_currentIndexChanged(int argNewIndex);
    void    on_m_cbStopBits_currentIndexChanged(int argNewIndex);
    void    on_m_pbPortStateToggle_clicked(bool);
    void    on_serialPort_configChanged(void);
    void    on_serialPort_connectStateChanged(const bool& argIsOpen);



public:
protected:
private:

    CComboBox       *m_cbDataBits;
    CComboBox       *m_cbFlowControl;
    CComboBox       *m_cbParity;
    CComboBox       *m_cbPortName;
    CComboBox       *m_cbRate;
    CComboBox       *m_cbStopBits;
    QPushButton     *m_pbPortStateToggle;
//    QPushButton     *m_pbRefreshPortsList;



};

#endif /*< CTOOLBARSERIALPORTCONFIG_H */
