#ifndef CNADM244TEST_H
#define CNADM244TEST_H

#include <QWidget>
#include <qdialog.h>
#include "interfaceplugin.h"

namespace Ui {
class CNaDM244Test;
}

class CNaDM244Test : public QDialog
{
    Q_OBJECT

public:
    explicit CNaDM244Test(QDialog *parent = nullptr);
    ~CNaDM244Test();
    void init(QString pluginName);

    InterfaceIOServer *m_ioserver;

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

public:
    Ui::CNaDM244Test *ui;
};

#endif // CNADM244TEST_H
