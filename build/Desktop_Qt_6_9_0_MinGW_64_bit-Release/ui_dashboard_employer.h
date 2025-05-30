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
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DashboardEmployer
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *placeholderLabel;

    void setupUi(QDialog *DashboardEmployer)
    {
        if (DashboardEmployer->objectName().isEmpty())
            DashboardEmployer->setObjectName("DashboardEmployer");
        DashboardEmployer->resize(400, 300);
        verticalLayout = new QVBoxLayout(DashboardEmployer);
        verticalLayout->setObjectName("verticalLayout");
        placeholderLabel = new QLabel(DashboardEmployer);
        placeholderLabel->setObjectName("placeholderLabel");

        verticalLayout->addWidget(placeholderLabel);


        retranslateUi(DashboardEmployer);

        QMetaObject::connectSlotsByName(DashboardEmployer);
    } // setupUi

    void retranslateUi(QDialog *DashboardEmployer)
    {
        DashboardEmployer->setWindowTitle(QCoreApplication::translate("DashboardEmployer", "Employer Dashboard", nullptr));
        placeholderLabel->setText(QCoreApplication::translate("DashboardEmployer", "Employer Dashboard Placeholder", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DashboardEmployer: public Ui_DashboardEmployer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DASHBOARD_EMPLOYER_H
