#ifndef ADDACCOUNT_H
#define ADDACCOUNT_H

#include <QDialog>

namespace Ui {
class AddAccount;
}

class AddAccount : public QDialog
{
    Q_OBJECT

public:
    explicit AddAccount(QWidget *parent = nullptr);
    ~AddAccount();

private slots:
    void on_pushButton_clicked();

private:
    Ui::AddAccount *ui;
};

#endif // ADDACCOUNT_H
