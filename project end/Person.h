#ifndef PERSON_H
#define PERSON_H

#include "Date.h"
#include <QDateTime>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonValue>

class Person
{
private:
    QString firstName;
    QString lastName;
    QString n_code;
    Date birthDate;
    QString phoneNumber;
    QString landLine; //telephone sabet
    QString username;
    QString password;
    QString email;

public:
        Person(QString _firstName,QString _lastName, QString _n_code, QString _phoneNumber,
               QString _landLine, QString _username, QString _password, int _year, int _month, int _day,QString _email);
        Person();

        ~Person();

        void setFirstName(QString _firstName);
        void setLastName(QString _lastName);
        void setN_Code(QString _n_code);
        void setBirthDate(int _year, int _month, int _day);
        void setPhoneNumber(QString _phoneNumber);
        void setLandLine(QString _landLine);
        void setUsername(QString _username);
        void setPassword(QString _password);
        void setemail(QString _email);

        QString getFirstName();
        QString getLastName();
        QString getN_Code();
        int getBirthYear();
        int getBirthMonth();
        int getBirthDay();
        QString getPhoneNumber();
        QString getLandLine();
        QString getUsername();
        QString getPassword();
        QString getemail();


        void write();

};

#endif // PERSON_H
