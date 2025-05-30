#ifndef DASHBOARDEMPLOYER_H
#define DASHBOARDEMPLOYER_H

#include <QDialog>
#include <QTableWidget>
#include <QString>
#include "core/dbmanager.h"
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

private slots:
    void on_postJobButton_clicked();
    void on_shortlistButton_clicked();
    void on_searchApplicantButton_clicked();
    void on_sortApplicantComboBox_currentIndexChanged(int index);
    void on_applicantsTable_cellClicked(int row, int column);

private:
    Ui::DashboardEmployer *ui;
    DBManager* dbManager;
    int employerUserId;
    JobNode* jobHead; // Use the existing JobNode from job_node.h
    Applicant* applicantHead;

    void initializeStructures();
    void addJobNode(int jobId, const QString& title, const QString& description, int experienceRequired,
                    const QString& salaryRange, const QString& deadline);
    void addToApplicantStack(Applicant* applicant);
    void sortApplicantStack(bool ascending, bool byId);
    void displayApplicantStack(QTableWidget* table); // Ensure correct parameter type
    void loadApplicantsTable();
    void loadNotificationsTable();
};

#endif // DASHBOARDEMPLOYER_H
