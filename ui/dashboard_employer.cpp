#include "ui_dashboard_employer.h"
#include "ui/dashboard_employer.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDate>
#include <QStack>
#include <QInputDialog>
#include <QDebug>

DashboardEmployer::DashboardEmployer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DashboardEmployer),
    dbManager(new DBManager()),
    employerUserId(0),
    jobHead(nullptr),
    applicantHead(nullptr)
{
    ui->setupUi(this);

    initializeStructures();
    loadApplicantsTable();
    connect(ui->postJobButton, &QPushButton::clicked, this, &DashboardEmployer::on_postJobButton_clicked);
    connect(ui->shortlistButton, &QPushButton::clicked, this, &DashboardEmployer::on_shortlistButton_clicked);
    connect(ui->searchApplicantButton, &QPushButton::clicked, this, &DashboardEmployer::on_searchApplicantButton_clicked);
    connect(ui->sortApplicantComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &DashboardEmployer::on_sortApplicantComboBox_currentIndexChanged);
    connect(ui->logoutButton, &QPushButton::clicked, this, &DashboardEmployer::reject);
    connect(ui->applicantsTable, &QTableWidget::cellClicked, this, &DashboardEmployer::on_applicantsTable_cellClicked);
}

DashboardEmployer::~DashboardEmployer()
{
    while (jobHead) {
        JobNode* temp = jobHead;
        jobHead = jobHead->next;
        delete temp;
    }
    while (applicantHead) {
        Applicant* temp = applicantHead;
        applicantHead = applicantHead->next;
        delete temp;
    }
    delete dbManager;
    delete ui;
}

void DashboardEmployer::setEmployerUserId(int userId)
{
    employerUserId = userId;
    loadApplicantsTable();

    QSqlDatabase db = dbManager->getDatabase();
    if (!db.isOpen()) {
        ui->licenseStatusLabel->setText("License Verification Status: Database connection failed");
        QMessageBox::critical(this, "Database Error", "Failed to connect to database: " + db.lastError().text());
        return;
    }

    // Map employer_id to user_id
    QSqlQuery userQuery(db);
    userQuery.prepare("SELECT user_id FROM Employers WHERE employer_id = :employer_id");
    userQuery.bindValue(":employer_id", employerUserId);
    if (!userQuery.exec()) {
        ui->licenseStatusLabel->setText("License Verification Status: Error finding user");
        QMessageBox::critical(this, "Query Error", "Failed to find employer user_id: " + userQuery.lastError().text());
        return;
    }

    if (!userQuery.next()) {
        ui->licenseStatusLabel->setText("License Verification Status: Employer not found in Employers table");
        QMessageBox::warning(this, "Data Error", QString("No employer found with employer_id %1 in Employers table").arg(employerUserId));
        return;
    }

    int actualUserId = userQuery.value("user_id").toInt();

    // Fetch license_verified using the correct user_id
    QSqlQuery licenseQuery(db);
    licenseQuery.prepare("SELECT license_verified FROM Users WHERE user_id = :user_id AND role = 'employer'");
    licenseQuery.bindValue(":user_id", actualUserId);
    if (!licenseQuery.exec()) {
        ui->licenseStatusLabel->setText("License Verification Status: Error loading status");
        QMessageBox::critical(this, "Query Error", "Failed to fetch license status: " + licenseQuery.lastError().text());
        return;
    }

    if (!licenseQuery.next()) {
        ui->licenseStatusLabel->setText("License Verification Status: Employer not found in Users table");
        QMessageBox::warning(this, "Data Error", QString("No employer found with user_id %1 in Users table").arg(actualUserId));
        return;
    }

    QString licenseNumber = licenseQuery.value("license_verified").toString();
    if (!licenseNumber.isEmpty()) {
        ui->licenseStatusLabel->setText(QString("License Verification Number: %1").arg(licenseNumber));
    } else {
        ui->licenseStatusLabel->setText("License Verification Status: Not Verified");
    }

    // Check for unread notifications about license updates
    QSqlQuery notifyQuery(db);
    notifyQuery.prepare("SELECT message FROM Notifications WHERE user_id = :user_id AND is_read = FALSE");
    notifyQuery.bindValue(":user_id", actualUserId);
    if (notifyQuery.exec()) {
        while (notifyQuery.next()) {
            QString message = notifyQuery.value("message").toString();
            if (message.contains("license verification number")) {
                QMessageBox::information(this, "Notification", message);
                // Mark the notification as read
                QSqlQuery updateNotify(db);
                updateNotify.prepare("UPDATE Notifications SET is_read = TRUE WHERE user_id = :user_id AND message = :message");
                updateNotify.bindValue(":user_id", actualUserId);
                updateNotify.bindValue(":message", message);
                updateNotify.exec();
            }
        }
    }
}

