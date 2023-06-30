#ifndef ADDMONEY_H
#define ADDMONEY_H

#include <QDialog>

namespace Ui {
class AddMoney;
}

class AddMoney : public QDialog
{
    Q_OBJECT

public:
    explicit AddMoney(QWidget *parent = nullptr);
    ~AddMoney();


private slots:
    void on_pushButton_clicked();

private:
    Ui::AddMoney *ui;

};

#endif // ADDMONEY_H
