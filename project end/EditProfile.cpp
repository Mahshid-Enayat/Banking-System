#include "EditProfile.h"
#include "ui_EditProfile.h"
#include <iostream>
#include <QLineEdit>
#include <QIcon>
#include <QFile>
#include <QTextStream>
#include <QtCore>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include "Login.h"
#include <QRegularExpressionValidator>
#include "QGraphicsPixmapItem"
#define Eye ":/eye.jpg"
using namespace std;

EditProfile::EditProfile(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditProfile)
{
    ui->setupUi(this);
    ui->PhoneNum->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]*")));
    ui->Landline->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]*")));
    QIcon icon(":/editprofile.png");
    this->setWindowIcon(icon);
    QPixmap eye(Eye);
    ui->hideshowpass->setIcon(eye);
    QPixmap eye2(Eye);
    ui->hideshowpass_2->setIcon(eye2);

}

EditProfile::~EditProfile()
{
    delete ui;
}

void EditProfile::setNCode(QString _nCode)
{
    this->ncode = _nCode;
    return;
}

QString EditProfile::getNCode()
{
     return ncode;
}

void EditProfile::on_hideshowpass_2_pressed()
{
     ui->password->setEchoMode(QLineEdit::Normal);
}
void EditProfile::on_hideshowpass_2_released()
{
    ui->password->setEchoMode(QLineEdit::Password);
    ui->password->setFocus();
}

void EditProfile::on_hideshowpass_pressed()
{
    ui->confirmpass->setEchoMode(QLineEdit::Normal);
}

void EditProfile::on_hideshowpass_released()
{
    ui->confirmpass->setEchoMode(QLineEdit::Password);
    ui->confirmpass->setFocus();

}

void EditProfile::on_editBtn_clicked()
{

    QFile f("D:/UserInfo.json");
    f.open(QIODevice::ReadWrite);
    QByteArray b = f.readAll();
    QJsonDocument first = QJsonDocument::fromJson(b);
    QJsonObject main;
    main = first.object();
    f.close();
    QJsonObject origin;
    QJsonArray objarr;
    QJsonObject json;


    if(ui->Username->text().isEmpty()||ui->password->text().isEmpty()||ui->confirmpass->text().isEmpty()||ui->Email->text().isEmpty())
    {
        QMessageBox::information(this,"","Please fill up all the items!");

    }

    else if(ui->password->text()==ui->confirmpass->text())
    {

        foreach(QJsonValue x ,main["Users"].toArray())
        {
             if(this->getNCode() == x["nCode"].toString())
              {

                    json["firstName"] = x["firstName"];
                    json["lastName"] = x["lastName"];
                    json["nCode"] = x["nCode"];
                    json["birthDay"] = x["birthDay"];
                    json["birthMonth"] = x["birthMonth"];
                    json["birthYear"] = x["birthYear"];
                    json["login"] = x["login"];
                    json["logout"] = x["logout"];
                    json["phoneNumber"]=ui->PhoneNum->text();
                    json["landline"]=ui->Landline->text();
                    json["username"]=ui->Username->text();
                    json["password"]=ui->password->text();
                    json["email"]=ui->Email->text();


                    objarr.append(json);

                    QMessageBox *msg=new QMessageBox(QMessageBox::Information,"Editing Profile","Your profile edited successfully !");
                    msg->show();
                    connect(msg,&QMessageBox::buttonClicked,msg,&QMessageBox::deleteLater,Qt::QueuedConnection);

               }
               else
               {
                    objarr.append(x.toObject());

               }
        origin["Users"]=objarr;
        QJsonDocument document;
        document.setObject( origin );
        QByteArray bytes = document.toJson(QJsonDocument::JsonFormat());
        //QFile file("D:/UserInfo.json");
        if(f.open(QIODevice::Append | QIODevice::WriteOnly | QIODevice::Truncate))
        {
             QTextStream iStream( &f );
             iStream << bytes;
             f.close();
        }

         else
         {
             cout << "file open failed: " << endl;
         }



     }
    }
     else
     {
         QMessageBox *msg=new QMessageBox(QMessageBox::Warning,"Error","Passwords didn't match ! Please try again!");
         msg->show();
         connect(msg,&QMessageBox::buttonClicked,msg,&QMessageBox::deleteLater,Qt::QueuedConnection);

     }

    return;
}



void EditProfile::on_pushButton_2_clicked()
{
    this->close();
    return;
}

