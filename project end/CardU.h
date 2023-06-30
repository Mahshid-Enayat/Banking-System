#ifndef CARDU_H
#define CARDU_H

#include <QDialog>
#include<QJsonObject>
#include<QJsonArray>
#include<QJsonDocument>
#include<QJsonValue>
#include<QDateTime>
#include<QDate>

namespace Ui {
class CardU;
}

class CardU : public QDialog
{
    Q_OBJECT

public:
    explicit CardU(QWidget *parent = nullptr);
    ~CardU();

    void setCardNumber();
    void setAccNumber(long long int _accNumber);
    void setCvv2();
    void setExpireDate();


    long long int getCardNumber() const;
    long long int getAccNumber() const;
    int getCvv2() const;
    QDate getExpireDate() const;
    void showInfo();

private slots:
    void on_ok_clicked();

private:
    Ui::CardU *ui;

    long long int cardNumber;
    long long int accNumber;
    int cvv2;
    QDate expireDate;
};

#endif // CARDU_H
