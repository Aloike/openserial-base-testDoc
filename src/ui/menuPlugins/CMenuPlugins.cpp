#include "CMenuPlugins.h"

#include <COpenserialPluginInterface.h>

#include "core/plugins/management/CPluginsManagerSingleton.h"

#include "CDialogPluginsManager.h"

/* ########################################################################## */
/* ########################################################################## */

CMenuPlugins::CMenuPlugins(QWidget *argParent)
    :   QMenu( tr("Plugins"), argParent )
{
    connect( this, SIGNAL(aboutToShow()),
             this, SLOT(on_aboutToShow()) );
}

/* ########################################################################## */
/* ########################################################################## */

void    CMenuPlugins::on_aboutToShow(void)
{
    this->clear();


    this->addAction( tr( "Manage..." ),
                     this,
                     SLOT(on_actionManage()) );


    this->addSeparator();


    CPluginsManagerSingleton*   p_pm
            = CPluginsManagerSingleton::getInstance();

    foreach( QString lID, p_pm->activatedPlugins().keys() )
    {
        COpenserialPluginInterface* p_pi
                =   p_pm->activatedPlugins().value( lID ).pluginInterface();

        if( p_pi->menu() != nullptr )
        {
            this->addMenu( p_pi->menu() );
        }
    }
}

/* ########################################################################## */
/* ########################################################################## */

void    CMenuPlugins::on_actionManage(void)
{
    CDialogPluginsManager   lDialog( this );

    lDialog.exec();
}

/* ########################################################################## */
/* ########################################################################## */
