#include "AddAccount.h"
#include "ui_AddAccount.h"
#include <iostream>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QTextStream>
#include <QtCore>
#include <QIODevice>
#include <QMessageBox>
#include <QRegularExpressionValidator>
#include <QIcon>
using namespace std;

AddAccount::AddAccount(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddAccount)
{
    ui->setupUi(this);
    ui->amountOfMoney->setValidator( new QRegularExpressionValidator(QRegularExpression("[0-9]*")));
    QIcon icon2(":/addAccount.png");
    this->setWindowIcon(icon2);
}

AddAccount::~AddAccount()
{
    delete ui;
}

void AddAccount::on_pushButton_clicked()
{
    if(ui->amountOfMoney->text().isEmpty())
    {
        QMessageBox::information(this,"Account Request","Please fill up all the items!");
        return;
    }
    else
    {
        if((ui->accountType->currentText() == "Current Account"  &&  ui->amountOfMoney->text().toLongLong() >=500000)  ||
               (ui->accountType->currentText() == "Saving Account"  &&  ui->amountOfMoney->text().toLongLong()>=200000)  ||
                (ui->accountType->currentText() == "Shortterm Account"  &&  ui->amountOfMoney->text().toLongLong()>=500000)  ||
                (ui->accountType->currentText() == "Longterm Account"  &&  ui->amountOfMoney->text().toLongLong()>=1000000)  )
        {
            QJsonObject accountRequest;
            QJsonArray accountRequestArr;
           try
            {
            QFile file("D:/Account Request.json");
            if(!file.open(QIODevice::ReadWrite))
            {
                bool isOpen =0;
                throw isOpen;
            }
            QJsonDocument d = QJsonDocument::fromJson(file.readAll());
            QJsonObject o = d.object();
            file.close();
            QJsonObject json;
            int sizeFile = ((o["accountRequest"].toArray()).size()) ;
            foreach(QJsonValue x ,o["accountRequest"].toArray())
            {
                if( accountRequestArr.size() == sizeFile -1 )
                {
                    json["nCode"] = x["nCode"].toString();
                }
                else
                {
                    accountRequestArr.append(x.toObject());
                }
            }

            json["accountType"] = ui->accountType->currentText();
            json["amountOfMoney"] = ui->amountOfMoney->text().toLongLong();
            accountRequestArr.append(json);
            accountRequest["accountRequest"] = accountRequestArr;
            QJsonDocument document;
            document.setObject( accountRequest );
            QByteArray bytes = document.toJson(QJsonDocument::JsonFormat());
            if(! file.open(QIODevice::Append | QIODevice::WriteOnly | QIODevice::Truncate))
             {
                bool isOpen =0;
                throw isOpen;
             }
            QTextStream iStream( &file );
            iStream << bytes;
            file.close();
            }

             catch(bool isOpen)
             {
                if(isOpen==0)
                {
                     QMessageBox *warningMsg = new QMessageBox();
                     warningMsg->setText("Account Request file can not open.");
                     warningMsg->setIcon(QMessageBox::Critical);
                     warningMsg->show();
                }
             }


            QMessageBox *msg=new QMessageBox(QMessageBox::Information,"Request","Your request has been successfully sent.");
            msg->show();
            connect(msg,&QMessageBox::buttonClicked,msg,&QMessageBox::deleteLater,Qt::QueuedConnection);
        }

        else
        {
            QMessageBox *msg=new QMessageBox(QMessageBox::Warning ,"Request Error","Your amount of money is not enough for this type of account!");
            msg->show();
            connect(msg,&QMessageBox::buttonClicked,msg,&QMessageBox::deleteLater,Qt::QueuedConnection);
        }

    }

    this->close();

}

