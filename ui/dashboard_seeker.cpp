#include "ui/dashboard_seeker.h"
#include "ui_dashboard_seeker.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QInputDialog>
#include <QDate>
#include <QRegularExpression>

DashboardSeeker::DashboardSeeker(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DashboardSeeker),
    dbManager(new DBManager()),
    seekerUserId(0),
    jobHead(nullptr)
{
    ui->setupUi(this);


    setStyleSheet(
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
        "QPushButton#logoutButton { background-color: #f44336; }"
        "QPushButton#logoutButton:hover { background-color: #da190b; }"
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
        "QLabel#titleLabel { font: bold 24px 'Arial'; color: #2D6A4F; background-color: #D1E8E2; border-radius: 5px; padding: 10px; }"
        "QLabel#postJobLabel { font: bold 18px 'Arial'; color: #2E4053; background-color: #D1E8E2; padding: 5px; }"
        "QLabel#applicantsLabel { font: bold 18px 'Arial'; color: #2E4053; background-color: #D1E8E2; padding: 5px; }"
        "QLabel#notificationsLabel { font: bold 18px 'Arial'; color: #2E4053; background-color: #D1E8E2; padding: 5px; }"
        "QLabel#licenseStatusLabel { font: bold 14px 'Arial'; color: #2D6A4F; background-color: #D1E8E2; padding: 5px; border-radius: 5px; }"
        );
    // ui->verticalLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
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
}

DashboardSeeker::~DashboardSeeker()
{
    while (jobHead) {
        JobNode* temp = jobHead;
        jobHead = jobHead->next;
        delete temp;
    }
    delete dbManager;
    delete ui;
}

void DashboardSeeker::setSeekerUserId(int userId)
{
    seekerUserId = userId;
    loadProfile();
    loadJobsTable();
    loadApplicationsTable();
}

void DashboardSeeker::initializeLinkedList()
{
    jobHead = nullptr;
}

void DashboardSeeker::addToLinkedList(int jobId, const QString& title, const QString& company, const QString& location,
                                      const QString& salary, const QString& deadline)
{
    JobNode* newNode = new JobNode(jobId, title, company, location, salary, deadline);
    newNode->next = jobHead;
    jobHead = newNode;
}

void DashboardSeeker::sortLinkedList(bool bySalary, bool ascending)
{
    if (!jobHead || !jobHead->next) return;

    JobNode* sorted = nullptr;
    while (jobHead) {
        JobNode* current = jobHead;
        jobHead = jobHead->next;
        JobNode** link = &sorted;

        while (*link) {
            bool condition;
            if (bySalary) {
                QStringList currentRange = current->salaryRange.split("-");
                QStringList linkRange = (*link)->salaryRange.split("-");
                if (currentRange.size() != 2 || linkRange.size() != 2) {
                    condition = false;
                } else {
                    int currentLow = currentRange[0].remove("$").remove(",").toInt();
                    int linkLow = linkRange[0].remove("$").remove(",").toInt();
                    condition = ascending ? (currentLow < linkLow) : (currentLow > linkLow);
                }
            } else {
                QDate currentDeadline = QDate::fromString(current->deadline, "yyyy-MM-dd");
                QDate linkDeadline = QDate::fromString((*link)->deadline, "yyyy-MM-dd");
                condition = ascending ? (currentDeadline < linkDeadline) : (currentDeadline > linkDeadline);
            }
            if (condition) break;
            link = &(*link)->next;
        }
        current->next = *link;
        *link = current;
    }
    jobHead = sorted;
}

void DashboardSeeker::displayLinkedList()
{
    ui->jobsTable->setRowCount(0);
    JobNode* current = jobHead;
    while (current) {
        int row = ui->jobsTable->rowCount();
        ui->jobsTable->insertRow(row);
        ui->jobsTable->setItem(row, 0, new QTableWidgetItem(QString::number(current->jobId)));
        ui->jobsTable->setItem(row, 1, new QTableWidgetItem(current->title));
        ui->jobsTable->setItem(row, 2, new QTableWidgetItem(current->companyName));
        ui->jobsTable->setItem(row, 3, new QTableWidgetItem(current->location));
        ui->jobsTable->setItem(row, 4, new QTableWidgetItem(current->salaryRange));
        ui->jobsTable->setItem(row, 5, new QTableWidgetItem(current->deadline));
        ui->jobsTable->setItem(row, 6, new QTableWidgetItem("Apply"));
        current = current->next;
    }
}

