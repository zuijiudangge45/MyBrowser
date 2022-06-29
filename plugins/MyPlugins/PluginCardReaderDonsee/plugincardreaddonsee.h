#ifndef PLUGINCARDREADDONSEE_H
#define PLUGINCARDREADDONSEE_H

#include <QObject>
#include "../PluginTest/interfaceplugin.h"
#include "cardreaderdonsee.h"
class PluginCardReadDonsee : public QObject, public InterfacePlugin, public CardReaderInterface
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.PluginCardReaderDonsee" FILE "pluginmetadata.json")
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
    CardReaderDonsee m_cardReader;
};

#endif // PLUGINCARDREADDONSEE_H
