#include "readermwrfeye.h"
#include "mwrf32.h"         //明华
#include "../../include/log.h"

#include <QTimer>

static HANDLE icdev;                  //初始化读卡器的句柄
static QTimer timer;                  //定时器
static MSGCardCallBack msgCardcallBack;      //回调函数

static unsigned char key_initial[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};  //初始密码
static unsigned char key_default[6] = {0xFD, 0x3D, 0xAF, 0x56, 0xD1, 0xA8};  //默认密码

ReaderMWRFEYE::ReaderMWRFEYE()
{
    msgCardcallBack = nullptr;

    connect(&timer, &QTimer::timeout, [=]{
        if(msgCardcallBack != nullptr)
        {
            Log_HardWare(INFO_TRACE, "trace, run hardware-Reader callback!");
            msgCardcallBack(cardId().toStdString().c_str());
        }
    });
    timer.start(400);
}

ReaderMWRFEYE::~ReaderMWRFEYE()
{
    rf_usbclose(icdev);
}

bool ReaderMWRFEYE::init()
{
    icdev = rf_usbopen();
    if((int)icdev < 0)
    {
        Log_HardWare(INFO_ERROR, "error , initial cardReader-MWRFEYE fail!");
        return false;
    }

    Log_HardWare(INFO_TRACE,"trace, initial cardReader-MWRFEYE successful!");
    return true;
}

void ReaderMWRFEYE::exit()
{
    rf_usbclose(icdev);
}

void ReaderMWRFEYE::beep(int msec)
{
    if(rf_beep(icdev, msec) != 0)
    {
        Log_HardWare(INFO_ERROR,"error, cardReader-MWRFEYE beep fail!");
    }
}

QString ReaderMWRFEYE::cardId()
{
    unsigned long snr;
    int rt = rf_card(icdev, 1, &snr);

    if(rt == 0)
    {
        return QString::number(snr, 16);
    }
    else if(rt == 1)
    {
        //无卡
        Log_HardWare(INFO_ERROR,"error, cardReader-MWRFEYE find card fail! error code : %d, 未放卡(don't have card)！", rt);
        return QString::number(rt);
    }
    else if(rt == -17)
    {
        //未连接读卡器
        Log_HardWare(INFO_ERROR,"error, cardReader-MWRFEYE find card fail! error code : %d, 未连接读卡器(don't connect cardReader)！", rt);
        return QString::number(rt);
    }
    else
    {
        Log_HardWare(INFO_ERROR,"error, cardReader-MWRFEYE find card fail! error code : %d.", rt);
        return QString::number(rt);
    }
}

bool ReaderMWRFEYE::ResetPwd()
{
    cardId();

    for(int i = 0; i < 16; i++)
    {
        if(rf_load_key(icdev, 0, i, key_default) != 0)
        {
            Log_HardWare(INFO_ERROR,"error, cardReader-MWRFEYE load-key fail! SecNumber: %d.", i);
            return false;
        }
        if(rf_authentication(icdev, 0, i) != 0)
        {
            Log_HardWare(INFO_ERROR,"error, cardReader-MWRFEYE authentication fail! SecNumber: %d.", i);
            return false;
        }
        if(rf_changeb3(icdev, i, key_initial, 0x00, 0x00, 0x00, 0x01, 0, key_initial) != 0)
        {
            Log_HardWare(INFO_ERROR,"error, cardReader-MWRFEYE ResetPwd fail! SecNumber: %d.", i);
            return false;
        }
    }
    return true;
}

bool ReaderMWRFEYE::SetDeafultPwd()
{
    cardId();

    for(int i = 0; i < 16; i++)
    {
        if(rf_load_key(icdev, 0, i, key_initial) != 0)
        {
            Log_HardWare(INFO_ERROR,"error, cardReader-MWRFEYE load-key fail! SecNumber: %d.", i);
            return false;
        }
        if(rf_authentication(icdev, 0, i) != 0)
        {
            Log_HardWare(INFO_ERROR,"error, cardReader-MWRFEYE authentication fail! SecNumber: %d.", i);
            return false;
        }
        if(rf_changeb3(icdev, i, key_default, 0x00, 0x00, 0x00, 0x01, 0, key_initial) != 0)
        {
            Log_HardWare(INFO_ERROR,"error, cardReader-MWRFEYE SetDeafultPwd fail! SecNumber: %d.", i);
            return false;
        }
    }
    return true;
}

bool ReaderMWRFEYE::read(int secNr, int dataAdr, QString &data)
{
    cardId();
    if(rf_load_key(icdev, 0, secNr, key_default) != 0)
    {
        Log_HardWare(INFO_ERROR,"error, cardReader-MWRFEYE load-key fail! SecNumber: %d.", secNr);
        return false;
    }
    if(rf_authentication(icdev, 0, secNr) != 0)
    {
        Log_HardWare(INFO_ERROR,"error, cardReader-MWRFEYE authentication fail! SecNumber: %d.", secNr);
        return false;
    }
    //--------------------读
    unsigned char _data[16] = {0};
    int rt = rf_read(icdev, dataAdr, _data);
    if(rt != 0)
    {
        Log_HardWare(INFO_ERROR, "error, cardReader-MWRFEYE read fail! data address %d, error code：%d", dataAdr, rt);
        data = QString("-1");
        return false;
    }
    Log_HardWare(INFO_TRACE, "successful, cardReader-MWRFEYE read successful!");

    QByteArray tmp((char*)_data, 16);
    data = QString(tmp);
    return true;
}

bool ReaderMWRFEYE::write(int secNr, int dataAdr, const QString &data)
{
    cardId();
    if(rf_load_key(icdev, 0, secNr, key_default) != 0)
    {
        Log_HardWare(INFO_ERROR,"error, cardReader-MWRFEYE load-key fail! SecNumber: %d.", secNr);
        return false;
    }
    if(rf_authentication(icdev, 0, secNr) != 0)
    {
        Log_HardWare(INFO_ERROR,"error, cardReader-MWRFEYE authentication fail! SecNumber: %d.", secNr);
        return false;
    }
    //--------------------------写
    QByteArray ba = data.toUtf8();
    unsigned char *_data  = (unsigned char *)ba.data();

    int rt = rf_write(icdev, dataAdr, _data);
    if(rt != 0)
    {
        Log_HardWare(INFO_ERROR, "error, cardReader-MWRFEYE write fail! data address %d, error code：%d", dataAdr, rt);
        return false;
    }
    Log_HardWare(INFO_TRACE, "successful, cardReader-MWRFEYE write successful!");
    return true;
}

void ReaderMWRFEYE::setCallBack(MSGCardCallBack _msgCardCallBack)
{
    msgCardcallBack = _msgCardCallBack;
}
