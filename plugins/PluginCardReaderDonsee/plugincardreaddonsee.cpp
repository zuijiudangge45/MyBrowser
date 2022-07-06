#include "plugincardreaddonsee.h"

bool PluginCardReadDonsee::init(int port, int baudRate)
{
    return m_cardReader.init(port, baudRate);
}

void PluginCardReadDonsee::exit()
{
    m_cardReader.exit();
}

void PluginCardReadDonsee::beep(int msec)
{
    m_cardReader.beep(msec);
}

QString PluginCardReadDonsee::cardId()
{
    return m_cardReader.cardId();
}

bool PluginCardReadDonsee::ResetPwd()
{
    return m_cardReader.ResetPwd();
}

bool PluginCardReadDonsee::SetDeafultPwd()
{
    return m_cardReader.SetDeafultPwd();
}

bool PluginCardReadDonsee::read(int secNr, int dataAdr, QString &data)
{
    return m_cardReader.read(secNr, dataAdr, data);
}

bool PluginCardReadDonsee::write(int secNr, int dataAdr, const QString &data)
{
    return m_cardReader.write(secNr, dataAdr, data);
}

void PluginCardReadDonsee::setCallBack(MSGCardCallBack msgCardCallBack)
{
    m_cardReader.setCallBack(msgCardCallBack);
}
