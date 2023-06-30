#include "CurrentAccount.h"
#include<iostream>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QTextStream>
#include <QtCore>
#include <QIODevice>
#include<QMessageBox>
using namespace std;

CurrentAccount::CurrentAccount()
{
    setInterest(0);
    setCalDateOfInterest(getOpenAccDate());
    setType("Current Account");
}

CurrentAccount::~CurrentAccount()
{

}


long long CurrentAccount::calculateInterest()
{
    return 0;
}

void CurrentAccount::transferMoneyViaAccount(QString accNum, int _index, QString _nCode , long long int amount, QString _toaccountNum)
{
    if(this->checkExistaccountNumber(_toaccountNum))
    {
        bool enough;
        QJsonObject accountBuild;
        QJsonArray accountBuildArr;
        QJsonObject person;
        QJsonArray arrayOfMyAccounts;
        QFile file("D:/Accounts.json");
        file.open(QIODevice::ReadWrite);
        QJsonDocument d = QJsonDocument::fromJson(file.readAll());
        QJsonObject o = d.object();
        file.close();
        foreach(QJsonValue x ,o["accounts"].toArray())
        {
            if(_nCode == x["nCode"].toString())
            {
                if(accNum == QString::number((((x["arrayOfMyAccounts"].toArray())[_index]).toObject())["accountNumber"].toInt()))
                {

                    QJsonObject chAcc;
                    chAcc["accountNumber"] =(((x["arrayOfMyAccounts"].toArray())[_index]).toObject())["accountNumber"].toInt();
                    chAcc["openDate"] =(((x["arrayOfMyAccounts"].toArray())[_index]).toObject())["openDate"].toString();
                    chAcc["accountType"] =(((x["arrayOfMyAccounts"].toArray())[_index]).toObject())["accountType"].toString();
                    long long int y = (((x["arrayOfMyAccounts"].toArray())[_index]).toObject())["balance"].toVariant().toLongLong();
                    if(y<=amount)
                    {

                        enough = false;


                        chAcc["balance"] = (((x["arrayOfMyAccounts"].toArray())[_index]).toObject())["balance"].toVariant().toLongLong();
                        arrayOfMyAccounts = x["arrayOfMyAccounts"].toArray();
                        arrayOfMyAccounts.removeAt(_index);
                        arrayOfMyAccounts.append(chAcc);
                        person["arrayOfMyAccounts"]=arrayOfMyAccounts;
                        person["nCode"] = x["nCode"];
                        accountBuildArr.append(person);
                    }
                    if(y>amount)
                    {

                        enough = true;
                        long long int m = y-amount;
                        chAcc["balance"] = m;

                        arrayOfMyAccounts = x["arrayOfMyAccounts"].toArray();
                        arrayOfMyAccounts.removeAt(_index);
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

        if(enough )
        {
           this->setEnoughBalance(true);
        }

        else if(false==enough)
        {
            this->setEnoughBalance(false);
        }
    }

    return;
}
