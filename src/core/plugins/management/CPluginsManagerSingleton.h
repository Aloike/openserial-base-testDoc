#ifndef CPLUGINSMANAGERSINGLETON_H
#define CPLUGINSMANAGERSINGLETON_H

#include "CPluginsSearchPathsManager.h"

#include <QStringList>


class   CPluginsManagerSingleton
        :   public  CPluginsSearchPathsManager
{
    Q_OBJECT

public:

    static CPluginsManagerSingleton*    getInstance(void);


    QHash<QString, CPluginContainer>    activatedPlugins(void) const;
    void    setActivatedPlugins( const QStringList& argActivatedPluginsList);



protected:
private:

    explicit CPluginsManagerSingleton(QObject *argParentPtr = 0);


    bool    pluginLoad( const QString& argHash,
                        const CPluginContainer &argPlugin );
    bool    pluginUnload( const QString& argHash );



public:
protected:
private:

    static CPluginsManagerSingleton*    s_p_instance;

    QHash<QString, CPluginContainer>    m_activatedPlugins;



};

#endif  /*< CPLUGINSMANAGERSINGLETON_H */