void DashboardEmployer::initializeStructures()
{
    jobHead = nullptr;
    applicantHead = nullptr;
}

void DashboardEmployer::addJobNode(int jobId, const QString& title, const QString& description, int experienceRequired,
                                   const QString& salaryRange, const QString& deadline)
{
    JobNode* newNode = new JobNode(jobId, title, description, experienceRequired, salaryRange, deadline);
    newNode->next = jobHead;
    jobHead = newNode;
}

void DashboardEmployer::addToApplicantStack(Applicant* applicant)
{
    applicant->next = applicantHead;
    applicantHead = applicant;
}

void DashboardEmployer::sortApplicantStack(bool ascending, bool byId)
{
    if (!applicantHead || !applicantHead->next) return;

    QStack<Applicant*> stack;
    Applicant* current = applicantHead;
    while (current) {
        stack.push(current);
        current = current->next;
    }

    applicantHead = nullptr;
    while (!stack.isEmpty()) {
        Applicant* temp = stack.pop();
        Applicant** link = &applicantHead;
        while (*link && ((ascending ?
                              (byId ? (*link)->seekerId < temp->seekerId : (*link)->fullName < temp->fullName) :
                              (byId ? (*link)->seekerId > temp->seekerId : (*link)->fullName > temp->fullName)))) {
            link = &(*link)->next;
        }
        temp->next = *link;
        *link = temp;
    }
}

void DashboardEmployer::displayApplicantStack(QTableWidget* table)
{
    table->setRowCount(0);
    Applicant* current = applicantHead;
    while (current) {
        int row = table->rowCount();
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(QString::number(current->jobId)));
        table->setItem(row, 1, new QTableWidgetItem(QString::number(current->seekerId)));
        table->setItem(row, 2, new QTableWidgetItem(current->fullName));
        table->setItem(row, 3, new QTableWidgetItem(current->status));
        table->setItem(row, 4, new QTableWidgetItem(current->applicationDetails.isEmpty() ? "No Details" : "View Details"));
        current = current->next;
    }
}

void DashboardEmployer::loadApplicantsTable()
{
    QSqlDatabase db = dbManager->getDatabase();
    if (!db.isOpen()) {
        QMessageBox::critical(this, "Database Error", "Database connection failed: " + db.lastError().text());
        return;
    }

    QSqlQuery query(db);
    query.prepare("SELECT a.application_id, a.job_id, a.seeker_id, js.full_name, a.status, a.application_details "
                  "FROM Applications a "
                  "JOIN Jobs j ON a.job_id = j.job_id "
                  "JOIN JobSeekers js ON a.seeker_id = js.seeker_id "
                  "WHERE j.employer_id = :employer_id");
    query.bindValue(":employer_id", employerUserId);
    ui->applicantsTable->setRowCount(0);

    while (applicantHead) {
        Applicant* temp = applicantHead;
        applicantHead = applicantHead->next;
        delete temp;
    }
    applicantHead = nullptr;

    if (query.exec()) {
        while (query.next()) {
            int applicationId = query.value("application_id").toInt();
            int jobId = query.value("job_id").toInt();
            int seekerId = query.value("seeker_id").toInt();
            QString fullName = query.value("full_name").toString();
            QString status = query.value("status").toString();
            QString applicationDetails = query.value("application_details").toString();
            Applicant* newApplicant = new Applicant{applicationId, jobId, seekerId, fullName, status, applicationDetails, nullptr};
            addToApplicantStack(newApplicant);
        }
        displayApplicantStack(ui->applicantsTable);
    } else {
        QMessageBox::critical(this, "Database Error", "Failed to load applicants: " + query.lastError().text());
    }
}

