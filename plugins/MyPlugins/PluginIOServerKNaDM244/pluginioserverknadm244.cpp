#include "pluginioserverknadm244.h"

bool PluginIOServerKNaDM244::connectServer(QString ipAddr, int port)
{
    return m_ioserver.connectServer(ipAddr, port);
}

void PluginIOServerKNaDM244::closeConnect()
{
    m_ioserver.closeConnect();
}

bool PluginIOServerKNaDM244::writeData(int DBlock, int value)
{
    return m_ioserver.writeData(DBlock, value);
}

int PluginIOServerKNaDM244::readData(int iotype, int DBlock)
{
    return m_ioserver.readData(static_cast<IOServerInterface::IOType>(iotype), DBlock);
}

bool PluginIOServerKNaDM244::getConState()
{
    return m_ioserver.getConState();
}
