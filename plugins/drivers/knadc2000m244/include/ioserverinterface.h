#ifndef IOSERVERINTERFACE_H
#define IOSERVERINTERFACE_H

#include <QString>

class IOServerInterface
{
public:
    enum IOType{ DI = 0, DO};
    virtual bool connectServer(QString ipAddr, int port) = 0;
    virtual void closeConnect() = 0;
    virtual bool writeData(int DBlock, int value) = 0;
    virtual int readData(IOType iotype, int DBlock) = 0;
    virtual bool getConState() = 0;
    virtual void slot_reconnectServer() = 0;
    virtual bool slot_ClientRecvData() = 0;
};

#endif // IOSERVERINTERFACE_H
