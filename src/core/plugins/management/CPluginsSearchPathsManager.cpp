#include "CPluginsSearchPathsManager.h"

#include <QDir>

#include <COpenserialPluginInterface.h>


/* ########################################################################## */
/* ########################################################################## */
/*
 *  Trace macros
 */
#include "core/trace/trace.h"

#if defined  QT_DEBUG && defined  TRACE_CPluginsSearchPathsManager_DEBUG
#   define TRACE_DBG(format,...)                                               \
           TRACE_DBG_BASE( format, ##__VA_ARGS__ );
#else
#   define  TRACE_DBG(format,...)
#endif

#define TRACE_INFO(format,...)                                                 \
        TRACE_INFO_BASE( format, ##__VA_ARGS__ );

#define TRACE_WARN(format,...)                                                  \
        TRACE_WARN_BASE( format, ##__VA_ARGS__ );

#define TRACE_ERR(format,...)                                                  \
        TRACE_ERR_BASE( format, ##__VA_ARGS__ );

/* ########################################################################## */
/* ########################################################################## */

CPluginsSearchPathsManager::CPluginsSearchPathsManager(QObject* argParentPtr)
    :   QObject( argParentPtr )
{

}

/* ########################################################################## */
/* ########################################################################## */

void CPluginsSearchPathsManager::addSearchPath(const QString &argPath)
{
    QString lCanonicalPath  = argPath;
//    TRACE_DBG( "lCanonicalPath == ''%s''",
//               lCanonicalPath.toStdString().c_str() );
    if( lCanonicalPath.endsWith( QDir::separator() ) )
    {
        lCanonicalPath.remove( lCanonicalPath.length() - 1,
                               1 );
//        TRACE_DBG( "lCanonicalPath == ''%s''",
//                   lCanonicalPath.toStdString().c_str() );
    }
    lCanonicalPath  = QDir().absoluteFilePath( lCanonicalPath );
//    TRACE_DBG( "lCanonicalPath == ''%s''",
//               lCanonicalPath.toStdString().c_str() );


    if( lCanonicalPath.isEmpty() )
    {
        TRACE_ERR( "Canonical path of ''%s'' is empty !",
                   argPath.toStdString().c_str() );
    }
    else if( this->m_pluginsSearchPathsList.contains( lCanonicalPath ) )
    {
        TRACE_ERR( "Canonical path of ''%s'' (''%s'') is already declared.",
                   argPath.toStdString().c_str(),
                   lCanonicalPath.toStdString().c_str() );
    }
    else
    {
        this->m_pluginsSearchPathsList.append( lCanonicalPath );
        TRACE_DBG( "Added plugin search path : ''%s''",
                   lCanonicalPath.toStdString().c_str() );
    }
}

/* ########################################################################## */
/* ########################################################################## */

QHash<QString,CPluginContainer>
        CPluginsSearchPathsManager::availablePlugins(void) const
{
    return this->m_pluginsAvailable;
}

/* ########################################################################## */
/* ########################################################################## */

QList<CPluginContainer>
        CPluginsSearchPathsManager::findPlugins(
                const QString &argSearchpath ) const
{
    QFileInfo                   lFISearchPath( argSearchpath );
    QList<CPluginContainer>     retVal;


    if( ! lFISearchPath.exists() )
    {
        TRACE_ERR( "Given path doesn't exist : '%s'",
                   argSearchpath.toStdString().c_str() );
    }
    else if( lFISearchPath.isDir() )
    {
        QDir    lDir( lFISearchPath.absoluteFilePath() );

        TRACE_DBG( "+-- Searching plugins in dir ''%s''",
                   lDir.absolutePath().toStdString().c_str() );

        foreach( QString lEntry,
                 lDir.entryList( QDir::Files | QDir::NoDotAndDotDot ) )
        {
            QString lEntryPath
                    = lDir.absoluteFilePath( lEntry );
//                    + QDir::separator() + lFISearchPath
//                    + QDir::separator() + lEntry;

            TRACE_DBG( "    +-- Trying to load ''%s''",
                       lEntryPath.toStdString().c_str() );


            TRACE_DBG( "        +-- Creating plugin container..." );
            CPluginContainer    lPluginContainer( lEntryPath );
            TRACE_DBG( "            +-- Done." );

            if( lPluginContainer.isValid() )
            {
                TRACE_DBG( "        +-- Found valid plugin" );
                retVal.append( lPluginContainer );
            }
            else
            {
                TRACE_DBG( "        +-- Not a valid plugin" );
            }
        }
    }
    else if( lFISearchPath.isFile() )
    {
        CPluginContainer    lPluginContainer(lFISearchPath.absoluteFilePath());

        if( lPluginContainer.isValid() )
        {
            retVal.append( lPluginContainer );
        }
        else
        {
            TRACE_DBG( "Not a valid plugin : ''%s''",
                       lFISearchPath.absoluteFilePath().toStdString().c_str() );
        }
    }
    else
    {
        TRACE_ERR( "Given path is not a dir nor file : '%s'",
                   argSearchpath.toStdString().c_str() );
    }


    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */

QStringList CPluginsSearchPathsManager::searchPathsList(void) const
{
    return this->m_pluginsSearchPathsList;
}

/* ########################################################################## */
/* ########################################################################## */

QHash<QString,CPluginContainer>
        CPluginsSearchPathsManager::updateAvailablePlugins(void)
{
//    QHash<QString,CPluginContainer> retVal;


    foreach( QString lPath, this->searchPathsList() )
    {
        QList<CPluginContainer> lPluginsContainersList
                = this->findPlugins( lPath );

//        retVal.insert( retVal.end(),
//                       lPluginsContainersList.begin(),
//                       lPluginsContainersList.end() );

        for(int i = 0 ; i < lPluginsContainersList.count() ; ++i )
        {
            QString lHash
                    = lPluginsContainersList.at( i ).name()
                    + lPluginsContainersList.at( i ).version();


            if( this->m_pluginsAvailable.contains( lHash ) )
            {
                TRACE_WARN( "The plugins list already contains the plugin"
                            " %s version %s",
                            lPluginsContainersList.at( i ).name()
                            .toStdString().c_str(),
                            lPluginsContainersList.at( i ).version()
                            .toStdString().c_str()
                            );
                TRACE_INFO( "+-- Previous plugin path   : %s",
                            this->m_pluginsAvailable[ lHash ].path()
                            .toStdString().c_str() );
                TRACE_INFO( "+-- New plugin path        : %s",
                            lPluginsContainersList.at( i ).path()
                            .toStdString().c_str() );
            }
            else
            {
                TRACE_DBG( "Adding new plugin with hash : %s",
                           lHash.toStdString().c_str() );
            }

            this->m_pluginsAvailable
                    .insert( lHash, lPluginsContainersList.at( i ) );
        }
    }


    return this->m_pluginsAvailable;
}

/* ########################################################################## */
/* ########################################################################## */
