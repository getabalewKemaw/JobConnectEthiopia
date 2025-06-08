/********************************************************************************
** Form generated from reading UI file 'signup.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
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
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SignUp
{
public:
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QSpacerItem *verticalSpacer_1;
    QLabel *roleLabel;
    QComboBox *roleComboBox;
    QLabel *emailLabel;
    QLineEdit *emailLineEdit;
    QLabel *passwordLabel;
    QLineEdit *passwordLineEdit;
    QLabel *confirmPasswordLabel;
    QLineEdit *confirmPasswordLineEdit;
    QLabel *firstNameLabel;
    QLineEdit *firstNameLineEdit;
    QLabel *lastNameLabel;
    QLineEdit *lastNameLineEdit;
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
        scrollArea = new QScrollArea(SignUp);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setGeometry(QRect(20, 20, 360, 560));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 360, 750));
        verticalLayout = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout->setObjectName("verticalLayout");
        titleLabel = new QLabel(scrollAreaWidgetContents);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setStyleSheet(QString::fromUtf8("\n"
"         font: bold 20px \"Arial\";\n"
"         color: #2D6A4F; /* Dark green for title */\n"
"        "));
        titleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout->addWidget(titleLabel);

        verticalSpacer_1 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_1);

        roleLabel = new QLabel(scrollAreaWidgetContents);
        roleLabel->setObjectName("roleLabel");

        verticalLayout->addWidget(roleLabel);

        roleComboBox = new QComboBox(scrollAreaWidgetContents);
        roleComboBox->addItem(QString());
        roleComboBox->addItem(QString());
        roleComboBox->setObjectName("roleComboBox");

        verticalLayout->addWidget(roleComboBox);

        emailLabel = new QLabel(scrollAreaWidgetContents);
        emailLabel->setObjectName("emailLabel");

        verticalLayout->addWidget(emailLabel);

        emailLineEdit = new QLineEdit(scrollAreaWidgetContents);
        emailLineEdit->setObjectName("emailLineEdit");

        verticalLayout->addWidget(emailLineEdit);

        passwordLabel = new QLabel(scrollAreaWidgetContents);
        passwordLabel->setObjectName("passwordLabel");

        verticalLayout->addWidget(passwordLabel);

        passwordLineEdit = new QLineEdit(scrollAreaWidgetContents);
        passwordLineEdit->setObjectName("passwordLineEdit");
        passwordLineEdit->setEchoMode(QLineEdit::EchoMode::Password);

        verticalLayout->addWidget(passwordLineEdit);

        confirmPasswordLabel = new QLabel(scrollAreaWidgetContents);
        confirmPasswordLabel->setObjectName("confirmPasswordLabel");

        verticalLayout->addWidget(confirmPasswordLabel);

        confirmPasswordLineEdit = new QLineEdit(scrollAreaWidgetContents);
        confirmPasswordLineEdit->setObjectName("confirmPasswordLineEdit");
        confirmPasswordLineEdit->setEchoMode(QLineEdit::EchoMode::Password);

        verticalLayout->addWidget(confirmPasswordLineEdit);

        firstNameLabel = new QLabel(scrollAreaWidgetContents);
        firstNameLabel->setObjectName("firstNameLabel");

        verticalLayout->addWidget(firstNameLabel);

        firstNameLineEdit = new QLineEdit(scrollAreaWidgetContents);
        firstNameLineEdit->setObjectName("firstNameLineEdit");

        verticalLayout->addWidget(firstNameLineEdit);

        lastNameLabel = new QLabel(scrollAreaWidgetContents);
        lastNameLabel->setObjectName("lastNameLabel");

        verticalLayout->addWidget(lastNameLabel);

        lastNameLineEdit = new QLineEdit(scrollAreaWidgetContents);
        lastNameLineEdit->setObjectName("lastNameLineEdit");

        verticalLayout->addWidget(lastNameLineEdit);

        companyNameLabel = new QLabel(scrollAreaWidgetContents);
        companyNameLabel->setObjectName("companyNameLabel");
        companyNameLabel->setVisible(false);

        verticalLayout->addWidget(companyNameLabel);

        companyNameLineEdit = new QLineEdit(scrollAreaWidgetContents);
        companyNameLineEdit->setObjectName("companyNameLineEdit");
        companyNameLineEdit->setVisible(false);

        verticalLayout->addWidget(companyNameLineEdit);

        licenseNumberLabel = new QLabel(scrollAreaWidgetContents);
        licenseNumberLabel->setObjectName("licenseNumberLabel");
        licenseNumberLabel->setVisible(false);

        verticalLayout->addWidget(licenseNumberLabel);

        licenseNumberLineEdit = new QLineEdit(scrollAreaWidgetContents);
        licenseNumberLineEdit->setObjectName("licenseNumberLineEdit");
        licenseNumberLineEdit->setVisible(false);

        verticalLayout->addWidget(licenseNumberLineEdit);

        websiteLabel = new QLabel(scrollAreaWidgetContents);
        websiteLabel->setObjectName("websiteLabel");
        websiteLabel->setVisible(false);

        verticalLayout->addWidget(websiteLabel);

        websiteLineEdit = new QLineEdit(scrollAreaWidgetContents);
        websiteLineEdit->setObjectName("websiteLineEdit");
        websiteLineEdit->setVisible(false);

        verticalLayout->addWidget(websiteLineEdit);

        industryLabel = new QLabel(scrollAreaWidgetContents);
        industryLabel->setObjectName("industryLabel");
        industryLabel->setVisible(false);

        verticalLayout->addWidget(industryLabel);

        industryLineEdit = new QLineEdit(scrollAreaWidgetContents);
        industryLineEdit->setObjectName("industryLineEdit");
        industryLineEdit->setVisible(false);

        verticalLayout->addWidget(industryLineEdit);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        backButton = new QPushButton(scrollAreaWidgetContents);
        backButton->setObjectName("backButton");

        horizontalLayout->addWidget(backButton);

        submitButton = new QPushButton(scrollAreaWidgetContents);
        submitButton->setObjectName("submitButton");

        horizontalLayout->addWidget(submitButton);

        cancelButton = new QPushButton(scrollAreaWidgetContents);
        cancelButton->setObjectName("cancelButton");

        horizontalLayout->addWidget(cancelButton);


        verticalLayout->addLayout(horizontalLayout);

        scrollArea->setWidget(scrollAreaWidgetContents);

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
        confirmPasswordLabel->setText(QCoreApplication::translate("SignUp", "Confirm Password:", nullptr));
        confirmPasswordLineEdit->setPlaceholderText(QCoreApplication::translate("SignUp", "Confirm your password", nullptr));
        firstNameLabel->setText(QCoreApplication::translate("SignUp", "First Name:", nullptr));
        firstNameLineEdit->setPlaceholderText(QCoreApplication::translate("SignUp", "Enter your first name", nullptr));
        lastNameLabel->setText(QCoreApplication::translate("SignUp", "Last Name:", nullptr));
        lastNameLineEdit->setPlaceholderText(QCoreApplication::translate("SignUp", "Enter your last name", nullptr));
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
