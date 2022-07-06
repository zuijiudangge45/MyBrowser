#include "plugincardreadermwrfeye.h"

bool PluginCardReaderMwRfEye::init(int port, int baudRate)
{
    Q_UNUSED(port);
    Q_UNUSED(baudRate);

    return m_cardReader.init();
}

void PluginCardReaderMwRfEye::exit()
{
    m_cardReader.exit();
}

void PluginCardReaderMwRfEye::beep(int msec)
{
    m_cardReader.beep(msec);
}

QString PluginCardReaderMwRfEye::cardId()
{
    return m_cardReader.cardId();
}

bool PluginCardReaderMwRfEye::ResetPwd()
{
    return m_cardReader.ResetPwd();
}

bool PluginCardReaderMwRfEye::SetDeafultPwd()
{
    return m_cardReader.SetDeafultPwd();
}

bool PluginCardReaderMwRfEye::read(int secNr, int dataAdr, QString &data)
{
    return m_cardReader.read(secNr, dataAdr, data);
}

bool PluginCardReaderMwRfEye::write(int secNr, int dataAdr, const QString &data)
{
    return m_cardReader.write(secNr, dataAdr, data);
}

void PluginCardReaderMwRfEye::setCallBack(MSGCardCallBack msgCardCallBack)
{
    m_cardReader.setCallBack(msgCardCallBack);
}
