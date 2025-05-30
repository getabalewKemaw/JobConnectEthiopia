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



    QDialog *welcomeDialog = new QDialog(this);
    welcomeDialog->setWindowTitle("Welcome to Job Matching System");
    welcomeDialog->setStyleSheet("QDialog { background-color: #E6F0FA; }");
    welcomeDialog->setFixedSize(400, 300);

    QVBoxLayout *layout = new QVBoxLayout(welcomeDialog);
    QLabel *titleLabel = new QLabel("Job Matching System", welcomeDialog);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font: bold 24px 'Arial'; color: #2D6A4F;");

    QLabel *welcomeLabel = new QLabel("Please choose an option:", welcomeDialog);
    welcomeLabel->setAlignment(Qt::AlignCenter);
    welcomeLabel->setStyleSheet("font: 16px 'Arial'; color: #2E4053;");

    QPushButton *loginButton = new QPushButton("Login", welcomeDialog);
    QPushButton *signUpButton = new QPushButton("Sign Up", welcomeDialog);

    loginButton->setStyleSheet("QPushButton { background-color: #4CAF50; color: white; border-radius: 4px; padding: 8px; font: 14px 'Arial'; }"
                               "QPushButton:hover { background-color: #45A049; }");
    signUpButton->setStyleSheet("QPushButton { background-color: #4CAF50; color: white; border-radius: 4px; padding: 8px; font: 14px 'Arial'; }"
                                "QPushButton:hover { background-color: #45A049; }");

    layout->addWidget(titleLabel);
    layout->addSpacing(20);
    layout->addWidget(welcomeLabel);
    layout->addSpacing(30);
    layout->addWidget(loginButton);
    layout->addSpacing(10);
    layout->addWidget(signUpButton);
    layout->addStretch();

    connect(loginButton, &QPushButton::clicked, this, [this, welcomeDialog]() {
        welcomeDialog->accept();
        loginDialog = new Login(this);
        connect(loginDialog, &QDialog::accepted, this, &MainWindow::handleLogin);
        loginDialog->exec();
        delete loginDialog;
    });

    connect(signUpButton, &QPushButton::clicked, this, [this, welcomeDialog]() {
        welcomeDialog->accept();
        SignUp *signUpDialog = new SignUp(this);
        signUpDialog->exec();
        delete signUpDialog;
    });

    welcomeDialog->exec();
    delete welcomeDialog;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleLogin()
{
    QString role = loginDialog->getRole();
    QString email = loginDialog->getEmail();
    int userId = 0;

    QMessageBox::information(this, "Debug", "Role retrieved: " + role + "\nEmail: " + email);

    DBManager dbManager;
    QSqlDatabase db = dbManager.getDatabase();
    if (!db.isOpen()) {
        QMessageBox::critical(this, "Database Error", "Database connection failed: " + db.lastError().text());
        return;
    }

    QSqlQuery query(db);
    query.prepare("SELECT user_id FROM Users WHERE email = :email AND is_active = TRUE");
    query.bindValue(":email", email);
    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", "Failed to fetch user ID: " + query.lastError().text());
        return;
    }
    if (!query.next()) {
        QMessageBox::critical(this, "Error", "User not found or account is inactive.");
        return;
    }
    userId = query.value("user_id").toInt();
    QMessageBox::information(this, "Debug", "User ID: " + QString::number(userId));

    // Fetch seeker_id or employer_id based on role
    int dashboardId = 0;
    if (role == "job_seeker") {
        QSqlQuery seekerQuery(db);
        seekerQuery.prepare("SELECT seeker_id FROM JobSeekers WHERE user_id = :user_id");
        seekerQuery.bindValue(":user_id", userId);
        if (!seekerQuery.exec() || !seekerQuery.next()) {
            QMessageBox::critical(this, "Error", "No JobSeeker profile found for this user. Please sign up as a Job Seeker first.");
            return;
        }
        dashboardId = seekerQuery.value("seeker_id").toInt();
    } else if (role == "employer") {
        QSqlQuery employerQuery(db);
        employerQuery.prepare("SELECT employer_id FROM Employers WHERE user_id = :user_id");
        employerQuery.bindValue(":user_id", userId);
        if (!employerQuery.exec() || !employerQuery.next()) {
            QMessageBox::critical(this, "Error", "No Employer profile found for this user. Please sign up as an Employer first.");
            return;
        }
        dashboardId = employerQuery.value("employer_id").toInt();
    }

    QDialog *dashboard = nullptr;
    if (role == "job_seeker") {
        dashboard = new DashboardSeeker(this);
        static_cast<DashboardSeeker*>(dashboard)->setSeekerUserId(dashboardId);
    } else if (role == "employer") {
        dashboard = new DashboardEmployer(this);
        static_cast<DashboardEmployer*>(dashboard)->setEmployerUserId(dashboardId);
    } else if (role == "admin") {
        dashboard = new DashboardAdmin(this);
    } else {
        QMessageBox::critical(this, "Error", "Unknown role: " + role);
        return;
    }

    if (dashboard) {
        dashboard->exec();  // Block until the dashboard is closed
        delete dashboard;   // Clean up after the dialog is closed
    }
}
