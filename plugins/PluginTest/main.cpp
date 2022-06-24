#include <QCoreApplication>
#include <QPluginLoader>
#include <QDir>
#include <QtDebug>
#include <QJsonObject>
#include <QJsonArray>
#include "pluginmwrfeyeinterface.h"

#include "Plugin.h"

void loadPlugin()
{
    QDir pluginsDir(qApp->applicationDirPath());
    pluginsDir.cd("plugins");
    qDebug()<<pluginsDir;

    foreach(QString fileName, pluginsDir.entryList(QDir::Files))
    {
        // 判断是否是库
        if (!QLibrary::isLibrary(fileName))
            continue;

        QPluginLoader loader(pluginsDir.absoluteFilePath(fileName));
        //返回插件的根组件对象
        QObject *pPlugin = loader.instance();
        if(pPlugin != Q_NULLPTR)
        {
            QJsonObject jsonObj = loader.metaData().value("MetaData").toObject();
            qDebug()<< "*********MetaData**********";
            qDebug()<< jsonObj.value("author").toVariant();
            qDebug()<< jsonObj.value("date").toVariant();
            qDebug()<< jsonObj.value("name").toVariant();
            qDebug()<< jsonObj.value("version").toVariant();
            qDebug()<< jsonObj.value("dependencies").toArray().toVariantList();

            //
//            Plugin *plugin = qobject_cast<Plugin *>(pPlugin);
            Plugin *plugin = dynamic_cast<Plugin *>(pPlugin);
            if (plugin != nullptr) {
                qDebug()<< "This is my plugin!";
            }
            else
            {
                qDebug()<< "This is not my plugin!";
            }

            //访问接口
            PluginMwRfEyeInterface *PInterface = qobject_cast<PluginMwRfEyeInterface *>(pPlugin);
            if(PInterface != Q_NULLPTR)
            {
//                PInterface->beep(50);
//                PInterface->beep(50);
//                PInterface->beep(50);
            }
            else
            {
                qWarning()<< "qobject_cast failed";
            }
        }
        else
        {
            qWarning()<< "load plugin failed";
        }
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    loadPlugin();
    return a.exec();
}