void DashboardEmployer::on_postJobButton_clicked()
{
    QString title = ui->jobTitleLineEdit->text().trimmed();
    QString description = ui->descriptionTextEdit->toPlainText().trimmed();
    bool ok;
    int experienceRequired = ui->experienceSpinBox->text().toInt(&ok);
    QString salaryRange = ui->salaryLineEdit->text().trimmed();
    QString deadlineStr = ui->deadlineLineEdit->text().trimmed();
    QString location = ui->locationLineEdit->text().trimmed();
    QString jobType = ui->jobTypeComboBox->currentText();
    QString workMode = ui->workModeComboBox->currentText();
    QString industry = ui->industryLineEdit->text().trimmed();
    QString skills = ui->skillsTextEdit->toPlainText().trimmed();

    if (title.isEmpty() || description.isEmpty() || !ok || salaryRange.isEmpty() || deadlineStr.isEmpty() ||
        location.isEmpty() || jobType.isEmpty() || workMode.isEmpty() || industry.isEmpty() || skills.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "All fields are required.");
        return;
    }

    QDate deadline = QDate::fromString(deadlineStr, "yyyy-MM-dd");
    if (!deadline.isValid()) {
        QMessageBox::warning(this, "Input Error", "Invalid deadline format. Use yyyy-MM-dd.");
        return;
    }

    QString licenseNumber = QInputDialog::getText(this, tr("License Verification"),
                                                  tr("Enter the license verification number provided by Admin:"),
                                                  QLineEdit::Normal, "", &ok);
    if (!ok || licenseNumber.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "License verification number is required.");
        return;
    }

    QSqlDatabase db = dbManager->getDatabase();
    if (!db.isOpen()) {
        QMessageBox::critical(this, "Database Error", "Database connection failed.");
        return;
    }

    // Map employer_id to user_id for license verification
    QSqlQuery userQuery(db);
    userQuery.prepare("SELECT user_id FROM Employers WHERE employer_id = :employer_id");
    userQuery.bindValue(":employer_id", employerUserId);
    if (!userQuery.exec() || !userQuery.next()) {
        QMessageBox::critical(this, "Database Error", "Failed to find employer user_id.");
        return;
    }
    int actualUserId = userQuery.value("user_id").toInt();

    QSqlQuery licenseQuery(db);
    licenseQuery.prepare("SELECT license_verified FROM Users WHERE user_id = :user_id AND role = 'employer'");
    licenseQuery.bindValue(":user_id", actualUserId);
    if (!licenseQuery.exec()) {
        QMessageBox::critical(this, "Database Error", "Failed to verify license: " + licenseQuery.lastError().text());
        return;
    }

    QString expectedLicense;
    if (licenseQuery.next()) {
        expectedLicense = licenseQuery.value("license_verified").toString();
    } else {
        QMessageBox::critical(this, "Database Error", "Employer not found in Users table.");
        return;
    }

    if (expectedLicense != licenseNumber) {
        QMessageBox::warning(this, "License Error", "Invalid license verification number.");
        return;
    }

    QSqlQuery insertQuery(db);
    insertQuery.prepare("INSERT INTO Jobs (employer_id, title, description, experience_required, salary_range, deadline, location, job_type, work_mode, industry, skills_required, is_active) "
                        "VALUES (:employer_id, :title, :description, :experience_required, :salary_range, :deadline, :location, :job_type, :work_mode, :industry, :skills_required, TRUE)");
    insertQuery.bindValue(":employer_id", employerUserId);
    insertQuery.bindValue(":title", title);
    insertQuery.bindValue(":description", description);
    insertQuery.bindValue(":experience_required", experienceRequired);
    insertQuery.bindValue(":salary_range", salaryRange);
    insertQuery.bindValue(":deadline", deadlineStr);
    insertQuery.bindValue(":location", location);
    insertQuery.bindValue(":job_type", jobType);
    insertQuery.bindValue(":work_mode", workMode);
    insertQuery.bindValue(":industry", industry);
    insertQuery.bindValue(":skills_required", skills);

    if (!insertQuery.exec()) {
        QMessageBox::critical(this, "Database Error", "Failed to post job: " + insertQuery.lastError().text() +
                                                          "\nEnsure all columns exist in the Jobs table.");
        return;
    }

    int jobId = insertQuery.lastInsertId().toInt();
    addJobNode(jobId, title, description, experienceRequired, salaryRange, deadlineStr);
    QMessageBox::information(this, "Success", "Job posted successfully!");
    ui->jobTitleLineEdit->clear();
    ui->descriptionTextEdit->clear();
    ui->experienceSpinBox->setValue(0);
    ui->salaryLineEdit->clear();
    ui->deadlineLineEdit->clear();
    ui->locationLineEdit->clear();
    ui->jobTypeComboBox->setCurrentIndex(0);
    ui->workModeComboBox->setCurrentIndex(0);
    ui->industryLineEdit->clear();
    ui->skillsTextEdit->clear();
}

