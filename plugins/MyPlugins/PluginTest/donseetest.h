#ifndef DONSEETEST_H
#define DONSEETEST_H

#include <QWidget>
#include "interfaceplugin.h"
namespace Ui {
class DonseeTest;
}

class DonseeTest : public QWidget
{
    Q_OBJECT

public:
    explicit DonseeTest(QWidget *parent = nullptr);
    ~DonseeTest();

    CardReaderInterface *m_cardreader;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

private:
    Ui::DonseeTest *ui;
};

#endif // DONSEETEST_H
