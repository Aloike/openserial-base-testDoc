#include "CGBPluginDetails.h"

#include <QFormLayout>
#include <QLabel>

#include "core/plugins/management/CPluginsManagerSingleton.h"

/* ########################################################################## */
/* ########################################################################## */

CGBPluginDetails::CGBPluginDetails( QWidget* argParent )
    :   QGroupBox( argParent )
    ,   m_lDescription( new QLabel( this ) )
    ,   m_lEditorName( new QLabel( this ) )
    ,   m_lName( new QLabel( this ) )
    ,   m_lPath( new QLabel( this ) )
    ,   m_lVersion( new QLabel( this ) )
{
    this->setTitle( tr( "Plugin details" ) );
    this->setEnabled( false );

    this->m_lDescription->setWordWrap( true );
//    this->m_lName->setFixedWidth( 250 );
    this->m_lPath->setTextInteractionFlags( Qt::TextSelectableByMouse );
    this->m_lPath->setAlignment( Qt::AlignRight );

    QFormLayout*    p_layout    = new QFormLayout( this );
    p_layout->setSizeConstraint( QLayout::SetNoConstraint );
    p_layout->addRow( tr( "Name :" ),           this->m_lName );
    p_layout->addRow( tr( "Version :" ),        this->m_lVersion );
    p_layout->addRow( tr( "Editor :" ),         this->m_lEditorName );
    p_layout->addRow( tr( "Path :" ),           this->m_lPath );
    p_layout->addRow( tr( "Description :" ),    this->m_lDescription );

//    this->setMaximumWidth( 500 );
    this->setMinimumWidth( 300 );
    this->clear();
}

/* ########################################################################## */
/* ########################################################################## */

void    CGBPluginDetails::clear(void)
{
    this->m_lDescription->clear();
    this->m_lEditorName->clear();
    this->m_lName->clear();
    this->m_lPath->clear();
    this->m_lVersion->clear();
}

/* ########################################################################## */
/* ########################################################################## */

void    CGBPluginDetails::setDisplayedPlugin(const QString &argPluginId)
{
    CPluginsManagerSingleton*   p_pm
            = CPluginsManagerSingleton::getInstance();
    if( ! p_pm->availablePlugins().contains( argPluginId ) )
    {
        this->clear();
        this->setEnabled( false );
    }
    else
    {
        this->clear();
        this->setEnabled( true );

        CPluginContainer    lPC
                = p_pm->availablePlugins().value( argPluginId );

        this->m_lDescription->setText( lPC.description() );
        this->m_lEditorName->setText( lPC.editorName() );
        this->m_lName->setText( lPC.nameHumanReadable() );
        this->m_lPath->setText( lPC.path() );
        this->m_lVersion->setText( lPC.version() );

        this->m_lName->adjustSize();
    }
}

/* ########################################################################## */
/* ########################################################################## */
