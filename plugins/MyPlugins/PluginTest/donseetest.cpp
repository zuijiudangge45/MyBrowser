#include "donseetest.h"
#include "QDebug"
#include "ui_donseetest.h"

DonseeTest::DonseeTest(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DonseeTest)
{
    ui->setupUi(this);
}

DonseeTest::~DonseeTest()
{
    delete ui;
}
//鸣响
void DonseeTest::on_pushButton_clicked()
{
    m_cardreader->beep(20);
}
//重置密码
void DonseeTest::on_pushButton_2_clicked()
{
    m_cardreader->ResetToInitPwd();
}
//设置密码
void DonseeTest::on_pushButton_3_clicked()
{
m_cardreader->initCardPwd();
}
//取卡号
void DonseeTest::on_pushButton_4_clicked()
{
    ui->label_4->setText(m_cardreader->cardId());
}

//读
void DonseeTest::on_pushButton_5_clicked()
{
    int shanqu  = ui->lineEdit->text().toInt();
    int shujukuai  = ui->lineEdit_2->text().toInt();
    QString  data;
    m_cardreader->read(shanqu, shujukuai, data);
    qDebug()<<QString("shanqu:%1,shujukuai:%2,shuju:%3").arg(shanqu).arg(shujukuai).arg(data);
}
//写
void DonseeTest::on_pushButton_6_clicked()
{
    int shanqu  = ui->lineEdit->text().toInt();
    int shujukuai  = ui->lineEdit_2->text().toInt();
    QString data = ui->lineEdit_3->text();
    m_cardreader->write(shanqu, shujukuai, data);
    qDebug()<<QString("shanqu:%1,shujukuai:%2,shuju:%3").arg(shanqu).arg(shujukuai).arg(data);
}
