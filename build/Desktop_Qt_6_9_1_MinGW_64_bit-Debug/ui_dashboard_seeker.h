/********************************************************************************
** Form generated from reading UI file 'dashboard_seeker.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DASHBOARD_SEEKER_H
#define UI_DASHBOARD_SEEKER_H

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
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DashboardSeeker
{
public:
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QLabel *profileStatusLabel;
    QSpacerItem *verticalSpacer_1;
    QLabel *profileLabel;
    QFormLayout *profileForm;
    QLabel *fullNameLabel;
    QLineEdit *fullNameLineEdit;
    QLabel *locationLabel;
    QLineEdit *locationLineEdit;
    QLabel *phoneLabel;
    QLineEdit *phoneLineEdit;
    QLabel *educationLabel;
    QTextEdit *educationTextEdit;
    QLabel *skillsLabel;
    QTextEdit *skillsTextEdit;
    QLabel *workExperienceLabel;
    QTextEdit *workExperienceTextEdit;
    QLabel *resumeLabel;
    QLineEdit *resumeLineEdit;
    QLabel *aboutLabel;
    QTextEdit *aboutTextEdit;
    QPushButton *updateProfileButton;
    QSpacerItem *verticalSpacer_2;
    QLabel *jobsLabel;
    QHBoxLayout *searchSortLayout;
    QLineEdit *searchLineEdit;
    QPushButton *searchButton;
    QComboBox *sortComboBox;
    QTableWidget *jobsTable;
    QHBoxLayout *applyLayout;
    QLineEdit *jobIdLineEdit;
    QPushButton *applyButton;
    QLabel *applicationsLabel;
    QTableWidget *applicationsTable;
    QSpacerItem *verticalSpacer_21;
    QPushButton *logoutButton;

    void setupUi(QDialog *DashboardSeeker)
    {
        if (DashboardSeeker->objectName().isEmpty())
            DashboardSeeker->setObjectName("DashboardSeeker");
        DashboardSeeker->resize(800, 900);
        DashboardSeeker->setStyleSheet(QString::fromUtf8("\n"
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
"    QLabel#profileStatusLabel { font: bold 14px \"Arial\"; color: #2D6A4F; background-color: #D1E8E2; padding: 5px; border-radius: 5px; }\n"
"   "));
        scrollArea = new QScrollArea(DashboardSeeker);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setGeometry(QRect(20, 20, 760, 860));
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAsNeeded);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 741, 1077));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setSpacing(10);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(10, 10, 10, 10);
        titleLabel = new QLabel(scrollAreaWidgetContents);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setStyleSheet(QString::fromUtf8("font: bold 24px \"Arial\"; color: #2D6A4F; background-color: #D1E8E2; border-radius: 5px; padding: 10px;"));
        titleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        profileStatusLabel = new QLabel(scrollAreaWidgetContents);
        profileStatusLabel->setObjectName("profileStatusLabel");

        verticalLayout->addWidget(profileStatusLabel);

        verticalSpacer_1 = new QSpacerItem(20, 15, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_1);

        profileLabel = new QLabel(scrollAreaWidgetContents);
        profileLabel->setObjectName("profileLabel");
        profileLabel->setStyleSheet(QString::fromUtf8("font: bold 18px \"Arial\"; color: #2E4053; background-color: #D1E8E2; padding: 5px;"));

        verticalLayout->addWidget(profileLabel);

        profileForm = new QFormLayout();
        profileForm->setObjectName("profileForm");
        profileForm->setLabelAlignment(Qt::AlignmentFlag::AlignRight|Qt::AlignmentFlag::AlignTrailing|Qt::AlignmentFlag::AlignVCenter);
        profileForm->setFormAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);
        profileForm->setHorizontalSpacing(10);
        profileForm->setVerticalSpacing(10);
        fullNameLabel = new QLabel(scrollAreaWidgetContents);
        fullNameLabel->setObjectName("fullNameLabel");

        profileForm->setWidget(0, QFormLayout::ItemRole::LabelRole, fullNameLabel);

        fullNameLineEdit = new QLineEdit(scrollAreaWidgetContents);
        fullNameLineEdit->setObjectName("fullNameLineEdit");
        fullNameLineEdit->setMinimumSize(QSize(300, 0));

        profileForm->setWidget(0, QFormLayout::ItemRole::FieldRole, fullNameLineEdit);

        locationLabel = new QLabel(scrollAreaWidgetContents);
        locationLabel->setObjectName("locationLabel");

        profileForm->setWidget(1, QFormLayout::ItemRole::LabelRole, locationLabel);

        locationLineEdit = new QLineEdit(scrollAreaWidgetContents);
        locationLineEdit->setObjectName("locationLineEdit");
        locationLineEdit->setMinimumSize(QSize(300, 0));

        profileForm->setWidget(1, QFormLayout::ItemRole::FieldRole, locationLineEdit);

        phoneLabel = new QLabel(scrollAreaWidgetContents);
        phoneLabel->setObjectName("phoneLabel");

        profileForm->setWidget(2, QFormLayout::ItemRole::LabelRole, phoneLabel);

        phoneLineEdit = new QLineEdit(scrollAreaWidgetContents);
        phoneLineEdit->setObjectName("phoneLineEdit");
        phoneLineEdit->setMinimumSize(QSize(300, 0));

        profileForm->setWidget(2, QFormLayout::ItemRole::FieldRole, phoneLineEdit);

        educationLabel = new QLabel(scrollAreaWidgetContents);
        educationLabel->setObjectName("educationLabel");

        profileForm->setWidget(3, QFormLayout::ItemRole::LabelRole, educationLabel);

        educationTextEdit = new QTextEdit(scrollAreaWidgetContents);
        educationTextEdit->setObjectName("educationTextEdit");
        educationTextEdit->setMinimumSize(QSize(300, 60));

        profileForm->setWidget(3, QFormLayout::ItemRole::FieldRole, educationTextEdit);

        skillsLabel = new QLabel(scrollAreaWidgetContents);
        skillsLabel->setObjectName("skillsLabel");

        profileForm->setWidget(4, QFormLayout::ItemRole::LabelRole, skillsLabel);

        skillsTextEdit = new QTextEdit(scrollAreaWidgetContents);
        skillsTextEdit->setObjectName("skillsTextEdit");
        skillsTextEdit->setMinimumSize(QSize(300, 60));

        profileForm->setWidget(4, QFormLayout::ItemRole::FieldRole, skillsTextEdit);

        workExperienceLabel = new QLabel(scrollAreaWidgetContents);
        workExperienceLabel->setObjectName("workExperienceLabel");

        profileForm->setWidget(5, QFormLayout::ItemRole::LabelRole, workExperienceLabel);

        workExperienceTextEdit = new QTextEdit(scrollAreaWidgetContents);
        workExperienceTextEdit->setObjectName("workExperienceTextEdit");
        workExperienceTextEdit->setMinimumSize(QSize(300, 60));

        profileForm->setWidget(5, QFormLayout::ItemRole::FieldRole, workExperienceTextEdit);

        resumeLabel = new QLabel(scrollAreaWidgetContents);
        resumeLabel->setObjectName("resumeLabel");

        profileForm->setWidget(6, QFormLayout::ItemRole::LabelRole, resumeLabel);

        resumeLineEdit = new QLineEdit(scrollAreaWidgetContents);
        resumeLineEdit->setObjectName("resumeLineEdit");
        resumeLineEdit->setMinimumSize(QSize(300, 0));

        profileForm->setWidget(6, QFormLayout::ItemRole::FieldRole, resumeLineEdit);

        aboutLabel = new QLabel(scrollAreaWidgetContents);
        aboutLabel->setObjectName("aboutLabel");

        profileForm->setWidget(7, QFormLayout::ItemRole::LabelRole, aboutLabel);

        aboutTextEdit = new QTextEdit(scrollAreaWidgetContents);
        aboutTextEdit->setObjectName("aboutTextEdit");
        aboutTextEdit->setMinimumSize(QSize(300, 60));

        profileForm->setWidget(7, QFormLayout::ItemRole::FieldRole, aboutTextEdit);

        updateProfileButton = new QPushButton(scrollAreaWidgetContents);
        updateProfileButton->setObjectName("updateProfileButton");

        profileForm->setWidget(8, QFormLayout::ItemRole::FieldRole, updateProfileButton);


        verticalLayout->addLayout(profileForm);

        verticalSpacer_2 = new QSpacerItem(20, 15, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        jobsLabel = new QLabel(scrollAreaWidgetContents);
        jobsLabel->setObjectName("jobsLabel");
        jobsLabel->setStyleSheet(QString::fromUtf8("font: bold 18px \"Arial\"; color: #2E4053; background-color: #D1E8E2; padding: 5px;"));

        verticalLayout->addWidget(jobsLabel);

        searchSortLayout = new QHBoxLayout();
        searchSortLayout->setSpacing(10);
        searchSortLayout->setObjectName("searchSortLayout");
        searchLineEdit = new QLineEdit(scrollAreaWidgetContents);
        searchLineEdit->setObjectName("searchLineEdit");
        searchLineEdit->setMinimumSize(QSize(200, 0));

        searchSortLayout->addWidget(searchLineEdit);

        searchButton = new QPushButton(scrollAreaWidgetContents);
        searchButton->setObjectName("searchButton");

        searchSortLayout->addWidget(searchButton);

        sortComboBox = new QComboBox(scrollAreaWidgetContents);
        sortComboBox->addItem(QString());
        sortComboBox->addItem(QString());
        sortComboBox->addItem(QString());
        sortComboBox->addItem(QString());
        sortComboBox->setObjectName("sortComboBox");

        searchSortLayout->addWidget(sortComboBox);


        verticalLayout->addLayout(searchSortLayout);

        jobsTable = new QTableWidget(scrollAreaWidgetContents);
        if (jobsTable->columnCount() < 12)
            jobsTable->setColumnCount(12);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        jobsTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        jobsTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        jobsTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        jobsTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        jobsTable->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        jobsTable->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        jobsTable->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        jobsTable->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        jobsTable->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        jobsTable->setHorizontalHeaderItem(9, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        jobsTable->setHorizontalHeaderItem(10, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        jobsTable->setHorizontalHeaderItem(11, __qtablewidgetitem11);
        jobsTable->setObjectName("jobsTable");
        jobsTable->setMinimumSize(QSize(0, 150));
        jobsTable->setColumnCount(12);

        verticalLayout->addWidget(jobsTable);

        applyLayout = new QHBoxLayout();
        applyLayout->setSpacing(10);
        applyLayout->setObjectName("applyLayout");
        jobIdLineEdit = new QLineEdit(scrollAreaWidgetContents);
        jobIdLineEdit->setObjectName("jobIdLineEdit");
        jobIdLineEdit->setMinimumSize(QSize(200, 0));

        applyLayout->addWidget(jobIdLineEdit);

        applyButton = new QPushButton(scrollAreaWidgetContents);
        applyButton->setObjectName("applyButton");

        applyLayout->addWidget(applyButton);


        verticalLayout->addLayout(applyLayout);

        applicationsLabel = new QLabel(scrollAreaWidgetContents);
        applicationsLabel->setObjectName("applicationsLabel");
        applicationsLabel->setStyleSheet(QString::fromUtf8("font: bold 18px \"Arial\"; color: #2E4053; background-color: #D1E8E2; padding: 5px;"));

        verticalLayout->addWidget(applicationsLabel);

        applicationsTable = new QTableWidget(scrollAreaWidgetContents);
        if (applicationsTable->columnCount() < 4)
            applicationsTable->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        applicationsTable->setHorizontalHeaderItem(0, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        applicationsTable->setHorizontalHeaderItem(1, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        applicationsTable->setHorizontalHeaderItem(2, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        applicationsTable->setHorizontalHeaderItem(3, __qtablewidgetitem15);
        applicationsTable->setObjectName("applicationsTable");
        applicationsTable->setMinimumSize(QSize(0, 100));
        applicationsTable->setColumnCount(4);

        verticalLayout->addWidget(applicationsTable);

        verticalSpacer_21 = new QSpacerItem(20, 15, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_21);

        logoutButton = new QPushButton(scrollAreaWidgetContents);
        logoutButton->setObjectName("logoutButton");

        verticalLayout->addWidget(logoutButton);

        scrollArea->setWidget(scrollAreaWidgetContents);

        retranslateUi(DashboardSeeker);
        QObject::connect(logoutButton, &QPushButton::clicked, DashboardSeeker, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(DashboardSeeker);
    } // setupUi

    void retranslateUi(QDialog *DashboardSeeker)
    {
        DashboardSeeker->setWindowTitle(QCoreApplication::translate("DashboardSeeker", "Job Seeker Dashboard - Job Matching System", nullptr));
        titleLabel->setText(QCoreApplication::translate("DashboardSeeker", "Job Seeker Dashboard", nullptr));
        profileStatusLabel->setText(QCoreApplication::translate("DashboardSeeker", "Profile Verification Status: Not Verified", nullptr));
        profileLabel->setText(QCoreApplication::translate("DashboardSeeker", "Profile", nullptr));
        fullNameLabel->setText(QCoreApplication::translate("DashboardSeeker", "Full Name:", nullptr));
        fullNameLineEdit->setPlaceholderText(QCoreApplication::translate("DashboardSeeker", "Enter Full Name (e.g., John Doe)", nullptr));
        locationLabel->setText(QCoreApplication::translate("DashboardSeeker", "Location:", nullptr));
        locationLineEdit->setPlaceholderText(QCoreApplication::translate("DashboardSeeker", "Enter Location (e.g., Nairobi, Kenya)", nullptr));
        phoneLabel->setText(QCoreApplication::translate("DashboardSeeker", "Phone:", nullptr));
        phoneLineEdit->setPlaceholderText(QCoreApplication::translate("DashboardSeeker", "Enter Phone Number (e.g., +254 712 345 678)", nullptr));
        educationLabel->setText(QCoreApplication::translate("DashboardSeeker", "Education:", nullptr));
        educationTextEdit->setPlaceholderText(QCoreApplication::translate("DashboardSeeker", "Enter Education (e.g., B.Sc. Computer Science, University of Nairobi, 2020)", nullptr));
        skillsLabel->setText(QCoreApplication::translate("DashboardSeeker", "Skills:", nullptr));
        skillsTextEdit->setPlaceholderText(QCoreApplication::translate("DashboardSeeker", "Enter Skills (e.g., Python, SQL, Communication)", nullptr));
        workExperienceLabel->setText(QCoreApplication::translate("DashboardSeeker", "Work Experience:", nullptr));
        workExperienceTextEdit->setPlaceholderText(QCoreApplication::translate("DashboardSeeker", "Enter Work Experience (e.g., Software Developer at XYZ Corp, 2021-2023)", nullptr));
        resumeLabel->setText(QCoreApplication::translate("DashboardSeeker", "Resume:", nullptr));
        resumeLineEdit->setPlaceholderText(QCoreApplication::translate("DashboardSeeker", "Upload Resume (e.g., resume.pdf)", nullptr));
        aboutLabel->setText(QCoreApplication::translate("DashboardSeeker", "About:", nullptr));
        aboutTextEdit->setPlaceholderText(QCoreApplication::translate("DashboardSeeker", "Enter About (e.g., Passionate about tech and innovation)", nullptr));
        updateProfileButton->setText(QCoreApplication::translate("DashboardSeeker", "Update Profile", nullptr));
        jobsLabel->setText(QCoreApplication::translate("DashboardSeeker", "Available Jobs", nullptr));
        searchLineEdit->setPlaceholderText(QCoreApplication::translate("DashboardSeeker", "Search by Title or Company", nullptr));
        searchButton->setText(QCoreApplication::translate("DashboardSeeker", "Search", nullptr));
        sortComboBox->setItemText(0, QCoreApplication::translate("DashboardSeeker", "Sort by Salary (Asc)", nullptr));
        sortComboBox->setItemText(1, QCoreApplication::translate("DashboardSeeker", "Sort by Salary (Desc)", nullptr));
        sortComboBox->setItemText(2, QCoreApplication::translate("DashboardSeeker", "Sort by Deadline (Asc)", nullptr));
        sortComboBox->setItemText(3, QCoreApplication::translate("DashboardSeeker", "Sort by Deadline (Desc)", nullptr));

        QTableWidgetItem *___qtablewidgetitem = jobsTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("DashboardSeeker", "Job ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = jobsTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("DashboardSeeker", "Title", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = jobsTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("DashboardSeeker", "Company", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = jobsTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("DashboardSeeker", "Location", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = jobsTable->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("DashboardSeeker", "Salary Range", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = jobsTable->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("DashboardSeeker", "Deadline", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = jobsTable->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("DashboardSeeker", "Job Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = jobsTable->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("DashboardSeeker", "Work Mode", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = jobsTable->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("DashboardSeeker", "Industry", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = jobsTable->horizontalHeaderItem(9);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("DashboardSeeker", "Skills Required", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = jobsTable->horizontalHeaderItem(10);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("DashboardSeeker", "Additional Details", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = jobsTable->horizontalHeaderItem(11);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("DashboardSeeker", "Action", nullptr));
        jobIdLineEdit->setPlaceholderText(QCoreApplication::translate("DashboardSeeker", "Enter Job ID to Apply", nullptr));
        applyButton->setText(QCoreApplication::translate("DashboardSeeker", "Apply", nullptr));
        applicationsLabel->setText(QCoreApplication::translate("DashboardSeeker", "My Applications", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = applicationsTable->horizontalHeaderItem(0);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("DashboardSeeker", "Job ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = applicationsTable->horizontalHeaderItem(1);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("DashboardSeeker", "Title", nullptr));
        QTableWidgetItem *___qtablewidgetitem14 = applicationsTable->horizontalHeaderItem(2);
        ___qtablewidgetitem14->setText(QCoreApplication::translate("DashboardSeeker", "Company", nullptr));
        QTableWidgetItem *___qtablewidgetitem15 = applicationsTable->horizontalHeaderItem(3);
        ___qtablewidgetitem15->setText(QCoreApplication::translate("DashboardSeeker", "Status", nullptr));
        logoutButton->setText(QCoreApplication::translate("DashboardSeeker", "Logout", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DashboardSeeker: public Ui_DashboardSeeker {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DASHBOARD_SEEKER_H
