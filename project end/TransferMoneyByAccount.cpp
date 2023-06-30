#include "TransferMoneyByAccount.h"
#include "ui_TransferMoneyByAccount.h"

#include <QMessageBox>
#include <iostream>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QTextStream>
#include <QtCore>
#include <QIODevice>
#include<memory>
#include "ShortTermAccount.h"
#include "LongTermAccount.h"
#include "CurrentAccount.h"
#include "SavingAccount.h"
#include"Account.h"
#include<QIcon>

using namespace std;

TransferMoneyByAccount::TransferMoneyByAccount(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TransferMoneyByAccount)
{
    ui->setupUi(this);
    QIcon icn(":/transfer.png");
    this->setWindowIcon(icn);
}

TransferMoneyByAccount::~TransferMoneyByAccount()
{
    delete ui;
}

void TransferMoneyByAccount::setaccNum(QString _accNum)
{
    accNum = _accNum;
}

QString TransferMoneyByAccount::getAccNum()
{
    return accNum;
}

void TransferMoneyByAccount::setNCode(QString _NCode)
{
    nCode =_NCode;
}

QString TransferMoneyByAccount::getNCode()
{
    return nCode;
}

void TransferMoneyByAccount::setIndex(int _index)
{
    index = _index;
}

int TransferMoneyByAccount::getIndex()
{
    return index;
}

void TransferMoneyByAccount::setTypeAccount(QString _accType)
{
  this->accType =_accType;
}

QString TransferMoneyByAccount::gettypeAccount()
{
    return this->accType;
}


void TransferMoneyByAccount::on_pushButton_clicked()
{



    if(ui->toaccount->text().isEmpty()||ui->amount->text().isEmpty())
    {
        QMessageBox::information(this,"message","Please fill up all the items!");
    }

    else
    {

    long long int price=ui->amount->text().toLongLong();

    shared_ptr<Account> acc;
    if(this->gettypeAccount()=="Shortterm Account")
    {
        acc =make_shared<ShortTermAccount>();
    }
    else if(this->gettypeAccount()=="Longterm Account")
    {
        acc =make_shared<LongTermAccount>();
        acc->transferMoneyViaAccount(this->getAccNum(),this->getIndex(),this->getNCode(),price,ui->toaccount->text());
        return;
    }
    else if(this->gettypeAccount()=="Saving Account")
    {
        acc =make_shared<SavingAccount>();
    }
    else if(this->gettypeAccount()=="Current Account")
    {
        acc =make_shared<CurrentAccount>();
    }

    acc->transferMoneyViaAccount(this->getAccNum(),this->getIndex(),this->getNCode(),price,ui->toaccount->text());

    if(acc->getEnoughBalance() && acc->checkExistaccountNumber(ui->toaccount->text()))
    {
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
        int flag=1;
        int i;
        bool done=false;

        foreach(QJsonValue x ,o["accounts"].toArray())
        {
            done = false;
                arraySize=x["arrayOfMyAccounts"].toArray();
                for(i=0;i<arraySize.size();i++)
                {
                if(ui->toaccount->text().toInt() == (((x["arrayOfMyAccounts"].toArray())[i]).toObject())["accountNumber"].toInt())
                {

                        done=true;
                        QJsonObject chAcc;
                        chAcc["accountNumber"] =(((x["arrayOfMyAccounts"].toArray())[i]).toObject())["accountNumber"].toInt();
                        chAcc["openDate"] =(((x["arrayOfMyAccounts"].toArray())[i]).toObject())["openDate"].toString();
                        chAcc["accountType"] =(((x["arrayOfMyAccounts"].toArray())[i]).toObject())["accountType"].toString();
                        long long int y = (((x["arrayOfMyAccounts"].toArray())[i]).toObject())["balance"].toVariant().toLongLong();


                            long long int m = y+price;
                            chAcc["balance"] = m;

                            arrayOfMyAccounts = x["arrayOfMyAccounts"].toArray();
                            arrayOfMyAccounts.removeAt(i);
                            arrayOfMyAccounts.append(chAcc);

                            person["arrayOfMyAccounts"]=arrayOfMyAccounts;
                            person["nCode"] = x["nCode"];
                            accountBuildArr.append(person);
                            flag=0;

                }
                }
                if(done==false)
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
        if(flag==0)
        {
           QMessageBox::information(this,"","Done successfully.");
        }
    }

    else
    {
        QMessageBox *msg=new QMessageBox(QMessageBox::Critical,"Error"," There is no such account or your balance is not enough!");
        msg->show();
        connect(msg,&QMessageBox::buttonClicked,msg,&QMessageBox::deleteLater,Qt::QueuedConnection);
    }
   }
    return;
}

