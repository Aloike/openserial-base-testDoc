#ifndef CDIALOGCONFIG_H
#define CDIALOGCONFIG_H

#include <QDialog>


class CConsole;
class CGroupBoxConfigConsole;


class   CDialogConfig
        :   public  QDialog
{
    Q_OBJECT

public:

    CDialogConfig(QWidget* argParent=0);


    void    setPointerConsole(CConsole* argConsole_p);



protected:
private:

    void    _createUi_layout(void);



public:
protected:
private:

    CGroupBoxConfigConsole*   m_wConfigConsole;



};

#endif /*< CDIALOGCONFIG_H */
