#include "LoginLogout.h"
#include "ui_LoginLogout.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>
#include <QIcon>
LoginLogout::LoginLogout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginLogout)
{
    ui->setupUi(this);
    QIcon ico2(":/log.png");
    this->setWindowIcon(ico2);

}

QString LoginLogout::getnCode()
{
return this->nCode;
}

void LoginLogout::setNCode(QString _nCode)
{
   nCode=_nCode;
}

LoginLogout::~LoginLogout()
{
    delete ui;
}


void LoginLogout::on_pushButton_clicked()
{
    try
    {
        QFile logFile("D:/Logs.json");
        if(!logFile.open(QIODevice::ReadWrite))
        {
            bool isOpen =0;
            throw isOpen;
        }
        QJsonDocument doc = QJsonDocument::fromJson(logFile.readAll()) ;
        QJsonObject obj = doc.object();
        logFile.close();
        foreach(QJsonValue val , obj["Logs"].toArray())
        {
            if(val["nCode"]==getnCode())
            {


                ui->listWidget1->addItem(new QListWidgetItem(val.toObject()["LogIn"].toString()));
                ui->listWidget->addItem(new QListWidgetItem(val.toObject()["LogOut"].toString()));

                ui->listWidget1->show();
                ui->listWidget->show();


            }
        }
    }
    catch(bool isOpen)
    {
        QMessageBox *msg = new QMessageBox();
        msg->setText("file open failed.");
        msg->setIcon(QMessageBox::Critical);

    }
}

