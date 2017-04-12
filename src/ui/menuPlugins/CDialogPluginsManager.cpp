#include "CDialogPluginsManager.h"

#include <QCheckBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QSpacerItem>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>

#include "core/plugins/management/CPluginsManagerSingleton.h"

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
    ,   m_pbAccept( new QPushButton( tr( "Accept" ), this ) )
    ,   m_pbCancel( new QPushButton( tr( "Cancel" ), this ) )
    ,   m_twList( new QTableWidget( this ) )
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
}

/* ########################################################################## */
/* ########################################################################## */

void    CDialogPluginsManager::_create_ui_layout(void)
{
    QHBoxLayout*    p_layoutButtons = new QHBoxLayout();
    p_layoutButtons->addSpacerItem( new QSpacerItem( 10,10,
                                                     QSizePolicy::Expanding ) );
    p_layoutButtons->addWidget( this->m_pbCancel );
    p_layoutButtons->addWidget( this->m_pbAccept );


    QVBoxLayout*    p_layoutMain    = new QVBoxLayout( this );
    p_layoutMain->addWidget( this->m_twList );
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
    this->m_twList->setShowGrid( false );
    this->m_twList->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOff );


    /*
     *  Columns
     */
    this->m_twList->setColumnCount( Column::count() );
    this->m_twList->setColumnHidden( Column::ID, true );


    /*
     *  Headers
     */
    this->m_twList->verticalHeader()->setVisible( false );

    this->m_twList->setHorizontalHeaderLabels( Column::names() );
    this->m_twList->horizontalHeader()
            ->setSectionResizeMode(QHeaderView::ResizeToContents);;


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

QStringList CDialogPluginsManager::listActivatedPlugins(void) const
{
    QStringList retVal;

    for(int lRow = 0 ; lRow < this->m_twList->rowCount() ; ++lRow )
    {
        QCheckBox   *p_cbActivated
                = qobject_cast<QCheckBox*>(
                    this->m_twList->cellWidget( lRow, Column::Activated ) );

        if( p_cbActivated == nullptr )
        {
            TRACE_ERR( "Can't get QCheckBox pointer of row %d !",
                       lRow );
        }
        else if( p_cbActivated->isChecked() )
        {
            retVal.append( this->m_twList->item( lRow, Column::ID )->text() );
        }
    }

    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */

void    CDialogPluginsManager::listPopulate(void)
{
    this->m_twList->clear();

    CPluginsManagerSingleton*   p_pm
            = CPluginsManagerSingleton::getInstance();

    QHash<QString,CPluginContainer> lPluginsList
            = p_pm->updateAvailablePlugins();

    TRACE_DBG( "lPluginsList contains %d elements.",
               lPluginsList.count() );

    this->m_twList->setRowCount( lPluginsList.size() );

    int lRow    = 0;
    foreach( QString lKey, lPluginsList.keys() )
    {
        CPluginContainer    lPC     = lPluginsList.value( lKey );

        QCheckBox   *p_cbActivated  = new QCheckBox( this );
        p_cbActivated->setCheckable( true );
        p_cbActivated->setChecked( false );

        this->m_twList->setCellWidget( lRow,
                                       Column::Activated,
                                       p_cbActivated );

        this->m_twList->setItem( lRow, Column::Name,
                                 new QTableWidgetItem( lPC.name() ) );
        this->m_twList->setItem( lRow, Column::Version,
                                 new QTableWidgetItem( lPC.version() ) );

        this->m_twList->setItem( lRow, Column::ID,
                                 new QTableWidgetItem( lKey ) );

        ++lRow;
    }
}

/* ########################################################################## */
/* ########################################################################## */
