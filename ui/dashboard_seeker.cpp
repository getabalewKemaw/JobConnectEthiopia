#include "dashboard_seeker.h"
#include "ui_dashboard_seeker.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QInputDialog>
#include <QDate>
#include <QFileDialog>
#include <QTextStream>
#include "core/dbmanager.h"

DashboardSeeker::DashboardSeeker(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DashboardSeeker),
    seekerUserId(0),
    jobHead(nullptr)
{
    ui->setupUi(this);
    setStyleSheet(
        "QPushButton { background-color: #4CAF50; color: white; padding: 6px 12px; border-radius: 4px; font: 13px 'Arial'; border: none; min-width: 90px; min-height: 30px; }"
        "QPushButton:hover { background-color: #45a049; }"
        "QPushButton:pressed { background-color: #3d8b40; }"
        "QPushButton#logoutButton { background-color: #f44336; }"
        "QPushButton#logoutButton:hover { background-color: #da190b; }"
        "QLineEdit, QTextEdit { border: 1px solid #d1d5db; border-radius: 4px; padding: 4px; font: 13px 'Arial'; min-width: 180px; min-height: 28px; background-color: #fff; }"
        "QLineEdit:focus, QTextEdit:focus { border-color: #4CAF50; }"
        "QTableWidget { border: 1px solid #d1d5db; border-radius: 4px; background-color: white; font: 13px 'Arial'; min-width: 500px; min-height: 250px; gridline-color: #e5e7eb; }"
        "QTableWidget::item:selected { background-color: #e6f0fa; color: #1f2937; }"
        "QLabel { color: #1f2937; font: 13px 'Arial'; }"
        "QComboBox { border: 1px solid #d1d5db; border-radius: 4px; padding: 4px; font: 13px 'Arial'; min-width: 120px; min-height: 28px; background-color: #fff; }"
        "QComboBox:hover { border-color: #4CAF50; }"
        "QComboBox::drop-down { border: none; }"
        "QDialog { background-color: white; border: 1px solid #e5e7eb; border-radius: 8px; }"
        "QLabel#titleLabel { font: bold 24px 'Arial'; color: #2D6A4F; background-color: #D1E8E2; border-radius: 5px; padding: 10px; }"
        "QLabel#profileLabel { font: bold 18px 'Arial'; color: #2E4053; background-color: #D1E8E2; padding: 5px; }"
        "QLabel#jobsLabel { font: bold 18px 'Arial'; color: #2E4053; background-color: #D1E8E2; padding: 5px; }"
        "QLabel#applicationsLabel { font: bold 18px 'Arial'; color: #2E4053; background-color: #D1E8E2; padding: 5px; }"
        "QLabel#profileStatusLabel { font: bold 14px 'Arial'; color: #2D6A4F; background-color: #D1E8E2; padding: 5px; border-radius: 5px; }"
        );
    adjustSize();

    initializeLinkedList();
    loadJobsTable();
    loadApplicationsTable();
    connect(ui->applyButton, &QPushButton::clicked, this, &DashboardSeeker::on_applyButton_clicked);
    connect(ui->updateProfileButton, &QPushButton::clicked, this, &DashboardSeeker::on_updateProfileButton_clicked);
    connect(ui->searchButton, &QPushButton::clicked, this, &DashboardSeeker::on_searchButton_clicked);
    connect(ui->sortComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &DashboardSeeker::on_sortComboBox_currentIndexChanged);
    connect(ui->logoutButton, &QPushButton::clicked, this, &DashboardSeeker::reject);
    connect(ui->applicationsTable, &QTableWidget::cellClicked, this, &DashboardSeeker::on_applicationsTable_cellClicked);
    connect(ui->jobsTable, &QTableWidget::cellClicked, this, &DashboardSeeker::on_jobsTable_cellClicked);
}

DashboardSeeker::~DashboardSeeker()
{
    while (jobHead) {
        JobNode* temp = jobHead;
        jobHead = jobHead->next;
        delete temp;
    }
    delete ui;
}

void DashboardSeeker::setSeekerUserId(int userId)
{
    seekerUserId = userId;
    loadProfile();
    loadJobsTable();
    loadApplicationsTable();
}

