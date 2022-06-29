#include "plugincardreaddonsee.h"

bool PluginCardReadDonsee::init(int port, int baudRate)
{
    return m_cardReader.init(port, baudRate);
}

void PluginCardReadDonsee::beep(int msec)
{
    m_cardReader.beep(msec);
}

QString PluginCardReadDonsee::cardId()
{
    return m_cardReader.cardId();
}

bool PluginCardReadDonsee::ResetToInitPwd()
{
    return m_cardReader.ResetToInitPwd();
}

bool PluginCardReadDonsee::initCardPwd()
{
    return m_cardReader.initCardPwd();
}

bool PluginCardReadDonsee::read(unsigned char secNr, unsigned char _Adr, QString &data)
{
    return m_cardReader.read(secNr, _Adr, data);
}

bool PluginCardReadDonsee::write(unsigned char secNr, unsigned char _Adr, QString _Data)
{
    return m_cardReader.write(secNr, _Adr, _Data);
}
