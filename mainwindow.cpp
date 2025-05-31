#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui/login.h"
#include "ui/signup.h"
#include "ui/dashboard_seeker.h"
#include "ui/dashboard_employer.h"
#include "ui/dashboard_admin.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Connect the getStartedButton to showLoginDialog
    connect(ui->getStartedButton, &QPushButton::clicked, this, &MainWindow::showLoginDialog);

    setStyleSheet("QMainWindow { background-color: #f5f7fa; }"
                  "QPushButton { "
                  "   background-color: #4CAF50; "
                  "   color: white; "
                  "   padding: 6px 12px; "
                  "   border-radius: 4px; "
                  "   font: 13px 'Arial'; "
                  "   border: none; "
                  "   min-width: 90px; "
                  "   min-height: 30px; "
                  "}"
                  "QPushButton:hover { background-color: #45a049; }"
                  "QPushButton:pressed { background-color: #3d8b40; }"
                  "QLineEdit, QTextEdit { "
                  "   border: 1px solid #d1d5db; "
                  "   border-radius: 4px; "
                  "   padding: 4px; "
                  "   font: 13px 'Arial'; "
                  "   min-width: 180px; "
                  "   min-height: 28px; "
                  "   background-color: #fff; "
                  "}"
                  "QLineEdit:focus, QTextEdit:focus { border-color: #4CAF50; }"
                  "QTableWidget { "
                  "   border: 1px solid #d1d5db; "
                  "   border-radius: 4px; "
                  "   background-color: white; "
                  "   font: 13px 'Arial'; "
                  "   min-width: 500px; "
                  "   min-height: 250px; "
                  "   gridline-color: #e5e7eb; "
                  "}"
                  "QTableWidget::item:selected { background-color: #e6f0fa; color: #1f2937; }"
                  "QLabel { "
                  "   color: #1f2937; "
                  "   font: 13px 'Arial'; "
                  "}"
                  "QComboBox { "
                  "   border: 1px solid #d1d5db; "
                  "   border-radius: 4px; "
                  "   padding: 4px; "
                  "   font: 13px 'Arial'; "
                  "   min-width: 120px; "
                  "   min-height: 28px; "
                  "   background-color: #fff; "
                  "}"
                  "QComboBox:hover { border-color: #4CAF50; }"
                  "QComboBox::drop-down { border: none; }"
                  "QDialog { "
                  "   background-color: white; "
                  "   border: 1px solid #e5e7eb; "
                  "   border-radius: 8px; "
                  "}"
                  );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showLoginDialog()
{
    Login *loginDialog = new Login(this);
    connect(loginDialog, &Login::showSignUp, this, [this, loginDialog]() {
        loginDialog->deleteLater(); // Destroy login dialog
        showSignUpDialog();
    });
    connect(loginDialog, &QDialog::accepted, this, &MainWindow::handleLogin);
    connect(loginDialog, &QDialog::accepted, loginDialog, &QDialog::deleteLater);
    connect(loginDialog, &QDialog::rejected, loginDialog, &QDialog::deleteLater);
    loginDialog->show();
}

void MainWindow::showSignUpDialog()
{
    SignUp *signUpDialog = new SignUp(this);
    connect(signUpDialog, &SignUp::userSignedUp, this, [](const QString& firstName, const QString& lastName) {
        QString welcomeMessage = QString("Welcome, %1 %2!").arg(firstName).arg(lastName);
        QMessageBox::information(nullptr, "Welcome", welcomeMessage);
    });
    connect(signUpDialog, &SignUp::showLogin, this, [this, signUpDialog]() {
        signUpDialog->deleteLater(); // Destroy signup dialog
        showLoginDialog();
    });
    connect(signUpDialog, &QDialog::accepted, signUpDialog, &QDialog::deleteLater);
    connect(signUpDialog, &QDialog::rejected, signUpDialog, &QDialog::deleteLater);
    signUpDialog->show();
}

