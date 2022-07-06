#ifndef PLUGINIOSERVERKNADM244_H
#define PLUGINIOSERVERKNADM244_H

#include <QObject>
#include "../PluginTest/interfaceplugin.h"
#include "ioserverknadc2000m244.h"

class PluginIOServerKNaDM244 : public QObject, public InterfacePlugin, public InterfaceIOServer
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.PluginIOServerKNaDM244" FILE "pluginmetadata.json")
    Q_INTERFACES(InterfacePlugin InterfaceIOServer)
public:
    virtual bool connectServer(QString ipAddr, int port) Q_DECL_OVERRIDE;
    virtual void closeConnect() Q_DECL_OVERRIDE;
    virtual bool writeData(int DBlock, int value) Q_DECL_OVERRIDE;
    virtual int readData(int iotype, int DBlock) Q_DECL_OVERRIDE;
    virtual bool getConState() Q_DECL_OVERRIDE;
private:
    IOServerKNaDC2000M244 m_ioserver;
};

#endif // PLUGINIOSERVERKNADM244_H
