#ifndef CARDREADERDONSEE_H
#define CARDREADERDONSEE_H

#include <windows.h>
#include <QtCore/qglobal.h>

#if defined(CARDREADERDONSEE_LIBRARY)
#  define CARDREADERDONSEE_EXPORT Q_DECL_EXPORT
#else
#  define CARDREADERDONSEE_EXPORT Q_DECL_IMPORT
#endif

typedef void (CALLBACK *MSGCardCallBack)(const char *cardId);

class CARDREADERDONSEE_EXPORT CardReaderDonsee
{
public:
    CardReaderDonsee();
    ~CardReaderDonsee();
    void setCallBack(MSGCardCallBack msgCardCallBack);

    bool init(int port, int baudRate);
    void beep(int msec);
    QString cardId();
    bool ResetToInitPwd();
    bool initCardPwd();
    bool read(unsigned char secNr, unsigned char _Adr, QString &data);
    bool write(unsigned char secNr, unsigned char _Adr, QString _Data);

private:
    struct Private;
    struct Private *d;
};

#endif // CARDREADERDONSEE_H
