#ifndef IOSERVERKNADA2KDDA0A0_H
#define IOSERVERKNADA2KDDA0A0_H

#include <QtCore/qglobal.h>

#if defined(IOSERVERKNADA2KDDA0A0_LIBRARY)
#  define IOSERVERKNADA2KDDA0A0_EXPORT Q_DECL_EXPORT
#else
#  define IOSERVERKNADA2KDDA0A0_EXPORT Q_DECL_IMPORT
#endif

#include "ioserverinterface.h"
#include <QTcpServer>
#include <QTcpSocket>

class IOSERVERKNADA2KDDA0A0_EXPORT IOServerKNaDA2KDDA0A0 : public QObject, public IOServerInterface
{
    Q_OBJECT
public:
    IOServerKNaDA2KDDA0A0();
    ~IOServerKNaDA2KDDA0A0();
    virtual bool connectServer(QString ipAddr, int port) Q_DECL_OVERRIDE;
    virtual void closeConnect() Q_DECL_OVERRIDE;
    virtual bool writeData(int DBlock, int value) Q_DECL_OVERRIDE;
    virtual int readData(IOType iotype, int DBlock) Q_DECL_OVERRIDE;
    virtual bool getConState() Q_DECL_OVERRIDE;
public slots:
    virtual void slot_reconnectServer() Q_DECL_OVERRIDE;
    virtual bool slot_ClientRecvData() Q_DECL_OVERRIDE;
private:
    bool m_conState;
    QTcpSocket *m_tcpSocket;
    QString m_strIpAddr;
    int m_port;
    unsigned char m_recvMsg[17];
};

#endif // IOSERVERKNADA2KDDA0A0_H
