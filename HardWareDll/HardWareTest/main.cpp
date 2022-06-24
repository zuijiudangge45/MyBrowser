#include "hardwaretest.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    HardWareTest w;
    w.show();
    return a.exec();
}
