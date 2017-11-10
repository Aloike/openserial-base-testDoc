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

    Q_SLOT  void    on_actionAboutThisApp_triggered(void);
    Q_SLOT  void    on_menuHelp_aboutToShow(void);
    Q_SLOT  void    on_menuOptions_aboutToShow(void);
    Q_SLOT  void    on_menuOptions_actionConfiguration(void);
    Q_SLOT  void    on_menuView_aboutToShow(void);
    Q_SLOT  void    on_serialPort_errorOccured(const QString& argErrorString);



public:
protected:
private:

    static  CMainWindow*    s_m_instance;

    CConsole    *m_console;



};

#endif /*< CMAINWINDOW_H */
