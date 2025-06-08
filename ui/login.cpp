#include "login.h"
#include "ui_login.h"
#include <QMessageBox>
#include "core/auth.h"
#include <QCryptographicHash>
#include "core/dbmanager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login),
    userRole(""),
    userEmail("")
{
    ui->setupUi(this);
    connect(ui->loginButton, &QPushButton::clicked, this, &Login::on_loginButton_clicked);
    connect(ui->cancelButton, &QPushButton::clicked, this, &Login::reject);
    connect(ui->backButton, &QPushButton::clicked, this, &Login::on_backButton_clicked);
}

Login::~Login()
{
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

    QString hashedPassword = QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex());

    QSqlDatabase db = DBManager::getInstance().getDatabase();
    if (!db.isOpen()) {
        ui->statusLabel->setText("Database connection failed.");
        qDebug() << "Database not open:" << db.lastError().text();
        return;
    }

    QSqlQuery query(db);
    // Use single-argument prepare with the query string
    if (!query.prepare("SELECT role, password FROM Users WHERE email = :email AND is_active = TRUE AND blocked = FALSE")) {
        ui->statusLabel->setText("Query preparation failed.");
        qDebug() << "Prepare failed:" << query.lastError().text();
        return;
    }

    query.bindValue(":email", email);
    if (!query.exec()) {
        ui->statusLabel->setText("Login query failed.");
        qDebug() << "Login query failed:" << query.lastError().text();
        qDebug() << "Query executed:" << query.lastQuery();
        return;
    }

    if (query.next()) {
        QString storedPassword = query.value("password").toString();
        userRole = query.value("role").toString();
        if (storedPassword == hashedPassword) {
            userEmail = email;
            clearFields();
            emit accepted();
            ui->statusLabel->setText("Login successful!");
        } else {
            ui->statusLabel->setText("Invalid email or password, or account is blocked.");
        }
    } else {
        ui->statusLabel->setText("Invalid email or password, or account is blocked.");
    }
}

void Login::on_backButton_clicked()
{
    emit showSignUp();
    reject();
}

void Login::clearFields()
{
    ui->emailLineEdit->clear();
    ui->passwordLineEdit->clear();
    ui->statusLabel->clear();
}
