#include "dll_rf_eye.h"
#include "mwrf32.h"         //明华
#include "log.h"
#include "cardReaderBase.h"

struct Dll_rf_eye::Private : public QObject, DLLCardReader
{
    //    Q_OBJECT
    HANDLE m_icdev;                 //初始化读卡器的句柄
    QTimer m_timer;                 //定时器
    MSGCardCallBack m_callBack;     //回调函数

    unsigned char m_key_initial[6];
    unsigned char m_key_new[6];

public:
    Private();
    ~Private();

    virtual bool init(int port, int baudRate) override;
    virtual void beep(int msec) override;
    virtual void setCallBack(MSGCardCallBack msgCardCallBack) override;
    virtual QString findCardId() override;
    virtual void loadKey(int secNr) override;
    virtual void loadKey_initial(int secNr) override;
    virtual bool authentication(int secNr) override;
    virtual bool changePwd(int secNr) override;
    virtual bool changePwd_initial(int secNr) override;
    virtual bool read(unsigned char _Adr, QString &data) override;
    virtual bool write(unsigned char _Adr, QString _Data) override;
    virtual void halt() override;
    virtual void exit() override;
};


Dll_rf_eye::Private::Private()
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


Dll_rf_eye::Private::~Private()
{
    exit();
}

bool Dll_rf_eye::Private::init(int port, int baudRate)
{
    Q_UNUSED(port);
    Q_UNUSED(baudRate);

    m_icdev = rf_usbopen();
    if((int)m_icdev < 0)
    {
        Log_accessControl(INFO_ERROR,"error , initial cardReader fail");
        return false;
    }
    else
    {
        Log_accessControl(INFO_TRACE,"trace, initial cardReader successful");
        return true;
    }
}

void Dll_rf_eye::Private::beep(int msec)
{
    //蜂鸣
    if(rf_beep(m_icdev, msec) != 0)
    {
        Log_accessControl(INFO_ERROR,"error %s","读卡器蜂鸣失败");
    }
    else
    {
        Log_accessControl(INFO_TRACE,"trace 读卡器蜂鸣%d分秒", msec);
    }
}

void Dll_rf_eye::Private::setCallBack(MSGCardCallBack msgCardCallBack)
{
    m_callBack = msgCardCallBack;
}

QString Dll_rf_eye::Private::findCardId()
{
    unsigned long snr;
    int rt = rf_card(m_icdev, 1, &snr);

    if(rt == 0)
    {
        return QString::number(snr, 16);
    }
    else if(rt == 1)
    {
        //无卡
        Log_accessControl(INFO_ERROR,"error 读卡器 寻卡失败,错误码为1,未放卡！", rt);
        return QString::number(-1);
    }
    else if(rt == -17)
    {
        //未连接读卡器
        Log_accessControl(INFO_ERROR,"error 读卡器 寻卡失败,错误码为-17，未连接读卡器！", rt);
        return QString::number(-1);
    }
    else
    {
        Log_accessControl(INFO_ERROR,"error 读卡器 寻卡失败,错误码为%d", rt);
        return QString::number(-1);
    }
}

/*
void Dll_rf_eye::Private::findCardId(unsigned long *snr)
{
    if(rf_card(m_icdev, 0, snr) == 0)
    {
        Log_accessControl(INFO_TRACE,"trace %s","读卡器 寻卡成功");
    }
    else
    {
        Log_accessControl(INFO_ERROR,"error %s","读卡器 寻卡失败");
    }
}

void Dll_rf_eye::Private::findCardId(char *carId)
{

}
*/

/*
 * 功 能：将密码装入读写模块RAM中
 * 参 数：icdev：通讯设备标识符
         _Mode：装入密码模式，同密码验证模式mode_auth
         _SecNr：扇区号（M1卡：0～15；  ML卡：0）
         _Nkey：写入读写器中的卡密码
 * 返 回：成功则返回 0
 */
void Dll_rf_eye::Private::loadKey(int secNr)
{
    int rt = rf_load_key(m_icdev, 0, secNr, m_key_new);
    if(rt == 0)
    {
        Log_accessControl(INFO_TRACE,"success 装载扇区密码成功");
    }
    else
    {
        Log_accessControl(INFO_ERROR,"error 装载扇区密码错误,错误码为%d", rt);
    }
}

void Dll_rf_eye::Private::loadKey_initial(int secNr)
{
    int rt = rf_load_key(m_icdev, 0, secNr, m_key_initial);
    if(rt == 0)
    {
        Log_accessControl(INFO_TRACE,"success 装载扇区密码成功");
    }
    else
    {
        Log_accessControl(INFO_ERROR,"error 装载扇区密码错误,错误码为%d", rt);
    }
}

