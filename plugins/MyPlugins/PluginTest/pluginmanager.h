#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>
#include <QDir>
#include <QPluginLoader>

class PluginManagerPrivate;

class PluginManager : public QObject
{
    Q_OBJECT
public:
    static PluginManager* getInstance();
public:
    //
    QDir getPluginPath();
    //加载所有插件
    void loadAllPlugins();
    //扫描Json文件中的插件元数据
    void scan(const QString &filepath);
    //加载某个插件
    void loadPlugin(const QString &filepath);
    //卸载所有插件
    void unloadAllPlugins();
    //卸载某个插件
    void unloadPlugin(const QString &filepath);
    //获取所有插件
    QList<QPluginLoader*> allPlugins();
    //获取某个插件
    QPluginLoader* getPlugin(const QString &name);


private:
    PluginManager();
    ~PluginManager();
private:
    static PluginManager *m_instance;
    PluginManagerPrivate *d;
};

#endif // PLUGINMANAGER_H
