#include "CPluginsManagerSingleton.h"

#include <QDialog>
#include <QFileInfo>
#include <QPluginLoader>
#include <QToolBar>

#include "core/comm/interface/CInterfaceSerialSingleton.h"
#include "ui/CMainWindow.h"

/* ########################################################################## */
/* ########################################################################## */
/*
 *  Trace macros
 */
#include "core/trace/trace.h"

#define TRACE_DBG(format,...)                                                  \
        TRACE_DBG_BASE( format, ##__VA_ARGS__ );

#define TRACE_INFO(format,...)                                                 \
        TRACE_INFO_BASE( format, ##__VA_ARGS__ );

#define TRACE_ERR(format,...)                                                  \
        TRACE_ERR_BASE( format, ##__VA_ARGS__ );

/* ########################################################################## */
/* ########################################################################## */

CPluginsManagerSingleton*    CPluginsManagerSingleton::s_p_instance = nullptr;

/* ########################################################################## */
/* ########################################################################## */

CPluginsManagerSingleton::CPluginsManagerSingleton(QObject *argParentPtr)
    :   CPluginsSearchPathsManager( argParentPtr )
{
}

/* ########################################################################## */
/* ########################################################################## */

const QHash<QString, CPluginContainer>&
        CPluginsManagerSingleton::activatedPlugins(void) const
{
    return this->m_activatedPlugins;
}

/* ########################################################################## */
/* ########################################################################## */

CPluginsManagerSingleton*   CPluginsManagerSingleton::getInstance(void)
{
    if( s_p_instance == nullptr )
    {
        s_p_instance    = new CPluginsManagerSingleton();
    }

    return s_p_instance;
}

/* ########################################################################## */
/* ########################################################################## */

bool    CPluginsManagerSingleton::pluginLoad(
                const QString           &argHash,
                const CPluginContainer  &argPluginContainer )
{
    bool    retVal  = true;

    COpenserialPluginInterface* p_pluginInterface
            = argPluginContainer.pluginInterface();


    if( p_pluginInterface == nullptr )
    {
        TRACE_ERR( "Can't get plugin interface of '%s'",
                   argHash.toStdString().c_str() );

        retVal  = false;
    }
    else
    {
        CInterfaceSerialSingleton*  p_ifaceSerial
                = CInterfaceSerialSingleton::instance();

        /*
         *  From interface manager to plugin
         */
        connect( p_ifaceSerial,
                 SIGNAL(connectStateChanged(const bool&)),
                 p_pluginInterface,
                 SLOT(on_interfaceSerial_connectStateChanged(const bool&)) );

        connect( p_ifaceSerial,
                 SIGNAL(dataReceived(const QByteArray&)),
                 p_pluginInterface,
                 SLOT(on_interfaceSerial_dataReceived(const QByteArray&)) );

        connect( p_ifaceSerial,
                 SIGNAL(dataSent(const QByteArray&)),
                 p_pluginInterface,
                 SLOT(on_interfaceSerial_dataSent(const QByteArray&)) );


        /*
         *  From plugin manager to serial interface manager
         */
        connect( p_pluginInterface,
                 SIGNAL(toIfaceSerial_sendData(QByteArray)),
                 p_ifaceSerial,
                 SLOT(sendData(QByteArray)) );


        if( p_pluginInterface->floatingWidget() != nullptr )
        {
            Qt::WindowFlags lFWFlags
                    = p_pluginInterface->floatingWidget()->windowFlags();
            p_pluginInterface->floatingWidget()
                    ->setParent( CMainWindow::getInstance(),
                                 lFWFlags );

            p_pluginInterface->floatingWidget()->show();
            p_pluginInterface->floatingWidget()->raise();
        }


        if( p_pluginInterface->toolBar() != nullptr )
        {
            CMainWindow::getInstance()
                    ->addToolBar( p_pluginInterface->toolBar() );
            p_pluginInterface->toolBar()->show();
        }
    }


    if( retVal == true )
    {
        this->m_activatedPlugins.insert( argHash, argPluginContainer );
    }


    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */

bool    CPluginsManagerSingleton::pluginUnload(const QString& argHash )
{
    bool    retVal  = true;


    if( ! this->activatedPlugins().contains( argHash ) )
    {
        TRACE_ERR( "Trying to unload a plugin which is not activated !" );
        retVal  = false;
    }
    else
    {
        CPluginContainer    lPC
                = this->m_activatedPlugins.take( argHash );

        COpenserialPluginInterface* p_ifacePlugin
                = lPC.pluginInterface();

        CInterfaceSerialSingleton*  p_ifaceSerial
                = CInterfaceSerialSingleton::instance();


        disconnect( p_ifaceSerial,
                    SIGNAL(connectStateChanged(const bool&)),
                    p_ifacePlugin,
                    SLOT(on_interfaceSerial_connectStateChanged(const bool&)) );

        disconnect( p_ifaceSerial,
                    SIGNAL(dataReceived(const QByteArray&)),
                    p_ifacePlugin,
                    SLOT(on_interfaceSerial_dataReceived(const QByteArray&)) );

        disconnect( p_ifaceSerial,
                    SIGNAL(dataSent(const QByteArray&)),
                    p_ifacePlugin,
                    SLOT(on_interfaceSerial_dataSent(const QByteArray&)) );


        /*
         *  From plugin manager to serial interface manager
         */
        disconnect( p_ifacePlugin,
                    SIGNAL(toIfaceSerial_sendData(QByteArray)),
                    p_ifaceSerial,
                    SLOT(sendData(QByteArray)) );


        /*
         *  Plugin's floating widget
         */
        if( p_ifacePlugin->floatingWidget() != nullptr )
        {
            p_ifacePlugin->floatingWidget()->close();
        }


        /*
         *  Plugin's toolbar
         */
        if( p_ifacePlugin->toolBar() != nullptr )
        {
            CMainWindow::getInstance()
                    ->removeToolBar( p_ifacePlugin->toolBar() );
        }
    }


    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */

void    CPluginsManagerSingleton
        ::setActivatedPlugins(const QStringList &argActivatedPluginsList)
{
    /*
     *  Remove plugins which are not activated anymore
     */
    TRACE_DBG( "+-- Removing deactivated plugins..." )
    foreach( QString lHash, this->m_activatedPlugins.keys() )
    {
        if( argActivatedPluginsList.contains( lHash ) )
        {
            TRACE_DBG( "    +-- Plugin still activated : '%s'",
                       lHash.toStdString().c_str() );
        }
        else if( this->pluginUnload( lHash ) == false )
        {
            TRACE_ERR( "    +-- An error occured while unloading plugin '%s'.",
                       lHash.toStdString().c_str() );
        }
        else
        {
            TRACE_DBG( "    +-- Plugin '%s' has been deactivated.",
                       lHash.toStdString().c_str() );
        }
    }
    TRACE_DBG( "    +-- Done." );


    /*
     *  Add newly activated plugins
     */
    TRACE_DBG( "+-- Adding newly activated plugins..." )
    foreach( QString lHash, argActivatedPluginsList )
    {
        if( this->m_activatedPlugins.keys().contains( lHash ) )
        {
            TRACE_DBG( "    +-- Plugin is already activated : %s",
                       lHash.toStdString().c_str() );
        }
        else if( ! this->availablePlugins().keys().contains( lHash ) )
        {
            TRACE_ERR("    +-- Plugin '%s'' is not part of"
                      " the available plugins list!",
                      lHash.toStdString().c_str() );
        }
        else if( ! this->pluginLoad( lHash,
                                     this->availablePlugins().value( lHash ) ) )
        {
            TRACE_ERR( "    +-- An error occured while"
                       " loading the plugin '%s' !",
                       lHash.toStdString().c_str() );
        }
        else
        {
            TRACE_DBG( "    +-- Plugin loaded successfully : '%s'",
                       lHash.toStdString().c_str() );
        }
    }
    TRACE_DBG( "    +-- Done." );
}

/* ########################################################################## */
/* ########################################################################## */
