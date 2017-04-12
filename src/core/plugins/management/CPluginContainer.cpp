#include "CPluginContainer.h"

/* ########################################################################## */
/* ########################################################################## */
/*
 *  Trace macros
 */
#include "core/trace/trace.h"

#if defined  QT_DEBUG && defined  TRACE_CPluginContainer_DEBUG
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

CPluginContainer::CPluginContainer(const CPluginContainer &argOther)
    :   QObject()
    ,   m_pluginLoaderShrdPtr( argOther.m_pluginLoaderShrdPtr )
    ,   m_pluginPath( argOther.m_pluginPath )
{
    TRACE_DBG( "+-- Copying entity" );
    TRACE_DBG( "    +-- name == %s",
               argOther.name().toStdString().c_str() );
    TRACE_DBG( "    +-- Done" );
}

/* ########################################################################## */
/* ########################################################################## */

CPluginContainer::CPluginContainer(const QString &argFileName)
    :   QObject()
    ,   m_pluginLoaderShrdPtr( new QPluginLoader() )
    ,   m_pluginPath()
{
    TRACE_DBG( "+-- Instanciating new entity" );
    TRACE_DBG( "    +-- argFileName == %s", argFileName.toStdString().c_str() );

    if( ! argFileName.isEmpty() )
    {
        this->loadPlugin( argFileName );
    }

    TRACE_DBG( "    +-- Done" );
}

/* ########################################################################## */
/* ########################################################################## */

CPluginContainer&   CPluginContainer::operator=(const CPluginContainer& argSrc)
{
    TRACE_DBG( "Operator '='" );

    if( this != &argSrc )
    {
        this->m_pluginLoaderShrdPtr = argSrc.m_pluginLoaderShrdPtr;
        this->m_pluginPath          = argSrc.m_pluginPath;
    }


    return *this;
}

/* ########################################################################## */
/* ########################################################################## */

QString CPluginContainer::description(void) const
{
    return this->pluginLoaderShrdPtr().get()->metaData()
            .value("MetaData").toObject()
            .value("description").toString( tr("No description available.") );
}

/* ########################################################################## */
/* ########################################################################## */

QString CPluginContainer::editorName(void) const
{
    return this->pluginLoaderShrdPtr().get()->metaData()
            .value("MetaData").toObject()
            .value("editor").toString( tr("No editor name provided.") );
}

/* ########################################################################## */
/* ########################################################################## */

bool    CPluginContainer::isValid(void) const
{
    bool    retVal  = true;


    if( ! this->pluginLoaderShrdPtr().get()->isLoaded() )
    {
        TRACE_DBG( "Not loaded." );
        retVal  = false;
    }
    else if( this->pluginInterface() == 0 )
    {
        TRACE_DBG( "Bad plugin interface." );
        retVal  = false;
    }
    else
    {
        retVal  = true;
    }


    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */

bool    CPluginContainer::loadPlugin(const QString &argPluginPath)
{
    std::shared_ptr<QPluginLoader>  lPluginLoaderShrdPtr(new QPluginLoader);
    COpenserialPluginInterface*     lPluginPtr              = 0;

    bool    retVal  = true;


    TRACE_DBG( "+-- Trying to load : '%s'",
               argPluginPath.toStdString().c_str() );

    /*
     *  Try to load the file as a plugin
     */
    lPluginLoaderShrdPtr.get()->setFileName( argPluginPath );
    if( lPluginLoaderShrdPtr.get()->load() == false )
    {
        TRACE_DBG( "    +-- Can't load file as plugin" );
        retVal  = false;
    }

    /*
     *  Verify that the loaded plugin implements the expected interface
     */
    else if(    (lPluginPtr = qobject_cast<COpenserialPluginInterface *>(
                                    lPluginLoaderShrdPtr.get()->instance() ) )
             == 0 )
    {
        TRACE_DBG( "    +-- Can't cast plugin to expected interface type" );
        retVal  = false;
    }


    /*
     *  Define the newly instanciated plugin loader as this object's one
     */
    else
    {
        this->m_pluginLoaderShrdPtr.swap( lPluginLoaderShrdPtr );
        this->m_pluginPath  = argPluginPath;
    }


    if( retVal == true )
    {
        TRACE_DBG( "    +-- Plugin loaded successfully : %s version %s",
                   this->name().toStdString().c_str(),
                   this->version().toStdString().c_str() );
    }
    else
    {
        TRACE_ERR( "Error while loading plugin ''%s'' : %s",
                   argPluginPath.toStdString().c_str(),
                   lPluginLoaderShrdPtr.get()->errorString()
                   .toStdString().c_str() );
    }


    return retVal;
}

/* ########################################################################## */
/* ########################################################################## */

QString CPluginContainer::name(void) const
{
    return this->pluginLoaderShrdPtr().get()->metaData()
            .value("MetaData").toObject()
            .value("name").toString("[[unknown name]]");
}

/* ########################################################################## */
/* ########################################################################## */

QString CPluginContainer::nameHumanReadable(void) const
{
    return this->pluginLoaderShrdPtr().get()->metaData()
            .value("MetaData").toObject()
            .value("nameHumanReadable").toString("[[unknown name]]");
}

/* ########################################################################## */
/* ########################################################################## */

QString CPluginContainer::path(void) const
{
    return this->m_pluginPath;
}

/* ########################################################################## */
/* ########################################################################## */

COpenserialPluginInterface* CPluginContainer::pluginInterface(void) const
{
    return  qobject_cast<COpenserialPluginInterface *>(
                    this->m_pluginLoaderShrdPtr.get()->instance() );
}

/* ########################################################################## */
/* ########################################################################## */

std::shared_ptr<QPluginLoader>
        CPluginContainer::pluginLoaderShrdPtr(void) const
{
    return this->m_pluginLoaderShrdPtr;
}

/* ########################################################################## */
/* ########################################################################## */

QString CPluginContainer::projectURL(void) const
{
    return this->pluginLoaderShrdPtr().get()->metaData()
            .value("MetaData").toObject()
            .value("projectURL").toString( tr("(No website provided)") );
}

/* ########################################################################## */
/* ########################################################################## */

QString CPluginContainer::version(void) const
{
    return this->pluginLoaderShrdPtr().get()->metaData()
            .value("MetaData").toObject()
            .value("version").toString("[[unknown version]]");
}

/* ########################################################################## */
/* ########################################################################## */
