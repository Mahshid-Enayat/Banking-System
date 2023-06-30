#include "CreditCharge.h"
#include "ui_CreditCharge.h"

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
#include <QRegularExpressionValidator>
#include<QIcon>
using namespace std;

inline long long int randomGen(long long int min_value  ,long long int max_value)
{
    rand();
    long long int random;
    random = rand() % (max_value - min_value)+ min_value;
    return random;
}


CreditCharge::CreditCharge(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreditCharge)
{
    ui->setupUi(this);
    ui->Amount->setValidator( new QRegularExpressionValidator(QRegularExpression("[0-9]*")));
    QIcon icn(":/charg.jpeg");
    this->setWindowIcon(icn);
}

CreditCharge::~CreditCharge()
{
    delete ui;
}

void CreditCharge::on_buy_clicked()
{
    if(ui->Amount->text().isEmpty())
    {
       QMessageBox::information(this,"","Please fill up all the items!");
       return;
    }
    else
    {
        this->pushB(ui->Amount->text().toLongLong());
    }
}

void CreditCharge::setaccNum(QString _accNum)
{
    accNum = _accNum;
}

QString CreditCharge::getAccNum()
{
    return accNum;
}

void CreditCharge::setNCode(QString _NCode)
{
    nCode =_NCode;
}

QString CreditCharge::getNCode()
{
    return nCode;
}

void CreditCharge::setIndex(int _index)
{
    index = _index;
}

int CreditCharge::getIndex()
{
    return index;
}

void CreditCharge::pushB(long long int price)
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
       QMessageBox::information(this,"Buy","Done successfully.");
       QMessageBox::information(this,"Your Code",QString::number(randomGen(10000000,99999999)));
    }

}