void DashboardSeeker::loadJobsTable()
{
    QSqlDatabase db = dbManager->getDatabase();
    if (!db.isOpen()) {
        QMessageBox::critical(this, "Database Error", "Database connection failed: " + db.lastError().text());
        return;
    }

    QSqlQuery query(db);
    query.prepare("SELECT j.job_id, j.title, e.company_name, j.location, j.salary_range, j.deadline "
                  "FROM Jobs j "
                  "JOIN Employers e ON j.employer_id = e.employer_id "
                  "WHERE j.is_active = TRUE");

    while (jobHead) {
        JobNode* temp = jobHead;
        jobHead = jobHead->next;
        delete temp;
    }
    jobHead = nullptr;

    if (query.exec()) {
        while (query.next()) {
            int jobId = query.value("job_id").toInt();
            QString title = query.value("title").toString();
            QString companyName = query.value("company_name").toString();
            QString location = query.value("location").toString();
            QString salaryRange = query.value("salary_range").toString();
            QString deadline = query.value("deadline").toString();
            addToLinkedList(jobId, title, companyName, location, salaryRange, deadline);
        }
        displayLinkedList();
    } else {
        QMessageBox::critical(this, "Database Error", "Failed to load jobs: " + query.lastError().text());
    }
}

void DashboardSeeker::loadProfile()
{
    QSqlDatabase db = dbManager->getDatabase();
    if (!db.isOpen()) {
        QMessageBox::critical(this, "Database Error", "Database connection failed: " + db.lastError().text());
        return;
    }

    if (seekerUserId <= 0) {
        QMessageBox::warning(this, "Profile Error", "Invalid seeker ID. Please log in again.");
        return;
    }

    QSqlQuery query(db);
    query.prepare("SELECT full_name, location, phone, education, skills, work_experience "
                  "FROM JobSeekers WHERE seeker_id = :seeker_id");
    query.bindValue(":seeker_id", seekerUserId);

    if (query.exec() && query.next()) {
        ui->fullNameLineEdit->setText(query.value("full_name").toString());
        ui->locationLineEdit->setText(query.value("location").toString());
        ui->phoneLineEdit->setText(query.value("phone").toString());
        ui->educationTextEdit->setText(query.value("education").toString());
        ui->skillsTextEdit->setText(query.value("skills").toString());
        ui->workExperienceTextEdit->setText(query.value("work_experience").toString());
    } else {
        QMessageBox::warning(this, "Profile Error", "Failed to load profile data: " + query.lastError().text());
        // Set placeholders or default values if data isn't available
        ui->fullNameLineEdit->setPlaceholderText("Enter Full Name (e.g., John Doe)");
        ui->locationLineEdit->setPlaceholderText("Enter Location (e.g., Nairobi, Kenya)");
        ui->phoneLineEdit->setPlaceholderText("Enter Phone Number (e.g., +254 712 345 678)");
        ui->educationTextEdit->setPlaceholderText("Enter Education (e.g., B.Sc. Computer Science, University of Nairobi, 2020)");
        ui->skillsTextEdit->setPlaceholderText("Enter Skills (e.g., Python, SQL, Communication)");
        ui->workExperienceTextEdit->setPlaceholderText("Enter Work Experience (e.g., Software Developer at XYZ Corp, 2021-2023)");
    }
}

void DashboardSeeker::loadApplicationsTable()
{
    QSqlDatabase db = dbManager->getDatabase();
    if (!db.isOpen()) {
        QMessageBox::critical(this, "Database Error", "Database connection failed: " + db.lastError().text());
        return;
    }

    QSqlQuery query(db);
    query.prepare("SELECT a.job_id, j.title, e.company_name, a.status "
                  "FROM Applications a "
                  "JOIN Jobs j ON a.job_id = j.job_id "
                  "JOIN Employers e ON j.employer_id = e.employer_id "
                  "WHERE a.seeker_id = :seeker_id");
    query.bindValue(":seeker_id", seekerUserId);
    ui->applicationsTable->setRowCount(0);

    if (query.exec()) {
        while (query.next()) {
            int row = ui->applicationsTable->rowCount();
            ui->applicationsTable->insertRow(row);
            ui->applicationsTable->setItem(row, 0, new QTableWidgetItem(query.value("job_id").toString()));
            ui->applicationsTable->setItem(row, 1, new QTableWidgetItem(query.value("title").toString()));
            ui->applicationsTable->setItem(row, 2, new QTableWidgetItem(query.value("company_name").toString()));
            ui->applicationsTable->setItem(row, 3, new QTableWidgetItem(query.value("status").toString()));
        }
    } else {
        QMessageBox::critical(this, "Database Error", "Failed to load applications: " + query.lastError().text());
    }
}

