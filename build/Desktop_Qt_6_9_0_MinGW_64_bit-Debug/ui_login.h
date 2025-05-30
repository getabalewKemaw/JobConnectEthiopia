/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *titleLabel;
    QSpacerItem *verticalSpacer_1;
    QLabel *emailLabel;
    QLineEdit *emailLineEdit;
    QLabel *passwordLabel;
    QLineEdit *passwordLineEdit;
    QLabel *statusLabel;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *backButton;
    QPushButton *loginButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName("Login");
        Login->resize(400, 400);
        Login->setStyleSheet(QString::fromUtf8("\n"
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
"    QPushButton {\n"
"        background-color: #4CAF50; /* Green for buttons */\n"
"        color: white;\n"
"        border-radius: 5px;\n"
"        padding: 8px;\n"
"        font: 14px \"Arial\";\n"
"    }\n"
"    QPushButton:hover {\n"
"        background-color: #45A049; /* Slightly darker green on hover */\n"
"    }\n"
"    QPushButton#cancelButton {\n"
"        background-color: #FF6B6B; /* Red for cancel button */\n"
"    }\n"
"    QPushButton#cancelButton:hover {\n"
"        background-co"
                        "lor: #FF5252; /* Slightly darker red on hover */\n"
"    }\n"
"   "));
        verticalLayoutWidget = new QWidget(Login);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(20, 20, 360, 360));
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

        statusLabel = new QLabel(verticalLayoutWidget);
        statusLabel->setObjectName("statusLabel");
        statusLabel->setStyleSheet(QString::fromUtf8("\n"
"        color: #FF6B6B; /* Red for error messages */\n"
"        font: 12px \"Arial\";\n"
"       "));
        statusLabel->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(statusLabel);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        backButton = new QPushButton(verticalLayoutWidget);
        backButton->setObjectName("backButton");

        horizontalLayout->addWidget(backButton);

        loginButton = new QPushButton(verticalLayoutWidget);
        loginButton->setObjectName("loginButton");

        horizontalLayout->addWidget(loginButton);

        cancelButton = new QPushButton(verticalLayoutWidget);
        cancelButton->setObjectName("cancelButton");

        horizontalLayout->addWidget(cancelButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(Login);
        QObject::connect(cancelButton, &QPushButton::clicked, Login, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QDialog *Login)
    {
        Login->setWindowTitle(QCoreApplication::translate("Login", "Login - Job Matching System", nullptr));
        titleLabel->setText(QCoreApplication::translate("Login", "Login to Your Account", nullptr));
        emailLabel->setText(QCoreApplication::translate("Login", "Email:", nullptr));
        emailLineEdit->setPlaceholderText(QCoreApplication::translate("Login", "Enter your email", nullptr));
        passwordLabel->setText(QCoreApplication::translate("Login", "Password:", nullptr));
        passwordLineEdit->setPlaceholderText(QCoreApplication::translate("Login", "Enter your password", nullptr));
        statusLabel->setText(QString());
        backButton->setText(QCoreApplication::translate("Login", "Back", nullptr));
        loginButton->setText(QCoreApplication::translate("Login", "Login", nullptr));
        cancelButton->setText(QCoreApplication::translate("Login", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
