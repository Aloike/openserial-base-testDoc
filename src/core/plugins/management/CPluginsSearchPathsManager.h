#ifndef CPLUGINSSEARCHPATHSMANAGER_H
#define CPLUGINSSEARCHPATHSMANAGER_H

#include <QObject>

#include <memory>

#include <QList>
#include <QPluginLoader>
#include <QStringList>

#include "CPluginContainer.h"


class   CPluginsSearchPathsManager
        :   public  QObject
{
    Q_OBJECT

public:

    CPluginsSearchPathsManager(QObject* argParentPtr=nullptr);

    void        addSearchPath(const QString& argPath);
    QStringList searchPathsList(void) const;


    QHash<QString, CPluginContainer>    updateAvailablePlugins(void);
    QHash<QString, CPluginContainer>    availablePlugins(void) const;



protected:
private:

    QList<CPluginContainer> findPlugins( const QString& argSearchpath ) const;

//    std::shared_ptr<QPluginLoader>
//            tryCreatePluginLoader( const QString& argFilePath ) const;



public:
protected:
private:

    QHash<QString,CPluginContainer> m_pluginsAvailable;
    QStringList                     m_pluginsSearchPathsList;



};

#endif  /*< CPLUGINSSEARCHPATHSMANAGER_H */
