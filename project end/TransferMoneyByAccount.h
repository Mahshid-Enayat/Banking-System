#ifndef TRANSFERMONEYBYACCOUNT_H
#define TRANSFERMONEYBYACCOUNT_H

#include <QDialog>

namespace Ui {
class TransferMoneyByAccount;
}

class TransferMoneyByAccount : public QDialog
{
    Q_OBJECT

public:
    explicit TransferMoneyByAccount(QWidget *parent = nullptr);
    ~TransferMoneyByAccount();

    void setaccNum(QString _accNum);
    QString getAccNum();
    void setNCode(QString _NCode);
    QString getNCode();
    void setIndex(int _index);
    int getIndex();
    void setTypeAccount(QString _accType);
    QString gettypeAccount();



private slots:
    void on_pushButton_clicked();

private:
    Ui::TransferMoneyByAccount *ui;

    QString accNum;
    QString nCode;
    int index;
    QString accType;
};

#endif // TRANSFERMONEYBYACCOUNT_H
