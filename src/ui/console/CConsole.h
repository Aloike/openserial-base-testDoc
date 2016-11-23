#ifndef CCONSOLE_H
#define CCONSOLE_H

#include <QPlainTextEdit>

/**
 *  @brief  The CConsole class is a terminal-like text edit.
 */
class   CConsole
        :   public  QPlainTextEdit
{
    Q_OBJECT

public:

    CConsole(QWidget* parent=nullptr);


    void    appendData(const QByteArray& argdata);


    bool    printTxEnabled(void) const;
    void    setPrintTxEnabled(const bool& argEnabled);



protected:

    virtual void    keyPressEvent(QKeyEvent *e) Q_DECL_OVERRIDE;



private:



public slots:
protected slots:
private slots:

    void    on_serialPort_connectStateChanged(const bool& argIsOpen);
    void    on_serialPort_dataReceived(const QByteArray& argReceivedData);
    void    on_serialPort_dataSent(const QByteArray& argReceivedData);



public:
protected:
private:

    bool    m_printTx;



};

#endif /*< CCONSOLE_H */
