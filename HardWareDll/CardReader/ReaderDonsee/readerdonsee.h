#ifndef READERDONSEE_H
#define READERDONSEE_H

#include <windows.h>
#include <QObject>
#include <QtCore/qglobal.h>

#if defined(READERDONSEE_LIBRARY)
#  define READERDONSEE_EXPORT Q_DECL_EXPORT
#else
#  define READERDONSEE_EXPORT Q_DECL_IMPORT
#endif

typedef void (CALLBACK *MSGCardCallBack)(const char *cardId);

class READERDONSEE_EXPORT ReaderDonsee : public QObject
{
public:
    ReaderDonsee();
    ~ReaderDonsee();

    bool init(int port, int baudRate);
    void exit();
    void beep(int msec);
    QString cardId();
    bool ResetPwd();
    bool SetDeafultPwd();
    bool read(int secNr, int dataAdr, QString &data);
    bool write(int secNr, int dataAdr, const QString &data);
    void setCallBack(MSGCardCallBack msgCardCallBack);
};

#endif // READERDONSEE_H
