/********************************************************************************
** Form generated from reading UI file 'signup.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNUP_H
#define UI_SIGNUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SignUp
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QSpacerItem *verticalSpacer_1;
    QLabel *roleLabel;
    QComboBox *roleComboBox;
    QLabel *emailLabel;
    QLineEdit *emailLineEdit;
    QLabel *passwordLabel;
    QLineEdit *passwordLineEdit;
    QLabel *fullNameLabel;
    QLineEdit *fullNameLineEdit;
    QLabel *companyNameLabel;
    QLineEdit *companyNameLineEdit;
    QLabel *licenseNumberLabel;
    QLineEdit *licenseNumberLineEdit;
    QLabel *websiteLabel;
    QLineEdit *websiteLineEdit;
    QLabel *industryLabel;
    QLineEdit *industryLineEdit;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *backButton;
    QPushButton *submitButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *SignUp)
    {
        if (SignUp->objectName().isEmpty())
            SignUp->setObjectName("SignUp");
        SignUp->resize(400, 600);
        SignUp->setStyleSheet(QString::fromUtf8("\n"
"    QDialog {\n"
"        background-color: #E6F0FA; /* Light blue background */\n"
"    }\n"
"    QLabel {\n"
"        font: 14px \"Arial\";\n"
"        color: #2E4053; /* Dark slate color for text */\n"
"    }\n"
"    QLineEdit {\n"
"        background-color: #FFFFFF;\n"
"        border: 1px solid #A3BFFA;\n"
"        border-radius: 5px;\n"
"        padding: 5px;\n"
"        font: 14px \"Arial\";\n"
"    }\n"
"    QLineEdit:focus {\n"
"        border: 2px solid #4C6EF5; /* Vibrant blue on focus */\n"
"    }\n"
"    QComboBox {\n"
"        background-color: #FFFFFF;\n"
"        border: 1px solid #A3BFFA;\n"
"        border-radius: 5px;\n"
"        padding: 5px;\n"
"        font: 14px \"Arial\";\n"
"    }\n"
"    QComboBox:hover {\n"
"        background-color: #F0F4FF;\n"
"    }\n"
"    QPushButton {\n"
"        background-color: #4CAF50; /* Green for buttons */\n"
"        color: white;\n"
"        border-radius: 5px;\n"
"        padding: 8px;\n"
"        font: 14px \"Arial\";\n"
"    }\n"
"    QPushButt"
                        "on:hover {\n"