void DashboardSeeker::setSeekerDetails(const QString& skills, const QString& education, const QString& workExperience)
{
    seekerSkills = skills;
    seekerEducation = education;
    seekerWorkExperience = workExperience;
}

void DashboardSeeker::initializeLinkedList()
{
    jobHead = nullptr;
}

void DashboardSeeker::addToLinkedList(int jobId, const QString& title, const QString& company, const QString& location,
                                      const QString& salary, const QString& deadline, const QString& jobType,
                                      const QString& workMode, const QString& industry, const QString& skillsRequired,
                                      const QString& additionalDetails)
{
    JobNode* newNode = new JobNode(jobId, title, company, location, salary, deadline, jobType, workMode, industry, skillsRequired, additionalDetails);
    newNode->next = jobHead;
    jobHead = newNode;
}

void DashboardSeeker::mergeSort(JobNode** headRef, bool bySalary, bool ascending)
{
    JobNode* head = *headRef;
    if (!head || !head->next) return;

    JobNode *left, *right;
    splitList(head, &left, &right);
    mergeSort(&left, bySalary, ascending);
    mergeSort(&right, bySalary, ascending);
    *headRef = merge(left, right, bySalary, ascending);
}

void DashboardSeeker::splitList(JobNode* head, JobNode** left, JobNode** right)
{
    JobNode *slow = head, *fast = head->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    *left = head;
    *right = slow->next;
    slow->next = nullptr;
}

JobNode* DashboardSeeker::merge(JobNode* left, JobNode* right, bool bySalary, bool ascending)
{
    if (!left) return right;
    if (!right) return left;

    JobNode* result = nullptr;
    bool condition = bySalary
                         ? (ascending ? left->salaryRange.split("-")[0].toInt() <= right->salaryRange.split("-")[0].toInt()
                                      : left->salaryRange.split("-")[0].toInt() >= right->salaryRange.split("-")[0].toInt())
                         : (ascending ? QDate::fromString(left->deadline, "yyyy-MM-dd") <= QDate::fromString(right->deadline, "yyyy-MM-dd")
                                      : QDate::fromString(left->deadline, "yyyy-MM-dd") >= QDate::fromString(right->deadline, "yyyy-MM-dd"));

    result = condition ? left : right;
    result->next = merge(condition ? left->next : left, condition ? right : right->next, bySalary, ascending);
    return result;
}

void DashboardSeeker::sortLinkedList(bool bySalary, bool ascending)
{
    mergeSort(&jobHead, bySalary, ascending);
}

void DashboardSeeker::displayLinkedList()
{
    ui->jobsTable->setRowCount(0);
    for (JobNode* current = jobHead; current; current = current->next) {
        int row = ui->jobsTable->rowCount();
        ui->jobsTable->insertRow(row);
        ui->jobsTable->setItem(row, 0, new QTableWidgetItem(QString::number(current->jobId)));
        ui->jobsTable->setItem(row, 1, new QTableWidgetItem(current->title));
        ui->jobsTable->setItem(row, 2, new QTableWidgetItem(current->companyName));
        ui->jobsTable->setItem(row, 3, new QTableWidgetItem(current->location));
        ui->jobsTable->setItem(row, 4, new QTableWidgetItem(current->salaryRange));
        ui->jobsTable->setItem(row, 5, new QTableWidgetItem(current->deadline));
        ui->jobsTable->setItem(row, 6, new QTableWidgetItem(current->jobType));
        ui->jobsTable->setItem(row, 7, new QTableWidgetItem(current->workMode));
        ui->jobsTable->setItem(row, 8, new QTableWidgetItem(current->industry));
        ui->jobsTable->setItem(row, 9, new QTableWidgetItem(current->skillsRequired));
        ui->jobsTable->setItem(row, 10, new QTableWidgetItem(current->additionalDetails));
        ui->jobsTable->setItem(row, 11, new QTableWidgetItem("View Details"));
    }
}

