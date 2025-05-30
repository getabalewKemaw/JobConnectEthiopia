#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "core/dbmanager.h"

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();
    QString getRole() const;
    QString getEmail() const;

private slots:
    void on_loginButton_clicked();
    void on_backButton_clicked();

private:
    Ui::Login *ui;
    DBManager *dbManager;
    QString userRole;
    QString userEmail;
    void clearFields();
};

#endif // LOGIN_H
