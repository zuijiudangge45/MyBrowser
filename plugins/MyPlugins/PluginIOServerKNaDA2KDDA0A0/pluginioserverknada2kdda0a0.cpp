#include "pluginioserverknada2kdda0a0.h"

bool PluginIOServerKNaDA2KDDA0A0::connectServer(QString ipAddr, int port)
{
    return m_ioserver.connectServer(ipAddr, port);
}

void PluginIOServerKNaDA2KDDA0A0::closeConnect()
{
    m_ioserver.closeConnect();
}

bool PluginIOServerKNaDA2KDDA0A0::writeData(int DBlock, int value)
{
    return m_ioserver.writeData(DBlock, value);
}

int PluginIOServerKNaDA2KDDA0A0::readData(int iotype, int DBlock)
{
    return m_ioserver.readData(static_cast<IOServerInterface::IOType>(iotype), DBlock);
}

bool PluginIOServerKNaDA2KDDA0A0::getConState()
{
    return m_ioserver.getConState();
}
