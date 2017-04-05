#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <QMainWindow>

class   CConsole;


class CMainWindow : public QMainWindow
{
    Q_OBJECT

public:

    static CMainWindow* getInstance(void);
    static void         freeInstance(void);



protected:
private:

    CMainWindow(QWidget *parent = 0);
    ~CMainWindow();


    void    _createConnections(void);
    void    _createUi(void);
    void    _createUi_menus(void);



public slots:
protected slots:
private slots:

    void    on_actionAboutThisApp_triggered(void);
    void    on_menuHelp_aboutToShow(void);
    void    on_menuOptions_aboutToShow(void);
    void    on_menuOptions_actionConfiguration(void);
    void    on_menuView_aboutToShow(void);
    void    on_serialPort_errorOccured(const QString& argErrorString);



public:
protected:
private:

    static  CMainWindow*    s_m_instance;

    CConsole    *m_console;



};

#endif /*< CMAINWINDOW_H */
