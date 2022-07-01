#ifndef IOSERVERKNADC2000M244_H
#define IOSERVERKNADC2000M244_H

#include <QtCore/qglobal.h>

#if defined(IOSERVERKNADC2000M244_LIBRARY)
#  define IOSERVERKNADC2000M244_EXPORT Q_DECL_EXPORT
#else
#  define IOSERVERKNADC2000M244_EXPORT Q_DECL_IMPORT
#endif

#include "ioserverinterface.h"
#include <QTcpServer>
#include <QTcpSocket>

class IOSERVERKNADC2000M244_EXPORT IOServerKNaDC2000M244 : public QObject, public IOServerInterface
{
    Q_OBJECT
public:
    IOServerKNaDC2000M244();
    ~IOServerKNaDC2000M244();
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

#endif // IOSERVERKNADC2000M244_H
