#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QString>
#include "rsa.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

private slots:
    void on_pushGenerate_clicked();

    void on_pushEncrypt_clicked();

    void on_pushDecrypt_clicked();

private:
    Ui::Dialog *ui;
    RSA rsa;
};

#endif // DIALOG_H
