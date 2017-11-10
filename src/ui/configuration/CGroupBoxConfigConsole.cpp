#include "CGroupBoxConfigConsole.h"


#include <QCheckBox>
#include <QFormLayout>

#include "ui/console/CConsole.h"


/* ########################################################################## */
/* ########################################################################## */

CGroupBoxConfigConsole::CGroupBoxConfigConsole(QWidget *parent)
    :   QGroupBox( parent )
    ,   m_cbPrintTx( new QCheckBox(this) )
    ,   p_console( 0 )
{
    this->setTitle( tr("Console configuration") );

    this->_createUi_layout();

    this->_createConnections();
}

/* ########################################################################## */
/* ########################################################################## */

void    CGroupBoxConfigConsole::_createConnections(void)
{
    connect( this->m_cbPrintTx, SIGNAL(stateChanged(int)),
             this, SLOT(on_m_cbPrintTx_stateChanged(int)) );
}

/* ########################################################################## */
/* ########################################################################## */

void    CGroupBoxConfigConsole::_createUi_layout()
{
    QFormLayout*    p_layoutMain    = new QFormLayout( this );


    this->setLayout( p_layoutMain );

    p_layoutMain->addRow( tr("Local echo activated :"), this->m_cbPrintTx );
}

/* ########################################################################## */
/* ########################################################################## */

void    CGroupBoxConfigConsole::on_m_cbPrintTx_stateChanged(int argNewState)
{
    if( this->p_console == 0 )
    {
        /* bad pointer */
    }
    else
    {
        this->p_console->setPrintTxEnabled( argNewState == Qt::Checked ?
                                                    true
                                                :   false );
    }
}

/* ########################################################################## */
/* ########################################################################## */

void    CGroupBoxConfigConsole::setPointerConsole(CConsole* argConsole_p)
{
    if( argConsole_p == 0 )
    {
        /* Bad pointer */
    }
    else
    {
        this->p_console = argConsole_p;
    }

    this->updateUi();
}

/* ########################################################################## */
/* ########################################################################## */

void CGroupBoxConfigConsole::updateUi()
{
    if( this->p_console == 0 )
    {
        /* Bad pointer */
    }
    else
    {
        this->m_cbPrintTx->setChecked( p_console->printTxEnabled() );
    }
}

/* ########################################################################## */
/* ########################################################################## */
