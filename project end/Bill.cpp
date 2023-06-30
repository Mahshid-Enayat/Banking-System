#include "Bill.h"
#include "ui_Bill.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QTextStream>
#include <QtCore>
#include <QIODevice>
#include <iostream>
#include <QString>
#include <QMessageBox>
#include <QRegularExpressionValidator>
#include <QIcon>
using namespace std;

Bill::Bill(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Bill)
{
    ui->setupUi(this);
    ui->price->setValidator( new QRegularExpressionValidator(QRegularExpression("[0-9]*")));
    ui->lineEdit->setValidator( new QRegularExpressionValidator(QRegularExpression("[0-9]*")));
    ui->lineEdit_3->setValidator( new QRegularExpressionValidator(QRegularExpression("[0-9]*")));
    QIcon icn(":/bill.jpeg");
    this->setWindowIcon(icn);
}

Bill::~Bill()
{
    delete ui;
}

void Bill::on_payButton_clicked()
{
    if(ui->price->text().isEmpty()||ui->lineEdit->text().isEmpty()||ui->lineEdit_3->text().isEmpty())
    {
       QMessageBox::information(this,"","Please fill up all the items!");
       return;
    }
    else
    {
        this->pushB(ui->price->text().toLongLong());
    }
}

void Bill::setaccNum(QString _accNum)
{
    accNum = _accNum;
}

QString Bill::getAccNum()
{
    return accNum;
}

void Bill::setNCode(QString _NCode)
{
    nCode =_NCode;
}

QString Bill::getNCode()
{
    return nCode;
}

void Bill::setIndex(int _index)
{
    index = _index;
}

int Bill::getIndex()
{
    return index;
}

void Bill::pushB(long long price)
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
