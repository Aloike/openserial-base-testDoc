#include "CDialogConfig.h"


#include <QGridLayout>

#include "CGroupBoxConfigConsole.h"


/* ########################################################################## */
/* ########################################################################## */

CDialogConfig::CDialogConfig(QWidget* argParent)
    :   QDialog(argParent)
    ,   m_wConfigConsole( new CGroupBoxConfigConsole(this) )
{
    this->_createUi_layout();
}

/* ########################################################################## */
/* ########################################################################## */

void    CDialogConfig::_createUi_layout()
{
    QGridLayout*    p_layoutMain    = new QGridLayout( this );

    this->setLayout( p_layoutMain );

    p_layoutMain->addWidget( this->m_wConfigConsole );
}

/* ########################################################################## */
/* ########################################################################## */

void    CDialogConfig::setPointerConsole(CConsole* argConsole_p)
{
    if( argConsole_p == 0 )
    {
        /* Bad pointer */
    }
    else
    {
        this->m_wConfigConsole->setPointerConsole( argConsole_p );
    }
}

/* ########################################################################## */
/* ########################################################################## */
