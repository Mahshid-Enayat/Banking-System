#include "Customer.h"
#include "ui_Customer.h"
#include"LoginLogout.h"
#include <QIODevice>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include "Login.h"
#include "AddAccount.h"
#include "MyAccounts.h"
#include "EditProfile.h"
#include<QIcon>
#include<QMessageBox>

Customer::Customer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Customer)
{
    ui->setupUi(this);
    QIcon icon1(":/c.png");
    this->setWindowIcon(icon1);

       ui->first->setText(getFirstName());
       ui->last->setText(getLastName());
       ui->ncode->setText(getN_Code());
       try{
           QJsonObject origin;
           QJsonArray logs;
           QDateTime logTime;
           QFile f("D:/Logs.json");
           f.open(QIODevice::ReadWrite);
           QJsonDocument d = QJsonDocument::fromJson(f.readAll());
           QJsonObject o = d.object();
           f.close();
           foreach(QJsonValue x ,o["Logs"].toArray())
           {
               logs.append(x.toObject());
           }


           QJsonObject obj;
           obj["LogIn"]=logTime.currentDateTime().toString();
           obj["nCode"]=this->getN_Code();
           logs.append(obj);
           origin["Logs"]=logs;
           QJsonDocument doc;
           doc.setObject(origin);
           QByteArray bytes = doc.toJson(QJsonDocument::JsonFormat());
           QFile logFile("D:/Logs.json");
           if( !logFile.open(QIODevice::Append|QIODevice::WriteOnly|QIODevice::Truncate))
            {
               bool isOpen=0;
               throw isOpen;

            }
           QTextStream iStream( &logFile );
           iStream << bytes;
           logFile.close();

       }

       catch(bool isOpen)
       {
           QMessageBox *msg = new QMessageBox;
           msg->setText("open file failed.");
           msg->show();
       }
}

Customer::Customer(QString _firstName, QString _lastName, QString _n_code,
                   QString _phoneNumber, QString _landLine, QString _username,
                   QString _password, int _year, int _month, int _day, QString _email)
                  :Person(_firstName,_lastName,_n_code,_phoneNumber,_landLine,_username,
                   _password,_year,_month,_day,_email),ui(new Ui::Customer)
{

    ui->setupUi(this);
    ui->first->setText(getFirstName());
    ui->last->setText(getLastName());
    ui->ncode->setText(getN_Code());
    QIcon icon1(":/c.png");
    this->setWindowIcon(icon1);
       try{
           QJsonObject origin;
           QJsonArray logs;
           QDateTime logTime;
           QFile f("D:/Logs.json");
           f.open(QIODevice::ReadWrite);
           QJsonDocument d = QJsonDocument::fromJson(f.readAll());
           QJsonObject o = d.object();
           f.close();
           foreach(QJsonValue x ,o["Logs"].toArray())
           {
               logs.append(x.toObject());
           }


           QJsonObject obj;
           obj["LogIn"]=logTime.currentDateTime().toString();
           obj["nCode"]=this->getN_Code();
           logs.append(obj);
           origin["Logs"]=logs;
           QJsonDocument doc;
           doc.setObject(origin);
           QByteArray bytes = doc.toJson(QJsonDocument::JsonFormat());
           QFile logFile("D:/Logs.json");
           if( !logFile.open(QIODevice::Append|QIODevice::WriteOnly|QIODevice::Truncate))
            {
               bool isOpen=0;
               throw isOpen;

            }
           QTextStream iStream( &logFile );
           iStream << bytes;
           logFile.close();

       }

       catch(bool isOpen)
       {
           QMessageBox *msg = new QMessageBox;
           msg->setText("open file failed.");
           msg->show();
       }
}

Customer::~Customer()
{
    delete ui;
}



void Customer::on_OpenNewAccount_clicked()
{
    QJsonObject accountRequest;
    QJsonArray accountRequestArr;
    QFile f("D:/Account Request.json");
    f.open(QIODevice::ReadWrite);
    QJsonDocument d = QJsonDocument::fromJson(f.readAll());
    QJsonObject o = d.object();
    f.close();
    foreach(QJsonValue x ,o["accountRequest"].toArray())
    {
        accountRequestArr.append(x.toObject());
    }

    QJsonObject json;
    json["nCode"] = this->getN_Code();
    accountRequestArr.append(json);
    accountRequest["accountRequest"] = accountRequestArr;
    QJsonDocument document;
    document.setObject( accountRequest );
    QByteArray bytes = document.toJson(QJsonDocument::JsonFormat());
    QFile file("D:/Account Request.json");
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
    AddAccount* acc= new AddAccount(this);
    acc->show();

}


void Customer::on_MyAccounts_clicked()
{

    MyAccounts * a = new MyAccounts(this);
    a->setNCode(ui->ncode->text());
    a->start();
    a->show();
    return;
}

void Customer::on_Logout_clicked()
{
       this->close();
       Login * l= new Login(this);
       l->show();
       try{
           QJsonObject origin;
           QJsonArray logs;
           QDateTime logTime;
           QFile f("D:/Logs.json");
           f.open(QIODevice::ReadWrite);
           QJsonDocument d = QJsonDocument::fromJson(f.readAll());
           QJsonObject o = d.object();
           f.close();
           foreach(QJsonValue x ,o["Logs"].toArray())
           {
               logs.append(x.toObject());
           }


           QJsonObject obj;
           obj["LogOut"]=logTime.currentDateTime().toString();
           obj["nCode"]=this->getN_Code();
           logs.append(obj);
           origin["Logs"]=logs;
           QJsonDocument doc;
           doc.setObject(origin);
           QByteArray bytes = doc.toJson(QJsonDocument::JsonFormat());
           QFile logFile("D:/Logs.json");
           if( !logFile.open(QIODevice::Append|QIODevice::WriteOnly|QIODevice::Truncate))
            {
               bool isOpen=0;
               throw isOpen;

            }
           QTextStream iStream( &logFile );
           iStream << bytes;
           logFile.close();

       }

       catch(bool isOpen)
       {
           QMessageBox *msg = new QMessageBox;
           msg->setText("open file failed.");
           msg->show();
       }
       return;
}



void Customer::on_editprofile_clicked()
{
    EditProfile* e=new EditProfile(this);
    e->setNCode(this->getN_Code());
    e->show();
    return;
}


void Customer::on_enteryExitTime_clicked()
{
    LoginLogout *window = new LoginLogout();
        window->setNCode(this->getN_Code());
        window->show();
        return;
}

