#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "donseetest.h"
#include "cnadm244test.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    DonseeTest *m_cardReaderTest;           //读卡器测试界面
    CNaDM244Test *m_ioserverTest;           //io服务器测试界面
    CardReaderInterface *m_cardReader;      //读卡器指针
    InterfaceIOServer *m_ioserver;
};
#endif // MAINWINDOW_H
