/********************************************************************************
** Form generated from reading UI file 'dashboard_admin.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DASHBOARD_ADMIN_H
#define UI_DASHBOARD_ADMIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DashboardAdmin
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QSpacerItem *verticalSpacer_1;
    QLabel *statsLabel;
    QLabel *statsDisplayLabel;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *searchSortLayout;
    QLineEdit *searchLineEdit;
    QPushButton *searchButton;
    QComboBox *sortComboBox;
    QTabWidget *userTabs;
    QWidget *employersTab;
    QVBoxLayout *employersLayout;
    QTableWidget *employerTable;
    QHBoxLayout *employerActionLayout;
    QLineEdit *verifyUserIdLineEdit;
    QLineEdit *licenseNumberLineEdit;
    QPushButton *verifyButton;
    QLineEdit *blockUserIdLineEdit;
    QPushButton *blockButton;
    QWidget *jobSeekersTab;
    QVBoxLayout *jobSeekersLayout;
    QTableWidget *jobSeekerTable;
    QHBoxLayout *jobSeekerActionLayout;
    QLineEdit *blockJobSeekerIdLineEdit;
    QPushButton *blockJobSeekerButton;
    QSpacerItem *verticalSpacer_3;
    QPushButton *logoutButton;

    void setupUi(QDialog *DashboardAdmin)
    {
        if (DashboardAdmin->objectName().isEmpty())
            DashboardAdmin->setObjectName("DashboardAdmin");
        DashboardAdmin->resize(800, 600);
        DashboardAdmin->setStyleSheet(QString::fromUtf8("\n"
"    QDialog {\n"
"        background-color: #E6F0FA; /* Light blue gradient background */\n"
"        border: 1px solid #A3BFFA;\n"
"    }\n"
"    QLabel {\n"
"        font: 14px \"Arial\";\n"
"        color: #2E4053; /* Dark slate color for text */\n"
"    }\n"
"    QTableWidget {\n"
"        background-color: #FFFFFF;\n"
"        border: 1px solid #A3BFFA;\n"
"        border-radius: 5px;\n"
"        font: 14px \"Arial\";\n"
"    }\n"
"    QLineEdit {\n"
"        background-color: #FFFFFF;\n"
"        border: 1px solid #A3BFFA;\n"
"        border-radius: 5px;\n"
"        padding: 5px;\n"
"        font: 14px \"Arial\";\n"
"    }\n"
"    QPushButton {\n"
"        background-color: #4CAF50; /* Vibrant green for buttons */\n"
"        color: white;\n"
"        border-radius: 5px;\n"
"        padding: 8px;\n"
"        font: 14px \"Arial\";\n"
"    }\n"
"    QPushButton:hover {\n"
"        background-color: #45A049; /* Darker green on hover */\n"
"    }\n"
"    QPushButton#logoutButton {\n"
"        background"
                        "-color: #FF6B6B; /* Red for logout */\n"