void DashboardSeeker::loadJobsTable()
{
    QSqlDatabase db = DBManager::getInstance().getDatabase();
    if (!db.isOpen()) return;

    QSqlQuery query(db);
    if (!query.exec("SELECT j.job_id, j.title, e.company_name, j.location, j.salary_range, j.deadline, "
                    "j.job_type, j.work_mode, j.industry, j.skills_required, j.additional_details "
                    "FROM Jobs j JOIN Employers e ON j.employer_id = e.employer_id WHERE j.is_active = TRUE")) return;

    while (jobHead) {
        delete jobHead;
        jobHead = jobHead->next;
    }
    jobHead = nullptr;

    while (query.next()) {
        addToLinkedList(query.value("job_id").toInt(), query.value("title").toString(), query.value("company_name").toString(),
                        query.value("location").toString(), query.value("salary_range").toString(), query.value("deadline").toString(),
                        query.value("job_type").toString(), query.value("work_mode").toString(), query.value("industry").toString(),
                        query.value("skills_required").toString(), query.value("additional_details").toString());
    }
    displayLinkedList();
}

void DashboardSeeker::loadProfile()
{
    QSqlDatabase db = DBManager::getInstance().getDatabase();
    if (!db.isOpen() || seekerUserId <= 0) return;

    QSqlQuery query(db);
    query.prepare("SELECT u.first_name, u.last_name, js.location, js.phone, js.education, js.skills, js.work_experience, "
                  "js.resume, js.about FROM JobSeekers js JOIN Users u ON js.user_id = u.user_id WHERE js.seeker_id = :seeker_id");
    query.bindValue(":seeker_id", seekerUserId);
    if (!query.exec() || !query.next()) return;

    QString fullName = query.value("first_name").toString() + " " + query.value("last_name").toString();
    ui->fullNameLineEdit->setText(fullName);
    ui->locationLineEdit->setText(query.value("location").toString());
    ui->phoneLineEdit->setText(query.value("phone").toString());
    ui->educationTextEdit->setText(query.value("education").toString());
    ui->skillsTextEdit->setText(query.value("skills").toString());
    ui->workExperienceTextEdit->setText(query.value("work_experience").toString());
    ui->resumeLineEdit->setText(query.value("resume").toString());
    ui->aboutTextEdit->setText(query.value("about").toString());
    updateWelcomeLabel(fullName);
}

void DashboardSeeker::loadApplicationsTable()
{
    QSqlDatabase db = DBManager::getInstance().getDatabase();
    if (!db.isOpen()) return;

    QSqlQuery query(db);
    query.prepare("SELECT a.job_id, j.title, e.company_name, a.status FROM Applications a "
                  "JOIN Jobs j ON a.job_id = j.job_id JOIN Employers e ON j.employer_id = e.employer_id "
                  "WHERE a.seeker_id = :seeker_id");
    query.bindValue(":seeker_id", seekerUserId);
    if (!query.exec()) return;

    ui->applicationsTable->setRowCount(0);
    while (query.next()) {
        int row = ui->applicationsTable->rowCount();
        ui->applicationsTable->insertRow(row);
        ui->applicationsTable->setItem(row, 0, new QTableWidgetItem(query.value("job_id").toString()));
        ui->applicationsTable->setItem(row, 1, new QTableWidgetItem(query.value("title").toString()));
        ui->applicationsTable->setItem(row, 2, new QTableWidgetItem(query.value("company_name").toString()));
        ui->applicationsTable->setItem(row, 3, new QTableWidgetItem(query.value("status").toString()));
    }
}

void DashboardSeeker::updateWelcomeLabel(const QString& fullName)
{
    ui->titleLabel->setText(fullName.isEmpty() ? "Job Seeker Dashboard" : QString("Job Seeker Dashboard - Welcome %1").arg(fullName));
}

