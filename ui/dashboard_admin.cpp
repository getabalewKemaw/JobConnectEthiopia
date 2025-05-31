#include "dashboard_admin.h"
#include "ui_dashboard_admin.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDateTime>

DashboardAdmin::DashboardAdmin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DashboardAdmin),
    dbManager(new DBManager()),
    employerHead(nullptr),
    jobSeekerHead(nullptr)
{
    ui->setupUi(this);
    loadSystemStats();
    initializeLinkedLists();
    loadEmployerTable();
    loadJobSeekerTable();
    connect(ui->verifyButton, &QPushButton::clicked, this, &DashboardAdmin::on_verifyButton_clicked);
    connect(ui->blockButton, &QPushButton::clicked, this, &DashboardAdmin::on_blockButton_clicked);
    connect(ui->blockJobSeekerButton, &QPushButton::clicked, this, &DashboardAdmin::on_blockJobSeekerButton_clicked);
    connect(ui->searchButton, &QPushButton::clicked, this, &DashboardAdmin::on_searchButton_clicked);
    connect(ui->sortComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &DashboardAdmin::on_sortComboBox_currentIndexChanged);
    connect(ui->logoutButton, &QPushButton::clicked, this, &DashboardAdmin::reject);
}

DashboardAdmin::~DashboardAdmin()
{
    while (employerHead) {
        UserNode* temp = employerHead;
        employerHead = employerHead->next;
        delete temp;
    }
    while (jobSeekerHead) {
        UserNode* temp = jobSeekerHead;
        jobSeekerHead = jobSeekerHead->next;
        delete temp;
    }
    delete dbManager;
    delete ui;
}

void DashboardAdmin::initializeLinkedLists()
{
    employerHead = nullptr;
    jobSeekerHead = nullptr;
}

