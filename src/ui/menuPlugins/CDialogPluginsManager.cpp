#include "CDialogPluginsManager.h"

#include <QCheckBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QSpacerItem>
#include <QPushButton>
#include <QTreeWidget>
#include <QVBoxLayout>

#include "core/plugins/management/CPluginsManagerSingleton.h"

#include "CGBPluginDetails.h"

/* ########################################################################## */
/* ########################################################################## */
/*
 *  Trace macros
 */
#include "core/trace/trace.h"

#if defined  QT_DEBUG && defined  TRACE_CDialogPluginsManager_DEBUG
#   define TRACE_DBG(format,...)                                               \
           TRACE_DBG_BASE( format, ##__VA_ARGS__ );
#else
#   define  TRACE_DBG(format,...)
#endif

#define TRACE_INFO(format,...)                                                 \
        TRACE_INFO_BASE( format, ##__VA_ARGS__ );

#define TRACE_ERR(format,...)                                                  \
        TRACE_ERR_BASE( format, ##__VA_ARGS__ );

/* ########################################################################## */
/* ########################################################################## */

CDialogPluginsManager::CDialogPluginsManager(QWidget *argParentPtr)
    :   QDialog(argParentPtr)
    ,   m_gbPluginDetails( new CGBPluginDetails( this ) )
    ,   m_pbAccept( new QPushButton( tr( "Accept" ), this ) )
    ,   m_pbCancel( new QPushButton( tr( "Cancel" ), this ) )
    ,   m_twList( new QTreeWidget( this ) )
{
    this->setWindowTitle( tr( "Plugins manager" ) );

    this->_create_ui_layout();
    this->_initialize_twList();

    this->_create_connections();
}

/* ########################################################################## */
/* ########################################################################## */

void    CDialogPluginsManager::_create_connections(void)
{
    connect( this->m_pbAccept, SIGNAL(clicked(bool)),
             this, SLOT(accept()) );

    connect( this->m_pbCancel, SIGNAL(clicked(bool)),
             this, SLOT(reject()) );

    connect( this->m_twList,
             SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),
             this,
             SLOT(on_m_twList_currentItemChanged( QTreeWidgetItem*,
                                                  QTreeWidgetItem* ) ) );
}

/* ########################################################################## */
/* ########################################################################## */

void    CDialogPluginsManager::_create_ui_layout(void)
{
    QHBoxLayout*    p_layoutCentral = new QHBoxLayout();
    p_layoutCentral->addWidget( this->m_twList );
    p_layoutCentral->addWidget( this->m_gbPluginDetails );


    QHBoxLayout*    p_layoutButtons = new QHBoxLayout();
    p_layoutButtons->addSpacerItem( new QSpacerItem( 10,10,
                                                     QSizePolicy::Expanding ) );
    p_layoutButtons->addWidget( this->m_pbCancel );
    p_layoutButtons->addWidget( this->m_pbAccept );


    QVBoxLayout*    p_layoutMain    = new QVBoxLayout( this );
    p_layoutMain->addLayout( p_layoutCentral );
    p_layoutMain->addLayout( p_layoutButtons );

    this->setLayout( p_layoutMain );
}

/* ########################################################################## */
/* ########################################################################## */

void    CDialogPluginsManager::_initialize_twList(void)
{
    this->m_twList->setEditTriggers(QAbstractItemView::NoEditTriggers);
    this->m_twList->setSelectionBehavior(QAbstractItemView::SelectRows);
    this->m_twList->setSelectionMode(QAbstractItemView::SingleSelection);
    this->m_twList->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );


    /*
     *  Columns
     */
    this->m_twList->setColumnCount( Column::count() );
    this->m_twList->setColumnHidden( Column::ID, true );


    /*
     *  Header
     */
    this->m_twList->header()->setVisible( false );


    this->listPopulate();
}

/* ########################################################################## */
/* ########################################################################## */

void    CDialogPluginsManager::accept(void)
{
    QDialog::accept();

    CPluginsManagerSingleton::getInstance()
            ->setActivatedPlugins( this->listActivatedPlugins() );
}

/* ########################################################################## */
/* ########################################################################## */

QString CDialogPluginsManager::currentlySelectedPluginId(void) const
{
    QString retVal  = "";


    QTreeWidgetItem*   p_item   = this->m_twList->currentItem();

    if( p_item == 0 )
    {
        /* Invalid item */
    }
    else
    {
        retVal  = p_item->text( Column::ID );
    }


    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */

QStringList CDialogPluginsManager::listActivatedPlugins(void) const
{
    QStringList retVal;

    for( int lTopLevelItemNbr = 0 ;
         lTopLevelItemNbr < this->m_twList->topLevelItemCount() ;
         ++lTopLevelItemNbr )
    {
        QTreeWidgetItem*    p_itemTopLevel
                = this->m_twList->topLevelItem( lTopLevelItemNbr );

        if( p_itemTopLevel == nullptr )
        {
            TRACE_ERR( "null p_itemTopLevel !" );
            continue;
        }


        for( int lChildNbr = 0 ;
             lChildNbr <  p_itemTopLevel->childCount() ;
             ++lChildNbr )
        {
            QTreeWidgetItem*    p_itemChild
                    = p_itemTopLevel->child( lChildNbr );

            if( p_itemChild == nullptr )
            {
                TRACE_ERR( "null p_itemChild !" );
                continue;
            }


            if( p_itemChild->checkState( Column::Activated ) == Qt::Checked )
            {
                retVal.append( p_itemChild->text( Column::ID ) );
            }
        }
    }

    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */

void    CDialogPluginsManager::listPopulate(void)
{
    CPluginsManagerSingleton*   p_pm
            = CPluginsManagerSingleton::getInstance();

    QHash<QString,CPluginContainer> lPluginsList
            = p_pm->updateAvailablePlugins();

    TRACE_DBG( "lPluginsList contains %d elements.",
               lPluginsList.count() );


    foreach( QString lKey, lPluginsList.keys() )
    {
        CPluginContainer    lPC     = lPluginsList.value( lKey );


        /*
         *  Find the Top Level / "Editor" item
         */
        QTreeWidgetItem *p_itemTopLevel = nullptr;
        for( int i = 0 ; i < this->m_twList->topLevelItemCount() ; ++i )
        {
            if(     this->m_twList->topLevelItem( i )->text(Column::Name)
                ==  lPC.editorName() )
            {
                p_itemTopLevel  = this->m_twList->topLevelItem( i );
                break;
            }
        }

        /* If the editor item doesn't exist, then create it */
        if( p_itemTopLevel == nullptr )
        {
            p_itemTopLevel  = new QTreeWidgetItem();

            p_itemTopLevel->setChildIndicatorPolicy( QTreeWidgetItem::
                                                     ShowIndicator );
            p_itemTopLevel->setFirstColumnSpanned( true );
            p_itemTopLevel->setText( Column::Name, lPC.editorName() );

            this->m_twList->addTopLevelItem( p_itemTopLevel );
        }



        /*
         *  Create the plugin item
         */
        QTreeWidgetItem *p_itemPlugin   = new QTreeWidgetItem();

        p_itemPlugin->setCheckState( Column::Activated,
                                     p_pm->activatedPlugins().contains(lKey)
                                        ?   Qt::Checked
                                        :   Qt::Unchecked );

        p_itemPlugin->setText( Column::ID,      lKey );
        p_itemPlugin->setText( Column::Name,    lPC.name() );
        p_itemPlugin->setText( Column::Version, lPC.version() );

        p_itemTopLevel->addChild( p_itemPlugin );
        p_itemTopLevel->setExpanded( true );
    }

    this->m_twList->resizeColumnToContents( Column::Activated );
    this->m_twList->resizeColumnToContents( Column::Name );
    this->m_twList->resizeColumnToContents( Column::Version );
    this->m_twList->setMinimumWidth( this->m_twList->header()->length() + 10 );
}

/* ########################################################################## */
/* ########################################################################## */

void    CDialogPluginsManager::on_m_twList_currentItemChanged(
                QTreeWidgetItem*,
                QTreeWidgetItem* )
{
    this->m_gbPluginDetails->setDisplayedPlugin(
                this->currentlySelectedPluginId() );
}

/* ########################################################################## */
/* ########################################################################## */
