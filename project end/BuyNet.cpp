#include "BuyNet.h"
#include "ui_BuyNet.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QTextStream>
#include <QtCore>
#include <QIODevice>
#include<iostream>
#include<QString>
#include<QMessageBox>
#include<QIcon>
using namespace std;

BuyNet::BuyNet(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BuyNet)
{
    ui->setupUi(this);
    QIcon icn(":/net.png");
    this->setWindowIcon(icn);
}

BuyNet::~BuyNet()
{
    delete ui;
}

void BuyNet::setaccNum(QString _accNum)
{
    accNum = _accNum;
}

QString BuyNet::getAccNum()
{
    return accNum;
}

void BuyNet::setNCode(QString _NCode)
{
    nCode =_NCode;
}

QString BuyNet::getNCode()
{
    return nCode;
}

void BuyNet::setIndex(int _index)
{
    index = _index;
}

int BuyNet::getIndex()
{
    return index;
}

void BuyNet::pushB(long long int price)
{
    bool enough= true;

    QJsonObject accountBuild;
    QJsonArray accountBuildArr;
    QJsonObject person;
    QJsonArray arrayOfMyAccounts;
    QFile file("D:/Accounts.json");
    file.open(QIODevice::ReadWrite);
    QJsonDocument d = QJsonDocument::fromJson(file.readAll());
    QJsonObject o = d.object();
    foreach(QJsonValue x ,o["accounts"].toArray())
    {
        if(this->getNCode() == x["nCode"].toString())
        {
            if(this->getAccNum() == QString::number((((x["arrayOfMyAccounts"].toArray())[this->getIndex()]).toObject())["accountNumber"].toInt()))
            {
                QJsonObject chAcc;
                chAcc["accountNumber"] =(((x["arrayOfMyAccounts"].toArray())[this->getIndex()]).toObject())["accountNumber"].toInt();
                chAcc["openDate"] =(((x["arrayOfMyAccounts"].toArray())[this->getIndex()]).toObject())["openDate"].toString();
                chAcc["accountType"] =(((x["arrayOfMyAccounts"].toArray())[this->getIndex()]).toObject())["accountType"].toString();
                long long int y = (((x["arrayOfMyAccounts"].toArray())[this->getIndex()]).toObject())["balance"].toVariant().toLongLong();
                if(y<=price)
                {

                    enough = false;

                    chAcc["balance"] = (((x["arrayOfMyAccounts"].toArray())[this->getIndex()]).toObject())["balance"].toVariant().toLongLong();
                    arrayOfMyAccounts = x["arrayOfMyAccounts"].toArray();
                    arrayOfMyAccounts.removeAt(this->getIndex());
                    arrayOfMyAccounts.append(chAcc);
                    person["arrayOfMyAccounts"]=arrayOfMyAccounts;
                    person["nCode"] = x["nCode"];
                    accountBuildArr.append(person);
                    QMessageBox *msg=new QMessageBox(QMessageBox::Critical,"Error","Your balance is not enough.");
                    msg->show();
                    connect(msg,&QMessageBox::buttonClicked,msg,&QMessageBox::deleteLater,Qt::QueuedConnection);


                }
                if(y>price)
                {
                    long long int m = y-price;
                    chAcc["balance"] = m;

                    arrayOfMyAccounts = x["arrayOfMyAccounts"].toArray();
                    arrayOfMyAccounts.removeAt(this->getIndex());
                    arrayOfMyAccounts.append(chAcc);

                    person["arrayOfMyAccounts"]=arrayOfMyAccounts;
                    person["nCode"] = x["nCode"];
                    accountBuildArr.append(person);


                }

            }

        }

        else
        {
           accountBuildArr.append(x.toObject());
        }
    }

    file.close();
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

    if(enough)
    {
       QMessageBox::information(this,"","Done successfully.");
    }

}


void BuyNet::on_p1_clicked()
{
  this->pushB(300000);    
}

void BuyNet::on_p2_clicked()
{
    this->pushB(350000);
}


void BuyNet::on_p3_clicked()
{
    this->pushB(450000);
}


void BuyNet::on_p4_clicked()
{
    this->pushB(500000);
}


void BuyNet::on_p5_clicked()
{
    this->pushB(580000);
}


void BuyNet::on_p6_clicked()
{
   this->pushB(650000);
}


void BuyNet::on_p7_clicked()
{
    this->pushB(700000);
}


void BuyNet::on_p8_clicked()
{
    this->pushB(740000);
}


void BuyNet::on_p9_clicked()
{
    this->pushB(800000);
}


void BuyNet::on_p10_clicked()
{
    this->pushB(840000);
}


void BuyNet::on_p11_clicked()
{
    this->pushB(890000);
}


void BuyNet::on_p12_clicked()
{
    this->pushB(950000);
}
