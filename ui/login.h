#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

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

signals:
    void showSignUp();

private slots:
    void on_loginButton_clicked();
    void on_backButton_clicked();

private:
    void clearFields();
    Ui::Login *ui;
    QString userRole;
    QString userEmail;
};

#endif // LOGIN_H
