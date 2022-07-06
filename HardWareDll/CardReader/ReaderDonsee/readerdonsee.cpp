#include "readerdonsee.h"
#include "../../include/log.h"
#include "comest32.H"

#include <QTimer>

static long Rhandle;                 //初始化读卡器的句柄
static QTimer timer;                 //定时器
static MSGCardCallBack msgCardcallBack;     //回调函数
static int iRt;                      //返回的状态码

static unsigned char key_initial[16] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff,0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
static unsigned char key_default[16] = {0xfd, 0x3d, 0xaf, 0x56, 0xd1, 0xa8, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

ReaderDonsee::ReaderDonsee()
{
    msgCardcallBack = nullptr;

    connect(&timer, &QTimer::timeout, [=]{
        if(msgCardcallBack != nullptr)
        {
            Log_HardWare(INFO_TRACE,"trace, run callback");
            msgCardcallBack(cardId().toStdString().c_str());
        }
    });
    timer.start(400);
}

ReaderDonsee::~ReaderDonsee()
{
    EU_Reader_Close(Rhandle);
}

bool ReaderDonsee::init(int port, int baudRate)
{
    Rhandle = EU_Reader_Open(port, baudRate);
    if(Rhandle <= 0)
    {
        Log_HardWare(INFO_ERROR, "error , initial cardReader-Donsee fail!");
        return false;
    }
    Log_HardWare(INFO_TRACE,"trace, initial cardReader-Donsee successful!");
    return true;
}

void ReaderDonsee::exit()
{
    EU_Reader_Close(Rhandle);
}

void ReaderDonsee::beep(int msec)
{
    if(EU_PosBeep(Rhandle, msec) != 0)
    {
        Log_HardWare(INFO_ERROR,"error, cardReader-Donsee beep fail!");
    }
}

QString ReaderDonsee::cardId()
{
    iRt = PEU_Reader_Request(Rhandle);
    if(iRt != 0)
    {
        Log_HardWare(INFO_ERROR,"error, cardReader-Donsee find card fail! error code : %d, 未放卡(don't have card)!", iRt);
        return QString::number(iRt);
    }
    unsigned char uid[4];
    iRt = PEU_Reader_GetUID(Rhandle, uid);
    if(iRt < 0)
    {
        Log_HardWare(INFO_ERROR,"error, cardReader-Donsee find card number fail! error code : %d.", iRt);
        return QString::number(iRt);
    }
    return QString("%1%2%3%4").arg(QString::number(uid[3], 16)).arg(QString::number(uid[2], 16)).arg(QString::number(uid[1], 16)).arg(QString::number(uid[0], 16));
}

bool ReaderDonsee::ResetPwd()
{
    unsigned char key[6];
    memcpy(key, key_default, sizeof(key));

    cardId();
    for(int i = 0; i < 16; i++)
    {
        if(PEU_Reader_Authentication_Pass(Rhandle, 0x60, i, key) != 0)
        {
            Log_HardWare(INFO_ERROR,"error %dsec key authentication fail!", i);
            return false;
        }
        if(PEU_Reader_Write(Rhandle, i * 4 + 3, key_initial))
        {
            Log_HardWare(INFO_ERROR,"error, the sec %d ResetPwd fail.", i);
            return false;
        }
    }
    return true;
}

bool ReaderDonsee::SetDeafultPwd()
{
    unsigned char key[6];
    memcpy(key, key_initial, sizeof(key));

    cardId();
    for(int i = 0; i < 16; i++)
    {
        if(PEU_Reader_Authentication_Pass(Rhandle, 0x60, i, key) != 0)
        {
            Log_HardWare(INFO_ERROR,"error %dsec key authentication fail!", i);
            return false;
        }
        if(PEU_Reader_Write(Rhandle, i * 4 + 3, key_default))
        {
            Log_HardWare(INFO_ERROR,"error, the sec %d ResetPwd fail.", i);
            return false;
        }
    }
    return true;
}

bool ReaderDonsee::read(int secNr, int dataAdr, QString &data)
{
    unsigned char key[6];
    memcpy(key, key_default, sizeof(key));

    cardId();
    if(PEU_Reader_Authentication_Pass(Rhandle, 0x60, secNr, key) != 0)
    {
        Log_HardWare(INFO_ERROR,"error %dsec key authentication fail!", secNr);
        return false;
    }

    unsigned char _data[16] = {0};
    iRt = PEU_Reader_Read(Rhandle, dataAdr, _data);
    if(iRt != 0)
    {
        data = QString::number(iRt);
        Log_HardWare(INFO_ERROR, "error, cardReader-Donsee read fail! data address %d, error code：%d", dataAdr, iRt);
        return false;
    }

    QByteArray tmp((char*)_data, 16);
    data = QString(tmp);

    char tmp_[100] = {0};
    HexToStr(_data, 16, (unsigned char*)tmp_);
    Log_HardWare(INFO_TRACE, "trace, read successful,（asc)：%s,（HexStr)：%s", _data, tmp_);
    return true;
}

bool ReaderDonsee::write(int secNr, int dataAdr, const QString &data)
{
    unsigned char key[6];
    memcpy(key, key_default, sizeof(key));

    cardId();
    if(PEU_Reader_Authentication_Pass(Rhandle, 0x60, secNr, key) != 0)
    {
        Log_HardWare(INFO_ERROR,"error %dsec key authentication fail!", secNr);
        return false;
    }

    QByteArray ba = data.toUtf8();
    unsigned char * _data  = (unsigned char *)ba.data();

    iRt = PEU_Reader_Write(Rhandle, dataAdr, _data);
    if(iRt != 0)
    {
        Log_HardWare(INFO_ERROR, "error, cardReader-Donsee write fail! data address %d, error code：%d", dataAdr, iRt);
        return false;
    }

    Log_HardWare(INFO_TRACE, "successful, cardReader-Donsee write successful!");
    return true;
}

void ReaderDonsee::setCallBack(MSGCardCallBack _msgCardCallBack)
{
    msgCardcallBack = _msgCardCallBack;
}
