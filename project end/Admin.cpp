#include "Admin.h"
#include "ui_Admin.h"
#include <QIcon>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QTextStream>
#include <QtCore>
#include <QIODevice>
#include "AccountRequest.h"
#include "AddMoney.h"
#include "BlockAccount.h"
#include "LoanAdmin.h"


Admin::Admin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Admin)
{
    ui->setupUi(this);
    QIcon icon(":/admin.png");
    this->setWindowIcon(icon);
    //this->log();


}

Admin::~Admin()
{
    delete ui;
}

/*void Admin::log()
{
    try{

            QFile accFile("D:/PRO/Accounts.json");
            if(!accFile.open(QIODevice :: ReadOnly))
            {
                bool isOpen =0;
                throw isOpen;
            }
            QJsonDocument doc = QJsonDocument::fromJson(accFile.readAll());
            QJsonObject obj = doc.object();
            accFile.close();
            QJsonObject accountBuild;
            QJsonObject person;
            QJsonArray accountBuildArr;
            QJsonArray arrayOfMyAccounts;
            foreach(QJsonValue val, obj["accounts"].toArray())
            {
                foreach(QJsonValue v,val.toObject()["arrayOfMyAccounts"].toArray())
                {

                   if(v.toObject()["accountType"].toString()=="Shortterm Account" )
                    {
                        long long interest;
                        //sode kotahmodat ro beriz
                        shared_ptr<Account> acc (new ShortTermAccount());
                        interest=acc->calculateInterest();
                        QJsonObject chAcc;
                        chAcc["accountNumber"] =v.toObject()["accountNumber"].toInt();
                        chAcc["creditor"] = v.toObject()["creditor"];
                        chAcc["debtor"] = v.toObject()["debtor"];
                        chAcc["openDate"] =v.toObject()["openDate"].toString();
                        chAcc["accountType"] =v.toObject()["accountType"].toString();
                        long long int y = v.toObject()["balance"].toVariant().toLongLong();
                        long long int m = y+interest;
                        chAcc["balance"] = m;

                        arrayOfMyAccounts.append(chAcc);

                     }

                     else if(v.toObject()["accountType"].toString()=="Longterm Account" )
                     {
                        //sode bolandmodat ro beriz
                        shared_ptr<Account> acc (new LongTermAccount());
                        long long interest;
                        interest=acc->calculateInterest();
                        QJsonObject chAcc;
                        chAcc["accountNumber"] =v.toObject()["accountNumber"].toInt();
                        chAcc["creditor"] = v.toObject()["creditor"];
                        chAcc["debtor"] = v.toObject()["debtor"];
                        chAcc["openDate"] =v.toObject()["openDate"].toString();
                        chAcc["accountType"] =v.toObject()["accountType"].toString();
                        long long int y = v.toObject()["balance"].toVariant().toLongLong();
                        long long int m = y+interest;
                        chAcc["balance"] = m;
                        arrayOfMyAccounts.append(chAcc);


                     }
                   else if(v.toObject()["accountType"].toString()=="Current Account")
                   {
                       QJsonObject chAcc;
                       chAcc["accountNumber"] =v.toObject()["accountNumber"].toInt();
                       chAcc["creditor"] = v.toObject()["creditor"];
                       chAcc["debtor"] = v.toObject()["debtor"];
                       chAcc["openDate"] =v.toObject()["openDate"].toString();
                       chAcc["accountType"] =v.toObject()["accountType"].toString();
                       chAcc["balance"]= v.toObject()["balance"].toVariant().toLongLong();
                       arrayOfMyAccounts.append(chAcc);

                   }
                   else if(v.toObject()["accountType"].toString()=="Saving Account")
                   {
                       QJsonObject chAcc;
                       chAcc["accountNumber"] =v.toObject()["accountNumber"].toInt();
                       chAcc["creditor"] = v.toObject()["creditor"];
                       chAcc["debtor"] = v.toObject()["debtor"];
                       chAcc["openDate"] =v.toObject()["openDate"].toString();
                       chAcc["accountType"] =v.toObject()["accountType"].toString();
                       chAcc["balance"]= v.toObject()["balance"].toVariant().toLongLong();
                       arrayOfMyAccounts.append(chAcc);
                   }

                }
                person["arrayOfMyAccounts"]=arrayOfMyAccounts;
                person["nCode"] = val["nCode"];
                accountBuildArr.append(person);
            }
            accountBuild["accounts"] = accountBuildArr;

            QJsonDocument document;
            document.setObject( accountBuild );
            QByteArray bytes = document.toJson(QJsonDocument::JsonFormat());
            if(! accFile.open(QIODevice::Append | QIODevice::WriteOnly | QIODevice::Truncate))
             {
                bool isOpen =0;
                throw isOpen;
             }
            QTextStream iStream( &accFile );
            iStream << bytes;
            accFile.close();

        }
        catch(bool isOpen)
        {
            QMessageBox *msg = new QMessageBox();
            msg->setText("file open failed.");
            msg->setIcon(QMessageBox::Critical);
        }
    }
}*/

void Admin::on_accountRequest_clicked()
{
    AccountRequest* a = new AccountRequest(this);
    a->show();
}


void Admin::on_pushButton_clicked()
{
    AddMoney * ad=new AddMoney(this);
    ad->show();
    return;
}


void Admin::on_bloCKaCCOUNT_clicked()
{
    BlockAccount* b=new BlockAccount(this);
       b->show();
       return;
}


void Admin::on_pushButton_2_clicked()
{
    LoanAdmin * lad=new LoanAdmin(this);
    lad->show();
    return;
}

