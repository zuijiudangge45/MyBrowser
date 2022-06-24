#ifndef HARDWARETEST_H
#define HARDWARETEST_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class HardWareTest; }
QT_END_NAMESPACE

class HardWareTest : public QMainWindow
{
    Q_OBJECT

public:
    HardWareTest(QWidget *parent = nullptr);
    ~HardWareTest();

private:
    Ui::HardWareTest *ui;
};
#endif // HARDWARETEST_H
