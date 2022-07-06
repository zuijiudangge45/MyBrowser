#ifndef PLUGINCARDREADERMWRFEYE_H
#define PLUGINCARDREADERMWRFEYE_H

#include <QObject>
#include "../PluginTest/interfaceplugin.h"
#include "readermwrfeye.h"
class PluginCardReaderMwRfEye : public QObject, public InterfacePlugin, public CardReaderInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.PluginCardReaderMwRfEye" FILE "pluginmetadata.json")
    Q_INTERFACES(InterfacePlugin CardReaderInterface)
public:
    virtual bool init(int port, int baudRate) Q_DECL_OVERRIDE;
    virtual void exit() Q_DECL_OVERRIDE;
    virtual void beep(int msec) Q_DECL_OVERRIDE;
    virtual QString cardId() Q_DECL_OVERRIDE;
    virtual bool ResetPwd() Q_DECL_OVERRIDE;
    virtual bool SetDeafultPwd() Q_DECL_OVERRIDE;
    virtual bool read(int secNr, int dataAdr, QString &data) Q_DECL_OVERRIDE;
    virtual bool write(int secNr, int dataAdr, const QString &data) Q_DECL_OVERRIDE;
    virtual void setCallBack(MSGCardCallBack msgCardCallBack) override;
private:
    ReaderMWRFEYE m_cardReader;
};

#endif // PLUGINCARDREADERMWRFEYE_H