void DashboardAdmin::addToLinkedList(UserNode*& head, int userId, const QString& name, bool isEmployer)
{
    UserNode* newNode = new UserNode{userId, name, isEmployer, nullptr};
    if (!head) {
        head = newNode;
    } else {
        UserNode* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void DashboardAdmin::mergeSort(UserNode** headRef, bool ascending, bool byId)
{
    UserNode* head = *headRef;
    if (!head || !head->next) return;

    UserNode *left, *right;
    splitList(head, &left, &right);

    mergeSort(&left, ascending, byId);
    mergeSort(&right, ascending, byId);

    *headRef = merge(left, right, ascending, byId);
}

void DashboardAdmin::splitList(UserNode* head, UserNode** left, UserNode** right)
{
    UserNode *slow = head, *fast = head->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    *left = head;
    *right = slow->next;
    slow->next = nullptr;
}

DashboardAdmin::UserNode* DashboardAdmin::merge(UserNode* left, UserNode* right, bool ascending, bool byId)
{
    if (!left) return right;
    if (!right) return left;

    UserNode* result = nullptr;
    bool condition;
    if (byId) {
        condition = ascending ? (left->userId <= right->userId) : (left->userId >= right->userId);
    } else {
        condition = ascending ? (left->name <= right->name) : (left->name >= right->name);
    }

    if (condition) {
        result = left;
        result->next = merge(left->next, right, ascending, byId);
    } else {
        result = right;
        result->next = merge(left, right->next, ascending, byId);
    }
    return result;
}

void DashboardAdmin::displayLinkedList(UserNode* head, QTableWidget* table)
{
    table->setRowCount(0);
    UserNode* current = head;
    while (current) {
        int row = table->rowCount();
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(QString::number(current->userId)));
        table->setItem(row, 1, new QTableWidgetItem(current->name));
        // Ensure other columns are populated based on table structure
        if (table->columnCount() > 2) {
            table->setItem(row, 2, new QTableWidgetItem(""));
            table->setItem(row, 3, new QTableWidgetItem(""));
            table->setItem(row, 4, new QTableWidgetItem(current->isEmployer ? "N/A" : "No"));
            table->setItem(row, 5, new QTableWidgetItem(""));
        }
        current = current->next;
    }
}

void DashboardAdmin::loadSystemStats()
{
    QSqlDatabase db = dbManager->getDatabase();
    if (!db.isOpen()) {
        QMessageBox::critical(this, "Database Error", "Database connection failed: " + db.lastError().text());
        return;
    }

    QSqlQuery query(db);
    int userCount = 0, jobCount = 0, applicationCount = 0;

    query.exec("SELECT COUNT(*) FROM Users");
    if (query.next()) userCount = query.value(0).toInt();

    query.exec("SELECT COUNT(*) FROM Jobs WHERE is_active = TRUE");
    if (query.next()) jobCount = query.value(0).toInt();

    query.exec("SELECT COUNT(*) FROM Applications");
    if (query.next()) applicationCount = query.value(0).toInt();

    ui->statsDisplayLabel->setText(QString("Users: %1 | Jobs: %2 | Applications: %3")
                                       .arg(userCount).arg(jobCount).arg(applicationCount));
}

void DashboardAdmin::loadEmployerTable()
{
    QSqlDatabase db = dbManager->getDatabase();
    if (!db.isOpen()) {
        QMessageBox::critical(this, "Database Error", "Database connection failed: " + db.lastError().text());
        return;
    }

    QSqlQuery query(db);
    query.prepare("SELECT u.user_id, e.employer_id, e.company_name, e.license_number, u.license_verified, u.is_active "
                  "FROM Users u JOIN Employers e ON u.user_id = e.user_id WHERE u.role = 'employer'");
    ui->employerTable->setRowCount(0);

    while (employerHead) {
        UserNode* temp = employerHead;
        employerHead = employerHead->next;
        delete temp;
    }
    employerHead = nullptr;

    if (query.exec()) {
        while (query.next()) {
            int userId = query.value("user_id").toInt();
            QString companyName = query.value("company_name").toString();
            QString licenseVerified = query.value("license_verified").toString();
            addToLinkedList(employerHead, userId, companyName, true);
            int row = ui->employerTable->rowCount();
            ui->employerTable->insertRow(row);
            ui->employerTable->setItem(row, 0, new QTableWidgetItem(QString::number(query.value("employer_id").toInt())));
            ui->employerTable->setItem(row, 1, new QTableWidgetItem(companyName));
            ui->employerTable->setItem(row, 2, new QTableWidgetItem(query.value("license_number").toString()));
            ui->employerTable->setItem(row, 3, new QTableWidgetItem(licenseVerified.isEmpty() ? "No" : licenseVerified));
            ui->employerTable->setItem(row, 4, new QTableWidgetItem(query.value("is_active").toBool() ? "No" : "Yes"));
            ui->employerTable->setItem(row, 5, new QTableWidgetItem(""));
        }
    } else {
        QMessageBox::critical(this, "Database Error", "Failed to load employers: " + query.lastError().text());
    }
}

void DashboardAdmin::loadJobSeekerTable()
{
    QSqlDatabase db = dbManager->getDatabase();
    if (!db.isOpen()) {
        QMessageBox::critical(this, "Database Error", "Database connection failed: " + db.lastError().text());
        return;
    }

    QSqlQuery query(db);
    query.prepare("SELECT u.user_id, js.seeker_id, u.first_name, u.last_name, js.location, js.phone, u.is_active "
                  "FROM Users u JOIN JobSeekers js ON u.user_id = js.user_id WHERE u.role = 'job_seeker'");
    ui->jobSeekerTable->setRowCount(0);

    while (jobSeekerHead) {
        UserNode* temp = jobSeekerHead;
        jobSeekerHead = jobSeekerHead->next;
        delete temp;
    }
    jobSeekerHead = nullptr;

    if (query.exec()) {
        while (query.next()) {
            int userId = query.value("user_id").toInt();
            QString fullName = query.value("first_name").toString() + " " + query.value("last_name").toString();
            addToLinkedList(jobSeekerHead, userId, fullName, false);
            int row = ui->jobSeekerTable->rowCount();
            ui->jobSeekerTable->insertRow(row);
            ui->jobSeekerTable->setItem(row, 0, new QTableWidgetItem(QString::number(query.value("seeker_id").toInt())));
            ui->jobSeekerTable->setItem(row, 1, new QTableWidgetItem(fullName));
            ui->jobSeekerTable->setItem(row, 2, new QTableWidgetItem(query.value("location").toString()));
            ui->jobSeekerTable->setItem(row, 3, new QTableWidgetItem(query.value("phone").toString()));
            ui->jobSeekerTable->setItem(row, 4, new QTableWidgetItem(query.value("is_active").toBool() ? "No" : "Yes"));
            ui->jobSeekerTable->setItem(row, 5, new QTableWidgetItem(""));
        }
    } else {
        QMessageBox::critical(this, "Database Error", "Failed to load job seekers: " + query.lastError().text());
    }
}

void DashboardAdmin::on_verifyButton_clicked()
{
    bool ok;
    int employerId = ui->verifyUserIdLineEdit->text().toInt(&ok);
    if (!ok || ui->verifyUserIdLineEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a valid Employer ID.");
        return;
    }

    QString licenseNumber = ui->licenseNumberLineEdit->text().trimmed();
    if (licenseNumber.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a license verification number.");
        return;
    }

    QSqlDatabase db = dbManager->getDatabase();
    if (!db.isOpen()) {
        QMessageBox::critical(this, "Database Error", "Database connection failed: " + db.lastError().text());
        return;
    }

    // Map employer_id to user_id
    QSqlQuery userQuery(db);
    userQuery.prepare("SELECT user_id FROM Employers WHERE employer_id = :employer_id");
    userQuery.bindValue(":employer_id", employerId);
    if (!userQuery.exec()) {
        QMessageBox::critical(this, "Database Error", "Failed to find employer: " + userQuery.lastError().text());
        return;
    }

    if (!userQuery.next()) {
        QMessageBox::warning(this, "Not Found", "No employer found with the given Employer ID.");
        return;
    }

    int userId = userQuery.value("user_id").toInt();

    // Update license_verified field
    QSqlQuery licenseQuery(db);
    licenseQuery.prepare("UPDATE Users SET license_verified = :license_number WHERE user_id = :user_id AND role = 'employer'");
    licenseQuery.bindValue(":license_number", licenseNumber);
    licenseQuery.bindValue(":user_id", userId);
    if (!licenseQuery.exec()) {
        QMessageBox::critical(this, "Database Error", "Failed to verify employer: " + licenseQuery.lastError().text());
        return;
    }

    if (licenseQuery.numRowsAffected() == 0) {
        QMessageBox::warning(this, "Not Found", "No employer found with the mapped User ID.");
        return;
    }

    // Send notification to the employer
    QSqlQuery notifyQuery(db);
    notifyQuery.prepare("INSERT INTO Notifications (user_id, message, created_at, is_read) "
                        "VALUES (:user_id, :message, :created_at, :is_read)");
    notifyQuery.bindValue(":user_id", userId);
    notifyQuery.bindValue(":message", QString("Your license verification number has been set to: %1").arg(licenseNumber));
    notifyQuery.bindValue(":created_at", QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
    notifyQuery.bindValue(":is_read", false);

    if (!notifyQuery.exec()) {
        QMessageBox::warning(this, "Notification Error", "Failed to send notification: " + notifyQuery.lastError().text());
    }

    QMessageBox::information(this, "Success", "Employer verified successfully! License number sent.");
    ui->verifyUserIdLineEdit->clear();
    ui->licenseNumberLineEdit->clear();
    loadEmployerTable();
}

void DashboardAdmin::on_blockButton_clicked()
{
    QString employerIdStr = ui->blockUserIdLineEdit->text().trimmed();
    bool ok;
    int employerId = employerIdStr.toInt(&ok);
    if (!ok || employerIdStr.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a valid Employer ID to block.");
        return;
    }

    QSqlDatabase db = dbManager->getDatabase();
    if (!db.isOpen()) {
        QMessageBox::critical(this, "Database Error", "Database connection failed: " + db.lastError().text());
        return;
    }

    // Map employer_id to user_id
    QSqlQuery userQuery(db);
    userQuery.prepare("SELECT user_id FROM Employers WHERE employer_id = :employer_id");
    userQuery.bindValue(":employer_id", employerId);
    if (!userQuery.exec() || !userQuery.next()) {
        QMessageBox::warning(this, "Not Found", "No employer found with the given Employer ID.");
        return;
    }

    int userId = userQuery.value("user_id").toInt();

    QSqlQuery blockQuery(db);
    blockQuery.prepare("UPDATE Users SET is_active = FALSE WHERE user_id = :user_id");
    blockQuery.bindValue(":user_id", userId);
    if (!blockQuery.exec()) {
        QMessageBox::critical(this, "Database Error", "Failed to block employer: " + blockQuery.lastError().text());
        return;
    }

    QMessageBox::information(this, "Success", "Employer blocked successfully!");
    ui->blockUserIdLineEdit->clear();
    loadEmployerTable();
}

void DashboardAdmin::on_blockJobSeekerButton_clicked()
{
    QString seekerIdStr = ui->blockJobSeekerIdLineEdit->text().trimmed();
    bool ok;
    int seekerId = seekerIdStr.toInt(&ok);
    if (!ok || seekerIdStr.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a valid Job Seeker ID to block.");
        return;
    }

    QSqlDatabase db = dbManager->getDatabase();
    if (!db.isOpen()) {
        QMessageBox::critical(this, "Database Error", "Database connection failed: " + db.lastError().text());
        return;
    }

    // Map seeker_id to user_id
    QSqlQuery userQuery(db);
    userQuery.prepare("SELECT user_id FROM JobSeekers WHERE seeker_id = :seeker_id");
    userQuery.bindValue(":seeker_id", seekerId);
    if (!userQuery.exec() || !userQuery.next()) {
        QMessageBox::warning(this, "Not Found", "No job seeker found with the given Seeker ID.");
        return;
    }

    int userId = userQuery.value("user_id").toInt();

    QSqlQuery blockQuery(db);
    blockQuery.prepare("UPDATE Users SET is_active = FALSE WHERE user_id = :user_id");
    blockQuery.bindValue(":user_id", userId);
    if (!blockQuery.exec()) {
        QMessageBox::critical(this, "Database Error", "Failed to block job seeker: " + blockQuery.lastError().text());
        return;
    }

    QMessageBox::information(this, "Success", "Job seeker blocked successfully!");
    ui->blockJobSeekerIdLineEdit->clear();
    loadJobSeekerTable();
}

void DashboardAdmin::on_searchButton_clicked()
{
    QString searchTerm = ui->searchLineEdit->text().trimmed().toLower();
    if (searchTerm.isEmpty()) {
        loadEmployerTable();
        loadJobSeekerTable();
        return;
    }

    ui->employerTable->setRowCount(0);
    ui->jobSeekerTable->setRowCount(0);
    UserNode* currentEmployer = employerHead;
    UserNode* currentJobSeeker = jobSeekerHead;

    while (currentEmployer) {
        if (QString::number(currentEmployer->userId).contains(searchTerm) ||
            currentEmployer->name.toLower().contains(searchTerm)) {
            int row = ui->employerTable->rowCount();
            ui->employerTable->insertRow(row);
            ui->employerTable->setItem(row, 0, new QTableWidgetItem(QString::number(currentEmployer->userId)));
            ui->employerTable->setItem(row, 1, new QTableWidgetItem(currentEmployer->name));
            ui->employerTable->setItem(row, 2, new QTableWidgetItem(""));
            ui->employerTable->setItem(row, 3, new QTableWidgetItem(""));
            ui->employerTable->setItem(row, 4, new QTableWidgetItem(""));
            ui->employerTable->setItem(row, 5, new QTableWidgetItem(""));
        }
        currentEmployer = currentEmployer->next;
    }

    while (currentJobSeeker) {
        if (QString::number(currentJobSeeker->userId).contains(searchTerm) ||
            currentJobSeeker->name.toLower().contains(searchTerm)) {
            int row = ui->jobSeekerTable->rowCount();
            ui->jobSeekerTable->insertRow(row);
            ui->jobSeekerTable->setItem(row, 0, new QTableWidgetItem(QString::number(currentJobSeeker->userId)));
            ui->jobSeekerTable->setItem(row, 1, new QTableWidgetItem(currentJobSeeker->name));
            ui->jobSeekerTable->setItem(row, 2, new QTableWidgetItem(""));
            ui->jobSeekerTable->setItem(row, 3, new QTableWidgetItem(""));
            ui->jobSeekerTable->setItem(row, 4, new QTableWidgetItem(""));
            ui->jobSeekerTable->setItem(row, 5, new QTableWidgetItem(""));
        }
        currentJobSeeker = currentJobSeeker->next;
    }
}

void DashboardAdmin::on_sortComboBox_currentIndexChanged(int index)
{
    bool ascending = (index == 0 || index == 2);
    bool byId = (index == 0 || index == 1);
    mergeSort(&employerHead, ascending, byId);
    mergeSort(&jobSeekerHead, ascending, byId);
    displayLinkedList(employerHead, ui->employerTable);
    displayLinkedList(jobSeekerHead, ui->jobSeekerTable);
}
