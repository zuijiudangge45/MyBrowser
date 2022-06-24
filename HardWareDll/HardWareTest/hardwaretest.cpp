#include "hardwaretest.h"
#include "ui_hardwaretest.h"

HardWareTest::HardWareTest(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::HardWareTest)
{
    ui->setupUi(this);
}

HardWareTest::~HardWareTest()
{
    delete ui;
}

