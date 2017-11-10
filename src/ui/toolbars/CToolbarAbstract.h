#ifndef CTOOLBARABSTRACT_H
#define CTOOLBARABSTRACT_H

#include <QToolBar>

class QAction;
class QMenu;


class   CToolbarAbstract    :   public QToolBar
{
    Q_OBJECT

public:

    CToolbarAbstract(QWidget* argParent=nullptr);

//    virtual QAction*    action(void);
    virtual QMenu*  menu(void);



protected slots:

    virtual void    on_actionVisibility_triggered(bool);



protected:

    QMenu*  m_menu;



};

#endif /*< CTOOLBARABSTRACT_H */
