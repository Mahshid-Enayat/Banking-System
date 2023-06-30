#include "signin.h"
#include "ui_signin.h"

#include <QLineEdit>
#include "Person.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>
#include <QTextStream>
#include <QtCore>
#include <QIODevice>
#include <QRegularExpressionValidator>
#include "Date.h"
#include <QMessageBox>
#include <QAbstractButton>
#include <QIcon>
#include "QGraphicsPixmapItem"
#define Eye ":/eye.jpg"
Signin::Signin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Signin)
{
    ui->setupUi(this);
    ui->NationalCode->setValidator( new QRegularExpressionValidator(QRegularExpression("[0-9]*")));
    ui->PhoneNumber->setValidator( new QRegularExpressionValidator(QRegularExpression("[0-9]*")));
    ui->Landline->setValidator( new QRegularExpressionValidator(QRegularExpression("[0-9]*")));
    QIcon icon(":/signup.png");
    this->setWindowIcon(icon);
    QPixmap eye(Eye);
    ui->hideshowPass->setIcon(eye);
    QPixmap eye2(Eye);
    ui->hideshowPass_2->setIcon(eye2);
    ui->BirthDate->setDateRange(QDate(1900,1,1),QDate(2022,7,6));

}

Signin::~Signin()
{
    delete ui;
}




void Signin::on_hideshowPass_pressed()
{
    ui->Password->setEchoMode(QLineEdit::Normal);
}

void Signin::on_hideshowPass_released()
{
    ui->Password->setEchoMode(QLineEdit::Password);
    ui->Password->setFocus();
}


void Signin::on_hideshowPass_2_pressed()
{
     ui->confirm->setEchoMode(QLineEdit::Normal);
}


void Signin::on_hideshowPass_2_released()
{
    ui->confirm->setEchoMode(QLineEdit::Password);
    ui->confirm->setFocus();
}


void Signin::on_FirstName_textChanged(const QString &arg1)
{
    if(ui->FirstName->text().isEmpty())
    {
         ui->label_11->clear();
    }
    else if(arg1.contains(QChar(' ')))
    {
        ui->FirstName->backspace();
        ui->label_11->setText("Wrong!");
    }
    else
    {
       ui->label_11->clear();
    }
    return;
}


void Signin::on_LastName_textChanged(const QString &arg2)
{
    if(ui->LastName->text().isEmpty())
    {
         ui->label_12->clear();
    }
    else if(arg2.contains(QChar(' ')))
    {
        ui->LastName->backspace();
        ui->label_12->setText("Wrong!");
    }
    else
    {
       ui->label_12->clear();
    }
    return;
}





void Signin::on_Username_textChanged(const QString &arg3)
{
    if(ui->Username->text().isEmpty())
    {
         ui->label_17->clear();
    }
    else if(arg3.contains(QChar(' ')))
    {
        ui->Username->backspace();
        ui->label_17->setText("Wrong!");
    }
    else
    {
       ui->label_17->clear();
    }
    return;
}


void Signin::on_Password_textChanged(const QString &arg4)
{
    if(ui->Password->text().isEmpty())
    {
         ui->label_18->clear();
    }
    else if(arg4.contains(QChar(' ')))
    {
        ui->Password->backspace();
        ui->label_18->setText("Wrong!");
    }
    else
    {
       ui->label_18->clear();
    }
    return;
}


void Signin::on_confirm_textChanged(const QString &arg5)
{
    if(ui->confirm->text().isEmpty())
    {
         ui->label_19->clear();
    }
    else if(arg5.contains(QChar(' ')))
    {
        ui->confirm->backspace();
        ui->label_19->setText("Wrong!");
    }
    else
    {
       ui->label_19->clear();
    }
    return;
}


void Signin::on_Email_textChanged(const QString &arg6)
{
    if(ui->Email->text().isEmpty())
    {
         ui->label_20->clear();
    }
    else if(arg6.contains(QChar(' ')))
    {
        ui->Email->backspace();
        ui->label_20->setText("Wrong!");
    }
    else
    {
       ui->label_20->clear();
    }
    return;
}


void Signin::on_nextBtn_clicked()
{
    if(ui->FirstName->text().isEmpty()||ui->LastName->text().isEmpty()||ui->NationalCode->text().isEmpty()||ui->PhoneNumber->text().isEmpty()||ui->Landline->text().isEmpty()||ui->Username->text().isEmpty()||ui->Password->text().isEmpty()||ui->confirm->text().isEmpty()||ui->Email->text().isEmpty())
            {
                QMessageBox::information(this,"","Please fill up all the items!");
                return;
            }


    try
        {if(ui->Password->text()==ui->confirm->text()){


                QFile f("D:/UserInfo.json");
                if(!f.open(QIODevice::ReadWrite ))
                {
                    bool isOpen =0;
                    throw isOpen;
                }
                QJsonDocument d = QJsonDocument::fromJson(f.readAll());
                QJsonObject o = d.object();
                f.close();
                int flag =0;
                foreach(QJsonValue x ,o["Users"].toArray())
                {
                    if(x["username"].toString()==ui->Username->text())
                    {
                        flag =1;
                        ui->label_17->setText("This username is already exist!");
                        break;
                    }
                }


                if(flag!=1)
                {
                    Person p;
                    p.setFirstName(ui->FirstName->text());
                    p.setLastName(ui->LastName->text());
                    p.setN_Code(ui->NationalCode->text());
                    p.setBirthDate(ui->BirthDate->date().year(),ui->BirthDate->date().month(),ui->BirthDate->date().day());
                    p.setPhoneNumber(ui->PhoneNumber->text());
                    p.setLandLine(ui->Landline->text());
                    p.setUsername(ui->Username->text());
                    p.setPassword(ui->Password->text());
                    p.setemail(ui->Email->text());
                    p.write();
                    QMessageBox *msg=new QMessageBox(QMessageBox::Information,"Signin Request","Wellcome");
                    msg->show();
                    connect(msg,&QMessageBox::buttonClicked,msg,&QMessageBox::deleteLater,Qt::QueuedConnection);
                    return;
                }

            }
            else
            {
                QMessageBox *msg=new QMessageBox(QMessageBox::Information,"Signin Request","Password and Confirm password fields value must be matched, Please try again!");
                msg->show();
                connect(msg,&QMessageBox::buttonClicked,msg,&QMessageBox::deleteLater,Qt::QueuedConnection);
                return;
         }
        }
        catch(bool isOpen)
        {
            if(isOpen==0)
            {
                QMessageBox *warningMsg = new QMessageBox();
                warningMsg->setText("UserInfo file can not open.");
                warningMsg->setIcon(QMessageBox::Critical);
                warningMsg->show();
            }
        }



}
