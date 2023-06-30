#include "AccountRequest.h"
#include "ui_AccountRequest.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QTextStream>
#include <QtCore>
#include <QIODevice>
#include <iostream>
#include <QMessageBox>
#include <QString>
#include "ShortTermAccount.h"
#include "SavingAccount.h"
#include "LongTermAccount.h"
#include "CurrentAccount.h"

using namespace std;

QJsonValue k;

AccountRequest::AccountRequest(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AccountRequest)
{
    ui->setupUi(this);
    this->showInformationRequest();
}

AccountRequest::~AccountRequest()
{
    delete ui;
}

void AccountRequest::showInformationRequest()
{
    try
    {
        QFile f("D:/Account Request.json");
             if(!f.open(QIODevice::ReadWrite))
              {
                    bool isOpen =0;
                    throw isOpen;
              }

             QJsonDocument d = QJsonDocument::fromJson(f.readAll());
             QJsonObject o = d.object();
             if(int sizeFile = ((o["accountRequest"].toArray()).size()) ==0 )
             {
                 ui->finish->setText("Finished");
                 this->close();
                 return;
             }
             f.close();
             ui->AccountType_line_edit->setText(((o["accountRequest"].toArray()[0]).toObject())["accountType"].toString());
             ui->nationalCode_line_edit->setText(((o["accountRequest"].toArray()[0]).toObject())["nCode"].toString());
             k = ((o["accountRequest"].toArray()[0]).toObject())["amountOfMoney"];
            ui->ammountOfMoney_line_edit->setText(QString::number(((o["accountRequest"].toArray()[0]).toObject())["amountOfMoney"].toVariant().toLongLong()));
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


}

void AccountRequest::popFrontFile()
{
    QJsonObject accountRequest;
    QJsonArray accountRequestArr;

    try {
        QFile file("D:/Account Request.json");
        if(!file.open(QIODevice::ReadWrite))
         {
           bool isOpen =0;
            throw isOpen;
         }

        file.open(QIODevice::ReadWrite);
        QJsonDocument d = QJsonDocument::fromJson(file.readAll());
        QJsonObject o = d.object();
        file.close();
        foreach(QJsonValue x ,o["accountRequest"].toArray())
        {
               accountRequestArr.append(x);
        }
        accountRequestArr.pop_front();
        accountRequest["accountRequest"] = accountRequestArr;
        QJsonDocument document;
        document.setObject( accountRequest );
        QByteArray bytes = document.toJson(QJsonDocument::JsonFormat());
        if( !file.open(QIODevice::Append | QIODevice::WriteOnly | QIODevice::Truncate))
         {
            bool isOpen =0;
             throw isOpen;
          }

        QTextStream iStream( &file );
        iStream << bytes;
        file.close();

    }
    catch (bool isOpen) {

        if(isOpen==0)
         {
         QMessageBox *warningMsg = new QMessageBox();
          warningMsg->setText("Account Request file can not open.");
          warningMsg->setIcon(QMessageBox::Critical);
          warningMsg->show();
         }
    }


}

void AccountRequest::buildAccount()
{
    QJsonObject accountBuild;
    QJsonArray accountBuildArr;
    QJsonObject person;
    QJsonArray arrayOfMyAccounts;
    try{

    QFile file("D:/Accounts.json");
    if(!file.open(QIODevice::ReadWrite))
    {
        bool isOpen =0;
        throw isOpen;
    }
    QJsonDocument d = QJsonDocument::fromJson(file.readAll());
    QJsonObject o = d.object();
    file.close();
    bool exist = false ;
    foreach(QJsonValue x ,o["accounts"].toArray())
    {
        if(ui->nationalCode_line_edit->text() == x["nCode"].toString())
        {
            exist = true;
            if(ui->AccountType_line_edit->text() == "Shortterm Account")
            {
                QJsonObject shortacc;
                ShortTermAccount sh;
                sh.giveaccNumber();
                shortacc["accountNumber"] = sh.getaccNumber();
                shortacc["openDate"] = sh.getOpenAccDate().toString();
                shortacc["accountType"] = ui->AccountType_line_edit->text();              
                shortacc["balance"] = k;
                arrayOfMyAccounts = x["arrayOfMyAccounts"].toArray();
                arrayOfMyAccounts.append(shortacc);
                person["arrayOfMyAccounts"]=arrayOfMyAccounts;
                person["nCode"] = ui->nationalCode_line_edit->text();
                accountBuildArr.append(person);
            }
            else if(ui->AccountType_line_edit->text() == "Longterm Account")
            {
                QJsonObject longacc;
                LongTermAccount sh;
                sh.giveaccNumber();
                longacc["accountNumber"] = sh.getaccNumber();
                longacc["openDate"] = sh.getOpenAccDate().toString();
                longacc["accountType"] = ui->AccountType_line_edit->text();
                longacc["balance"] = k;
                arrayOfMyAccounts = x["arrayOfMyAccounts"].toArray();
                arrayOfMyAccounts.append(longacc);
                person["arrayOfMyAccounts"]=arrayOfMyAccounts;
                person["nCode"] = ui->nationalCode_line_edit->text();
                accountBuildArr.append(person);
            }
            else if(ui->AccountType_line_edit->text() == "Saving Account")
            {
                QJsonObject saveacc;
                SavingAccount sh;
                sh.giveaccNumber();
                saveacc["accountNumber"] = sh.getaccNumber();
                saveacc["openDate"] = sh.getOpenAccDate().toString();
                saveacc["accountType"] = ui->AccountType_line_edit->text();
                saveacc["balance"] = k;
                arrayOfMyAccounts = x["arrayOfMyAccounts"].toArray();
                arrayOfMyAccounts.append(saveacc);
                person["arrayOfMyAccounts"]=arrayOfMyAccounts;
                person["nCode"] = ui->nationalCode_line_edit->text();
                accountBuildArr.append(person);
            }
            else if(ui->AccountType_line_edit->text() == "Current Account")
            {
                QJsonObject currentacc;
                CurrentAccount sh;
                sh.giveaccNumber();
                currentacc["accountNumber"] = sh.getaccNumber();
                currentacc["openDate"] = sh.getOpenAccDate().toString();
                currentacc["accountType"] = ui->AccountType_line_edit->text();
                currentacc["balance"] = k;
                arrayOfMyAccounts = x["arrayOfMyAccounts"].toArray();
                arrayOfMyAccounts.append(currentacc);
                person["arrayOfMyAccounts"]=arrayOfMyAccounts;
                person["nCode"] = ui->nationalCode_line_edit->text();
                accountBuildArr.append(person);
            }
        }
        if(ui->nationalCode_line_edit->text() != x["nCode"].toString())
        {accountBuildArr.append(x.toObject());}
    }

    if(exist == false)
    {        
      person["nCode"] = ui->nationalCode_line_edit->text();
      if(ui->AccountType_line_edit->text() == "Shortterm Account")
      {
          QJsonObject shortacc;
          ShortTermAccount sh;
          sh.giveaccNumber();
          shortacc["accountNumber"] = sh.getaccNumber();
          shortacc["openDate"] = sh.getOpenAccDate().toString();
          shortacc["accountType"] = ui->AccountType_line_edit->text();
          shortacc["balance"] = k;
          arrayOfMyAccounts.append(shortacc);
          person["arrayOfMyAccounts"]=arrayOfMyAccounts;
          accountBuildArr.append(person);

      }
      else if(ui->AccountType_line_edit->text() == "Longterm Account")
      {
          QJsonObject longacc;
          LongTermAccount sh;
          sh.giveaccNumber();
          longacc["accountNumber"] = sh.getaccNumber();
          longacc["openDate"] = sh.getOpenAccDate().toString();
          longacc["accountType"] = ui->AccountType_line_edit->text();
          longacc["balance"] = k;
          arrayOfMyAccounts.append(longacc);
          person["arrayOfMyAccounts"]=arrayOfMyAccounts;
          accountBuildArr.append(person);

      }
      else if(ui->AccountType_line_edit->text() == "Saving Account")
      {
          QJsonObject saveacc;
          SavingAccount sh;
          sh.giveaccNumber();
          saveacc["accountNumber"] = sh.getaccNumber();
          saveacc["openDate"] = sh.getOpenAccDate().toString();
          saveacc["accountType"] = ui->AccountType_line_edit->text();
          saveacc["balance"] = k;
          arrayOfMyAccounts.append(saveacc);
          person["arrayOfMyAccounts"]=arrayOfMyAccounts;
          accountBuildArr.append(person);

      }
      else if(ui->AccountType_line_edit->text() == "Current Account")
      {
          QJsonObject currentacc;
          CurrentAccount sh;
          sh.giveaccNumber();
          currentacc["accountNumber"] = sh.getaccNumber();
          currentacc["openDate"] = sh.getOpenAccDate().toString();
          currentacc["accountType"] = ui->AccountType_line_edit->text();
          currentacc["balance"] = k;
          arrayOfMyAccounts.append(currentacc);
          person["arrayOfMyAccounts"]=arrayOfMyAccounts;
          accountBuildArr.append(person);

      }

    }

  accountBuild["accounts"] = accountBuildArr;

  QJsonDocument document;
  document.setObject( accountBuild );
  QByteArray bytes = document.toJson(QJsonDocument::JsonFormat());
  if( !file.open(QIODevice::Append | QIODevice::WriteOnly | QIODevice::Truncate))
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
          warningMsg->setText("Error");
          warningMsg->setIcon(QMessageBox::Critical);
          warningMsg->show();
         }
   }
}

void AccountRequest::on_accept_clicked()
{
  this->buildAccount();
  this->popFrontFile();
  this->showInformationRequest();
}


void AccountRequest::on_decline_clicked()
{
  this->popFrontFile();
  this->showInformationRequest();
}
