#ifndef ACCOUNTREQUEST_H
#define ACCOUNTREQUEST_H

#include <QDialog>

namespace Ui {
class AccountRequest;
}

class AccountRequest : public QDialog
{
    Q_OBJECT

public:
    explicit AccountRequest(QWidget *parent = nullptr);
    ~AccountRequest();

    void showInformationRequest();
    void popFrontFile();
    void buildAccount();

private slots:
    void on_accept_clicked();

    void on_decline_clicked();

private:
    Ui::AccountRequest *ui;
};

#endif // ACCOUNTREQUEST_H