void DashboardSeeker::on_applyButton_clicked()
{
    int selectedRow = ui->jobsTable->currentRow();
    if (selectedRow < 0) {
        QMessageBox::warning(this, "Error", "Please select a job to apply for.");
        return;
    }

    int jobId = ui->jobsTable->item(selectedRow, 0)->text().toInt();

    if (seekerUserId <= 0) {
        QMessageBox::critical(this, "Error", "Invalid seeker ID: " + QString::number(seekerUserId) + ". Please log in again.");
        return;
    }

    QSqlDatabase db = dbManager->getDatabase();
    if (!db.isOpen()) {
        QMessageBox::critical(this, "Database Error", "Database connection failed: " + db.lastError().text());
        return;
    }

    // Verify jobId exists in Jobs table
    QSqlQuery jobCheckQuery(db);
    jobCheckQuery.prepare("SELECT COUNT(*) FROM Jobs WHERE job_id = :job_id");
    jobCheckQuery.bindValue(":job_id", jobId);
    if (!jobCheckQuery.exec() || !jobCheckQuery.next() || jobCheckQuery.value(0).toInt() == 0) {
        QMessageBox::critical(this, "Error", "Invalid job ID: " + QString::number(jobId));
        return;
    }

    // Check for duplicate application
    QSqlQuery checkQuery(db);
    checkQuery.prepare("SELECT COUNT(*) FROM Applications WHERE job_id = :job_id AND seeker_id = :seeker_id");
    checkQuery.bindValue(":job_id", jobId);
    checkQuery.bindValue(":seeker_id", seekerUserId);
    if (checkQuery.exec() && checkQuery.next() && checkQuery.value(0).toInt() > 0) {
        QMessageBox::warning(this, "Duplicate Application", "You have already applied for this job.");
        return;
    }

    // Detailed application form with validation
    QString coverLetter = QInputDialog::getMultiLineText(this, tr("Application Form"),
                                                         tr("Cover Letter (min 50 chars):"),
                                                         "Dear Hiring Manager,\n\nI am excited to apply for this position...\n\nSincerely,\n[Your Name]");
    if (coverLetter.length() < 50) {
        QMessageBox::warning(this, "Input Error", "Cover letter must be at least 50 characters.");
        return;
    }

    QString question1 = QInputDialog::getText(this, tr("Application Form"),
                                              tr("Why do you want to work here? (min 20 chars)"));
    if (question1.length() < 20) {
        QMessageBox::warning(this, "Input Error", "Response must be at least 20 characters.");
        return;
    }

    QString question2 = QInputDialog::getText(this, tr("Application Form"),
                                              tr("What relevant experience do you have? (min 20 chars)"));
    if (question2.length() < 20) {
        QMessageBox::warning(this, "Input Error", "Response must be at least 20 characters.");
        return;
    }

    QString applicationDetails = QString("Cover Letter:\n%1\n\nWhy do you want to work here?\n%2\n\nRelevant Experience:\n%3")
                                     .arg(coverLetter).arg(question1).arg(question2);

    // Insert application into database
    QSqlQuery query(db);
    query.prepare("INSERT INTO Applications (job_id, seeker_id, status, application_details, applied_at) "
                  "VALUES (:job_id, :seeker_id, :status, :application_details, :applied_at)");
    query.bindValue(":job_id", jobId);
    query.bindValue(":seeker_id", seekerUserId);
    query.bindValue(":status", "pending");
    query.bindValue(":application_details", applicationDetails);
    query.bindValue(":applied_at", QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));

    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", "Failed to apply: " + query.lastError().text() +
                                                          "\nQuery: " + query.lastQuery());
        return;
    }

    // Verify the application was stored
    QSqlQuery verifyQuery(db);
    verifyQuery.prepare("SELECT application_id FROM Applications WHERE job_id = :job_id AND seeker_id = :seeker_id AND application_details = :details");
    verifyQuery.bindValue(":job_id", jobId);
    verifyQuery.bindValue(":seeker_id", seekerUserId);
    verifyQuery.bindValue(":details", applicationDetails);
    if (!verifyQuery.exec() || !verifyQuery.next()) {
        QMessageBox::critical(this, "Storage Error", "Application was not stored in the database.");
        return;
    }

    // Fetch the employer associated with the job and send a notification
    QSqlQuery employerQuery(db);
    employerQuery.prepare("SELECT j.employer_id, e.user_id, j.title "
                          "FROM Jobs j "
                          "JOIN Employers e ON j.employer_id = e.employer_id "
                          "WHERE j.job_id = :job_id");
    employerQuery.bindValue(":job_id", jobId);
    if (!employerQuery.exec() || !employerQuery.next()) {
        QMessageBox::warning(this, "Notification Error", "Could not find employer for this job: " + employerQuery.lastError().text());
        return;
    }

    int employerUserId = employerQuery.value("user_id").toInt();
    QString jobTitle = employerQuery.value("title").toString();

    QSqlQuery notifyQuery(db);
    notifyQuery.prepare("INSERT INTO Notifications (user_id, message, created_at, is_read) "
                        "VALUES (:user_id, :message, :created_at, :is_read)");
    notifyQuery.bindValue(":user_id", employerUserId);
    notifyQuery.bindValue(":message", "A new application has been submitted for your job posting: " + jobTitle);
    notifyQuery.bindValue(":created_at", QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));
    notifyQuery.bindValue(":is_read", false);

    if (!notifyQuery.exec()) {
        QMessageBox::warning(this, "Notification Error", "Failed to send notification to employer: " + notifyQuery.lastError().text());
    }

    QMessageBox::information(this, "Success", "Application submitted successfully! Employer has been notified.");
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

    QRegularExpression phoneRegex("^\\+\\d{3}\\s\\d{3}\\s\\d{3}\\s\\d{3}$");
    if (fullName.isEmpty() || location.isEmpty() || !phoneRegex.match(phone).hasMatch() || education.isEmpty() ||
        skills.isEmpty() || workExperience.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "All fields are required. Phone must be in format +XXX XXX XXX XXX.");
        return;
    }

    QSqlDatabase db = dbManager->getDatabase();
    if (!db.isOpen()) {
        QMessageBox::critical(this, "Database Error", "Database connection failed: " + db.lastError().text());
        return;
    }

    QSqlQuery query(db);
    query.prepare("UPDATE JobSeekers SET full_name = :full_name, location = :location, phone = :phone, "
                  "education = :education, skills = :skills, work_experience = :work_experience "
                  "WHERE seeker_id = :seeker_id");
    query.bindValue(":full_name", fullName);
    query.bindValue(":location", location);
    query.bindValue(":phone", phone);
    query.bindValue(":education", education);
    query.bindValue(":skills", skills);
    query.bindValue(":work_experience", workExperience);
    query.bindValue(":seeker_id", seekerUserId);

    if (!query.exec()) {
        QMessageBox::critical(this, "Database Error", "Failed to update profile: " + query.lastError().text());
        return;
    }

    QMessageBox::information(this, "Success", "Profile updated successfully!");
}

