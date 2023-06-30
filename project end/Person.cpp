#include "Person.h"
#include<iostream>

using namespace std;

Person::Person(QString _firstName,QString _lastName,QString _n_code,QString _phoneNumber,
               QString _landLine,QString _username,QString _password ,int _year,int _month,int _day, QString _email)
    :birthDate(_year,_month , _day)
{
    firstName = _firstName;
    lastName = _lastName;
    n_code = _n_code;
    phoneNumber = _phoneNumber;
    landLine=_landLine;
    username = _username;
    password = _password;
    email= _email;

    return;
}

Person::Person()
{
    return;
}

Person::~Person()
{
    return;
}

void Person::setFirstName(QString _firstName)
{
    firstName = _firstName;
    return;
}

void Person::setLastName(QString _lastName)
{
    lastName = _lastName;
    return;
}

void Person::setN_Code(QString _n_code)
{
    n_code = _n_code;
    return;
}

void Person::setBirthDate(int _year, int _month, int _day)
{
    this->birthDate.setYear(_year);
    this->birthDate.setMonth(_month);
    this->birthDate.setDay(_day);
    return;
}

void Person::setPhoneNumber(QString _phoneNumber)
{
    phoneNumber = _phoneNumber;
    return;
}

void Person::setLandLine(QString _landLine)
{
    landLine=_landLine;
    return;
}

void Person::setUsername(QString _username)
{
    username = _username;
    return;
}

void Person::setPassword(QString _password)
{
    password = _password;
    return;
}

void Person::setemail(QString _email)
{
    email=_email;
    return;
}

QString Person::getFirstName()
{
    return this->firstName;
}

QString Person::getLastName()
{
    return this->lastName;
}

QString Person::getN_Code()
{
    return this->n_code;
}

int Person::getBirthYear()
{
    return this->birthDate.getYear();
}

int Person::getBirthMonth()
{
    return this->birthDate.getMonth();
}

int Person::getBirthDay()
{
    return this->birthDate.getDay();
}

QString Person::getPhoneNumber()
{
    return this->phoneNumber;
}

QString Person::getLandLine()
{
    return this->landLine;
}

QString Person::getUsername()
{
    return this->username;
}

QString Person::getPassword()
{
    return this->password;
}

QString Person::getemail()
{
    return this->email;
}

void Person::write()
{


    QJsonObject origin;
    QJsonArray users;
    QFile f("D:/UserInfo.json");
    f.open(QIODevice::ReadWrite);
    QJsonDocument d = QJsonDocument::fromJson(f.readAll());
    QJsonObject o = d.object();
    f.close();
    foreach(QJsonValue x ,o["Users"].toArray())
    {
        users.append(x.toObject());
    }


    QJsonObject json;
    json["firstName"] = firstName;
    json["lastName"] = lastName;
    json["nCode"] = n_code;
    json["birthYear"] = birthDate.getYear();
    json["birthMonth"] = birthDate.getMonth();
    json["birthDay"] = birthDate.getDay();
    json["username"] = username;
    json["password"] = password;
    json["phoneNumber"] = phoneNumber;
    json["landline"] = landLine;   
    json["email"] = email;
    users.append(json);
    origin["Users"] = users;
    QJsonDocument document;
    document.setObject( origin );
    QByteArray bytes = document.toJson(QJsonDocument::JsonFormat());
    QFile file("D:/UserInfo.json");
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
}
