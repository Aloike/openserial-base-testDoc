#ifndef CMENUPLUGINS_H
#define CMENUPLUGINS_H

#include <QMenu>


class   CMenuPlugins
        :   public  QMenu
{
    Q_OBJECT

public:

    CMenuPlugins(QWidget* argParent=nullptr);



protected:
private:

    Q_SLOT  void    on_aboutToShow(void);



};

#endif  /*< CMENUPLUGINS_H */
