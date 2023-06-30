#include "LoanCustomer.h"
#include "ui_LoanCustomer.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QTextStream>
#include <QtCore>
#include <QIODevice>
#include <QMessageBox>
#include <iostream>
#include<QIcon>
using namespace std;
void LoanCustomer::setaccNum(QString _accNum)
{
    accNum = _accNum;
}

QString LoanCustomer::getAccNum()
{
    return accNum;
}


LoanCustomer::LoanCustomer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoanCustomer)
{
    ui->setupUi(this);
    QIcon ic(":/loan.png");
    this->setWindowIcon(ic);


}
LoanCustomer::~LoanCustomer()
{
    delete ui;
}


void LoanCustomer::loanAmount()
{
    QFile file("D:/Loan.json");
    file.open(QIODevice::ReadWrite);
    QJsonDocument d = QJsonDocument::fromJson(file.readAll());
    QJsonObject o = d.object();
    file.close();

    foreach(QJsonValue x ,o["Loans"].toArray())
    {
        if(this->getAccNum() == QString::number(x["accountNumber"].toInt()))
        {
            ui->loanAmount->setText(QString::number(x["loanAmount"].toVariant().toLongLong()));
        }

    }
}

void LoanCustomer::on_pay_clicked()
{

    bool enough= true;
    long long price=ui->loanAmount->text().toLongLong();
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

    bool b=false;
    foreach(QJsonValue x ,o["accounts"].toArray())
    {
            b=false;
            arraySize=x["arrayOfMyAccounts"].toArray();
            for(int i=0;i<arraySize.size();i++)
            {
            if(this->getAccNum() == QString::number((((x["arrayOfMyAccounts"].toArray())[i]).toObject())["accountNumber"].toInt()))
            {
                b=true;
                QJsonObject chAcc;
                chAcc["accountNumber"] =(((x["arrayOfMyAccounts"].toArray())[i]).toObject())["accountNumber"].toInt();
                chAcc["openDate"] =(((x["arrayOfMyAccounts"].toArray())[i]).toObject())["openDate"].toString();
                chAcc["accountType"] =(((x["arrayOfMyAccounts"].toArray())[i]).toObject())["accountType"].toString();
                long long int y = (((x["arrayOfMyAccounts"].toArray())[i]).toObject())["balance"].toVariant().toLongLong();
                if(y<=price)
                {

                    enough = false;


                    chAcc["balance"] = (((x["arrayOfMyAccounts"].toArray())[i]).toObject())["balance"].toVariant().toLongLong();
                    arrayOfMyAccounts = x["arrayOfMyAccounts"].toArray();
                    arrayOfMyAccounts.removeAt(i);
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
                    arrayOfMyAccounts.removeAt(i);
                    arrayOfMyAccounts.append(chAcc);

                    person["arrayOfMyAccounts"]=arrayOfMyAccounts;
                    person["nCode"] = x["nCode"];
                    accountBuildArr.append(person);
                    enough=true;



            }

            }
         }

        if(b==false)
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
        QJsonObject popLoan;
        QJsonArray popLoanArr;
        QFile f2("D:/Loan.json");
        f2.open(QIODevice::ReadWrite);
        QJsonDocument d2 = QJsonDocument::fromJson(f2.readAll());
        QJsonObject o2 = d2.object();
        f2.close();

        foreach(QJsonValue x2 ,o2["Loans"].toArray())
        {
               if(this->getAccNum() != QString::number(x2["accountNumber"].toInt()))
               {
                   popLoanArr.append(x2.toObject());
               }
        }

        popLoan["Loans"] = popLoanArr;
        QJsonDocument document2;
        document2.setObject( popLoan );
        QByteArray bytes2 = document2.toJson(QJsonDocument::JsonFormat());
        if( f2.open(QIODevice::Append | QIODevice::WriteOnly | QIODevice::Truncate))
         {
            QTextStream iStream( &f2 );
            iStream << bytes2;
            f2.close();
          }
       QMessageBox::information(this,"","Done successfully.");
    }


    return;
}