void DashboardSeeker::on_applyButton_clicked()
{
    int selectedRow = ui->jobsTable->currentRow();
    if (selectedRow < 0) {
        QMessageBox::warning(this, "Error", "Please select a job from the table.");
        return;
    }

    int jobId = ui->jobsTable->item(selectedRow, 0)->text().toInt();
    if (seekerUserId <= 0) {
        QMessageBox::critical(this, "Error", "Invalid seeker ID. Please log in again.");
        return;
    }

    QSqlDatabase db = DBManager::getInstance().getDatabase();
    if (!db.isOpen()) {
        QMessageBox::critical(this, "Database Error", "Connection failed.");
        return;
    }

    // Check if job ID is valid and active
    QSqlQuery jobCheckQuery(db);
    jobCheckQuery.prepare("SELECT COUNT(*) FROM Jobs WHERE job_id = :job_id AND is_active = TRUE");
    jobCheckQuery.bindValue(":job_id", jobId);
    if (!jobCheckQuery.exec() || !jobCheckQuery.next() || jobCheckQuery.value(0).toInt() == 0) {
        QMessageBox::critical(this, "Error", "Invalid or inactive job ID: " + QString::number(jobId));
        return;
    }

    // Check if seeker has already applied for this job
    QSqlQuery applicationCheckQuery(db);
    applicationCheckQuery.prepare("SELECT COUNT(*) FROM Applications WHERE job_id = :job_id AND seeker_id = :seeker_id");
    applicationCheckQuery.bindValue(":job_id", jobId);
    applicationCheckQuery.bindValue(":seeker_id", seekerUserId);
    if (!applicationCheckQuery.exec() || !applicationCheckQuery.next() || applicationCheckQuery.value(0).toInt() > 0) {
        QMessageBox::warning(this, "Error", "You have already applied for this job.");
        return;
    }

    QString coverLetter = QInputDialog::getMultiLineText(this, "Application Form", "Cover Letter (min 50 chars):",
                                                         "Dear Hiring Manager,\nI am excited to apply...\nSincerely,\n[Your Name]");
    if (coverLetter.length() < 50) {
        QMessageBox::warning(this, "Input Error", "Cover letter must be at least 50 characters.");
        return;
    }

    QString question1 = QInputDialog::getText(this, "Application Form", "Why do you want to work here? (min 20 chars)");
    if (question1.length() < 20) {
        QMessageBox::warning(this, "Input Error", "Response must be at least 20 characters.");
        return;
    }

    QString question2 = QInputDialog::getText(this, "Application Form", "What experience do you have? (min 20 chars)");
    if (question2.length() < 20) {
        QMessageBox::warning(this, "Input Error", "Response must be at least 20 characters.");
        return;
    }

    QString applicationDetails = QString("Cover Letter:\n%1\n\nWhy work here?\n%2\n\nExperience:\n%3")
                                     .arg(coverLetter, question1, question2);

    QString resumePath = QFileDialog::getOpenFileName(this, "Upload Resume", "", "Files (*.pdf *.doc *.docx)");
    if (resumePath.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please upload a resume.");
        return;
    }
    QFile file(resumePath);
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray resumeData = file.readAll();
        applicationDetails += QString("\n\nResume: %1 (Attached)").arg(QFileInfo(resumePath).fileName());
        file.close();
    } else {
        QMessageBox::warning(this, "File Error", "Could not read resume.");
        return;
    }

    QSqlQuery query(db);
    query.prepare("INSERT INTO Applications (job_id, seeker_id, status, application_details, applied_at, resume_data) "
                  "VALUES (:job_id, :seeker_id, :status, :application_details, :applied_at, :resume_data)");
    query.bindValue(":job_id", jobId);
    query.bindValue(":seeker_id", seekerUserId);
    query.bindValue(":status", "pending");
    query.bindValue(":application_details", applicationDetails);
    query.bindValue(":applied_at", QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
    query.bindValue(":resume_data", resumePath);
    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", "Failed to apply: " + query.lastError().text());
        return;
    }

    QSqlQuery employerQuery(db);
    employerQuery.prepare("SELECT e.user_id, j.title FROM Jobs j JOIN Employers e ON j.employer_id = e.employer_id WHERE j.job_id = :job_id");
    employerQuery.bindValue(":job_id", jobId);
    if (!employerQuery.exec() || !employerQuery.next()) {
        QMessageBox::warning(this, "Notification Error", "Could not find employer.");
        return;
    }

    int employerUserId = employerQuery.value("user_id").toInt();
    QString jobTitle = employerQuery.value("title").toString();

    QSqlQuery notifyQuery(db);
    notifyQuery.prepare("INSERT INTO Notifications (user_id, message, created_at, is_read) "
                        "VALUES (:user_id, :message, :created_at, :is_read)");
    notifyQuery.bindValue(":user_id", employerUserId);
    notifyQuery.bindValue(":message", "New application for: " + jobTitle);
    notifyQuery.bindValue(":created_at", QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
    notifyQuery.bindValue(":is_read", false);
    if (notifyQuery.exec()) {
        QMessageBox::information(this, "Success", "Application submitted! Employer notified.");
    } else {
        QMessageBox::warning(this, "Notification Error", "Failed to notify employer.");
    }
    loadApplicationsTable();
}

