QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Account.cpp \
    AccountRequest.cpp \
    AddAccount.cpp \
    AddMoney.cpp \
    Admin.cpp \
    BankBranch.cpp \
    Bill.cpp \
    BlockAccount.cpp \
    BuyNet.cpp \
    CardByCard.cpp \
    CardU.cpp \
    Cheq.cpp \
    CreditCharge.cpp \
    CurrentAccount.cpp \
    Customer.cpp \
    Date.cpp \
    EditProfile.cpp \
    LoanAdmin.cpp \
    LoanCustomer.cpp \
    Login.cpp \
    LoginLogout.cpp \
    LongTermAccount.cpp \
    MyAccounts.cpp \
    Person.cpp \
    SavingAccount.cpp \
    ShortTermAccount.cpp \
    TransferMoneyByAccount.cpp \
    main.cpp \
    mainwindow.cpp \
    signin.cpp

HEADERS += \
    Account.h \
    AccountRequest.h \
    AddAccount.h \
    AddMoney.h \
    Admin.h \
    BankBranch.h \
    Bill.h \
    BlockAccount.h \
    BuyNet.h \
    CardByCard.h \
    CardU.h \
    Cheq.h \
    CreditCharge.h \
    CurrentAccount.h \
    Customer.h \
    Date.h \
    EditProfile.h \
    LoanAdmin.h \
    LoanCustomer.h \
    Login.h \
    LoginLogout.h \
    LongTermAccount.h \
    MyAccounts.h \
    Person.h \
    SavingAccount.h \
    ShortTermAccount.h \
    TransferMoneyByAccount.h \
    mainwindow.h \
    signin.h

FORMS += \
    AccountRequest.ui \
    AddAccount.ui \
    AddMoney.ui \
    Admin.ui \
    BankBranch.ui \
    Bill.ui \
    BlockAccount.ui \
    BuyNet.ui \
    CardByCard.ui \
    CardU.ui \
    Cheq.ui \
    CreditCharge.ui \
    Customer.ui \
    EditProfile.ui \
    LoanAdmin.ui \
    LoanCustomer.ui \
    Login.ui \
    LoginLogout.ui \
    MyAccounts.ui \
    TransferMoneyByAccount.ui \
    mainwindow.ui \
    signin.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    ../PRO/PRO.qrc \
    ../PRO/PRO.qrc

DISTFILES += \
    ../PRO/Account Request.json \
    ../PRO/Accounts.json \
    ../PRO/Card.json \
    ../PRO/Loan.json \
    ../PRO/Logs.json \
    ../PRO/UserInfo.json \
    ../PRO/account.png \
    ../PRO/addAccount.png \
    ../PRO/admin.png \
    ../PRO/bank.png \
    ../PRO/bankbranch.png \
    ../PRO/block.png \
    ../PRO/c.png \
    ../PRO/cheque.png \
    ../PRO/editprofile.png \
    ../PRO/eye.jpg \
    ../PRO/loan.png \
    ../PRO/log.png \
    ../PRO/login.png \
    ../PRO/logo.jpg \
    ../PRO/money.png \
    ../PRO/openacc.png \
    ../PRO/signup.png \
    ../PRO/user.png
