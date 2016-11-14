#include "CToolbarAbstract.h"

#include <QMenu>


CToolbarAbstract::CToolbarAbstract(QWidget *argParent)
    :   QToolBar( argParent )
    ,   m_menu( new QMenu( this ) )
{
    this->setWindowTitle( "[[Unknown toolbar title]]" );
}

QMenu*  CToolbarAbstract::menu(void)
{
    this->m_menu->clear();

    this->m_menu->setTitle( this->windowTitle() );

    QAction*    p_actionVisibility  = this->m_menu->addAction( tr("Visible") );
    p_actionVisibility->setCheckable( true );
    p_actionVisibility->setChecked( this->isVisible() );
    connect( p_actionVisibility, SIGNAL(triggered(bool)),
             this, SLOT(on_actionVisibility_triggered(bool)) );


    return this->m_menu;
}

void    CToolbarAbstract::on_actionVisibility_triggered(bool)
{
    if( this->isVisible() )
    {
        this->hide();
    }
    else
    {
        this->show();
    }
}
