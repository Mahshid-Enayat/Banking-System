#include "MyAccounts.h"
#include "ui_MyAccounts.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QTextStream>
#include <QtCore>
#include <QIODevice>
#include <QMessageBox>
#include "BuyNet.h"
#include "Bill.h"
#include "CreditCharge.h"
#include "Cheq.h"
#include "TransferMoneyByAccount.h"
#include"LoanCustomer.h"

MyAccounts::MyAccounts(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyAccounts)
{
    ui->setupUi(this);
    index =0;
}

MyAccounts::~MyAccounts()
{
    delete ui;
}

void MyAccounts::setNCode(QString _nCode)
{
    this->ncode = _nCode;
}

QString MyAccounts::getNCode()
{
    return ncode;
}

void MyAccounts::start()
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
           ui->accountType->setText((((x["arrayOfMyAccounts"].toArray())[0]).toObject())["accountType"].toString());
           ui->accountNum->setText(QString::number((((x["arrayOfMyAccounts"].toArray())[0]).toObject())["accountNumber"].toInt()));
           ui->balance->setText(QString::number((((x["arrayOfMyAccounts"].toArray())[0]).toObject())["balance"].toVariant().toLongLong()));
        }
    }
}


void MyAccounts::on_next_clicked()
{
    index++;
    QFile file("D:/Accounts.json");
    file.open(QIODevice::ReadWrite);
    QJsonDocument d = QJsonDocument::fromJson(file.readAll());
    QJsonObject o = d.object();
    file.close();
    foreach(QJsonValue x ,o["accounts"].toArray())
    {
        if(this->getNCode() == x["nCode"].toString())
        {
           ui->accountType->setText((((x["arrayOfMyAccounts"].toArray())[index]).toObject())["accountType"].toString());
           ui->accountNum->setText(QString::number((((x["arrayOfMyAccounts"].toArray())[index]).toObject())["accountNumber"].toInt()));
           ui->balance->setText(QString::number((((x["arrayOfMyAccounts"].toArray())[index]).toObject())["balance"].toVariant().toLongLong()));
        }
    }
}

void MyAccounts::on_befor_clicked()
{
    index--;
    QFile file("D:/Accounts.json");
    file.open(QIODevice::ReadWrite);
    QJsonDocument d = QJsonDocument::fromJson(file.readAll());
    QJsonObject o = d.object();
    file.close();
    foreach(QJsonValue x ,o["accounts"].toArray())
    {
        if(this->getNCode() == x["nCode"].toString())
        {
           ui->accountType->setText((((x["arrayOfMyAccounts"].toArray())[index]).toObject())["accountType"].toString());
           ui->accountNum->setText(QString::number((((x["arrayOfMyAccounts"].toArray())[index]).toObject())["accountNumber"].toInt()));
           ui->balance->setText(QString::number((((x["arrayOfMyAccounts"].toArray())[index]).toObject())["balance"].toVariant().toLongLong()));
        }
    }
}


void MyAccounts::on_buyingNet_clicked()
{
    if(ui->accountType->text().isEmpty())
    {
        QMessageBox *msg=new QMessageBox(QMessageBox::Critical,"message","You don't have any account!");
        msg->show();
        connect(msg,&QMessageBox::buttonClicked,msg,&QMessageBox::deleteLater,Qt::QueuedConnection);
    }
    else{
    BuyNet* net = new BuyNet(this);
    net->setaccNum(ui->accountNum->text());
    net->setNCode(this->getNCode());
     net->setIndex(this->index);
     this->close();
     net->show();
    }
    return;
}


