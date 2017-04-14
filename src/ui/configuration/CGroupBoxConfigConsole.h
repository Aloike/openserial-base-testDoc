#ifndef CGROUPBOXCONFIGCONSOLE_H
#define CGROUPBOXCONFIGCONSOLE_H

#include <QGroupBox>


class QCheckBox;
class CConsole;


class   CGroupBoxConfigConsole
        :   public  QGroupBox
{
    Q_OBJECT

public:

    explicit CGroupBoxConfigConsole(QWidget *parent = 0);


    void    setPointerConsole(CConsole* argConsole_p);



protected:
private:

    void    _createConnections(void);
    void    _createUi_layout(void);

    void    updateUi(void);



public slots:
protected slots:
private slots:

    void    on_m_cbPrintTx_stateChanged(int argNewState);



public:
protected:
private:

    QCheckBox*  m_cbPrintTx;

    CConsole*   p_console;



};

#endif /*< CGROUPBOXCONFIGCONSOLE_H */
