#ifndef CPLUGINCONTAINER_H
#define CPLUGINCONTAINER_H

#include <QObject>

#include <memory>

#include <QPluginLoader>

#include <COpenserialPluginInterface.h>


class   CPluginContainer
        :   public  QObject
{
    Q_OBJECT

public:

    explicit CPluginContainer( const QString& argFileName=QString());
    CPluginContainer(const CPluginContainer& argOther);

//    ~CPluginContainer() {}

    CPluginContainer&   operator=(const CPluginContainer& argSrc);


    bool    isValid(void) const;


    bool    loadPlugin(const QString& argPluginPath);


    QString path(void) const;
    QString name(void) const;
    QString nameHumanReadable(void) const;
    QString version(void) const;
    QString description(void) const;


    std::shared_ptr<QPluginLoader>  pluginLoaderShrdPtr(void) const;
    COpenserialPluginInterface*     pluginInterface(void) const;



protected:
private:



public:
protected:
private:

    std::shared_ptr<QPluginLoader>  m_pluginLoaderShrdPtr;
    QString                         m_pluginPath;



};

#endif  /*< CPLUGINCONTAINER_H */
