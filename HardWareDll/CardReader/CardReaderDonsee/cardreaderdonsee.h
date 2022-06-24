#ifndef CARDREADERDONSEE_H
#define CARDREADERDONSEE_H

#include "CardReaderDonsee_global.h"

class CARDREADERDONSEE_EXPORT CardReaderDonsee
{
public:
    CardReaderDonsee();
    ~CardReaderDonsee();
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
