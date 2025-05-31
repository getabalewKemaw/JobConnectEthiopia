#ifndef DASHBOARD_ADMIN_H
#define DASHBOARD_ADMIN_H

#include <QDialog>
#include <QTableWidget>
#include "core/dbmanager.h"

namespace Ui {
class DashboardAdmin;
}

class DashboardAdmin : public QDialog
{
    Q_OBJECT

public:
    explicit DashboardAdmin(QWidget *parent = nullptr);
    ~DashboardAdmin();

    struct UserNode {
        int userId;
        QString name;
        bool isEmployer;
        UserNode* next;
    };

private slots:
    void loadSystemStats();
    void loadEmployerTable();
    void loadJobSeekerTable();
    void on_verifyButton_clicked();
    void on_blockButton_clicked();
    void on_blockJobSeekerButton_clicked();
    void on_searchButton_clicked();
    void on_sortComboBox_currentIndexChanged(int index);

private:
    Ui::DashboardAdmin *ui;
    DBManager *dbManager;
    UserNode* employerHead;
    UserNode* jobSeekerHead;
    void initializeLinkedLists();
    void addToLinkedList(UserNode*& head, int userId, const QString& name, bool isEmployer);
    void mergeSort(UserNode** headRef, bool ascending, bool byId); // Added for Merge Sort
    void splitList(UserNode* head, UserNode** left, UserNode** right); // Added for Merge Sort
    UserNode* merge(UserNode* left, UserNode* right, bool ascending, bool byId); // Added for Merge Sort
    void displayLinkedList(UserNode* head, QTableWidget* table);
};

#endif // DASHBOARD_ADMIN_H
