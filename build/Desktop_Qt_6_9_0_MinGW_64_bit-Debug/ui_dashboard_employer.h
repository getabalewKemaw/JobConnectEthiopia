/********************************************************************************
** Form generated from reading UI file 'dashboard_employer.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DASHBOARD_EMPLOYER_H
#define UI_DASHBOARD_EMPLOYER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DashboardEmployer
{
public:
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QLabel *licenseStatusLabel;
    QSpacerItem *verticalSpacer_1;
    QLabel *postJobLabel;
    QFormLayout *postJobForm;
    QLabel *jobTitleLabel;
    QLineEdit *jobTitleLineEdit;
    QLabel *descriptionLabel;
    QTextEdit *descriptionTextEdit;
    QLabel *experienceLabel;
    QSpinBox *experienceSpinBox;
    QLabel *salaryLabel;
    QLineEdit *salaryLineEdit;
    QLabel *deadlineLabel;
    QLineEdit *deadlineLineEdit;
    QLabel *locationLabel;
    QLineEdit *locationLineEdit;
    QLabel *jobTypeLabel;
    QComboBox *jobTypeComboBox;
    QLabel *workModeLabel;
    QComboBox *workModeComboBox;
    QLabel *industryLabel;
    QLineEdit *industryLineEdit;
    QLabel *skillsLabel;
    QTextEdit *skillsTextEdit;
    QPushButton *postJobButton;
    QSpacerItem *verticalSpacer_2;
    QLabel *applicantsLabel;
    QHBoxLayout *applicantControls;
    QLineEdit *searchApplicantLineEdit;
    QPushButton *searchApplicantButton;
    QComboBox *sortApplicantComboBox;
    QTableWidget *applicantsTable;
    QHBoxLayout *shortlistLayout;
    QLineEdit *shortlistSeekerIdLineEdit;
    QPushButton *shortlistButton;
    QSpacerItem *verticalSpacer_3;
    QLabel *notificationsLabel;
    QTableWidget *notificationsTable;
    QSpacerItem *verticalSpacer_4;
    QPushButton *logoutButton;

    void setupUi(QDialog *DashboardEmployer)
    {
        if (DashboardEmployer->objectName().isEmpty())
            DashboardEmployer->setObjectName("DashboardEmployer");
        DashboardEmployer->resize(800, 800);
        DashboardEmployer->setStyleSheet(QString::fromUtf8("\n"
"    QDialog { background-color: #f0f8ff; border: 1px solid #A3BFFA; font-family: Arial, sans-serif; }\n"
"    QLabel { font: 14px \"Arial\"; color: #2e2e2e; font-weight: bold; padding: 5px; }\n"
"    QTableWidget { background-color: #FFFFFF; border: 1px solid #A3BFFA; border-radius: 5px; font: 14px \"Arial\"; alternate-background-color: #f5f5f5; gridline-color: #ddd; }\n"
"    QTableWidget::item { padding: 5px; }\n"
"    QHeaderView::section { background-color: #4CAF50; color: white; padding: 5px; border: 1px solid #A3BFFA; }\n"
"    QLineEdit, QTextEdit { background-color: #FFFFFF; border: 1px solid #A3BFFA; border-radius: 5px; padding: 5px; font: 14px \"Arial\"; placeholder-text-color: #888; }\n"
"    QLineEdit:focus, QTextEdit:focus { border: 2px solid #4C6EF5; }\n"
"    QPushButton { background-color: #4CAF50; color: white; border: none; border-radius: 5px; padding: 8px; font: 14px \"Arial\"; min-width: 80px; }\n"
"    QPushButton:hover { background-color: #45A049; }\n"
"    QPushButton#logoutButton {"
                        " background-color: #f44336; }\n"
"    QPushButton#logoutButton:hover { background-color: #da190b; }\n"
"    QComboBox { background-color: #FFFFFF; border: 1px solid #A3BFFA; border-radius: 5px; padding: 5px; font: 14px \"Arial\"; min-width: 100px; }\n"
"    QSpinBox { background-color: #FFFFFF; border: 1px solid #A3BFFA; border-radius: 5px; padding: 5px; font: 14px \"Arial\"; }\n"
"    QLabel#licenseStatusLabel { font: bold 14px \"Arial\"; color: #2D6A4F; background-color: #D1E8E2; padding: 5px; border-radius: 5px; }\n"
"   "));
        scrollArea = new QScrollArea(DashboardEmployer);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setGeometry(QRect(20, 20, 760, 760));
        scrollArea->setWidgetResizable(true);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setSpacing(10);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(10, 10, 10, 10);
        titleLabel = new QLabel(scrollAreaWidgetContents);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setStyleSheet(QString::fromUtf8("font: bold 24px \"Arial\"; color: #2D6A4F; background-color: #D1E8E2; border-radius: 5px; padding: 10px;"));
        titleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        licenseStatusLabel = new QLabel(scrollAreaWidgetContents);
        licenseStatusLabel->setObjectName("licenseStatusLabel");

        verticalLayout->addWidget(licenseStatusLabel);

        verticalSpacer_1 = new QSpacerItem(20, 15, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_1);

        postJobLabel = new QLabel(scrollAreaWidgetContents);
        postJobLabel->setObjectName("postJobLabel");
        postJobLabel->setStyleSheet(QString::fromUtf8("font: bold 18px \"Arial\"; color: #2E4053; background-color: #D1E8E2; padding: 5px;"));

        verticalLayout->addWidget(postJobLabel);

        postJobForm = new QFormLayout();
        postJobForm->setObjectName("postJobForm");
        postJobForm->setLabelAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        postJobForm->setFormAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);
        postJobForm->setHorizontalSpacing(10);
        postJobForm->setVerticalSpacing(10);
        jobTitleLabel = new QLabel(scrollAreaWidgetContents);
        jobTitleLabel->setObjectName("jobTitleLabel");

        postJobForm->setWidget(0, QFormLayout::ItemRole::LabelRole, jobTitleLabel);

        jobTitleLineEdit = new QLineEdit(scrollAreaWidgetContents);
        jobTitleLineEdit->setObjectName("jobTitleLineEdit");
        jobTitleLineEdit->setMinimumSize(QSize(300, 0));

        postJobForm->setWidget(0, QFormLayout::ItemRole::FieldRole, jobTitleLineEdit);

        descriptionLabel = new QLabel(scrollAreaWidgetContents);
        descriptionLabel->setObjectName("descriptionLabel");

        postJobForm->setWidget(1, QFormLayout::ItemRole::LabelRole, descriptionLabel);

        descriptionTextEdit = new QTextEdit(scrollAreaWidgetContents);
        descriptionTextEdit->setObjectName("descriptionTextEdit");
        descriptionTextEdit->setMinimumSize(QSize(300, 60));

        postJobForm->setWidget(1, QFormLayout::ItemRole::FieldRole, descriptionTextEdit);

        experienceLabel = new QLabel(scrollAreaWidgetContents);
        experienceLabel->setObjectName("experienceLabel");

        postJobForm->setWidget(2, QFormLayout::ItemRole::LabelRole, experienceLabel);

        experienceSpinBox = new QSpinBox(scrollAreaWidgetContents);
        experienceSpinBox->setObjectName("experienceSpinBox");
        experienceSpinBox->setMinimum(0);
        experienceSpinBox->setMaximum(50);
        experienceSpinBox->setValue(0);

        postJobForm->setWidget(2, QFormLayout::ItemRole::FieldRole, experienceSpinBox);

        salaryLabel = new QLabel(scrollAreaWidgetContents);
        salaryLabel->setObjectName("salaryLabel");

        postJobForm->setWidget(3, QFormLayout::ItemRole::LabelRole, salaryLabel);

        salaryLineEdit = new QLineEdit(scrollAreaWidgetContents);
        salaryLineEdit->setObjectName("salaryLineEdit");
        salaryLineEdit->setMinimumSize(QSize(300, 0));

        postJobForm->setWidget(3, QFormLayout::ItemRole::FieldRole, salaryLineEdit);

        deadlineLabel = new QLabel(scrollAreaWidgetContents);
        deadlineLabel->setObjectName("deadlineLabel");

        postJobForm->setWidget(4, QFormLayout::ItemRole::LabelRole, deadlineLabel);

        deadlineLineEdit = new QLineEdit(scrollAreaWidgetContents);
        deadlineLineEdit->setObjectName("deadlineLineEdit");
        deadlineLineEdit->setMinimumSize(QSize(300, 0));

        postJobForm->setWidget(4, QFormLayout::ItemRole::FieldRole, deadlineLineEdit);

        locationLabel = new QLabel(scrollAreaWidgetContents);
        locationLabel->setObjectName("locationLabel");

        postJobForm->setWidget(5, QFormLayout::ItemRole::LabelRole, locationLabel);

        locationLineEdit = new QLineEdit(scrollAreaWidgetContents);
        locationLineEdit->setObjectName("locationLineEdit");
        locationLineEdit->setMinimumSize(QSize(300, 0));

        postJobForm->setWidget(5, QFormLayout::ItemRole::FieldRole, locationLineEdit);

        jobTypeLabel = new QLabel(scrollAreaWidgetContents);
        jobTypeLabel->setObjectName("jobTypeLabel");

        postJobForm->setWidget(6, QFormLayout::ItemRole::LabelRole, jobTypeLabel);

        jobTypeComboBox = new QComboBox(scrollAreaWidgetContents);
        jobTypeComboBox->addItem(QString());
        jobTypeComboBox->addItem(QString());
        jobTypeComboBox->addItem(QString());
        jobTypeComboBox->setObjectName("jobTypeComboBox");

        postJobForm->setWidget(6, QFormLayout::ItemRole::FieldRole, jobTypeComboBox);

        workModeLabel = new QLabel(scrollAreaWidgetContents);
        workModeLabel->setObjectName("workModeLabel");

        postJobForm->setWidget(7, QFormLayout::ItemRole::LabelRole, workModeLabel);

        workModeComboBox = new QComboBox(scrollAreaWidgetContents);
        workModeComboBox->addItem(QString());
        workModeComboBox->addItem(QString());
        workModeComboBox->addItem(QString());
        workModeComboBox->setObjectName("workModeComboBox");

        postJobForm->setWidget(7, QFormLayout::ItemRole::FieldRole, workModeComboBox);

        industryLabel = new QLabel(scrollAreaWidgetContents);
        industryLabel->setObjectName("industryLabel");

        postJobForm->setWidget(8, QFormLayout::ItemRole::LabelRole, industryLabel);

        industryLineEdit = new QLineEdit(scrollAreaWidgetContents);
        industryLineEdit->setObjectName("industryLineEdit");
        industryLineEdit->setMinimumSize(QSize(300, 0));

        postJobForm->setWidget(8, QFormLayout::ItemRole::FieldRole, industryLineEdit);

        skillsLabel = new QLabel(scrollAreaWidgetContents);
        skillsLabel->setObjectName("skillsLabel");

        postJobForm->setWidget(9, QFormLayout::ItemRole::LabelRole, skillsLabel);

        skillsTextEdit = new QTextEdit(scrollAreaWidgetContents);
        skillsTextEdit->setObjectName("skillsTextEdit");
        skillsTextEdit->setMinimumSize(QSize(300, 60));

        postJobForm->setWidget(9, QFormLayout::ItemRole::FieldRole, skillsTextEdit);

        postJobButton = new QPushButton(scrollAreaWidgetContents);
        postJobButton->setObjectName("postJobButton");

        postJobForm->setWidget(10, QFormLayout::ItemRole::FieldRole, postJobButton);


        verticalLayout->addLayout(postJobForm);

        verticalSpacer_2 = new QSpacerItem(20, 15, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        applicantsLabel = new QLabel(scrollAreaWidgetContents);
        applicantsLabel->setObjectName("applicantsLabel");
        applicantsLabel->setStyleSheet(QString::fromUtf8("font: bold 18px \"Arial\"; color: #2E4053; background-color: #D1E8E2; padding: 5px;"));

        verticalLayout->addWidget(applicantsLabel);

        applicantControls = new QHBoxLayout();
        applicantControls->setSpacing(10);
        applicantControls->setObjectName("applicantControls");
        searchApplicantLineEdit = new QLineEdit(scrollAreaWidgetContents);
        searchApplicantLineEdit->setObjectName("searchApplicantLineEdit");
        searchApplicantLineEdit->setMinimumSize(QSize(200, 0));

        applicantControls->addWidget(searchApplicantLineEdit);

        searchApplicantButton = new QPushButton(scrollAreaWidgetContents);
        searchApplicantButton->setObjectName("searchApplicantButton");

        applicantControls->addWidget(searchApplicantButton);

        sortApplicantComboBox = new QComboBox(scrollAreaWidgetContents);
        sortApplicantComboBox->addItem(QString());
        sortApplicantComboBox->addItem(QString());
        sortApplicantComboBox->addItem(QString());
        sortApplicantComboBox->addItem(QString());
        sortApplicantComboBox->setObjectName("sortApplicantComboBox");

        applicantControls->addWidget(sortApplicantComboBox);


        verticalLayout->addLayout(applicantControls);

        applicantsTable = new QTableWidget(scrollAreaWidgetContents);
        if (applicantsTable->columnCount() < 5)
            applicantsTable->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        applicantsTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        applicantsTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        applicantsTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        applicantsTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        applicantsTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        applicantsTable->setObjectName("applicantsTable");
        applicantsTable->setMinimumSize(QSize(0, 100));
        applicantsTable->setColumnCount(5);

        verticalLayout->addWidget(applicantsTable);

        shortlistLayout = new QHBoxLayout();
        shortlistLayout->setSpacing(10);
        shortlistLayout->setObjectName("shortlistLayout");
        shortlistSeekerIdLineEdit = new QLineEdit(scrollAreaWidgetContents);
        shortlistSeekerIdLineEdit->setObjectName("shortlistSeekerIdLineEdit");
        shortlistSeekerIdLineEdit->setMinimumSize(QSize(200, 0));

        shortlistLayout->addWidget(shortlistSeekerIdLineEdit);

        shortlistButton = new QPushButton(scrollAreaWidgetContents);
        shortlistButton->setObjectName("shortlistButton");

        shortlistLayout->addWidget(shortlistButton);


        verticalLayout->addLayout(shortlistLayout);

        verticalSpacer_3 = new QSpacerItem(20, 15, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        notificationsLabel = new QLabel(scrollAreaWidgetContents);
        notificationsLabel->setObjectName("notificationsLabel");
        notificationsLabel->setStyleSheet(QString::fromUtf8("font: bold 18px \"Arial\"; color: #2E4053; background-color: #D1E8E2; padding: 5px;"));

        verticalLayout->addWidget(notificationsLabel);

        notificationsTable = new QTableWidget(scrollAreaWidgetContents);
        if (notificationsTable->columnCount() < 4)
            notificationsTable->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        notificationsTable->setHorizontalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        notificationsTable->setHorizontalHeaderItem(1, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        notificationsTable->setHorizontalHeaderItem(2, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        notificationsTable->setHorizontalHeaderItem(3, __qtablewidgetitem8);
        notificationsTable->setObjectName("notificationsTable");
        notificationsTable->setMinimumSize(QSize(0, 100));
        notificationsTable->setColumnCount(4);

        verticalLayout->addWidget(notificationsTable);

        verticalSpacer_4 = new QSpacerItem(20, 15, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        logoutButton = new QPushButton(scrollAreaWidgetContents);
        logoutButton->setObjectName("logoutButton");

        verticalLayout->addWidget(logoutButton);

        scrollArea->setWidget(scrollAreaWidgetContents);

        retranslateUi(DashboardEmployer);
        QObject::connect(logoutButton, &QPushButton::clicked, DashboardEmployer, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(DashboardEmployer);
    } // setupUi

    void retranslateUi(QDialog *DashboardEmployer)
    {
        DashboardEmployer->setWindowTitle(QCoreApplication::translate("DashboardEmployer", "Employer Dashboard - Job Matching System", nullptr));
        titleLabel->setText(QCoreApplication::translate("DashboardEmployer", "Employer Dashboard", nullptr));
        licenseStatusLabel->setText(QCoreApplication::translate("DashboardEmployer", "License Verification Status: Not Verified", nullptr));
        postJobLabel->setText(QCoreApplication::translate("DashboardEmployer", "Post a New Job", nullptr));
        jobTitleLabel->setText(QCoreApplication::translate("DashboardEmployer", "Job Title:", nullptr));
        jobTitleLineEdit->setPlaceholderText(QCoreApplication::translate("DashboardEmployer", "Enter job title (e.g., Software Engineer)", nullptr));
        descriptionLabel->setText(QCoreApplication::translate("DashboardEmployer", "Description:", nullptr));
        descriptionTextEdit->setPlaceholderText(QCoreApplication::translate("DashboardEmployer", "Enter detailed job description (e.g., responsibilities, tools)", nullptr));
        experienceLabel->setText(QCoreApplication::translate("DashboardEmployer", "Experience (Years):", nullptr));
        salaryLabel->setText(QCoreApplication::translate("DashboardEmployer", "Salary Range:", nullptr));
        salaryLineEdit->setPlaceholderText(QCoreApplication::translate("DashboardEmployer", "Enter salary range (e.g., $60,000-$80,000)", nullptr));
        deadlineLabel->setText(QCoreApplication::translate("DashboardEmployer", "Deadline:", nullptr));
        deadlineLineEdit->setPlaceholderText(QCoreApplication::translate("DashboardEmployer", "Enter deadline (e.g., 2025-06-30)", nullptr));
        locationLabel->setText(QCoreApplication::translate("DashboardEmployer", "Location:", nullptr));
        locationLineEdit->setPlaceholderText(QCoreApplication::translate("DashboardEmployer", "Enter location (e.g., Nairobi, Kenya)", nullptr));
        jobTypeLabel->setText(QCoreApplication::translate("DashboardEmployer", "Job Type:", nullptr));
        jobTypeComboBox->setItemText(0, QCoreApplication::translate("DashboardEmployer", "Full-Time", nullptr));
        jobTypeComboBox->setItemText(1, QCoreApplication::translate("DashboardEmployer", "Part-Time", nullptr));
        jobTypeComboBox->setItemText(2, QCoreApplication::translate("DashboardEmployer", "Contract", nullptr));

        workModeLabel->setText(QCoreApplication::translate("DashboardEmployer", "Work Mode:", nullptr));
        workModeComboBox->setItemText(0, QCoreApplication::translate("DashboardEmployer", "On-Site", nullptr));
        workModeComboBox->setItemText(1, QCoreApplication::translate("DashboardEmployer", "Remote", nullptr));
        workModeComboBox->setItemText(2, QCoreApplication::translate("DashboardEmployer", "Hybrid", nullptr));

        industryLabel->setText(QCoreApplication::translate("DashboardEmployer", "Industry:", nullptr));
        industryLineEdit->setPlaceholderText(QCoreApplication::translate("DashboardEmployer", "Enter industry (e.g., Technology)", nullptr));
        skillsLabel->setText(QCoreApplication::translate("DashboardEmployer", "Skills Required:", nullptr));
        skillsTextEdit->setPlaceholderText(QCoreApplication::translate("DashboardEmployer", "Enter required skills (e.g., Python, SQL, Communication)", nullptr));
        postJobButton->setText(QCoreApplication::translate("DashboardEmployer", "Post Job", nullptr));
        applicantsLabel->setText(QCoreApplication::translate("DashboardEmployer", "View Applicants", nullptr));
        searchApplicantLineEdit->setPlaceholderText(QCoreApplication::translate("DashboardEmployer", "Search by Seeker ID or Name", nullptr));
        searchApplicantButton->setText(QCoreApplication::translate("DashboardEmployer", "Search", nullptr));
        sortApplicantComboBox->setItemText(0, QCoreApplication::translate("DashboardEmployer", "Sort by ID (Asc)", nullptr));
        sortApplicantComboBox->setItemText(1, QCoreApplication::translate("DashboardEmployer", "Sort by ID (Desc)", nullptr));
        sortApplicantComboBox->setItemText(2, QCoreApplication::translate("DashboardEmployer", "Sort by Name (Asc)", nullptr));
        sortApplicantComboBox->setItemText(3, QCoreApplication::translate("DashboardEmployer", "Sort by Name (Desc)", nullptr));

        QTableWidgetItem *___qtablewidgetitem = applicantsTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("DashboardEmployer", "Job ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = applicantsTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("DashboardEmployer", "Seeker ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = applicantsTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("DashboardEmployer", "Full Name", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = applicantsTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("DashboardEmployer", "Status", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = applicantsTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("DashboardEmployer", "Action", nullptr));
        shortlistSeekerIdLineEdit->setPlaceholderText(QCoreApplication::translate("DashboardEmployer", "Enter Seeker ID to Shortlist", nullptr));
        shortlistButton->setText(QCoreApplication::translate("DashboardEmployer", "Shortlist", nullptr));
        notificationsLabel->setText(QCoreApplication::translate("DashboardEmployer", "Notifications", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = notificationsTable->horizontalHeaderItem(0);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("DashboardEmployer", "Notification ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = notificationsTable->horizontalHeaderItem(1);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("DashboardEmployer", "Message", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = notificationsTable->horizontalHeaderItem(2);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("DashboardEmployer", "Created At", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = notificationsTable->horizontalHeaderItem(3);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("DashboardEmployer", "Read", nullptr));
        logoutButton->setText(QCoreApplication::translate("DashboardEmployer", "Logout", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DashboardEmployer: public Ui_DashboardEmployer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DASHBOARD_EMPLOYER_H
