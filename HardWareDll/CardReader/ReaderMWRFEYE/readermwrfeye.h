#ifndef READERMWRFEYE_H
#define READERMWRFEYE_H

#include <windows.h>
#include <QObject>
#include <QtCore/qglobal.h>

#if defined(READERMWRFEYE_LIBRARY)
#  define READERMWRFEYE_EXPORT Q_DECL_EXPORT
#else
#  define READERMWRFEYE_EXPORT Q_DECL_IMPORT
#endif

typedef void (CALLBACK *MSGCardCallBack)(const char *cardId);

class READERMWRFEYE_EXPORT ReaderMWRFEYE : public QObject
{
public:
    ReaderMWRFEYE();
    ~ReaderMWRFEYE();

    bool init();
    void beep(int msec);
    QString cardId();
    bool ResetPwd();
    bool SetDeafultPwd();
    bool read(int secNr, int dataAdr, QString &data);
    bool write(int secNr, int dataAdr, const QString &data);
    void setCallBack(MSGCardCallBack msgCardCallBack);
};

#endif // READERMWRFEYE_H
