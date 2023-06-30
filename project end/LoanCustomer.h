#ifndef LOANCUSTOMER_H
#define LOANCUSTOMER_H

#include <QDialog>
#include <QString>
namespace Ui {
class LoanCustomer;
}

class LoanCustomer : public QDialog
{
    Q_OBJECT

public:
    explicit LoanCustomer(QWidget *parent = nullptr);
    ~LoanCustomer();

    void setaccNum(QString _accNum);
    QString getAccNum();

    void loanAmount();


private slots:
    void on_pay_clicked();

private:
    Ui::LoanCustomer *ui;

    QString accNum;
};

#endif // LOANCUSTOMER_H
