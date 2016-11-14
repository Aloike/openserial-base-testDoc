#ifndef CMAINWINDOWSTATUSBAR_H
#define CMAINWINDOWSTATUSBAR_H

#include <QStatusBar>

class CLed;


class CMainWindowStatusBar : public QStatusBar
{
    Q_OBJECT

public:

    CMainWindowStatusBar(QWidget *argParent=nullptr);



protected:
private:

    void    _createUi(void);



public slots:
protected slots:
private slots:

    void    on_serialPort_connectStateChanged(bool argIsConnected);
    void    on_serialPort_errorOccured(QString argErrorString);



public:
protected:
private:



};

#endif /*< CMAINWINDOWSTATUSBAR_H */
