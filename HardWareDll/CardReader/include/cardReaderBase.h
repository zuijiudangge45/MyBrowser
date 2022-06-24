#ifndef DLLCARDREADER_H
#define DLLCARDREADER_H

#include <QString>
#include <QTimer>
#include <windows.h>

typedef void (CALLBACK *MSGCardCallBack)(const char *cardId);

class DLLCardReader
{
public:
    virtual void setCallBack(MSGCardCallBack msgCardCallBack) = 0;
    virtual bool init(int port, int baudRate) = 0;
    virtual void beep(int msec) = 0;
    virtual QString findCardId() = 0;

    virtual bool read(unsigned char _Adr, QString &data) = 0;
    virtual bool write(unsigned char _Adr, QString data) = 0;

    virtual bool changePwd(int secNr) = 0;
    virtual bool changePwd_initial(int secNr) = 0;
    virtual void loadKey(int secNr) = 0;
    virtual void loadKey_initial(int secNr) = 0;
    virtual bool authentication(int secNr) = 0;
    virtual void halt() = 0;
    virtual void exit() = 0;
};

#endif // CARDREADERBASE_H

