#include "ui_dashboard_employer.h"
#include "dashboard_employer.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDate>
#include <QInputDialog>
#include <QDebug>
#include <QFileDialog>
#include <QTextStream>
#include <QStringList>

DashboardEmployer::DashboardEmployer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DashboardEmployer),
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
    connect(ui->searchApplicantLineEdit, &QLineEdit::textChanged, this, &DashboardEmployer::on_searchApplicantLineEdit_textChanged);
    connect(ui->fileUploadButton, &QPushButton::clicked, this, [this]() {
        QString filePath = QFileDialog::getOpenFileName(this, tr("Upload Job Description File"), "", tr("Files (*.pdf *.txt *.png)"));
        if (!filePath.isEmpty()) {
            ui->fileUploadButton->setProperty("filePath", filePath);
            ui->fileUploadButton->setText(QFileInfo(filePath).fileName());
        }
    });
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
    delete ui;
}

void DashboardEmployer::setEmployerUserId(int userId)
{
    employerUserId = userId;
    loadApplicantsTable();

    QSqlDatabase db = DBManager::getInstance().getDatabase();
    if (!db.isOpen()) {
        ui->licenseStatusLabel->setText("License Verification Status: Database connection failed");
        QMessageBox::critical(this, "Database Error", "Failed to connect to database: " + db.lastError().text());
        return;
    }

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

    QSqlQuery licenseQuery(db);
    licenseQuery.prepare("SELECT license_verified FROM Users WHERE user_id = :user_id");
    licenseQuery.bindValue(":user_id", actualUserId);
    if (!licenseQuery.exec()) {
        ui->licenseStatusLabel->setText("License Verification Status: Error loading status");
        QMessageBox::critical(this, "Query Error", "Failed to fetch license status: " + licenseQuery.lastError().text());
        return;
    }

    if (!licenseQuery.next()) {
        ui->licenseStatusLabel->setText("License Verification Status: User not found in Users table");
        QMessageBox::warning(this, "Data Error", QString("No user found with user_id %1 in Users table").arg(actualUserId));
        return;
    }

    QString licenseNumber = licenseQuery.value("license_verified").toString();
    if (!licenseNumber.isEmpty()) {
        ui->licenseStatusLabel->setText(QString("License Verification Number: %1").arg(licenseNumber));
    } else {
        ui->licenseStatusLabel->setText("License Verification Status: Not Verified");
    }

    QSqlQuery notifyQuery(db);
    notifyQuery.prepare("SELECT message FROM Notifications WHERE user_id = :user_id AND is_read = FALSE");
    notifyQuery.bindValue(":user_id", actualUserId);
    if (notifyQuery.exec()) {
        while (notifyQuery.next()) {
            QString message = notifyQuery.value("message").toString();
            if (message.contains("license verification number")) {
                QMessageBox::information(this, "Notification", message);
                QSqlQuery updateNotify(db);
                updateNotify.prepare("UPDATE Notifications SET is_read = TRUE WHERE user_id = :user_id AND message = :message");
                updateNotify.bindValue(":user_id", actualUserId);
                updateNotify.bindValue(":message", message);
                updateNotify.exec();
            }
        }
    }
}

void DashboardEmployer::setLoggedInUser(const QString& fullName)
{
    loggedInUser = fullName;
    updateWelcomeLabel();
}

