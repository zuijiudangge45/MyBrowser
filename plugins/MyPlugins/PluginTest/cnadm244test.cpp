#include "cnadm244test.h"
#include "ui_cnadm244test.h"

CNaDM244Test::CNaDM244Test(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::CNaDM244Test)
{
    ui->setupUi(this);
}

CNaDM244Test::~CNaDM244Test()
{
    delete ui;
}

void CNaDM244Test::init(QString pluginName)
{
    if(pluginName == "m244")
    {
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_4->setEnabled(false);
    }
    else
    {
        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
    }
}
//读
void CNaDM244Test::on_pushButton_clicked()
{
    int rtn = -1;
    int currentIndex = ui->comboBox->currentIndex();
    if(currentIndex == 0)
    {
        currentIndex = ui->comboBox_2->currentIndex();
        if(currentIndex == 0)
        {
            rtn = m_ioserver->readData(0, 0);
        }
        else if(currentIndex == 1)
        {
            rtn = m_ioserver->readData(0, 1);
        }
        else if(currentIndex == 2)
        {
            rtn = m_ioserver->readData(0, 2);
        }
        else if(currentIndex == 3)
        {
            rtn = m_ioserver->readData(0, 3);
        }
    }
    else if(currentIndex == 1)
    {
        currentIndex = ui->comboBox_2->currentIndex();
        if(currentIndex == 0)
        {
            rtn = m_ioserver->readData(1, 0);
        }
        else if(currentIndex == 1)
        {
            rtn = m_ioserver->readData(1, 1);
        }
        else if(currentIndex == 2)
        {
            rtn = m_ioserver->readData(1, 2);
        }
        else if(currentIndex == 3)
        {
            rtn = m_ioserver->readData(1, 3);
        }
    }
    ui->lineEdit->setText(QString::number(rtn));
}
//写
void CNaDM244Test::on_pushButton_2_clicked()
{
    int currentIndex = ui->comboBox_3->currentIndex();
        int value = ui->comboBox_4->currentIndex();
        if(currentIndex == 0)
        {
            m_ioserver->writeData(0, value);
        }
        else if(currentIndex == 1)
        {
            m_ioserver->writeData(1, value);
        }
        else if(currentIndex == 2)
        {
            m_ioserver->writeData(2, value);
        }
        else if(currentIndex == 3)
        {
            m_ioserver->writeData(3, value);
        }
}
