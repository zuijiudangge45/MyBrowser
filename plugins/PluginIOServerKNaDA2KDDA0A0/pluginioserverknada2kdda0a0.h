#ifndef PLUGINIOSERVERKNADA2KDDA0A0_H
#define PLUGINIOSERVERKNADA2KDDA0A0_H

#include <QObject>
#include "../PluginTest/interfaceplugin.h"
#include "ioserverknada2kdda0a0.h"

class PluginIOServerKNaDA2KDDA0A0 : public QObject, public InterfacePlugin, public InterfaceIOServer
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.PluginIOServerKNaDA2KDDA0A0" FILE "pluginmetadata.json")
    Q_INTERFACES(InterfacePlugin InterfaceIOServer)
public:
    virtual bool connectServer(QString ipAddr, int port) Q_DECL_OVERRIDE;
    virtual void closeConnect() Q_DECL_OVERRIDE;
    virtual bool writeData(int DBlock, int value) Q_DECL_OVERRIDE;
    virtual int readData(int iotype, int DBlock) Q_DECL_OVERRIDE;
    virtual bool getConState() Q_DECL_OVERRIDE;
private:
    IOServerKNaDA2KDDA0A0 m_ioserver;
};

#endif // PLUGINIOSERVERKNADA2KDDA0A0_H
