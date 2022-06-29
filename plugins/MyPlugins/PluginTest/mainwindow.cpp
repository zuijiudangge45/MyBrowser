#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "pluginmanager.h"
#include "interfaceplugin.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    PluginManager::getInstance()->loadAllPlugins();
}

MainWindow::~MainWindow()
{
    delete ui;
    if(m_cardReaderTest)
    {
        delete m_cardReaderTest;
        m_cardReaderTest = nullptr;
    }
    PluginManager::getInstance()->unloadAllPlugins();

}

//测试东信
void MainWindow::on_pushButton_clicked()
{
    //    qDebug()<< PluginManager::getInstance()->allPlugins();
    //    qDebug()<< PluginManager::getInstance()->allPlugins().first()->metaData().value("MetaData").toObject().value("name").toVariant();
    QPluginLoader *loader = PluginManager::getInstance()->getPlugin("cardReaderDonsee");
    if(loader)
    {
        m_cardReader = qobject_cast<CardReaderInterface*>(loader->instance());
        if(m_cardReader)
        {
            m_cardReader->init(3, 115200);
            m_cardReaderTest = new DonseeTest(this);
            m_cardReaderTest->m_cardreader = m_cardReader;
            m_cardReaderTest->show();
        }
    }
    else
    {
        qDebug()<< "error";
    }
}
//测试明华
void MainWindow::on_pushButton_2_clicked()
{
    QPluginLoader *loader = PluginManager::getInstance()->getPlugin("cardReaderMwRfEye");
    if(loader)
    {
        m_cardReader = qobject_cast<CardReaderInterface*>(loader->instance());
        if(m_cardReader)
        {
            m_cardReader->init(NULL, NULL);
            m_cardReaderTest = new DonseeTest(this);
            m_cardReaderTest->m_cardreader = m_cardReader;
            m_cardReaderTest->show();
        }
    }
    else
    {
        qDebug()<< "error";
    }

}
//测试m244
void MainWindow::on_pushButton_3_clicked()
{
    qDebug()<<PluginManager::getInstance()->allPlugins().count();
    QPluginLoader *loader = PluginManager::getInstance()->getPlugin("IOServerCNaDM244");
    if(loader)
    {
        m_ioserver = qobject_cast<InterfaceIOServer*>(loader->instance());
        if(m_ioserver)
        {
            if(m_ioserver->connectServer("192.168.2.30", 502))
            {
                m_ioserverTest = new CNaDM244Test;
                m_ioserverTest->m_ioserver = m_ioserver;
                m_ioserverTest->show();
            }
            else
            {
                qDebug()<<"init ioserver error";
            }

        }
    }
    else
    {
        qDebug()<< "error get instance";
    }
}
