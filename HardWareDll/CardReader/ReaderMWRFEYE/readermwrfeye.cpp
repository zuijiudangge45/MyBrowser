#include "readermwrfeye.h"
#include "mwrf32.h"         //明华
#include "../../include/log.h"

#include <QTimer>

static HANDLE m_icdev;                  //初始化读卡器的句柄
static QTimer m_timer;                  //定时器
static MSGCardCallBack m_callBack;      //回调函数

static unsigned char m_key_initial[6] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};  //初始密码
static unsigned char m_key_default[6] = {0xFD, 0x3D, 0xAF, 0x56, 0xD1, 0xA8};  //默认密码

ReaderMWRFEYE::ReaderMWRFEYE()
{
    m_callBack = nullptr;

    connect(&m_timer, &QTimer::timeout, [=]{
        if(m_callBack != nullptr)
        {
            Log_HardWare(INFO_TRACE, "trace, run hardware-Reader callback!");
            m_callBack(cardId().toStdString().c_str());
        }
    });
    m_timer.start(400);
}

ReaderMWRFEYE::~ReaderMWRFEYE()
{

}

bool ReaderMWRFEYE::init()
{
    return true;
}

void ReaderMWRFEYE::beep(int msec)
{

}

QString ReaderMWRFEYE::cardId()
{
    return QString();
}

bool ReaderMWRFEYE::ResetPwd()
{
    return true;

}

bool ReaderMWRFEYE::SetDeafultPwd()
{
    return true;

}

bool ReaderMWRFEYE::read(int secNr, int dataAdr, QString &data)
{
    return true;

}

bool ReaderMWRFEYE::write(int secNr, int dataAdr, const QString &data)
{
    return true;

}

void ReaderMWRFEYE::setCallBack(MSGCardCallBack msgCardCallBack)
{

}
