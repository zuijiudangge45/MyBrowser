#include "pluginmanagerprivate.h"

bool PluginManagerPrivate::check(const QString &filepath)
{
    bool status = true;

    foreach(QVariant item, m_dependencies.value(filepath))
    {
        QVariantMap map = item.toMap();
        QVariant name = map.value("name");          //依赖的插件的名称
        QVariant version = map.value("version");    //依赖的插件的版本
        QString path = m_names.key(name);            //依赖的插件的路径

        //检测插件是否依赖于其他插件
        //先检查插件名称
        if (!m_names.values().contains(name)) {
            qDebug() << Q_FUNC_INFO << "  Missing dependency:" << name.toString() << "for plugin" << path;
            status = false;
            continue;
        }
        // 再检测插件版本
        if (m_versions.value(path) != version) {
            qDebug() << Q_FUNC_INFO << "    Version mismatch:" << name.toString() << "version"
                     << m_versions.value(m_names.key(name)).toString() << "but" << version.toString() << "required for plugin" << path;
            status = false;
            continue;
        }
        // 然后，检测被依赖的插件是否还依赖于另外的插件
        if (!check(path)) {
            qDebug() << Q_FUNC_INFO << "Corrupted dependency:" << name.toString() << "for plugin" << path;
            status = false;
            continue;
        }
    }

    return status;
}
