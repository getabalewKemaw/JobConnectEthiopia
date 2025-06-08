#ifndef DASHBOARD_SEEKER_H
#define DASHBOARD_SEEKER_H

#include <QDialog>
#include "core/dbmanager.h"
#include "core/job_node.h"

namespace Ui {
class DashboardSeeker;
}

class DashboardSeeker : public QDialog
{
    Q_OBJECT

public:
    explicit DashboardSeeker(QWidget *parent = nullptr);
    ~DashboardSeeker();
    void setSeekerUserId(int userId);
    void setSeekerDetails(const QString& skills, const QString& education, const QString& workExperience);

private slots:
    void on_applyButton_clicked();
    void on_updateProfileButton_clicked();
    void on_searchButton_clicked();
    void on_sortComboBox_currentIndexChanged(int index);
    void on_applicationsTable_cellClicked(int row, int column);
    void on_jobsTable_cellClicked(int row, int column);

private:
    Ui::DashboardSeeker *ui;
    DBManager *dbManager;
    int seekerUserId;
    JobNode* jobHead;
    QString seekerSkills;
    QString seekerEducation;
    QString seekerWorkExperience;

    void loadJobsTable();
    void loadProfile();
    void loadApplicationsTable();
    void initializeLinkedList();
    void addToLinkedList(int jobId, const QString& title, const QString& company, const QString& location,
                         const QString& salary, const QString& deadline, const QString& jobType,
                         const QString& workMode, const QString& industry, const QString& skillsRequired,
                         const QString& additionalDetails);
    void sortLinkedList(bool bySalary, bool ascending);
    void mergeSort(JobNode** headRef, bool bySalary, bool ascending);
    void splitList(JobNode* head, JobNode** left, JobNode** right);
    JobNode* merge(JobNode* left, JobNode* right, bool bySalary, bool ascending);
    void displayLinkedList();
    void updateWelcomeLabel(const QString& fullName); // Updated to take fullName argument
};

#endif // DASHBOARD_SEEKER_H
