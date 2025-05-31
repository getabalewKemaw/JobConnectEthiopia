#include "signup.h"
#include "ui_signup.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include<core/dbmanager.h>
#include <QRegularExpression>
#include <QCryptographicHash>

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
    connect(ui->backButton, &QPushButton::clicked, this, &SignUp::on_backButton_clicked);
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

bool SignUp::ensureDatabaseConnection()
{
    QSqlDatabase db = dbManager->getDatabase();
    if (!db.isValid()) {
        QMessageBox::critical(this, "Database Error", "Invalid database connection.");
        return false;
    }
    if (!db.isOpen()) {
        if (!db.open()) {
            QMessageBox::critical(this, "Database Error", "Failed to open database: " + db.lastError().text());
            return false;
        }
    }
    return true;
}

bool SignUp::validateInputs()
{
    if (!ensureDatabaseConnection()) {
        return false;
    }

    QString email = ui->emailLineEdit->text().trimmed();
    QString password = ui->passwordLineEdit->text();
    QString confirmPassword = ui->confirmPasswordLineEdit->text();
    QString firstName = ui->firstNameLineEdit->text().trimmed();
    QString lastName = ui->lastNameLineEdit->text().trimmed();
    QString role = ui->roleComboBox->currentText();

    // Validate Email
    QRegularExpression emailRegex("^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}$");
    if (email.isEmpty() || !emailRegex.match(email).hasMatch()) {
        QMessageBox::warning(this, "Input Error", "Please enter a valid email address (e.g., user@example.com).");
        return false;
    }

    // Check for duplicate email
    QSqlQuery query(dbManager->getDatabase());
    query.prepare("SELECT COUNT(*) FROM Users WHERE email = :email");
    query.bindValue(":email", email);
    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", "Failed to check email: " + query.lastError().text());
        return false;
    }
    if (query.next() && query.value(0).toInt() > 0) {
        QMessageBox::warning(this, "Registration Error", "Email already exists.");
        return false;
    }

    // Validate Password
    QRegularExpression passwordRegex("^(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[@$!%*?&])[A-Za-z\\d@$!%*?&]{8,}$");
    if (password.isEmpty() || !passwordRegex.match(password).hasMatch()) {
        QMessageBox::warning(this, "Input Error", "Password must be at least 8 characters long, with at least one uppercase letter, one lowercase letter, one digit, and one special character (@$!%*?&).");
        return false;
    }

    // Validate Confirm Password
    if (confirmPassword != password) {
        QMessageBox::warning(this, "Input Error", "Passwords do not match.");
        return false;
    }

    // Validate First Name
    QRegularExpression nameRegex("^[A-Za-z\\s]+$");
    if (firstName.isEmpty() || !nameRegex.match(firstName).hasMatch()) {
        QMessageBox::warning(this, "Input Error", "First name must contain only letters and spaces.");
        return false;
    }

    // Validate Last Name
    if (lastName.isEmpty() || !nameRegex.match(lastName).hasMatch()) {
        QMessageBox::warning(this, "Input Error", "Last name must contain only letters and spaces.");
        return false;
    }

    if (role == "Employer") {
        QString companyName = ui->companyNameLineEdit->text().trimmed();
        QString licenseNumber = ui->licenseNumberLineEdit->text().trimmed();
        QString website = ui->websiteLineEdit->text().trimmed();
        QString industry = ui->industryLineEdit->text().trimmed();

        // Validate Company Name
        QRegularExpression companyRegex("^[A-Za-z0-9\\s]+$");
        if (companyName.isEmpty() || !companyRegex.match(companyName).hasMatch()) {
            QMessageBox::warning(this, "Input Error", "Company name must contain only letters, numbers, and spaces.");
            return false;
        }

        // Validate License Number
        QRegularExpression licenseRegex("^[A-Za-z0-9]{5,}$");
        if (licenseNumber.isEmpty() || !licenseRegex.match(licenseNumber).hasMatch()) {
            QMessageBox::warning(this, "Input Error", "License number must be at least 5 characters long and contain only letters and numbers.");
            return false;
        }

        // Check for duplicate license number
        query.prepare("SELECT COUNT(*) FROM Employers WHERE license_number = :license_number");
        query.bindValue(":license_number", licenseNumber);
        if (!query.exec()) {
            QMessageBox::critical(this, "Database Error", "Failed to check license number: " + query.lastError().text());
            return false;
        }
        if (query.next() && query.value(0).toInt() > 0) {
            QMessageBox::warning(this, "Registration Error", "License number already exists.");
            return false;
        }

        // Validate Website (optional field)
        if (!website.isEmpty()) {
            QRegularExpression websiteRegex("^(https?://)?([\\w\\-]+\\.)+[\\w\\-]+(/[\\w\\-./?%&=]*)?$");
            if (!websiteRegex.match(website).hasMatch()) {
                QMessageBox::warning(this, "Input Error", "Please enter a valid website URL (e.g., https://example.com).");
                return false;
            }
        }

        // Validate Industry
        if (industry.isEmpty() || !nameRegex.match(industry).hasMatch()) {
            QMessageBox::warning(this, "Input Error", "Industry must contain only letters and spaces.");
            return false;
        }
    }

    return true;
}

void SignUp::on_submitButton_clicked()
{
    if (!ensureDatabaseConnection()) {
        return;
    }

    if (!validateInputs()) {
        return;
    }

    QSqlQuery query(dbManager->getDatabase());
    query.exec("BEGIN TRANSACTION");

    QString email = ui->emailLineEdit->text().trimmed();
    QString password = ui->passwordLineEdit->text();
    // Hash the password using SHA-256
    QString hashedPassword = QString(QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toHex());
    QString firstName = ui->firstNameLineEdit->text().trimmed();
    QString lastName = ui->lastNameLineEdit->text().trimmed();
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

    // Insert into Users with hashed password
    query.prepare("INSERT INTO Users (email, password, role, first_name, last_name) "
                  "VALUES (:email, :password, :role, :first_name, :last_name)");
    query.bindValue(":email", email);
    query.bindValue(":password", hashedPassword);
    query.bindValue(":role", role);
    query.bindValue(":first_name", firstName);
    query.bindValue(":last_name", lastName);
    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", "Failed to create user: " + query.lastError().text());
        query.exec("ROLLBACK");
        return;
    }

    // Get the last inserted user_id
    int userId = query.lastInsertId().toInt();

    if (role == "job_seeker") {
        query.prepare("INSERT INTO JobSeekers (user_id) VALUES (:user_id)");
        query.bindValue(":user_id", userId);
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
        // Emit signal with first_name, last_name, and role for dashboard redirect
        emit userSignedUp(firstName, lastName, role);
        emit accepted();
    }
}

void SignUp::on_backButton_clicked()
{
    emit showLogin(); // Emit signal to show LoginUI
    reject(); // Close the signup dialog
}

void SignUp::clearFields()
{
    ui->emailLineEdit->clear();
    ui->passwordLineEdit->clear();
    ui->confirmPasswordLineEdit->clear();
    ui->firstNameLineEdit->clear();
    ui->lastNameLineEdit->clear();
    ui->companyNameLineEdit->clear();
    ui->licenseNumberLineEdit->clear();
    ui->websiteLineEdit->clear();
    ui->industryLineEdit->clear();
    ui->roleComboBox->setCurrentIndex(0);
}
