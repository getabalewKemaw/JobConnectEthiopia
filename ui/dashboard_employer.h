#ifndef DASHBOARDEMPLOYER_H
#define DASHBOARDEMPLOYER_H

#include <QDialog>
#include <QTableWidget>
#include <QString>
#include "core/dbmanager.h" // For DBManager singleton
#include "core/job_node.h" // Include JobNode definition from here

namespace Ui {
class DashboardEmployer;
}

struct Applicant {
    int applicationId;
    int jobId;
    int seekerId;
    QString fullName;
    QString status;
    QString applicationDetails;
    Applicant* next;
};

class DashboardEmployer : public QDialog
{
    Q_OBJECT

public:
    explicit DashboardEmployer(QWidget *parent = nullptr);
    ~DashboardEmployer();
    void setEmployerUserId(int userId);
    void setLoggedInUser(const QString& fullName);

private slots:
    void on_postJobButton_clicked();
    void on_shortlistButton_clicked();
    void on_searchApplicantButton_clicked();
    void on_sortApplicantComboBox_currentIndexChanged(int index);
    void on_applicantsTable_cellClicked(int row, int column);
    void on_searchApplicantLineEdit_textChanged(const QString& text); // For search suggestions

private:
    Ui::DashboardEmployer *ui;
    // Removed dbManager pointer, use DBManager::getInstance() instead
    int employerUserId;
    JobNode* jobHead; // Use the existing JobNode from job_node.h
    Applicant* applicantHead;
    QString loggedInUser;

    void initializeStructures();
    void addJobNode(int jobId, const QString& title, const QString& description, int experienceRequired,
                    const QString& salaryRange, const QString& deadline);
    void addToApplicantStack(Applicant* applicant);
    void sortApplicantStack(bool ascending, bool byId);
    void displayApplicantStack(QTableWidget* table); // Ensure correct parameter type
    void loadApplicantsTable();
    void loadNotificationsTable();
    void updateWelcomeLabel();
    void mergeSort(Applicant** headRef, bool ascending, bool byId);
    void splitList(Applicant* head, Applicant** left, Applicant** right);
    Applicant* merge(Applicant* left, Applicant* right, bool ascending, bool byId);
};

#endif // DASHBOARDEMPLOYER_H
