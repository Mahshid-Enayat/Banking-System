#include "BlockAccount.h"
#include "ui_BlockAccount.h"

#include <iostream>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QTextStream>
#include <QtCore>
#include <QIODevice>
#include <QString>
#include <QRegularExpressionValidator>
#include <QIcon>
using namespace std;


BlockAccount::BlockAccount(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BlockAccount)
{
    ui->setupUi(this);
    ui->accNumber->setValidator( new QRegularExpressionValidator(QRegularExpression("[0-9]*")));
    ui->ncode->setValidator( new QRegularExpressionValidator(QRegularExpression("[0-9]*")));

    QIcon i(":/block.png");
    this->setWindowIcon(i);
}

BlockAccount::~BlockAccount()
{
    delete ui;
}


void BlockAccount::on_okBtn_clicked()
{
    QString acNum;
    QJsonObject accountBuild;
    QJsonArray accountBuildArr;
    QJsonObject person;
    QJsonArray arrayOfMyAccounts;
    QJsonArray arraySize;
    QFile file("D:/Accounts.json");
    file.open(QIODevice::ReadWrite);
    QJsonDocument d = QJsonDocument::fromJson(file.readAll());
    QJsonObject o = d.object();
    file.close();
    int done=0;
    int i;
    bool b=false;
    foreach(QJsonValue x ,o["accounts"].toArray())
    {

        if(ui->ncode->text() == x["nCode"].toString())
        {

            done=2;
                 arraySize=x["arrayOfMyAccounts"].toArray();
                 for(i=0;i<arraySize.size();i++)
                 {
                 if(ui->accNumber->text().toInt() == (((x["arrayOfMyAccounts"].toArray())[i]).toObject())["accountNumber"].toInt())
                 {
                        acNum=QString::number((((x["arrayOfMyAccounts"].toArray())[i]).toObject())["accountNumber"].toInt());
                        b=true;
                        arrayOfMyAccounts = x["arrayOfMyAccounts"].toArray();
                        arrayOfMyAccounts.removeAt(i);

                        person["arrayOfMyAccounts"]=arrayOfMyAccounts;
                        person["nCode"] = x["nCode"];
                        accountBuildArr.append(person);
                        done=1;

                 }
                 }
                 if(b==false)
                 {
                      accountBuildArr.append(x.toObject());
                 }

        }

        else
        {
           accountBuildArr.append(x.toObject());
        }
    }


    accountBuild["accounts"] = accountBuildArr;

    QJsonDocument document;
    document.setObject( accountBuild );
    QByteArray bytes = document.toJson(QJsonDocument::JsonFormat());
    if( file.open(QIODevice::Append | QIODevice::WriteOnly | QIODevice::Truncate))
     {
         QTextStream iStream( &file );
         iStream << bytes;
         file.close();
      }

     else
     {
         cout << "file open failed: " << endl;
      }

    QFile f("D:/Card.json");
    f.open(QIODevice::ReadWrite);
    QJsonDocument dd = QJsonDocument::fromJson(f.readAll());
    QJsonObject oo = dd.object();
    QJsonArray cardArray;
    QJsonObject cardObj;
    f.close();

    foreach(QJsonValue x1 ,oo["Cards"].toArray())
    {

        if(x1["accountNumber"].toString() == acNum)
        {

        }

        else
        {
            cardArray.append(x1.toObject());
        }
    }


    cardObj["Cards"] = cardArray;

    QJsonDocument document1;
    document1.setObject(cardObj );
    QByteArray bytes1 = document1.toJson(QJsonDocument::JsonFormat());
    if( f.open(QIODevice::Append | QIODevice::WriteOnly | QIODevice::Truncate))
     {
         QTextStream iStream( &f );
         iStream << bytes1;
         f.close();
    }



    if(done==0)
    {
        QMessageBox *msg=new QMessageBox(QMessageBox::Critical,"Blocking account","There is no user with this national code!");
        msg->show();
        connect(msg,&QMessageBox::buttonClicked,msg,&QMessageBox::deleteLater,Qt::QueuedConnection);
    }
    if(done==2)
    {
        QMessageBox *msg=new QMessageBox(QMessageBox::Critical,"Blocking account","There is no account with this number!");
        msg->show();
        connect(msg,&QMessageBox::buttonClicked,msg,&QMessageBox::deleteLater,Qt::QueuedConnection);
    }
    if(done==1)
    {
        QMessageBox *msg=new QMessageBox(QMessageBox::Information,"Blocking account","Done successfully!");
        msg->show();
        connect(msg,&QMessageBox::buttonClicked,msg,&QMessageBox::deleteLater,Qt::QueuedConnection);
    }


    this->close();

    return;

}
