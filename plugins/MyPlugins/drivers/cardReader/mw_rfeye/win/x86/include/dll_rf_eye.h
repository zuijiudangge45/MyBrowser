#ifndef DLL_RF_EYE_H
#define DLL_RF_EYE_H

#include <QtCore/qglobal.h>
#include <QTimer>
#include <QObject>


#if defined(DLL_RF_EYE_LIBRARY)
#  define DLL_RF_EYE_EXPORT Q_DECL_EXPORT
#else
#  define DLL_RF_EYE_EXPORT Q_DECL_IMPORT
#endif

struct Private;

class DLL_RF_EYE_EXPORT Dll_rf_eye
{
public:
    Dll_rf_eye();
    ~Dll_rf_eye();
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

#endif // DLL_RF_EYE_H
