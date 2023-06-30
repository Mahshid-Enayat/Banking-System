#include <QRegularExpressionValidator>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>
#include<iostream>
#include "CardByCard.h"
#include "ui_CardByCard.h"

using namespace std;

CardByCard::CardByCard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CardByCard)
{
    ui->setupUi(this);
    ui->fromCardLineEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]*")));
    ui->toCardLineEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]*")));
    ui->amountLineEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]*")));
    ui->cvv2LineEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]*")));
    ui->otpLineEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]*")));
}

void CardByCard::setaccNum(QString _accNum)
{
    accNum = _accNum;
}

QString CardByCard::getAccNum()
{
    return accNum;
}

void CardByCard::setNCode(QString _NCode)
{
    nCode =_NCode;
}

QString CardByCard::getNCode()
{
    return nCode;
}

void CardByCard::setIndex(int _index)
{
    index = _index;
}

int CardByCard::getIndex()
{
    return index;
}

void CardByCard::reduceSenderBalance(long long price)
{

    bool enough= true;

    QJsonObject accountBuild;
    QJsonArray accountBuildArr;
    QJsonObject person;
    QJsonArray arrayOfMyAccounts;

   try
    {
        QFile cardFile("D:/Card.json");
        if(!cardFile.open(QIODevice::ReadWrite))
        {
            bool isOpen = 0;
            throw isOpen;
        }
        QJsonDocument d = QJsonDocument::fromJson(cardFile.readAll());
        QJsonObject o = d.object();
        cardFile.close();
        foreach(QJsonValue w ,o["Cards"].toArray())
        {
            if(ui->fromCardLineEdit->text().toLongLong() == (w).toObject()["cardNumber"].toVariant().toLongLong() && this->getAccNum()==(w).toObject()["accountNumber"].toString())
            {
                     if((!(ui->expiredYearLineEdit->text().toInt()==(w).toObject()["exp_year"].toInt())) && (!ui->expiredYearLineEdit->text().isEmpty()) )
                     {
                         ui->expYearLabel->setText("This field is incorrect");
                         ui->expYearLabel->show();
                         ui->expiredYearLineEdit->clear();
                     }
                     if((!(ui->expiredMonth->text().toInt()==(w).toObject()["exp_month"].toInt())) && (ui->expiredMonth->text()!='0') )
                     {
                         ui->expMonthLabel->setText("This field is incorrect");
                         ui->expMonthLabel->show();
                         ui->expiredMonth->clear();
                     }
                     if((ui->expiredYearLineEdit->text().toInt()==(w).toObject()["exp_year"].toInt()) &&
                             (ui->expiredMonth->text().toInt()==(w).toObject()["exp_month"].toInt())  &&
                             (ui->cvv2LineEdit->text().toInt()== (w).toObject()["cvv2"].toInt()))
                     {
                         QFile file("D:/Accounts.json");
                         file.open(QIODevice::ReadWrite);
                         QJsonDocument d = QJsonDocument::fromJson(file.readAll());
                         QJsonObject o = d.object();
                         file.close();
                         foreach(QJsonValue x ,o["accounts"].toArray())
                         {
                             if(this->getNCode() == x["nCode"].toString())
                             {
                                 if(this->getAccNum()== QString::number((((x["arrayOfMyAccounts"].toArray())[this->getIndex()]).toObject())["accountNumber"].toInt()))
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
                     }}}}

    catch(bool isOpen)
    {
        QMessageBox *msg = new QMessageBox();
        msg->setText("File open failed");
        msg->setIcon(QMessageBox::Critical);
        msg->show();
    }
}

void CardByCard::increasReceiverBalance(long long price)
{
    QJsonObject accountBuild;
    QJsonArray accountBuildArr;
    QJsonObject person;
    QJsonArray arrayOfMyAccounts;
    int exist = 0;

   try
    {
        QFile cardFile("D:/Card.json");
        if(!cardFile.open(QIODevice::ReadWrite))
        {
            bool isOpen = 0;
            throw isOpen;
        }
        QJsonDocument d = QJsonDocument::fromJson(cardFile.readAll());
        QJsonObject o = d.object();
        cardFile.close();
        QString accNum;
        QString NCOde;
        foreach(QJsonValue w ,o["Cards"].toArray())
        {
            if(ui->toCardLineEdit->text().toLongLong() == (w).toObject()["cardNumber"].toVariant().toLongLong())
            {
                exist = 1;
                accNum = (w).toObject()["accountNumber"].toString();
                NCOde = (w).toObject()["nCode"].toString();
                         QFile file("D:/Accounts.json");
                         file.open(QIODevice::ReadWrite);
                         QJsonDocument d = QJsonDocument::fromJson(file.readAll());
                         QJsonObject o = d.object();
                         file.close();
                         foreach(QJsonValue x ,o["accounts"].toArray())
                         {
                             if(NCOde == x["nCode"].toString())
                             {
                                 if(accNum== QString::number((((x["arrayOfMyAccounts"].toArray())[this->getIndex()]).toObject())["accountNumber"].toInt()))
                                 {
                                     QJsonObject chAcc;
                                     chAcc["accountNumber"] =(((x["arrayOfMyAccounts"].toArray())[this->getIndex()]).toObject())["accountNumber"].toInt();
                                     chAcc["openDate"] =(((x["arrayOfMyAccounts"].toArray())[this->getIndex()]).toObject())["openDate"].toString();
                                     chAcc["accountType"] =(((x["arrayOfMyAccounts"].toArray())[this->getIndex()]).toObject())["accountType"].toString();
                                     long long int y = (((x["arrayOfMyAccounts"].toArray())[this->getIndex()]).toObject())["balance"].toVariant().toLongLong();
                                     long long int m = y+price;
                                     chAcc["balance"] = m;
                                     arrayOfMyAccounts = x["arrayOfMyAccounts"].toArray();
                                     arrayOfMyAccounts.removeAt(this->getIndex());
                                     arrayOfMyAccounts.append(chAcc);
                                     person["arrayOfMyAccounts"]=arrayOfMyAccounts;
                                     person["nCode"] = x["nCode"];
                                     accountBuildArr.append(person);


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
                     }}}

    catch(bool isOpen)
    {
        QMessageBox *msg = new QMessageBox();
        msg->setText("File open failed");
        msg->setIcon(QMessageBox::Critical);
        msg->show();
    }



    if(exist==1)
    {
        QMessageBox *msg = new QMessageBox();
        msg->setText("Transfer is Done.");
        msg->setIcon(QMessageBox::Information);
        msg->show();
    }
    else if(exist==0)
    {
        QMessageBox *msg = new QMessageBox();
        msg->setText("This information is not true.");
        msg->setIcon(QMessageBox::Critical);
        msg->show();
    }

}
void CardByCard::on_OKbtn_clicked()
{
    reduceSenderBalance(ui->amountLineEdit->text().toLongLong());
    increasReceiverBalance(ui->amountLineEdit->text().toLongLong());

}

CardByCard::~CardByCard()
{
    delete ui;
}