void MyAccounts::on_requestCard_clicked()
{



    if(ui->accountType->text().isEmpty())
    {
        QMessageBox *msg=new QMessageBox(QMessageBox::Critical,"message","You don't have any account!");
        msg->show();
        connect(msg,&QMessageBox::buttonClicked,msg,&QMessageBox::deleteLater,Qt::QueuedConnection);
        return;

    }
    if (ui->accountType->text()=="Longterm Account")
    {  QMessageBox *msg=new QMessageBox(QMessageBox::Warning,"Card Request","Sorry, You can't have a card for longterm account");
        msg->show();
        connect(msg,&QMessageBox::buttonClicked,msg,&QMessageBox::deleteLater,Qt::QueuedConnection);
    }
    else{
     CardU* card = new CardU(this);
     card->setCardNumber();
     card->setCvv2();
     card->setExpireDate();
     card->setAccNumber(ui->accountNum->text().toLongLong());

    QJsonObject origin;
    QJsonArray cards;


    QFile f("D:/Card.json");
    f.open(QIODevice::ReadWrite);
    QJsonDocument d = QJsonDocument::fromJson(f.readAll());
    QJsonObject o = d.object();
    f.close();
    foreach(QJsonValue x ,o["Cards"].toArray())
    {
        cards.append(x.toObject());
    }
    QJsonObject json;
    json["accountNumber"] = ui->accountNum->text();
    json["accountType"] = ui->accountType->text();
    json["nCode"] = this->getNCode();
    json["cardNumber"] = card->getCardNumber();
    json["cvv2"] = card->getCvv2();
    json["expireYear"] = card->getExpireDate().year();
    json["expireMonth"]=card->getExpireDate().month();

    cards.append(json);
    origin["Cards"] = cards;
    QJsonDocument document;
    document.setObject( origin );
    QByteArray bytes = document.toJson(QJsonDocument::JsonFormat());
    QFile file("D:/Card.json");
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

    QMessageBox *msg=new QMessageBox(QMessageBox::Information," Card Request","Your request has been successfully done.");
    msg->show();
    connect(msg,&QMessageBox::buttonClicked,msg,&QMessageBox::deleteLater,Qt::QueuedConnection);
    card->showInfo();
    card->show();
     }
         return;
}

void MyAccounts::on_bill_clicked()
{
    if(ui->accountType->text().isEmpty())
    {
        QMessageBox *msg=new QMessageBox(QMessageBox::Critical,"message","You don't have any account!");
        msg->show();
        connect(msg,&QMessageBox::buttonClicked,msg,&QMessageBox::deleteLater,Qt::QueuedConnection);
    }
    else{
    Bill* b = new Bill(this);
    b->setaccNum(ui->accountNum->text());
    b->setNCode(this->getNCode());
    b->setIndex(this->index);
    this->close();
    b->show();
    }
    return;
}


void MyAccounts::on_CreditCharge_clicked()
{
    if(ui->accountType->text().isEmpty())
    {
        QMessageBox *msg=new QMessageBox(QMessageBox::Critical,"message","You don't have any account!");
        msg->show();
        connect(msg,&QMessageBox::buttonClicked,msg,&QMessageBox::deleteLater,Qt::QueuedConnection);
    }
    else{
    CreditCharge * c = new CreditCharge(this);
    c->setaccNum(ui->accountNum->text());
    c->setNCode(this->getNCode());
    c->setIndex(this->index);
    this->close();
    c->show();
    }
    return;
}

void MyAccounts::on_Cheque_clicked()
{
    if(ui->accountType->text().isEmpty())
    {
        QMessageBox *msg=new QMessageBox(QMessageBox::Critical,"message","You don't have any account!");
        msg->show();
        connect(msg,&QMessageBox::buttonClicked,msg,&QMessageBox::deleteLater,Qt::QueuedConnection);
    }
    else
    {
    Cheq * win = new Cheq(this);
        win->setaccNum(ui->accountNum->text());
        win->setNCode(this->getNCode());
        this->close();
        win->show();

    }
        return;
}


void MyAccounts::on_transferByAccount_clicked()
{
    if(ui->accountType->text().isEmpty())
    {
        QMessageBox *msg=new QMessageBox(QMessageBox::Critical,"message","You don't have any account!");
        msg->show();
        connect(msg,&QMessageBox::buttonClicked,msg,&QMessageBox::deleteLater,Qt::QueuedConnection);
    }
    else{
     TransferMoneyByAccount* n = new TransferMoneyByAccount(this);
     n->setaccNum(ui->accountNum->text());
     n->setNCode(this->getNCode());
     n->setIndex(this->index);
     n->setTypeAccount(ui->accountType->text());
     this->close();
     n->show();

    }

    return;
}


void MyAccounts::on_loan_clicked()
{
        QFile file("D:/Loan.json");
        file.open(QIODevice::ReadWrite);
        QJsonDocument d = QJsonDocument::fromJson(file.readAll());
        QJsonObject o = d.object();
        file.close();
        int flag=0;

        foreach(QJsonValue x ,o["Loans"].toArray())
        {
            if(ui->accountNum->text().toInt() ==  x["accountNumber"].toInt())
            {

                LoanCustomer* lc=new LoanCustomer(this);
                lc->setaccNum(ui->accountNum->text());
                lc->loanAmount();
                lc->show();
                this->close();
                flag=1;
            }


        }

        if(flag==0)
        {
            QMessageBox *msg=new QMessageBox(QMessageBox::Information,"Loan Repayment","You don't have any loan with this account number!");
            msg->show();
            connect(msg,&QMessageBox::buttonClicked,msg,&QMessageBox::deleteLater,Qt::QueuedConnection);
            //cout <<"You don't have any loan with this account number!\n";
        }

        return;
}

