#include "pluginmanager.h"
#include "pluginmanagerprivate.h"
#include "interfaceplugin.h"
#include <QApplication>
#include <QJsonObject>
#include <QJsonArray>
#include <QFileInfo>

PluginManager* PluginManager::m_instance = nullptr;

PluginManager::PluginManager()
{
    d = new PluginManagerPrivate;
}

PluginManager::~PluginManager()
{
    delete d;
    d = nullptr;

    delete m_instance;
    m_instance = nullptr;
}

PluginManager *PluginManager::getInstance()
{
    if(m_instance == nullptr)
        m_instance = new PluginManager;
    return m_instance;
}

QDir PluginManager::getPluginPath()
{
    QDir path(qApp->applicationDirPath());
    path.cd("./plugins");
    return path;
}

void PluginManager::loadAllPlugins()
{
    //获取插件目录
    QDir path(getPluginPath());
    //加载插件元数据
    foreach(QFileInfo info, path.entryInfoList(QDir::Files | QDir::NoDotAndDotDot))
    {
        scan(info.absoluteFilePath());
    }
    //加载插件
    foreach(QFileInfo info, path.entryInfoList(QDir::Files | QDir::NoDotAndDotDot))
    {
        loadPlugin(info.absoluteFilePath());
    }
}

void PluginManager::scan(const QString &filepath)
{
    if(!QLibrary::isLibrary(filepath))  //判断是否是库（后缀有效性） * Windows：.dll、.DLL * Unix/Linux：.so
        return;

    QPluginLoader loader(filepath);
    QJsonObject json = loader.metaData().value("MetaData").toObject();

    d->m_names.insert(filepath, json.value("name").toVariant());
    d->m_versions.insert(filepath, json.value("version").toVariant());
    d->m_dependencies.insert(filepath, json.value("dependencies").toArray().toVariantList());
}

void PluginManager::loadPlugin(const QString &filepath)
{
    if(!QLibrary::isLibrary(filepath))  //判断是否是库（后缀有效性） * Windows：.dll、.DLL * Unix/Linux：.so
        return;

    if(!d->check(filepath))
        return;

    //加载插件
    QPluginLoader *loader = new QPluginLoader(filepath);
    if(loader->load())
    {
        InterfacePlugin *plugin = qobject_cast<InterfacePlugin*>(loader->instance());
        if(plugin)
        {
            d->m_loaders.insert(filepath, loader);
        }
        else
        {
            delete loader;
            loader = nullptr;
        }
    }
}

void PluginManager::unloadAllPlugins()
{
    foreach(const QString &path, d->m_loaders.keys())
    {
        unloadPlugin(path);
    }
}

void PluginManager::unloadPlugin(const QString &filepath)
{
    QPluginLoader *loader = d->m_loaders.value(filepath);

    //卸载插件
    if(loader->unload())
    {
        d->m_dependencies.remove(filepath);
        delete loader;
        loader = nullptr;
    }
}

QList<QPluginLoader *> PluginManager::allPlugins()
{
    return d->m_loaders.values();
}

QPluginLoader *PluginManager::getPlugin(const QString &name)
{
    return d->m_loaders.value(d->m_names.key(name));
}