"        background-color: #45A049; /* Slightly darker green on hover */\n"
"    }\n"
"    QPushButton#cancelButton {\n"
"        background-color: #FF6B6B; /* Red for cancel button */\n"
"    }\n"
"    QPushButton#cancelButton:hover {\n"
"        background-color: #FF5252; /* Slightly darker red on hover */\n"
"    }\n"
"   "));
        verticalLayoutWidget = new QWidget(SignUp);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(20, 20, 360, 560));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        titleLabel = new QLabel(verticalLayoutWidget);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setStyleSheet(QString::fromUtf8("\n"
"        font: bold 20px \"Arial\";\n"
"        color: #2D6A4F; /* Dark green for title */\n"
"       "));
        titleLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        verticalSpacer_1 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_1);

        roleLabel = new QLabel(verticalLayoutWidget);
        roleLabel->setObjectName("roleLabel");

        verticalLayout->addWidget(roleLabel);

        roleComboBox = new QComboBox(verticalLayoutWidget);
        roleComboBox->addItem(QString());
        roleComboBox->addItem(QString());
        roleComboBox->setObjectName("roleComboBox");

        verticalLayout->addWidget(roleComboBox);

        emailLabel = new QLabel(verticalLayoutWidget);
        emailLabel->setObjectName("emailLabel");

        verticalLayout->addWidget(emailLabel);

        emailLineEdit = new QLineEdit(verticalLayoutWidget);
        emailLineEdit->setObjectName("emailLineEdit");

        verticalLayout->addWidget(emailLineEdit);

        passwordLabel = new QLabel(verticalLayoutWidget);
        passwordLabel->setObjectName("passwordLabel");

        verticalLayout->addWidget(passwordLabel);

        passwordLineEdit = new QLineEdit(verticalLayoutWidget);
        passwordLineEdit->setObjectName("passwordLineEdit");
        passwordLineEdit->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(passwordLineEdit);

        fullNameLabel = new QLabel(verticalLayoutWidget);
        fullNameLabel->setObjectName("fullNameLabel");

        verticalLayout->addWidget(fullNameLabel);

        fullNameLineEdit = new QLineEdit(verticalLayoutWidget);
        fullNameLineEdit->setObjectName("fullNameLineEdit");

        verticalLayout->addWidget(fullNameLineEdit);

        companyNameLabel = new QLabel(verticalLayoutWidget);
        companyNameLabel->setObjectName("companyNameLabel");
        companyNameLabel->setVisible(false);

        verticalLayout->addWidget(companyNameLabel);

        companyNameLineEdit = new QLineEdit(verticalLayoutWidget);
        companyNameLineEdit->setObjectName("companyNameLineEdit");
        companyNameLineEdit->setVisible(false);

        verticalLayout->addWidget(companyNameLineEdit);

        licenseNumberLabel = new QLabel(verticalLayoutWidget);
        licenseNumberLabel->setObjectName("licenseNumberLabel");
        licenseNumberLabel->setVisible(false);

        verticalLayout->addWidget(licenseNumberLabel);

        licenseNumberLineEdit = new QLineEdit(verticalLayoutWidget);
        licenseNumberLineEdit->setObjectName("licenseNumberLineEdit");
        licenseNumberLineEdit->setVisible(false);

        verticalLayout->addWidget(licenseNumberLineEdit);

        websiteLabel = new QLabel(verticalLayoutWidget);
        websiteLabel->setObjectName("websiteLabel");
        websiteLabel->setVisible(false);

        verticalLayout->addWidget(websiteLabel);

        websiteLineEdit = new QLineEdit(verticalLayoutWidget);
        websiteLineEdit->setObjectName("websiteLineEdit");
        websiteLineEdit->setVisible(false);

        verticalLayout->addWidget(websiteLineEdit);

        industryLabel = new QLabel(verticalLayoutWidget);
        industryLabel->setObjectName("industryLabel");
        industryLabel->setVisible(false);

        verticalLayout->addWidget(industryLabel);

        industryLineEdit = new QLineEdit(verticalLayoutWidget);
        industryLineEdit->setObjectName("industryLineEdit");
        industryLineEdit->setVisible(false);

        verticalLayout->addWidget(industryLineEdit);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        backButton = new QPushButton(verticalLayoutWidget);
        backButton->setObjectName("backButton");

        horizontalLayout->addWidget(backButton);

        submitButton = new QPushButton(verticalLayoutWidget);
        submitButton->setObjectName("submitButton");

        horizontalLayout->addWidget(submitButton);

        cancelButton = new QPushButton(verticalLayoutWidget);
        cancelButton->setObjectName("cancelButton");

        horizontalLayout->addWidget(cancelButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(SignUp);
        QObject::connect(cancelButton, &QPushButton::clicked, SignUp, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(SignUp);
    } // setupUi

    void retranslateUi(QDialog *SignUp)
    {
        SignUp->setWindowTitle(QCoreApplication::translate("SignUp", "Sign Up - Job Matching System", nullptr));
        titleLabel->setText(QCoreApplication::translate("SignUp", "Create Your Account", nullptr));
        roleLabel->setText(QCoreApplication::translate("SignUp", "I am a:", nullptr));
        roleComboBox->setItemText(0, QCoreApplication::translate("SignUp", "Job Seeker", nullptr));
        roleComboBox->setItemText(1, QCoreApplication::translate("SignUp", "Employer", nullptr));

        emailLabel->setText(QCoreApplication::translate("SignUp", "Email:", nullptr));
        emailLineEdit->setPlaceholderText(QCoreApplication::translate("SignUp", "Enter your email", nullptr));
        passwordLabel->setText(QCoreApplication::translate("SignUp", "Password:", nullptr));
        passwordLineEdit->setPlaceholderText(QCoreApplication::translate("SignUp", "Enter your password", nullptr));
        fullNameLabel->setText(QCoreApplication::translate("SignUp", "Full Name:", nullptr));
        fullNameLineEdit->setPlaceholderText(QCoreApplication::translate("SignUp", "Enter your full name", nullptr));
        companyNameLabel->setText(QCoreApplication::translate("SignUp", "Company Name:", nullptr));
        companyNameLineEdit->setPlaceholderText(QCoreApplication::translate("SignUp", "Enter your company name", nullptr));
        licenseNumberLabel->setText(QCoreApplication::translate("SignUp", "License Number:", nullptr));
        licenseNumberLineEdit->setPlaceholderText(QCoreApplication::translate("SignUp", "Enter your license number", nullptr));
        websiteLabel->setText(QCoreApplication::translate("SignUp", "Website (Optional):", nullptr));
        websiteLineEdit->setPlaceholderText(QCoreApplication::translate("SignUp", "Enter your website", nullptr));
        industryLabel->setText(QCoreApplication::translate("SignUp", "Industry:", nullptr));
        industryLineEdit->setPlaceholderText(QCoreApplication::translate("SignUp", "Enter your industry", nullptr));
        backButton->setText(QCoreApplication::translate("SignUp", "Back", nullptr));
        submitButton->setText(QCoreApplication::translate("SignUp", "Submit", nullptr));
        cancelButton->setText(QCoreApplication::translate("SignUp", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SignUp: public Ui_SignUp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNUP_H
