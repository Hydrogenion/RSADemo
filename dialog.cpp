#include "dialog.h"
#include "ui_dialog.h"
#include <QDebug>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    // load skin
    QString qss;
//    QString path ("E:\\QtProjects\\RSA\\qss\\gray.css");
    QString path(":/qss/gray.css");
    QFile qssFile(path);
    qssFile.open(QFile::ReadOnly);
    if(qssFile.isOpen()){
        qss = QLatin1String(qssFile.readAll());
        qApp->setStyleSheet(qss);
        qssFile.close();
    }
    ui->setupUi(this);

    // init comboBox
    QStringList comboList;
    comboList << "RSA512" << "RSA768" << "RSA1024";
    ui->comboSelect->addItems(comboList);

}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushGenerate_clicked()
{
    QString mode = ui->comboSelect->currentText();
    qDebug()<<mode;
    int keyLen=1024;
    if (mode == "RSA512"){
        keyLen = 512;
    }
    else if (mode == "RSA768"){
        keyLen = 768;
    }
    else if (mode == "RSA1024"){
        keyLen = 1024;
    }
    int timeCost = rsa.generateKey(keyLen);
    QString bk = QString::fromStdString(rsa.getPublicKey());
    QString vk = QString::fromStdString(rsa.getPrivateKey());
    ui->textPublicKey->setText(bk);
    ui->textPrivateKey->setText(vk);
    ui->textLog->append("Generating public and private keys costs "+QString::number(timeCost,10) +" ms");
}

//void Dialog::on_pushEncrypt_clicked()
//{
//    QString plainText = ui->textInput->toPlainText();
//    auto cipher = rsa.encryption(plainText.toStdString());
//    ui->textResult->setText(QString::fromStdString(cipher));
//}

//void Dialog::on_pushDecrypt_clicked()
//{
//    QString cipherText = ui->textInput->toPlainText();
//    auto plainText = rsa.decryption(cipherText.toStdString());
//    ui->textResult->setText(QString::fromStdString(plainText));
//}

void Dialog::on_pushEncrypt_clicked()
{
    QString plainText = ui->textInput->toPlainText();
    auto cipher = rsa.encryption(plainText.toStdString());
    ui->textResult->setText(QString::fromStdString(cipher));
}

void Dialog::on_pushDecrypt_clicked()
{
    QString cipherText = ui->textInput->toPlainText();
    auto plainText = rsa.decryption(cipherText.toStdString());
    ui->textResult->setText(QString::fromStdString(plainText));
}