bool Dll_rf_eye::Private::authentication(int secNr)
{
    int rt = rf_authentication(m_icdev, 0, secNr);
    //    int rt = rf_HL_authentication(m_icdev, 1, 0, 0, secNr);
    if( rt== 0)
    {
        Log_accessControl(INFO_DEBUG,"debug 验证扇区密码成功");
        return true;
    }
    else
    {
        Log_accessControl(INFO_ERROR,"error 验证第%d扇区密码错误,错误码为:%d", secNr, rt);
        return false;
    }
}
/*
 * 功 能：修改块3的数据
参 数：icdev：通讯设备标识符
      _SecNr：扇区号（0～15）
      _KeyA：密码A
      _B0：块0控制字，低3位（D2D1D0）对应C10、C20、C30
      _B1：块1控制字，低3位（D2D1D0）对应C11、C21、C31
      _B2：块2控制字，低3位（D2D1D0）对应C12、C22、C32
      _B3：块3控制字，低3位（D2D1D0）对应C13、C23、C33
      _Bk：保留参数，取值为0
      _KeyB：密码B
返 回：成功则返回 0
*/
bool Dll_rf_eye::Private::changePwd(int secNr)
{
    int rt = rf_changeb3(m_icdev, secNr, m_key_new, 0x00, 0x00, 0x00, 0x01, 0, m_key_initial);
    if(rt == 0)
    {
        Log_accessControl(INFO_TRACE,"trace 重置第%d扇区密码成功", secNr);
        return true;
    }
    else
    {
        Log_accessControl(INFO_ERROR,"error 重置第%d扇区密码错误, 错误码为: %d", secNr, rt);
        return false;
    }
}

bool Dll_rf_eye::Private::changePwd_initial(int secNr)
{
    int rt = rf_changeb3(m_icdev, secNr, m_key_initial, 0x00, 0x00, 0x00, 0x01, 0, m_key_initial);
    if(rt == 0)
    {
        Log_accessControl(INFO_TRACE,"trace 重置第%d扇区密码成功", secNr);
        return true;
    }
    else
    {
        Log_accessControl(INFO_ERROR,"error 重置第%d扇区密码错误,错误码为：%d", secNr, rt);
        return false;
    }
}

bool Dll_rf_eye::Private::read(unsigned char _Adr, QString &data)
{
    unsigned char _data[16] = {0};
    int rt = rf_read(m_icdev, _Adr, _data);
    if(rt == 0)
    {
        Log_accessControl(INFO_TRACE, "successful %s","读数据成功");
        QByteArray tmp((char*)_data, 16);
        data = QString(tmp);
        return true;
    }
    else
    {
        Log_accessControl(INFO_ERROR, "error 读第%d数据块失败，失败码：%d", _Adr, rt);
        data = QString("-1");
        return false;
    }
}

bool Dll_rf_eye::Private::write(unsigned char _Adr, QString _Data)
{
    QByteArray ba = _Data.toUtf8();
    unsigned char *data  = (unsigned char *)ba.data();

    int rt = rf_write(m_icdev, _Adr, data);
    if(rt == 0)
    {
        Log_accessControl(INFO_TRACE,"trace 写第%d数据块成功", _Adr);
        return true;
    }
    else
    {
        Log_accessControl(INFO_ERROR,"error 写第%d数据块失败，失败码：%d", _Adr, rt);
        return false;
    }
}

void Dll_rf_eye::Private::halt()
{
    rf_halt(m_icdev);
}

void Dll_rf_eye::Private::exit()
{
    rf_usbclose(m_icdev);
    Log_accessControl(INFO_DEBUG,"debug %s","释放串口");
}

Dll_rf_eye::Dll_rf_eye()
{
    d = new Private;
}

Dll_rf_eye::~Dll_rf_eye()
{
    delete d;
}

bool Dll_rf_eye::init()
{
    return d->init(0, 0);
}

void Dll_rf_eye::beep(int msec)
{
    d->beep(msec);
}

QString Dll_rf_eye::cardId()
{
    return d->findCardId();
}

bool Dll_rf_eye::ResetToInitPwd()
{
    for(int i = 0; i < 16; i++)
    {
        d->findCardId();
        d->loadKey(i);
        if(!d->authentication(i))
        {
            printf("error, authentication fail.");
            return false;
        }
        if(!d->changePwd_initial(i))
        {
            printf("error, changePwd_initial fail.");
            return false;
        }
    }
    return true;
}

bool Dll_rf_eye::initCardPwd()
{
    for(int i = 0; i < 16; i++)
    {
        d->findCardId();
        d->loadKey_initial(i);
        if(!d->authentication(i))
        {
            printf("error, authentication fail.");
            return false;
        }
        if(!d->changePwd(i))
        {
            printf("error, changePwd fail.");
            return false;
        }
        d->loadKey(i);
    }
    return true;
}

bool Dll_rf_eye::read(unsigned char secNr, unsigned char _Adr, QString &data)
{
    d->findCardId();
    d->loadKey(secNr);
    if(!d->authentication(secNr))
    {
        printf("error, authentication fail.");
        return false;
    }
    return d->read(_Adr, data);
}

bool Dll_rf_eye::write(unsigned char secNr, unsigned char _Adr, QString _Data)
{
    d->findCardId();
    d->loadKey(secNr);
    if(!d->authentication(secNr))
    {
        printf("error, authentication fail.");
        return false;
    }
    return d->write(_Adr, _Data);
}
