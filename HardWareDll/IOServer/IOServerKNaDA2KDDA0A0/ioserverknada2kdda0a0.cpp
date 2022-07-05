#include "ioserverknada2kdda0a0.h"
#include "log.h"

#include <QEventLoop>
#include <QTimer>
IOServerKNaDA2KDDA0A0::IOServerKNaDA2KDDA0A0()
{
    m_tcpSocket = nullptr;
    m_conState = false;
}

IOServerKNaDA2KDDA0A0::~IOServerKNaDA2KDDA0A0()
{
    closeConnect();
}

bool IOServerKNaDA2KDDA0A0::connectServer(QString ipAddr, int port)
{
    if(m_tcpSocket)
    {
        Log_accessControl(INFO_WARN, "The socket is connecting. Can't connect again");
        return false;
    }
    m_tcpSocket = new QTcpSocket(this);
    m_tcpSocket->connectToHost(QHostAddress(ipAddr), port);
    if(!m_tcpSocket->waitForConnected(30000))
    {
        Log_accessControl(INFO_ERROR, "ipAddr: %s, port: %d, error: %s", ipAddr.toStdString().c_str(), port, m_tcpSocket->errorString().toStdString().c_str());
        m_conState = false;
        return false;
    }
    else
    {
        connect(m_tcpSocket, &QTcpSocket::readyRead, this, &IOServerKNaDA2KDDA0A0::slot_ClientRecvData);
        connect(m_tcpSocket, &QTcpSocket::disconnected, this, &IOServerKNaDA2KDDA0A0::slot_reconnectServer);
        m_strIpAddr = ipAddr;
        m_port = port;
        m_conState = true;
        return true;
    }
}

void IOServerKNaDA2KDDA0A0::closeConnect()
{
    if(m_tcpSocket)
    {
        m_tcpSocket->disconnect();
        m_tcpSocket->disconnectFromHost();
        if (m_tcpSocket->state() == QAbstractSocket::UnconnectedState || m_tcpSocket->waitForDisconnected(3000))
        {
            delete m_tcpSocket;
            m_tcpSocket = nullptr;
            m_conState = false;
        }
    }
}

bool IOServerKNaDA2KDDA0A0::writeData(int DBlock, int value)
{
    unsigned char WriteData[12]={0};
    WriteData[0]=0x00;
    WriteData[1]=0x01;
    WriteData[2]=0x00;
    WriteData[3]=0x00;
    WriteData[4]=0x00;
    WriteData[5]=0x06;
    //010300190004
    WriteData[6]=0xFF;              //
    WriteData[7]=0x05;              //
    WriteData[8]=0x00;              //8、9是起始寄存器地址

    if(DBlock==0)
    {        //DO0
        WriteData[9]=0x64;
    }
    else if(DBlock==1)
    {        //DO1
        WriteData[9]=0x65;
    }
    else if(DBlock==2)
    {        //DO2
        WriteData[9]=0x66;
    }
    else if(DBlock==3)
    {        //DO3
        WriteData[9]=0x67;
    }
    else if(DBlock==4)
    {        //DO1
        WriteData[9]=0x68;
    }
    else if(DBlock==5)
    {        //DO2
        WriteData[9]=0x69;
    }
    else if(DBlock==6)
    {        //DO3
        WriteData[9]=0x6A;
    }
    else if(DBlock==7)
    {        //DO1
        WriteData[9]=0x6B;
    }
    else if(DBlock==8)
    {        //DO2
        WriteData[9]=0x6C;
    }
    else if(DBlock==9)
    {        //DO3
        WriteData[9]=0x6D;
    }
    else if(DBlock==10)
    {        //DO1
        WriteData[9]=0x6E;
    }
    else if(DBlock==11)
    {        //DO2
        WriteData[9]=0x6F;
    }
    else if(DBlock==12)
    {        //DO3
        WriteData[9]=0x70;
    }
    else if(DBlock==13)
    {        //DO1
        WriteData[9]=0x71;
    }
    else if(DBlock==14)
    {        //DO2
        WriteData[9]=0x72;
    }
    else if(DBlock==15)
    {        //DO3
        WriteData[9]=0x73;
    }
    else
    {
        return false;
    }

    if(value > 0)
    {
        WriteData[10]=0xFF;
        WriteData[11]=0x00;
    }
    else
    {
        WriteData[10]=0x00;
        WriteData[11]=0x00;
    }

    int sendRe = m_tcpSocket->write((const char*)WriteData, 12);
    if(sendRe == -1)
    {
        return false;
    }
    else
        return true;
}

