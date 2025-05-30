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

private slots:
    void on_applyButton_clicked();
    void on_updateProfileButton_clicked();
    void on_searchButton_clicked();
    void on_sortComboBox_currentIndexChanged(int index);
    void on_applicationsTable_cellClicked(int row, int column); // Added missing slot

private:
    Ui::DashboardSeeker *ui;
    DBManager *dbManager;
    int seekerUserId;
    JobNode* jobHead;

    void loadJobsTable();
    void loadProfile();
    void loadApplicationsTable();
    void initializeLinkedList();
    void addToLinkedList(int jobId, const QString& title, const QString& company, const QString& location, const QString& salary, const QString& deadline);
    void sortLinkedList(bool bySalary, bool ascending);
    void displayLinkedList();
};

#endif // DASHBOARD_SEEKER_H