"    }\n"
"    QPushButton#logoutButton:hover {\n"
"        background-color: #FF5252; /* Darker red on hover */\n"
"    }\n"
"    QComboBox {\n"
"        background-color: #FFFFFF;\n"
"        border: 1px solid #A3BFFA;\n"
"        border-radius: 5px;\n"
"        padding: 5px;\n"
"        font: 14px \"Arial\";\n"
"    }\n"
"   "));
        verticalLayoutWidget = new QWidget(DashboardAdmin);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(20, 20, 760, 560));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        titleLabel = new QLabel(verticalLayoutWidget);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setStyleSheet(QString::fromUtf8("\n"
"        font: bold 24px \"Arial\";\n"
"        color: #2D6A4F; /* Rich green for title */\n"
"        background-color: #D1E8E2; /* Soft green background */\n"
"        border-radius: 5px;\n"
"        padding: 10px;\n"
"       "));
        titleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        verticalSpacer_1 = new QSpacerItem(20, 10, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_1);

        statsLabel = new QLabel(verticalLayoutWidget);
        statsLabel->setObjectName("statsLabel");
        statsLabel->setStyleSheet(QString::fromUtf8("\n"
"        font: bold 18px \"Arial\";\n"
"        color: #2E4053;\n"
"        background-color: #D1E8E2;\n"
"        padding: 5px;\n"
"       "));

        verticalLayout->addWidget(statsLabel);

        statsDisplayLabel = new QLabel(verticalLayoutWidget);
        statsDisplayLabel->setObjectName("statsDisplayLabel");
        statsDisplayLabel->setStyleSheet(QString::fromUtf8("\n"
"        font: 14px \"Arial\";\n"
"        color: #2E4053;\n"
"        background-color: #FFFFFF;\n"
"        border-radius: 5px;\n"
"        padding: 5px;\n"
"       "));
        statsDisplayLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(statsDisplayLabel);

        verticalSpacer_2 = new QSpacerItem(20, 10, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        searchSortLayout = new QHBoxLayout();
        searchSortLayout->setObjectName("searchSortLayout");
        searchLineEdit = new QLineEdit(verticalLayoutWidget);
        searchLineEdit->setObjectName("searchLineEdit");

        searchSortLayout->addWidget(searchLineEdit);

        searchButton = new QPushButton(verticalLayoutWidget);
        searchButton->setObjectName("searchButton");

        searchSortLayout->addWidget(searchButton);

        sortComboBox = new QComboBox(verticalLayoutWidget);
        sortComboBox->addItem(QString());
        sortComboBox->addItem(QString());
        sortComboBox->addItem(QString());
        sortComboBox->addItem(QString());
        sortComboBox->setObjectName("sortComboBox");

        searchSortLayout->addWidget(sortComboBox);


        verticalLayout->addLayout(searchSortLayout);

        userTabs = new QTabWidget(verticalLayoutWidget);
        userTabs->setObjectName("userTabs");
        employersTab = new QWidget();
        employersTab->setObjectName("employersTab");
        employersLayout = new QVBoxLayout(employersTab);
        employersLayout->setObjectName("employersLayout");
        employerTable = new QTableWidget(employersTab);
        if (employerTable->columnCount() < 6)
            employerTable->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        employerTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        employerTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        employerTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        employerTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        employerTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        employerTable->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        employerTable->setObjectName("employerTable");
        employerTable->setColumnCount(6);

        employersLayout->addWidget(employerTable);

        employerActionLayout = new QHBoxLayout();
        employerActionLayout->setObjectName("employerActionLayout");
        verifyUserIdLineEdit = new QLineEdit(employersTab);
        verifyUserIdLineEdit->setObjectName("verifyUserIdLineEdit");

        employerActionLayout->addWidget(verifyUserIdLineEdit);

        licenseNumberLineEdit = new QLineEdit(employersTab);
        licenseNumberLineEdit->setObjectName("licenseNumberLineEdit");

        employerActionLayout->addWidget(licenseNumberLineEdit);

        verifyButton = new QPushButton(employersTab);
        verifyButton->setObjectName("verifyButton");

        employerActionLayout->addWidget(verifyButton);

        blockUserIdLineEdit = new QLineEdit(employersTab);
        blockUserIdLineEdit->setObjectName("blockUserIdLineEdit");

        employerActionLayout->addWidget(blockUserIdLineEdit);

        blockButton = new QPushButton(employersTab);
        blockButton->setObjectName("blockButton");

        employerActionLayout->addWidget(blockButton);


        employersLayout->addLayout(employerActionLayout);

        userTabs->addTab(employersTab, QString());
        jobSeekersTab = new QWidget();
        jobSeekersTab->setObjectName("jobSeekersTab");
        jobSeekersLayout = new QVBoxLayout(jobSeekersTab);
        jobSeekersLayout->setObjectName("jobSeekersLayout");
        jobSeekerTable = new QTableWidget(jobSeekersTab);
        if (jobSeekerTable->columnCount() < 6)
            jobSeekerTable->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        jobSeekerTable->setHorizontalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        jobSeekerTable->setHorizontalHeaderItem(1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        jobSeekerTable->setHorizontalHeaderItem(2, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        jobSeekerTable->setHorizontalHeaderItem(3, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        jobSeekerTable->setHorizontalHeaderItem(4, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        jobSeekerTable->setHorizontalHeaderItem(5, __qtablewidgetitem11);
        jobSeekerTable->setObjectName("jobSeekerTable");
        jobSeekerTable->setColumnCount(6);

        jobSeekersLayout->addWidget(jobSeekerTable);

        jobSeekerActionLayout = new QHBoxLayout();
        jobSeekerActionLayout->setObjectName("jobSeekerActionLayout");
        blockJobSeekerIdLineEdit = new QLineEdit(jobSeekersTab);
        blockJobSeekerIdLineEdit->setObjectName("blockJobSeekerIdLineEdit");

        jobSeekerActionLayout->addWidget(blockJobSeekerIdLineEdit);

        blockJobSeekerButton = new QPushButton(jobSeekersTab);
        blockJobSeekerButton->setObjectName("blockJobSeekerButton");

        jobSeekerActionLayout->addWidget(blockJobSeekerButton);


        jobSeekersLayout->addLayout(jobSeekerActionLayout);

        userTabs->addTab(jobSeekersTab, QString());

        verticalLayout->addWidget(userTabs);

        verticalSpacer_3 = new QSpacerItem(20, 10, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        logoutButton = new QPushButton(verticalLayoutWidget);
        logoutButton->setObjectName("logoutButton");

        verticalLayout->addWidget(logoutButton);


        retranslateUi(DashboardAdmin);
        QObject::connect(logoutButton, &QPushButton::clicked, DashboardAdmin, qOverload<>(&QDialog::reject));

        userTabs->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(DashboardAdmin);
    } // setupUi

    void retranslateUi(QDialog *DashboardAdmin)
    {
        DashboardAdmin->setWindowTitle(QCoreApplication::translate("DashboardAdmin", "Admin Dashboard - Job Matching System", nullptr));
        titleLabel->setText(QCoreApplication::translate("DashboardAdmin", "Admin Dashboard", nullptr));
        statsLabel->setText(QCoreApplication::translate("DashboardAdmin", "System Statistics", nullptr));
        statsDisplayLabel->setText(QCoreApplication::translate("DashboardAdmin", "Users: 0 | Jobs: 0 | Applications: 0", nullptr));
        searchLineEdit->setPlaceholderText(QCoreApplication::translate("DashboardAdmin", "Search by ID or Name", nullptr));
        searchButton->setText(QCoreApplication::translate("DashboardAdmin", "Search", nullptr));
        sortComboBox->setItemText(0, QCoreApplication::translate("DashboardAdmin", "Sort by ID (Asc)", nullptr));
        sortComboBox->setItemText(1, QCoreApplication::translate("DashboardAdmin", "Sort by ID (Desc)", nullptr));
        sortComboBox->setItemText(2, QCoreApplication::translate("DashboardAdmin", "Sort by Name (Asc)", nullptr));
        sortComboBox->setItemText(3, QCoreApplication::translate("DashboardAdmin", "Sort by Name (Desc)", nullptr));

        QTableWidgetItem *___qtablewidgetitem = employerTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("DashboardAdmin", "User ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = employerTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("DashboardAdmin", "Company Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = employerTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("DashboardAdmin", "License Number", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = employerTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("DashboardAdmin", "License Verified", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = employerTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("DashboardAdmin", "Blocked", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = employerTable->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("DashboardAdmin", "Action", nullptr));
        verifyUserIdLineEdit->setPlaceholderText(QCoreApplication::translate("DashboardAdmin", "Enter Employer ID to Verify", nullptr));
        licenseNumberLineEdit->setPlaceholderText(QCoreApplication::translate("DashboardAdmin", "Enter License Number (e.g., ADMIN123)", nullptr));
        verifyButton->setText(QCoreApplication::translate("DashboardAdmin", "Verify License", nullptr));
        blockUserIdLineEdit->setPlaceholderText(QCoreApplication::translate("DashboardAdmin", "Enter User ID to Block", nullptr));
        blockButton->setText(QCoreApplication::translate("DashboardAdmin", "Block User", nullptr));
        userTabs->setTabText(userTabs->indexOf(employersTab), QCoreApplication::translate("DashboardAdmin", "Employers", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = jobSeekerTable->horizontalHeaderItem(0);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("DashboardAdmin", "User ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = jobSeekerTable->horizontalHeaderItem(1);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("DashboardAdmin", "Full Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = jobSeekerTable->horizontalHeaderItem(2);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("DashboardAdmin", "Location", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = jobSeekerTable->horizontalHeaderItem(3);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("DashboardAdmin", "Phone", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = jobSeekerTable->horizontalHeaderItem(4);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("DashboardAdmin", "Blocked", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = jobSeekerTable->horizontalHeaderItem(5);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("DashboardAdmin", "Action", nullptr));
        blockJobSeekerIdLineEdit->setPlaceholderText(QCoreApplication::translate("DashboardAdmin", "Enter User ID to Block", nullptr));
        blockJobSeekerButton->setText(QCoreApplication::translate("DashboardAdmin", "Block User", nullptr));
        userTabs->setTabText(userTabs->indexOf(jobSeekersTab), QCoreApplication::translate("DashboardAdmin", "Job Seekers", nullptr));
        logoutButton->setText(QCoreApplication::translate("DashboardAdmin", "Logout", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DashboardAdmin: public Ui_DashboardAdmin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DASHBOARD_ADMIN_H