void DashboardSeeker::on_updateProfileButton_clicked()
{
    QString fullName = ui->fullNameLineEdit->text().trimmed();
    QString location = ui->locationLineEdit->text().trimmed();
    QString phone = ui->phoneLineEdit->text().trimmed();
    QString education = ui->educationTextEdit->toPlainText().trimmed();
    QString skills = ui->skillsTextEdit->toPlainText().trimmed();
    QString workExperience = ui->workExperienceTextEdit->toPlainText().trimmed();
    QString resume = ui->resumeLineEdit->text().trimmed();
    QString about = ui->aboutTextEdit->toPlainText().trimmed();

    if (fullName.isEmpty() || location.isEmpty() || phone.isEmpty() || education.isEmpty() ||
        skills.isEmpty() || workExperience.isEmpty() || resume.isEmpty() || about.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "All fields are required.");
        return;
    }
    if (fullName.split(" ").count() < 2) {
        QMessageBox::warning(this, "Input Error", "Full name must include at least first and last name.");
        return;
    }
    if (phone.length() < 10) {
        QMessageBox::warning(this, "Input Error", "Phone must be at least 10 characters.");
        return;
    }
    if (education.length() < 10 || about.length() < 10) {
        QMessageBox::warning(this, "Input Error", "Education and About must be at least 10 characters.");
        return;
    }

    QSqlDatabase db = DBManager::getInstance().getDatabase();
    if (!db.isOpen()) {
        QMessageBox::critical(this, "Database Error", "Connection failed.");
        return;
    }

    QSqlQuery query(db);
    query.prepare("UPDATE JobSeekers SET location = :location, phone = :phone, education = :education, "
                  "skills = :skills, work_experience = :work_experience, resume = :resume, about = :about "
                  "WHERE seeker_id = :seeker_id");
    query.bindValue(":location", location);
    query.bindValue(":phone", phone);
    query.bindValue(":education", education);
    query.bindValue(":skills", skills);
    query.bindValue(":work_experience", workExperience);
    query.bindValue(":resume", resume);
    query.bindValue(":about", about);
    query.bindValue(":seeker_id", seekerUserId);
    if (query.exec()) {
        QStringList nameParts = fullName.split(" ", Qt::SkipEmptyParts);
        QSqlQuery userQuery(db);
        userQuery.prepare("UPDATE Users SET first_name = :first_name, last_name = :last_name "
                          "WHERE user_id = (SELECT user_id FROM JobSeekers WHERE seeker_id = :seeker_id)");
        userQuery.bindValue(":first_name", nameParts[0]);
        userQuery.bindValue(":last_name", nameParts.value(1, ""));
        userQuery.bindValue(":seeker_id", seekerUserId);
        if (userQuery.exec()) {
            QMessageBox::information(this, "Success", "Profile updated!");
        } else {
            QMessageBox::warning(this, "Update Error", "Failed to update name.");
        }
    } else {
        QMessageBox::critical(this, "Database Error", "Failed to update profile.");
    }
    loadProfile();
}

