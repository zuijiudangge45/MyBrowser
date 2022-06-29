#ifndef PLUGINMANAGERPRIVATE_H
#define PLUGINMANAGERPRIVATE_H
#include <QString>
#include <QVariant>
#include <QDebug>
#include <QPluginLoader>
class PluginManagerPrivate
{
public:
    //插件依赖检测
    bool check(const QString &filepath);

    QHash<QString,QVariant> m_names;             //插件路径--插件名称
    QHash<QString,QVariant> m_versions;         //插件路径--插件版本
    QHash<QString,QVariantList> m_dependencies; //插件路径--插件依赖的其他插件列表
    QHash<QString,QPluginLoader*> m_loaders;    //插件路径--插件的加载实例

};

#endif // PLUGINMANAGERPRIVATE_H