void DashboardEmployer::on_shortlistButton_clicked()
{
    QString seekerIdStr = ui->shortlistSeekerIdLineEdit->text().trimmed();
    bool ok;
    int seekerId = seekerIdStr.toInt(&ok);
    if (!ok || seekerIdStr.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please enter a valid Seeker ID to update status.");
        return;
    }

    QSqlDatabase db = dbManager->getDatabase();
    if (!db.isOpen()) {
        QMessageBox::critical(this, "Database Error", "Database connection failed: " + db.lastError().text());
        return;
    }

    QSqlQuery appQuery(db);
    appQuery.prepare("SELECT a.application_id, a.job_id, j.title "
                     "FROM Applications a "
                     "JOIN Jobs j ON a.job_id = j.job_id "
                     "WHERE a.seeker_id = :seeker_id AND j.employer_id = :employer_id");
    appQuery.bindValue(":seeker_id", seekerId);
    appQuery.bindValue(":employer_id", employerUserId);
    if (!appQuery.exec()) {
        QMessageBox::critical(this, "Database Error", "Failed to find application: " + appQuery.lastError().text());
        return;
    }

    if (!appQuery.next()) {
        QMessageBox::warning(this, "Error", "No application found for this seeker ID under your jobs.");
        return;
    }

    int applicationId = appQuery.value("application_id").toInt();
    QString jobTitle = appQuery.value("title").toString();

    QStringList statusOptions = {"pending", "shortlisted", "rejected", "hired"};
    QString newStatus = QInputDialog::getItem(this, "Update Status", "Select new status:", statusOptions, 0, false);
    if (newStatus.isEmpty()) return;

    QSqlQuery updateQuery(db);
    updateQuery.prepare("UPDATE Applications SET status = :status WHERE application_id = :application_id");
    updateQuery.bindValue(":status", newStatus);
    updateQuery.bindValue(":application_id", applicationId);

    if (!updateQuery.exec()) {
        QMessageBox::critical(this, "Database Error", "Failed to update status: " + updateQuery.lastError().text());
        return;
    }

    QSqlQuery seekerQuery(db);
    seekerQuery.prepare("SELECT js.user_id "
                        "FROM JobSeekers js "
                        "WHERE js.seeker_id = :seeker_id");
    seekerQuery.bindValue(":seeker_id", seekerId);
    if (!seekerQuery.exec() || !seekerQuery.next()) {
        QMessageBox::warning(this, "Notification Error", "Could not find seeker for this application: " + seekerQuery.lastError().text());
        return;
    }

    int seekerUserId = seekerQuery.value("user_id").toInt();

    QSqlQuery notifyQuery(db);
    notifyQuery.prepare("INSERT INTO Notifications (user_id, message, created_at, is_read) "
                        "VALUES (:user_id, :message, :created_at, :is_read)");
    notifyQuery.bindValue(":user_id", seekerUserId);
    notifyQuery.bindValue(":message", "Your application for '" + jobTitle + "' has been updated to: " + newStatus);
    notifyQuery.bindValue(":created_at", QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
    notifyQuery.bindValue(":is_read", false);

    if (!notifyQuery.exec()) {
        QMessageBox::warning(this, "Notification Error", "Failed to send notification to seeker: " + notifyQuery.lastError().text());
    }

    QMessageBox::information(this, "Success", "Application status updated to '" + newStatus + "'. Seeker has been notified.");
    ui->shortlistSeekerIdLineEdit->clear();
    loadApplicantsTable();
}

void DashboardEmployer::on_searchApplicantButton_clicked()
{
    QString searchTerm = ui->searchApplicantLineEdit->text().trimmed().toLower();
    if (searchTerm.isEmpty()) {
        loadApplicantsTable();
        return;
    }

    ui->applicantsTable->setRowCount(0);
    Applicant* current = applicantHead;
    while (current) {
        if (QString::number(current->seekerId).contains(searchTerm) ||
            current->fullName.toLower().contains(searchTerm)) {
            int row = ui->applicantsTable->rowCount();
            ui->applicantsTable->insertRow(row);
            ui->applicantsTable->setItem(row, 0, new QTableWidgetItem(QString::number(current->jobId)));
            ui->applicantsTable->setItem(row, 1, new QTableWidgetItem(QString::number(current->seekerId)));
            ui->applicantsTable->setItem(row, 2, new QTableWidgetItem(current->fullName));
            ui->applicantsTable->setItem(row, 3, new QTableWidgetItem(current->status));
            ui->applicantsTable->setItem(row, 4, new QTableWidgetItem(current->applicationDetails.isEmpty() ? "No Details" : "View Details"));
        }
        current = current->next;
    }
}

void DashboardEmployer::on_sortApplicantComboBox_currentIndexChanged(int index)
{
    bool ascending = (index == 0 || index == 2);
    bool byId = (index == 0 || index == 1);
    sortApplicantStack(ascending, byId);
    displayApplicantStack(ui->applicantsTable);
}

void DashboardEmployer::on_applicantsTable_cellClicked(int row, int column)
{
    if (column == 4 && ui->applicantsTable->item(row, 4)->text() == "View Details") {
        int seekerId = ui->applicantsTable->item(row, 1)->text().toInt();
        int jobId = ui->applicantsTable->item(row, 0)->text().toInt();
        QSqlDatabase db = dbManager->getDatabase();
        if (!db.isOpen()) {
            QMessageBox::critical(this, "Database Error", "Database connection failed: " + db.lastError().text());
            return;
        }

        QSqlQuery query(db);
        query.prepare("SELECT application_details FROM Applications WHERE seeker_id = :seeker_id AND job_id = :job_id");
        query.bindValue(":seeker_id", seekerId);
        query.bindValue(":job_id", jobId);
        if (query.exec() && query.next()) {
            QString details = query.value("application_details").toString();
            QMessageBox::information(this, "Application Details", details);
        } else {
            QMessageBox::warning(this, "Error", "Could not load application details: " + query.lastError().text());
        }
    }
}
