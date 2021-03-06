#include "cardreaderdonsee.h"
#include "comest32.H"
#include "log.h"
#include "cardReaderBase.h"

struct CardReaderDonsee::Private : public QObject, DLLCardReader
{
    long m_Rhandle;                 //初始化读卡器的句柄
    QTimer m_timer;                 //定时器
    MSGCardCallBack m_callBack;     //回调函数
    int m_iRt;                      //返回的状态码

    unsigned char m_key_initial[6];
    unsigned char m_key_new[6];
    unsigned char m_key_authentication[6];

public:
    Private();
    ~Private();
    virtual bool init(int port, int baudRate) override;
    virtual void beep(int msec) override;
    virtual void setCallBack(MSGCardCallBack msgCardCallBack) override;
    virtual QString findCardId() override;
    virtual bool authentication(int secNr) override;
    virtual bool changePwd(int secNr) override;
    virtual bool changePwd_initial(int secNr) override;
    virtual bool read(unsigned char _Adr, QString &data) override;
    virtual bool write(unsigned char _Adr, QString _Data) override;
    virtual void loadKey(int secNr) override;
    virtual void loadKey_initial(int secNr) override;;
    virtual void halt() override {};
    virtual void exit() override;
};


CardReaderDonsee::Private::Private()
{
    m_key_initial[0] = 0xFF;
    m_key_initial[1] = 0xFF;
    m_key_initial[2] = 0xFF;
    m_key_initial[3] = 0xFF;
    m_key_initial[4] = 0xFF;
    m_key_initial[5] = 0xFF;

    m_key_new[0] = 0xFD;
    m_key_new[1] = 0x3D;
    m_key_new[2] = 0xAF;
    m_key_new[3] = 0x56;
    m_key_new[4] = 0xD1;
    m_key_new[5] = 0xA8;

    m_callBack = nullptr;

    connect(&m_timer, &QTimer::timeout, [=]{
        if(m_callBack != nullptr)
        {
            Log_accessControl(INFO_TRACE,"trace, run callback");
            m_callBack(findCardId().toStdString().c_str());
        }
    });
    m_timer.start(400);
}

CardReaderDonsee::Private::~Private()
{
    exit();
}

bool CardReaderDonsee::Private::init(int port, int baudRate)
{
    m_Rhandle = EU_Reader_Open(port, baudRate);
    if(m_Rhandle <= 0)
    {
        Log_accessControl(INFO_ERROR,"error 东信读卡器初始化失败");
        return false;
    }
    else
    {
        Log_accessControl(INFO_TRACE,"trace 东信读卡器初始化成功");
        return true;
    }
}

void CardReaderDonsee::Private::beep(int msec)
{
    if(EU_PosBeep(m_Rhandle, msec) != 0)
    {
        Log_accessControl(INFO_ERROR,"error 读卡器蜂鸣失败");
    }
    else
    {
        Log_accessControl(INFO_TRACE,"trace 读卡器蜂鸣%d分秒", msec);
    }
}

void CardReaderDonsee::Private::setCallBack(MSGCardCallBack msgCardCallBack)
{
    m_callBack = msgCardCallBack;

}

QString CardReaderDonsee::Private::findCardId()
{
    m_iRt = PEU_Reader_Request(m_Rhandle);
    if(m_iRt != 0)
    {
        Log_accessControl(INFO_ERROR, "error %s","寻卡失败");
        return QString::number(-1);
    }
    unsigned char uid[4];
    m_iRt = PEU_Reader_GetUID(m_Rhandle, uid);
    if(m_iRt < 0)
    {
        Log_accessControl(INFO_ERROR,"error 获取卡号失败，失败码为%d", m_iRt);
        return QString::number(-1);
    }
    return QString("%1%2%3%4").arg(QString::number(uid[3], 16)).arg(QString::number(uid[2], 16)).arg(QString::number(uid[1], 16)).arg(QString::number(uid[0], 16));

}

bool CardReaderDonsee::Private::authentication(int secNr)
{
    m_iRt = PEU_Reader_Authentication_Pass(m_Rhandle, 0x60, secNr, m_key_authentication);
    if(m_iRt != 0)
    {
        Log_accessControl(INFO_ERROR,"error 第%d扇区秘钥认证失败", secNr);
        return false;
    }
    else
    {
        Log_accessControl(INFO_TRACE,"trace 第%d扇区秘钥认证成功", secNr);
        return true;
    }
}

#if 0

for(unsigned int i = 0; i < sizeof(m_key_authentication); i++)
{
    Log_accessControl(INFO_TRACE, "m_key_authentication [%d]:%d", i, m_key_authentication[i]);
}
for(unsigned int i = 0; i < sizeof(key_DONSEE); i++)
{
    Log_accessControl(INFO_TRACE, "key_DONSEE [%d]:%d;", i, key_DONSEE[i]);
}
#endif