void DashboardEmployer::updateWelcomeLabel()
{
    if (!loggedInUser.isEmpty()) {
        ui->titleLabel->setText(QString("Employer Dashboard - Welcome %1").arg(loggedInUser));
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

void DashboardEmployer::mergeSort(Applicant** headRef, bool ascending, bool byId)
{
    Applicant* head = *headRef;
    if (!head || !head->next) return;

    Applicant *left, *right;
    splitList(head, &left, &right);

    mergeSort(&left, ascending, byId);
    mergeSort(&right, ascending, byId);

    *headRef = merge(left, right, ascending, byId);
}

void DashboardEmployer::splitList(Applicant* head, Applicant** left, Applicant** right)
{
    Applicant *slow = head, *fast = head->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    *left = head;
    *right = slow->next;
    slow->next = nullptr;
}

Applicant* DashboardEmployer::merge(Applicant* left, Applicant* right, bool ascending, bool byId)
{
    if (!left) return right;
    if (!right) return left;

    Applicant* result = nullptr;
    if ((ascending && byId && left->seekerId <= right->seekerId) ||
        (ascending && !byId && left->fullName <= right->fullName) ||
        (!ascending && byId && left->seekerId >= right->seekerId) ||
        (!ascending && !byId && left->fullName >= right->fullName)) {
        result = left;
        result->next = merge(left->next, right, ascending, byId);
    } else {
        result = right;
        result->next = merge(left, right->next, ascending, byId);
    }
    return result;
}

void DashboardEmployer::sortApplicantStack(bool ascending, bool byId)
{
    mergeSort(&applicantHead, ascending, byId);
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
    QSqlDatabase db = DBManager::getInstance().getDatabase();
    if (!db.isOpen()) {
        QMessageBox::critical(this, "Database Error", "Database connection failed: " + db.lastError().text());
        return;
    }

    QSqlQuery query(db);
    query.prepare("SELECT a.application_id, a.job_id, a.seeker_id, u.first_name, u.last_name, a.status, a.application_details "
                  "FROM Applications a "
                  "JOIN Jobs j ON a.job_id = j.job_id "
                  "JOIN JobSeekers js ON a.seeker_id = js.seeker_id "
                  "JOIN Users u ON js.user_id = u.user_id "
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
            QString firstName = query.value("first_name").toString();
            QString lastName = query.value("last_name").toString();
            QString fullName = firstName + " " + lastName;
            QString status = query.value("status").toString();
            QString applicationDetails = query.value("application_details").toString();
            Applicant* newApplicant = new Applicant{applicationId, jobId, seekerId, fullName, status, applicationDetails, nullptr};
            addToApplicantStack(newApplicant);
        }
        displayApplicantStack(ui->applicantsTable);
    } else {
        QMessageBox::critical(this, "Database Error", "Failed to load applicants: " + query.lastError().text() +
                                                          "\nEnsure Applications, Jobs, JobSeekers, and Users tables exist with the specified columns.");
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
    QString filePath = ui->fileUploadButton->property("filePath").toString();

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

    QSqlDatabase db = DBManager::getInstance().getDatabase();
    if (!db.isOpen()) {
        QMessageBox::critical(this, "Database Error", "Database connection failed.");
        return;
    }

    QSqlQuery userQuery(db);
    userQuery.prepare("SELECT user_id FROM Employers WHERE employer_id = :employer_id");
    userQuery.bindValue(":employer_id", employerUserId);
    if (!userQuery.exec() || !userQuery.next()) {
        QMessageBox::critical(this, "Database Error", "Failed to find employer user_id.");
        return;
    }
    int actualUserId = userQuery.value("user_id").toInt();

    QSqlQuery licenseQuery(db);
    licenseQuery.prepare("SELECT license_verified FROM Users WHERE user_id = :user_id");
    licenseQuery.bindValue(":user_id", actualUserId);
    if (!licenseQuery.exec()) {
        QMessageBox::critical(this, "Database Error", "Failed to verify license: " + licenseQuery.lastError().text());
        return;
    }

    QString expectedLicense;
    if (licenseQuery.next()) {
        expectedLicense = licenseQuery.value("license_verified").toString();
    } else {
        QMessageBox::critical(this, "Database Error", "User not found in Users table.");
        return;
    }

    if (expectedLicense.isEmpty() || expectedLicense != licenseNumber) {
        QMessageBox::warning(this, "License Error", "Invalid or missing license verification number.");
        return;
    }

    if (!filePath.isEmpty()) {
        if (filePath.endsWith(".png")) {
            description += "\n\n[PNG File Uploaded: Cannot display image in text. Contact employer for details.]";
        } else {
            QFile file(filePath);
            if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
                QTextStream in(&file);
                description += "\n\nFile Content:\n" + in.readAll();
                file.close();
            } else {
                QMessageBox::warning(this, "File Error", "Could not read the uploaded file.");
                return;
            }
        }
    }

    QSqlQuery insertQuery(db);
    insertQuery.prepare("INSERT INTO Jobs (employer_id, title, description, experience_required, salary_range, deadline, location, job_type, work_mode, industry, is_active) "
                        "VALUES (:employer_id, :title, :description, :experience_required, :salary_range, :deadline, :location, :job_type, :work_mode, :industry, TRUE)");
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
    if (!insertQuery.exec()) {
        QMessageBox::critical(this, "Database Error", "Failed to post job: " + insertQuery.lastError().text() +
                                                          "\nEnsure all columns exist in the Jobs table.");
        return;
    }

    int jobId = insertQuery.lastInsertId().toInt();

    // Parse and insert skills into JobSkills
    QSqlQuery query(db); // Declare query here
    QStringList skillList = skills.split(",", Qt::SkipEmptyParts);
    foreach (const QString& skill, skillList) {
        QString trimmedSkill = skill.trimmed();
        int skillId = -1;
        QSqlQuery skillQuery(db);
        skillQuery.prepare("SELECT skill_id FROM Skills WHERE skill_name = :skill_name");
        skillQuery.bindValue(":skill_name", trimmedSkill);
        if (skillQuery.exec() && skillQuery.next()) {
            skillId = skillQuery.value("skill_id").toInt();
        } else {
            QSqlQuery insertSkillQuery(db);
            insertSkillQuery.prepare("INSERT INTO Skills (skill_name) VALUES (:skill_name)");
            insertSkillQuery.bindValue(":skill_name", trimmedSkill);
            if (!insertSkillQuery.exec()) {
                QMessageBox::critical(this, "Database Error", "Failed to insert new skill: " + insertSkillQuery.lastError().text());
                query.exec("ROLLBACK");
                return;
            }
            skillId = insertSkillQuery.lastInsertId().toInt();
        }
        QSqlQuery jobSkillQuery(db);
        jobSkillQuery.prepare("INSERT INTO JobSkills (job_id, skill_id) VALUES (:job_id, :skill_id)");
        jobSkillQuery.bindValue(":job_id", jobId);
        jobSkillQuery.bindValue(":skill_id", skillId);
        if (!jobSkillQuery.exec()) {
            QMessageBox::critical(this, "Database Error", "Failed to link skill to job: " + jobSkillQuery.lastError().text());
            query.exec("ROLLBACK");
            return;
        }
    }

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
    ui->fileUploadButton->setProperty("filePath", "");
    ui->fileUploadButton->setText("Upload File");
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

    QSqlDatabase db = DBManager::getInstance().getDatabase();
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

void DashboardEmployer::on_searchApplicantLineEdit_textChanged(const QString& text)
{
    QString searchTerm = text.trimmed().toLower();
    ui->applicantsTable->setRowCount(0);
    Applicant* current = applicantHead;

    while (current) {
        if (searchTerm.isEmpty() ||
            QString::number(current->seekerId).contains(searchTerm) ||
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

void DashboardEmployer::on_searchApplicantButton_clicked()
{
    // No need for separate search button action; handled by textChanged
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
        QSqlDatabase db = DBManager::getInstance().getDatabase();
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
