#ifndef PLUGINCARDREADERMWRFEYE_H
#define PLUGINCARDREADERMWRFEYE_H

#include <QObject>
#include "../PluginTest/interfaceplugin.h"
#include "dll_rf_eye.h"
class PluginCardReaderMwRfEye : public QObject, public InterfacePlugin, public CardReaderInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.PluginCardReaderMwRfEye" FILE "pluginmetadata.json")
    Q_INTERFACES(InterfacePlugin CardReaderInterface)
public:
    virtual bool init(int port, int baudRate) Q_DECL_OVERRIDE;
    virtual void beep(int msec) Q_DECL_OVERRIDE;
    virtual QString cardId() Q_DECL_OVERRIDE;
    virtual bool ResetToInitPwd() Q_DECL_OVERRIDE;
    virtual bool initCardPwd() Q_DECL_OVERRIDE;
    virtual bool read(unsigned char secNr, unsigned char _Adr, QString &data) Q_DECL_OVERRIDE;
    virtual bool write(unsigned char secNr, unsigned char _Adr, QString _Data) Q_DECL_OVERRIDE;
private:
    Dll_rf_eye m_cardReader;
};

#endif // PLUGINCARDREADERMWRFEYE_H