void MainWindow::handleLogin()
{
    Login *loginDialog = qobject_cast<Login*>(sender());
    if (!loginDialog) {
        QMessageBox::critical(this, "Error", "Unable to retrieve login dialog.");
        return;
    }

    QString role = loginDialog->getRole();
    QString email = loginDialog->getEmail();
    int userId = 0;
    QString fullName;

    // Initialize DBManager for database access
    DBManager dbManager;
    QSqlDatabase db = dbManager.getDatabase();
    if (!db.isOpen()) {
        QMessageBox::critical(this, "Database Error", "Database connection failed: " + db.lastError().text());
        return;
    }

    // Fetch user_id and full name
    QSqlQuery userQuery(db);
    userQuery.prepare("SELECT user_id, CONCAT(first_name, ' ', last_name) AS full_name "
                      "FROM Users WHERE email = :email AND is_active = TRUE");
    userQuery.bindValue(":email", email);
    if (!userQuery.exec()) {
        QMessageBox::critical(this, "Database Error", "Failed to fetch user details: " + userQuery.lastError().text());
        return;
    }
    if (!userQuery.next()) {
        QMessageBox::critical(this, "Error", "User not found or account is inactive.");
        return;
    }
    userId = userQuery.value("user_id").toInt();
    fullName = userQuery.value("full_name").toString();

    // Fetch seeker_id, employer_id, or admin_id based on role
    int dashboardId = 0;
    if (role == "job_seeker") {
        QSqlQuery seekerQuery(db);
        seekerQuery.prepare("SELECT seeker_id FROM JobSeekers WHERE user_id = :user_id");
        seekerQuery.bindValue(":user_id", userId);
        if (!seekerQuery.exec()) {
            QMessageBox::critical(this, "Database Error", "Failed to load JobSeeker profile: " + seekerQuery.lastError().text());
            return;
        }
        if (!seekerQuery.next()) {
            QMessageBox::critical(this, "Error", "No JobSeeker profile found for this user. Please sign up as a Job Seeker first.");
            return;
        }
        dashboardId = seekerQuery.value("seeker_id").toInt();
    } else if (role == "employer") {
        QSqlQuery employerQuery(db);
        employerQuery.prepare("SELECT employer_id FROM Employers WHERE user_id = :user_id");
        employerQuery.bindValue(":user_id", userId);
        if (!employerQuery.exec()) {
            QMessageBox::critical(this, "Database Error", "Failed to load Employer profile: " + employerQuery.lastError().text());
            return;
        }
        if (!employerQuery.next()) {
            QMessageBox::critical(this, "Error", "No Employer profile found for this user. Please sign up as an Employer first.");
            return;
        }
        dashboardId = employerQuery.value("employer_id").toInt();
    } else if (role == "admin") {
        // Admin role doesn't require an additional ID, but we can validate
        QSqlQuery adminQuery(db);
        adminQuery.prepare("SELECT COUNT(*) FROM Users WHERE user_id = :user_id AND role = 'admin'");
        adminQuery.bindValue(":user_id", userId);
        if (!adminQuery.exec() || !adminQuery.next() || adminQuery.value(0).toInt() == 0) {
            QMessageBox::critical(this, "Error", "Admin privileges not found for this user.");
            return;
        }
    } else {
        QMessageBox::critical(this, "Error", "Unknown role: " + role);
        return;
    }

    // Initialize the appropriate dashboard
    dashboard = nullptr;
    if (role == "job_seeker") {
        dashboard = new DashboardSeeker(this);
        static_cast<DashboardSeeker*>(dashboard)->setSeekerUserId(dashboardId);
    } else if (role == "employer") {
        dashboard = new DashboardEmployer(this);
        static_cast<DashboardEmployer*>(dashboard)->setEmployerUserId(dashboardId);
        static_cast<DashboardEmployer*>(dashboard)->setLoggedInUser(fullName);
    } else if (role == "admin") {
        dashboard = new DashboardAdmin(this);
    }

    if (dashboard) {
        dashboard->exec();
        delete dashboard;
        dashboard = nullptr; // Ensure pointer is reset
    }
}
