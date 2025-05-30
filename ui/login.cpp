#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include "core/auth.h"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login),
    dbManager(new DBManager())
{
    ui->setupUi(this);
    connect(ui->loginButton, &QPushButton::clicked, this, &Login::on_loginButton_clicked);
    connect(ui->cancelButton, &QPushButton::clicked, this, &Login::reject);
    connect(ui->backButton, &QPushButton::clicked, this, &Login::on_backButton_clicked);
}

Login::~Login()
{
    delete dbManager;
    delete ui;
}

QString Login::getRole() const
{
    return userRole;
}

QString Login::getEmail() const
{
    return userEmail;
}

void Login::on_loginButton_clicked()
{
    QString email = ui->emailLineEdit->text().trimmed();
    QString password = ui->passwordLineEdit->text();

    if (email.isEmpty() || password.isEmpty()) {
        ui->statusLabel->setText("Email and password are required.");
        return;
    }

    Auth auth;
    if (!auth.login(email, password, userRole)) {
        ui->statusLabel->setText("Invalid email or password, or account is blocked.");
        return;
    }

    userEmail = email;
    clearFields();
    emit accepted();
}

void Login::on_backButton_clicked()
{
    reject();
}

void Login::clearFields()
{
    ui->emailLineEdit->clear();
    ui->passwordLineEdit->clear();
    ui->statusLabel->clear();
}
