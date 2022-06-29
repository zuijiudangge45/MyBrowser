#include "ioserverknadc2000m244.h"
#include "log.h"

#include <QEventLoop>
#include <QTimer>
IOServerKNaDC2000M244::IOServerKNaDC2000M244()
{
    m_tcpSocket = nullptr;
    m_conState = false;
}

IOServerKNaDC2000M244::~IOServerKNaDC2000M244()
{
    closeConnect();
}

bool IOServerKNaDC2000M244::connectServer(QString ipAddr, int port)
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
        connect(m_tcpSocket, &QTcpSocket::readyRead, this, &IOServerKNaDC2000M244::slot_ClientRecvData);
        connect(m_tcpSocket, &QTcpSocket::disconnected, this, &IOServerKNaDC2000M244::slot_reconnectServer);
        m_strIpAddr = ipAddr;
        m_port = port;
        m_conState = true;
        return true;
    }
}

void IOServerKNaDC2000M244::closeConnect()
{
    if(m_tcpSocket)
    {
        m_tcpSocket->close();
        delete m_tcpSocket;
        m_tcpSocket = nullptr;
    }
    m_conState = false;
}

bool IOServerKNaDC2000M244::writeData(int DBlock, int value)
{
    unsigned char WriteData[15]={0};
    WriteData[0]=0x00;
    WriteData[1]=0x01;
    WriteData[2]=0x00;
    WriteData[3]=0x00;
    WriteData[4]=0x00;
    WriteData[5]=0x09;
    //010300190004
    WriteData[6]=0x01;              //
    WriteData[7]=0x10;              //

    WriteData[8]=0x00;              //8、9是起始寄存器地址

    WriteData[10]=0x00;
    WriteData[11]=0x01;
    //080001000100000000
    WriteData[12]=0x02;            //13、14是0、1 开闭值
    WriteData[13]=0x00;

    if(DBlock==0)
    {        //DO0
        WriteData[9]=0x19;
    }
    else if(DBlock==1)
    {        //DO1
        WriteData[9]=0x1a;
    }
    else if(DBlock==2)
    {        //DO2
        WriteData[9]=0x1b;
    }
    else if(DBlock==3)
    {        //DO3
        WriteData[9]=0x1c;
    }

    if(value > 0)
    {
        WriteData[14]=0x01;
    }
    else
    {
        WriteData[14]=0x00;
    }

    int sendRe = m_tcpSocket->write((const char*)WriteData, 15);
    if(sendRe == -1)
        return false;
    else
        return true;
}

int IOServerKNaDC2000M244::readData(IOServerInterface::IOType iotype, int DBlock)
{
    unsigned char ReadData[12];
    ReadData[0]=0x00;
    ReadData[1]=0x01;
    ReadData[2]=0x00;
    ReadData[3]=0x00;
    ReadData[4]=0x00;
    ReadData[5]=0x06;
    ReadData[6]=0x01;
    ReadData[7]=0x03;
    ReadData[8]=0x00;

    ReadData[10]=0x00;
    ReadData[11]=0x04;

    if(iotype == DO)                 //0 - 读输入；1 - 读输出
    {
        ReadData[9]=0x19;
    }
    else if(iotype == DI)
    {
        ReadData[9]=0x21;
    }

    int sendRe = m_tcpSocket->write((const char*)ReadData, 12);
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
        return m_recvMsg[10];
    }
    else if(DBlock == 1)
    {
        return m_recvMsg[12];
    }
    else if(DBlock == 2)
    {
        return m_recvMsg[14];
    }
    else if (DBlock == 3)
    {
        return m_recvMsg[16];
    }
    return -1;
}

bool IOServerKNaDC2000M244::getConState()
{
    return m_conState;
}

void IOServerKNaDC2000M244::slot_reconnectServer()
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
        connect(m_tcpSocket, &QTcpSocket::readyRead, this, &IOServerKNaDC2000M244::slot_ClientRecvData);
        connect(m_tcpSocket, &QTcpSocket::disconnected, this, &IOServerKNaDC2000M244::slot_reconnectServer);
        m_conState = true;
    }
}

bool IOServerKNaDC2000M244::slot_ClientRecvData()
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