int IOServerKNaDA2KDDA0A0::readData(IOServerInterface::IOType iotype, int DBlock)
{
    unsigned char ReadData[12];
    ReadData[0]=0x00;
    ReadData[1]=0x01;
    ReadData[2]=0x00;
    ReadData[3]=0x00;
    ReadData[4]=0x00;
    ReadData[5]=0x06;
    ReadData[6]=0xFF;

    ReadData[8]=0x00;

    ReadData[10]=0x00;
    ReadData[11]=0x10;

    if(iotype == DO)                 //0 - 读输入；1 - 读输出
    {
        ReadData[7]=0x01;            //功能码

        ReadData[9]=0x64;            //起始寄存器地址
    }
    else if(iotype == DI)
    {
        ReadData[7]=0x02;

        ReadData[9]=0xC8;
    }
    else
    {
        return -1;
    }
    qDebug()<<"ReadData : " << QByteArray((char*)ReadData, sizeof(ReadData));
    int sendRe = m_tcpSocket->write((const char*)ReadData, sizeof(ReadData));
    if(sendRe == -1)
    {
        qDebug()<<"socket 读数据有误";
        return -1;
    }

    QTimer timer;
    timer.setSingleShot(true);

    QEventLoop eventLoop;

    connect(m_tcpSocket, &QIODevice::readyRead, &eventLoop, &QEventLoop::quit);
    connect(&timer,SIGNAL(timeout()),&eventLoop,SLOT(quit()));

    timer.start(200);

    eventLoop.exec(QEventLoop::ExcludeUserInputEvents);

    disconnect(m_tcpSocket, &QIODevice::readyRead, &eventLoop, &QEventLoop::quit);
    disconnect(&timer,&QTimer::timeout,&eventLoop,&QEventLoop::quit);


    if(DBlock == 0)
    {
        return m_recvMsg[9] & 0x01;
    }
    else if(DBlock == 1)
    {
        return (m_recvMsg[9] & 0x02) > 0 ? 1 : 0;
    }
    else if(DBlock == 2)
    {
        return (m_recvMsg[9] & 0x04) >> 2;
    }
    else if (DBlock == 3)
    {
        return (m_recvMsg[9] & 0x08) >> 3;
    }
    else if(DBlock == 4)
    {
        return (m_recvMsg[9] & 0x10) >> 4;
    }
    else if(DBlock == 5)
    {
        return (m_recvMsg[9] & 0x20) >> 5;
    }
    else if(DBlock == 6)
    {
        return (m_recvMsg[9] & 0x40) >> 6;
    }
    else if (DBlock == 7)
    {
        return (m_recvMsg[9] & 0x80) >> 7;
    }
    else if(DBlock == 8)
    {
        return m_recvMsg[10] & 0x01;
    }
    else if(DBlock == 9)
    {
        return (m_recvMsg[10] & 0x02) > 0 ? 1 : 0;
    }
    else if(DBlock == 10)
    {
        return (m_recvMsg[10] & 0x04) >> 2;
    }
    else if (DBlock == 11)
    {
        return (m_recvMsg[10] & 0x08) >> 3;
    }
    else if(DBlock == 12)
    {
        return (m_recvMsg[10] & 0x10) >> 4;
    }
    else if(DBlock == 13)
    {
        return (m_recvMsg[10] & 0x20) >> 5;
    }
    else if(DBlock == 14)
    {
        return (m_recvMsg[10] & 0x40) >> 6;
    }
    else if (DBlock == 15)
    {
        return (m_recvMsg[10] & 0x80) >> 7;
    }
    else
    {
        return -1;
    }
    return -1;
}

bool IOServerKNaDA2KDDA0A0::getConState()
{
    return m_conState;
}

void IOServerKNaDA2KDDA0A0::slot_reconnectServer()
{
    m_conState = false;
    delete  m_tcpSocket;
    m_tcpSocket = nullptr;
    m_tcpSocket = new QTcpSocket(this);
    m_tcpSocket->connectToHost(m_strIpAddr, m_port);

    if(!m_tcpSocket->waitForConnected(3000))
    {
        //重连失败
        delete  m_tcpSocket;
        m_tcpSocket = nullptr;
        Log_accessControl(INFO_ERROR, "The connection has been disconnected. Reconnection failed!");
    }
    else
    {
        connect(m_tcpSocket, &QTcpSocket::readyRead, this, &IOServerKNaDA2KDDA0A0::slot_ClientRecvData);
        connect(m_tcpSocket, &QTcpSocket::disconnected, this, &IOServerKNaDA2KDDA0A0::slot_reconnectServer);
        m_conState = true;
    }
}

bool IOServerKNaDA2KDDA0A0::slot_ClientRecvData()
{
    memset(m_recvMsg, 0, sizeof(m_recvMsg));
    int recvRe = m_tcpSocket->read((char*)m_recvMsg, 1024);
    if(recvRe == -1)
    {
        Log_accessControl(INFO_ERROR, "clientRecvData is error, errorstr: read message error");
        return false;
    }
    Log_accessControl(INFO_TRACE, "clientRecvData is successful, get %d bytes, recvMsg :", recvRe, m_recvMsg);

    //    qDebug()<<"recvMsg : "<< QByteArray((char*)m_recvMsg, sizeof(m_recvMsg));
    return true;
}
