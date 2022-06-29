#ifndef CNADM244TEST_H
#define CNADM244TEST_H

#include <QWidget>
#include "interfaceplugin.h"

namespace Ui {
class CNaDM244Test;
}

class CNaDM244Test : public QWidget
{
    Q_OBJECT

public:
    explicit CNaDM244Test(QWidget *parent = nullptr);
    ~CNaDM244Test();

    InterfaceIOServer *m_ioserver;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::CNaDM244Test *ui;
};

#endif // CNADM244TEST_H
