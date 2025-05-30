#include "signup.h"
#include "ui_signup.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

SignUp::SignUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUp),
    dbManager(new DBManager())
{
    ui->setupUi(this);
    setupConnections();
    // Initially hide Employer-specific fields
    ui->companyNameLabel->setVisible(false);
    ui->companyNameLineEdit->setVisible(false);
    ui->licenseNumberLabel->setVisible(false);
    ui->licenseNumberLineEdit->setVisible(false);
    ui->websiteLabel->setVisible(false);
    ui->websiteLineEdit->setVisible(false);
    ui->industryLabel->setVisible(false);
    ui->industryLineEdit->setVisible(false);
}

SignUp::~SignUp()
{
    delete dbManager;
    delete ui;
}

void SignUp::setupConnections()
{
    connect(ui->submitButton, &QPushButton::clicked, this, &SignUp::on_submitButton_clicked);
    connect(ui->roleComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &SignUp::on_roleComboBox_currentIndexChanged);
    connect(ui->cancelButton, &QPushButton::clicked, this, &SignUp::reject);
    connect(ui->backButton, &QPushButton::clicked, this, &SignUp::on_backButton_clicked);  // Connect Back button
}

void SignUp::on_roleComboBox_currentIndexChanged(int index)
{
    bool isEmployer = (ui->roleComboBox->currentText() == "Employer");
    ui->companyNameLabel->setVisible(isEmployer);
    ui->companyNameLineEdit->setVisible(isEmployer);
    ui->licenseNumberLabel->setVisible(isEmployer);
    ui->licenseNumberLineEdit->setVisible(isEmployer);
    ui->websiteLabel->setVisible(isEmployer);
    ui->websiteLineEdit->setVisible(isEmployer);
    ui->industryLabel->setVisible(isEmployer);
    ui->industryLineEdit->setVisible(isEmployer);
}

bool SignUp::validateInputs()
{
    QString email = ui->emailLineEdit->text().trimmed();
    QString password = ui->passwordLineEdit->text();
    QString fullName = ui->fullNameLineEdit->text().trimmed();
    QString role = ui->roleComboBox->currentText();

    if (email.isEmpty() || password.isEmpty() || fullName.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Email, password, and full name are required.");
        return false;
    }

    // Check for duplicate email
    QSqlQuery query(dbManager->getDatabase());
    query.prepare("SELECT COUNT(*) FROM Users WHERE email = :email");
    query.bindValue(":email", email);
    if (!query.exec() || !query.next() || query.value(0).toInt() > 0) {
        QMessageBox::warning(this, "Registration Error", "Email already exists.");
        return false;
    }

    if (role == "Employer") {
        QString companyName = ui->companyNameLineEdit->text().trimmed();
        QString licenseNumber = ui->licenseNumberLineEdit->text().trimmed();
        if (companyName.isEmpty() || licenseNumber.isEmpty()) {
            QMessageBox::warning(this, "Input Error", "Company name and license number are required for Employers.");
            return false;
        }
    }

    return true;
}

void SignUp::on_submitButton_clicked()
{
    if (!validateInputs()) {
        return;
    }

    QSqlQuery query(dbManager->getDatabase());
    query.exec("BEGIN TRANSACTION");

    QString email = ui->emailLineEdit->text().trimmed();
    QString password = ui->passwordLineEdit->text();
    QString fullName = ui->fullNameLineEdit->text().trimmed();
    QString uiRole = ui->roleComboBox->currentText();
    QString role;

    // Map UI role to database role
    if (uiRole == "Job Seeker") {
        role = "job_seeker";
    } else if (uiRole == "Employer") {
        role = "employer";
    } else {
        QMessageBox::critical(this, "Role Error", "Invalid role selected.");
        query.exec("ROLLBACK");
        return;
    }

    // Insert into Users
    query.prepare("INSERT INTO Users (email, password, role) VALUES (:email, :password, :role)");
    query.bindValue(":email", email);
    query.bindValue(":password", password);
    query.bindValue(":role", role);
    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", "Failed to create user: " + query.lastError().text());
        query.exec("ROLLBACK");
        return;
    }

    // Get the last inserted user_id
    int userId = query.lastInsertId().toInt();

    if (role == "job_seeker") {
        query.prepare("INSERT INTO JobSeekers (user_id, full_name) VALUES (:user_id, :full_name)");
        query.bindValue(":user_id", userId);
        query.bindValue(":full_name", fullName);
    } else { // Employer
        QString companyName = ui->companyNameLineEdit->text().trimmed();
        QString licenseNumber = ui->licenseNumberLineEdit->text().trimmed();
        QString website = ui->websiteLineEdit->text().trimmed();
        QString industry = ui->industryLineEdit->text().trimmed();
        query.prepare("INSERT INTO Employers (user_id, company_name, license_number, license_verified, website, industry) "
                      "VALUES (:user_id, :company_name, :license_number, FALSE, :website, :industry)");
        query.bindValue(":user_id", userId);
        query.bindValue(":company_name", companyName);
        query.bindValue(":license_number", licenseNumber);
        query.bindValue(":website", website);
        query.bindValue(":industry", industry);
    }

    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", "Failed to create profile: " + query.lastError().text());
        query.exec("ROLLBACK");
    } else {
        query.exec("COMMIT");
        QMessageBox::information(this, "Success", "Account created successfully! Please log in.");
        clearFields();
        emit accepted(); // Signal to close dialog
    }
}

void SignUp::on_backButton_clicked()
{
    reject();  // Close the signup dialog to return to the welcome screen
}

void SignUp::clearFields()
{
    ui->emailLineEdit->clear();
    ui->passwordLineEdit->clear();
    ui->fullNameLineEdit->clear();
    ui->companyNameLineEdit->clear();
    ui->licenseNumberLineEdit->clear();
    ui->websiteLineEdit->clear();
    ui->industryLineEdit->clear();
    ui->roleComboBox->setCurrentIndex(0); // Reset to Job Seeker
}