void DashboardSeeker::on_searchButton_clicked()
{
    QString searchTerm = ui->searchLineEdit->text().trimmed().toLower();
    if (searchTerm.isEmpty()) {
        displayLinkedList();
        return;
    }

    ui->jobsTable->setRowCount(0);
    JobNode* current = jobHead;
    while (current) {
        if (current->title.toLower().contains(searchTerm) || current->companyName.toLower().contains(searchTerm)) {
            int row = ui->jobsTable->rowCount();
            ui->jobsTable->insertRow(row);
            ui->jobsTable->setItem(row, 0, new QTableWidgetItem(QString::number(current->jobId)));
            ui->jobsTable->setItem(row, 1, new QTableWidgetItem(current->title));
            ui->jobsTable->setItem(row, 2, new QTableWidgetItem(current->companyName));
            ui->jobsTable->setItem(row, 3, new QTableWidgetItem(current->location));
            ui->jobsTable->setItem(row, 4, new QTableWidgetItem(current->salaryRange));
            ui->jobsTable->setItem(row, 5, new QTableWidgetItem(current->deadline));
            ui->jobsTable->setItem(row, 6, new QTableWidgetItem("Apply"));
        }
        current = current->next;
    }
}

void DashboardSeeker::on_sortComboBox_currentIndexChanged(int index)
{
    bool bySalary = (index == 0 || index == 1);
    bool ascending = (index == 0 || index == 2);
    sortLinkedList(bySalary, ascending);
    displayLinkedList();
}

void DashboardSeeker::on_applicationsTable_cellClicked(int row, int column)
{
    if (column == 0) {
        int jobId = ui->applicationsTable->item(row, 0)->text().toInt();
        QSqlDatabase db = dbManager->getDatabase();
        if (!db.isOpen()) {
            QMessageBox::critical(this, "Database Error", "Database connection failed: " + db.lastError().text());
            return;
        }

        QSqlQuery query(db);
        query.prepare("SELECT application_details FROM Applications WHERE job_id = :job_id AND seeker_id = :seeker_id");
        query.bindValue(":job_id", jobId);
        query.bindValue(":seeker_id", seekerUserId);
        if (query.exec() && query.next()) {
            QString details = query.value("application_details").toString();
            QMessageBox::information(this, "Application Details", details);
        } else {
            QMessageBox::warning(this, "Error", "Could not load application details: " + query.lastError().text());
        }
    }
}
