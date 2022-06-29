#include "plugincardreadermwrfeye.h"

bool PluginCardReaderMwRfEye::init(int port, int baudRate)
{
    return m_cardReader.init(port, baudRate);
}

void PluginCardReaderMwRfEye::beep(int msec)
{
    m_cardReader.beep(msec);
}

QString PluginCardReaderMwRfEye::cardId()
{
    return m_cardReader.cardId();
}

bool PluginCardReaderMwRfEye::ResetToInitPwd()
{
    return m_cardReader.ResetToInitPwd();
}

bool PluginCardReaderMwRfEye::initCardPwd()
{
    return m_cardReader.initCardPwd();
}

bool PluginCardReaderMwRfEye::read(unsigned char secNr, unsigned char _Adr, QString &data)
{
    return m_cardReader.read(secNr, _Adr, data);
}

bool PluginCardReaderMwRfEye::write(unsigned char secNr, unsigned char _Adr, QString _Data)
{
    return m_cardReader.write(secNr, _Adr, _Data);
}