bool CardReaderDonsee::Private::changePwd(int secNr)
{
    unsigned char key_DONSEE[16] = {0xfd, 0x3d, 0xaf, 0x56, 0xd1, 0xa8, 0xff, 0x07, 0x80, 0x69, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
    key_DONSEE[0] = m_key_new[0];
    key_DONSEE[1] = m_key_new[1];
    key_DONSEE[2] = m_key_new[2];
    key_DONSEE[3] = m_key_new[3];
    key_DONSEE[4] = m_key_new[4];
    key_DONSEE[5] = m_key_new[5];



    m_iRt = PEU_Reader_Write(m_Rhandle, secNr *4 + 3, key_DONSEE);
    if(m_iRt != 0)
    {
        Log_accessControl(INFO_ERROR,"error, 修改第%d扇区密码失败", secNr);
        return false;
    }
    else
    {
        Log_accessControl(INFO_TRACE,"trace, 修改第%d扇区密码成功", secNr);
        return true;
    }
}

#if 0
for(unsigned int i = 0; i < sizeof(m_key_authentication); i++)
{
    Log_accessControl(INFO_TRACE, "m_key_authentication [%d]:%d", i, m_key_authentication[i]);
}
for(unsigned int i = 0; i < sizeof(key_DONSEE_initial); i++)
{
    Log_accessControl(INFO_TRACE, "key_DONSEE [%d]:%d;", i, key_DONSEE_initial[i]);
}
#endif

bool CardReaderDonsee::Private::changePwd_initial(int secNr)
{
    unsigned char key_DONSEE_initial[16] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0x80, 0x69, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
    key_DONSEE_initial[0] = m_key_initial[0];
    key_DONSEE_initial[1] = m_key_initial[1];
    key_DONSEE_initial[2] = m_key_initial[2];
    key_DONSEE_initial[3] = m_key_initial[3];
    key_DONSEE_initial[4] = m_key_initial[4];
    key_DONSEE_initial[5] = m_key_initial[5];

    m_iRt =PEU_Reader_Write(m_Rhandle, secNr * 4 + 3, key_DONSEE_initial);
    if(m_iRt != 0)
    {
        Log_accessControl(INFO_ERROR,"error, 修改第%d扇区密码失败", secNr);
        return false;
    }
    else
    {
        Log_accessControl(INFO_TRACE,"trace, 修改第%d扇区密码成功", secNr);
        return true;
    }
}

bool CardReaderDonsee::Private::read(unsigned char _Adr, QString &data)
{
    unsigned char _data[16] = {0};

    m_iRt = PEU_Reader_Read(m_Rhandle, _Adr, _data);
    if(m_iRt == 0)
    {
        QByteArray tmp((char*)_data, 16);
        data = QString(tmp);

        char tmp_[100] = {0};
        HexToStr(_data, 16, (unsigned char*)tmp_);
        Log_accessControl(INFO_TRACE,"trace 读卡成功,（asc)：%s,（HexStr)：%s", _data, tmp_);
        return true;
    }
    else
    {
        data = QString::number(-1);
        Log_accessControl(INFO_ERROR,"error %s","读卡失败");
        return false;
    }
}

bool CardReaderDonsee::Private::write(unsigned char _Adr, QString _Data)
{
    QByteArray ba = _Data.toUtf8();
    unsigned char * data  = (unsigned char *)ba.data();

    m_iRt = PEU_Reader_Write(m_Rhandle, _Adr, data);
    if(m_iRt != 0)
    {
        Log_accessControl(INFO_ERROR,"error 写第%d数据块失败，失败码%d", _Adr, m_iRt);
        return false;
    }
    else
    {
        Log_accessControl(INFO_TRACE,"trace 写第%d数据块成功", _Adr);
        return true;
    }
}

void CardReaderDonsee::Private::loadKey(int secNr)
{
    Q_UNUSED(secNr);
    memcpy(m_key_authentication, m_key_new, sizeof(m_key_new));
}

void CardReaderDonsee::Private::loadKey_initial(int secNr)
{
    Q_UNUSED(secNr);
    memcpy(m_key_authentication, m_key_initial, sizeof(m_key_initial));
}

void CardReaderDonsee::Private::exit()
{
    EU_Reader_Close(m_Rhandle);
}

CardReaderDonsee::CardReaderDonsee()
{
    d = new Private;
}

CardReaderDonsee::~CardReaderDonsee()
{
    delete d;
}

void CardReaderDonsee::setCallBack(MSGCardCallBack msgCardCallBack)
{
    d->setCallBack(msgCardCallBack);
}

bool CardReaderDonsee::init(int port, int baudRate)
{
    return d->init(port, baudRate);
}

void CardReaderDonsee::beep(int msec)
{
    d->beep(msec);
}

QString CardReaderDonsee::cardId()
{
    return d->findCardId();
}

bool CardReaderDonsee::ResetToInitPwd()
{
    d->loadKey(NULL);
    for(int i = 0; i < 16; i++)
    {
        d->findCardId();
        if(!d->authentication(i))
        {
            Log_accessControl(INFO_ERROR,"error authentication fail.");
            return false;
        }
        if(!d->changePwd_initial(i))
        {
            Log_accessControl(INFO_ERROR,"error, changePwd_initial fail.");
            return false;
        }
    }
    return true;
}

bool CardReaderDonsee::initCardPwd()
{
    d->loadKey_initial(NULL);
    for(int i = 0; i < 16; i++)
    {
        d->findCardId();
        if(!d->authentication(i))
        {
            Log_accessControl(INFO_ERROR,"error authentication fail.");
            return false;
        }
        if(!d->changePwd(i))
        {
            Log_accessControl(INFO_ERROR,"error, changePwd fail.");

            return false;
        }
    }
    return true;
}

bool CardReaderDonsee::read(unsigned char secNr, unsigned char _Adr, QString &data)
{
    d->findCardId();
    d->loadKey(NULL);
    if(!d->authentication(secNr))
    {
        Log_accessControl(INFO_ERROR,"error authentication fail.");
        return false;
    }
    return d->read(_Adr, data);
}

bool CardReaderDonsee::write(unsigned char secNr, unsigned char _Adr, QString _Data)
{
    d->findCardId();
    d->loadKey(NULL);
    if(!d->authentication(secNr))
    {
        Log_accessControl(INFO_ERROR,"error authentication fail.");
        return false;
    }
    return d->write(_Adr, _Data);
}
