#include "LoanAdmin.h"
#include "ui_LoanAdmin.h"

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
#include<QIcon>
using namespace std;



LoanAdmin::LoanAdmin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoanAdmin)
{
    ui->setupUi(this);
    ui->nCode->setValidator( new QRegularExpressionValidator(QRegularExpression("[0-9]*")));
    ui->accNum->setValidator( new QRegularExpressionValidator(QRegularExpression("[0-9]*")));
    ui->money->setValidator( new QRegularExpressionValidator(QRegularExpression("[0-9]*")));

    QIcon ic(":/loan.png");
    this->setWindowIcon(ic);
}

LoanAdmin::~LoanAdmin()
{
    delete ui;
}

void LoanAdmin::on_okBtn_clicked()
{
    if(ui->accNum->text().isEmpty()||ui->nCode->text().isEmpty()||ui->money->text().isEmpty())
    {
        //QMessageBox::information(this,"message","Please fill up all the items!");
        //return;
    }
    else
    {
    long long int money=ui->money->text().toLongLong();

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
        if(ui->nCode->text() == x["nCode"].toString())
        {
            flag=2;

            arraySize=x["arrayOfMyAccounts"].toArray();
            for(i=0;i<arraySize.size();i++)
            {
            if(ui->accNum->text().toInt() == (((x["arrayOfMyAccounts"].toArray())[i]).toObject())["accountNumber"].toInt())
            {
                done=true;
                QJsonObject chAcc;
                chAcc["accountNumber"] =(((x["arrayOfMyAccounts"].toArray())[i]).toObject())["accountNumber"].toInt();
                chAcc["openDate"] =(((x["arrayOfMyAccounts"].toArray())[i]).toObject())["openDate"].toString();
                chAcc["accountType"] =(((x["arrayOfMyAccounts"].toArray())[i]).toObject())["accountType"].toString();
                long long int y = (((x["arrayOfMyAccounts"].toArray())[i]).toObject())["balance"].toVariant().toLongLong();


                    long long int m = y+money;
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

    if(flag==1)
    {
        QMessageBox *msg=new QMessageBox(QMessageBox::Critical,"message","User with this national code was not found!");
        msg->show();
        connect(msg,&QMessageBox::buttonClicked,msg,&QMessageBox::deleteLater,Qt::QueuedConnection);
    }
    if(flag==2)
    {
        QMessageBox *msg=new QMessageBox(QMessageBox::Critical,"message","There is no such account!");
        msg->show();
        connect(msg,&QMessageBox::buttonClicked,msg,&QMessageBox::deleteLater,Qt::QueuedConnection);
    }
    if(flag==0)
    {

       QJsonObject origin1;
       QJsonArray loans;
       QFile f2("D:/Loan.json");
       f2.open(QIODevice::ReadWrite);
       QJsonDocument d1 = QJsonDocument::fromJson(f2.readAll());
       QJsonObject o1 = d1.object();
       f2.close();
       foreach(QJsonValue x ,o1["Loans"].toArray())
       {
           loans.append(x.toObject());
       }
       QJsonObject json;
       json["accountNumber"] = ui->accNum->text().toInt();
       json["loanAmount"]= ui->money->text().toLongLong();
       json["nCode"] = ui->nCode->text();


       loans.append(json);
       origin1["Loans"] = loans;
       QJsonDocument document1;
       document1.setObject( origin1 );
       QByteArray bytes1 = document1.toJson(QJsonDocument::JsonFormat());
       QFile f3("D:/Loan.json");
       if( f3.open(QIODevice::Append | QIODevice::WriteOnly | QIODevice::Truncate))
        {
            QTextStream iStream( &f3 );
            iStream << bytes1;
            f3.close();
         }

        else
        {
            cout << "file open failed: " << endl;
        }




       QMessageBox::information(this,"","Done successfully.");
    }
   }

    return;
}

