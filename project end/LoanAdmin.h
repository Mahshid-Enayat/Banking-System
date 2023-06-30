#ifndef LOANADMIN_H
#define LOANADMIN_H

#include <QDialog>

namespace Ui {
class LoanAdmin;
}

class LoanAdmin : public QDialog
{
    Q_OBJECT

public:
    explicit LoanAdmin(QWidget *parent = nullptr);
    ~LoanAdmin();

private slots:
    void on_okBtn_clicked();

private:
    Ui::LoanAdmin *ui;
};

#endif // LOANADMIN_H