void DashboardSeeker::on_searchButton_clicked()
{
    QString searchTerm = ui->searchLineEdit->text().trimmed().toLower();
    if (searchTerm.isEmpty()) {
        displayLinkedList();
        return;
    }

    ui->jobsTable->setRowCount(0);
    for (JobNode* current = jobHead; current; current = current->next) {
        if (current->title.toLower().contains(searchTerm) || current->companyName.toLower().contains(searchTerm)) {
            int row = ui->jobsTable->rowCount();
            ui->jobsTable->insertRow(row);
            ui->jobsTable->setItem(row, 0, new QTableWidgetItem(QString::number(current->jobId)));
            ui->jobsTable->setItem(row, 1, new QTableWidgetItem(current->title));
            ui->jobsTable->setItem(row, 2, new QTableWidgetItem(current->companyName));
            ui->jobsTable->setItem(row, 3, new QTableWidgetItem(current->location));
            ui->jobsTable->setItem(row, 4, new QTableWidgetItem(current->salaryRange));
            ui->jobsTable->setItem(row, 5, new QTableWidgetItem(current->deadline));
            ui->jobsTable->setItem(row, 6, new QTableWidgetItem(current->jobType));
            ui->jobsTable->setItem(row, 7, new QTableWidgetItem(current->workMode));
            ui->jobsTable->setItem(row, 8, new QTableWidgetItem(current->industry));
            ui->jobsTable->setItem(row, 9, new QTableWidgetItem(current->skillsRequired));
            ui->jobsTable->setItem(row, 10, new QTableWidgetItem(current->additionalDetails));
            ui->jobsTable->setItem(row, 11, new QTableWidgetItem("View Details"));
        }
    }
}

void DashboardSeeker::on_sortComboBox_currentIndexChanged(int index)
{
    sortLinkedList(index == 0 || index == 2, index == 0 || index == 1);
    displayLinkedList();
}

void DashboardSeeker::on_applicationsTable_cellClicked(int row, int column)
{
    if (column == 3) {
        QString newStatus = QInputDialog::getText(this, "Update Status", "New status:", QLineEdit::Normal,
                                                  ui->applicationsTable->item(row, 3)->text());
        if (!newStatus.isEmpty()) {
            QSqlDatabase db = DBManager::getInstance().getDatabase();
            if (db.isOpen()) {
                QSqlQuery query(db);
                query.prepare("UPDATE Applications SET status = :status WHERE job_id = :job_id AND seeker_id = :seeker_id");
                query.bindValue(":status", newStatus);
                query.bindValue(":job_id", ui->applicationsTable->item(row, 0)->text());
                query.bindValue(":seeker_id", seekerUserId);
                if (query.exec()) {
                    ui->applicationsTable->setItem(row, 3, new QTableWidgetItem(newStatus));
                    QMessageBox::information(this, "Success", "Status updated.");
                } else {
                    QMessageBox::critical(this, "Error", "Failed to update status.");
                }
            }
        }
    }
}

void DashboardSeeker::on_jobsTable_cellClicked(int row, int column)
{
    if (column == 11) {
        int jobId = ui->jobsTable->item(row, 0)->text().toInt();
        JobNode* current = jobHead;
        while (current && current->jobId != jobId) current = current->next;
        if (current) {
            QString details = QString("Job ID: %1\nTitle: %2\nCompany: %3\nLocation: %4\nSalary: %5\nDeadline: %6\n"
                                      "Type: %7\nMode: %8\nIndustry: %9\nSkills: %10\nDetails: %11")
                                  .arg(current->jobId)
                                  .arg(current->title)
                                  .arg(current->companyName)
                                  .arg(current->location)
                                  .arg(current->salaryRange)
                                  .arg(current->deadline)
                                  .arg(current->jobType)
                                  .arg(current->workMode)
                                  .arg(current->industry)
                                  .arg(current->skillsRequired)
                                  .arg(current->additionalDetails);

            QSqlDatabase db = DBManager::getInstance().getDatabase();
            if (db.isOpen()) {
                QSqlQuery query(db);
                query.prepare("SELECT description FROM Jobs WHERE job_id = :job_id");
                query.bindValue(":job_id", jobId);
                if (query.exec() && query.next()) {
                    QString description = query.value("description").toString();
                    if (description.contains("[PNG File Uploaded:")) {
                        details += "\n\nEmployer Note: PNG file uploaded. Contact employer.";
                    } else if (description.contains("File Content:")) {
                        details += "\n\nEmployer File: " + description.section("File Content:\n", 1);
                    }
                }
            }
            QMessageBox::information(this, "Job Details", details);
        }
    }
}
