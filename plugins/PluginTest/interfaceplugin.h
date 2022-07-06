#ifndef INTERFACEPLUGIN_H
#define INTERFACEPLUGIN_H

#include <QtPlugin>

typedef void (__stdcall *MSGCardCallBack)(const char *cardId);

class InterfacePlugin
{
public:
    virtual ~InterfacePlugin() {}   //虚析构函数是为了解决基类的指针指向派生类对象时，用基类的指针删除派生类对象会调用派生类的析构函数。
};

class CardReaderInterface
{
public:
    virtual ~CardReaderInterface() {};

    virtual bool init(int port, int baudRate) = 0;
    virtual void exit() = 0;
    virtual void beep(int msec) = 0;
    virtual QString cardId() = 0;
    virtual bool ResetPwd() = 0;
    virtual bool SetDeafultPwd() = 0;
    virtual bool read(int secNr, int dataAdr, QString &data) = 0;
    virtual bool write(int secNr, int dataAdr, const QString &data) = 0;
    virtual void setCallBack(MSGCardCallBack msgCardCallBack) = 0;
};

class InterfaceIOServer
{
public:
    virtual ~InterfaceIOServer() {};

    virtual bool connectServer(QString ipAddr, int port) = 0;
    virtual void closeConnect() = 0;
    virtual bool writeData(int DBlock, int value) = 0;
    virtual int readData(int iotype, int DBlock) = 0;
    virtual bool getConState() = 0;
};

QT_BEGIN_NAMESPACE
//
#define InterfacePlugin_iid "YJ.Plugin.PluginInterface"
Q_DECLARE_INTERFACE(InterfacePlugin, InterfacePlugin_iid);
//
#define pluginCardReaderInterface_iid "org.qt-project.Qt.PluginCardReaderInterface/1.0"
Q_DECLARE_INTERFACE(CardReaderInterface, pluginCardReaderInterface_iid);
//
#define pluginIOServerInterface_iid "org.qt-project.Qt.PluginIOServerInterface/1.0"
Q_DECLARE_INTERFACE(InterfaceIOServer, pluginIOServerInterface_iid);
QT_END_NAMESPACE



#endif // INTERFACEPLUGIN_H
