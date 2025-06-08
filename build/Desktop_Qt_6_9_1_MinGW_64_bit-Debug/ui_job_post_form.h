/********************************************************************************
** Form generated from reading UI file 'job_post_form.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_JOB_POST_FORM_H
#define UI_JOB_POST_FORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_JobPostForm
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *placeholderLabel;

    void setupUi(QDialog *JobPostForm)
    {
        if (JobPostForm->objectName().isEmpty())
            JobPostForm->setObjectName("JobPostForm");
        JobPostForm->resize(400, 300);
        verticalLayout = new QVBoxLayout(JobPostForm);
        verticalLayout->setObjectName("verticalLayout");
        placeholderLabel = new QLabel(JobPostForm);
        placeholderLabel->setObjectName("placeholderLabel");

        verticalLayout->addWidget(placeholderLabel);


        retranslateUi(JobPostForm);

        QMetaObject::connectSlotsByName(JobPostForm);
    } // setupUi

    void retranslateUi(QDialog *JobPostForm)
    {
        JobPostForm->setWindowTitle(QCoreApplication::translate("JobPostForm", "Post a Job", nullptr));
        placeholderLabel->setText(QCoreApplication::translate("JobPostForm", "Job Post Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class JobPostForm: public Ui_JobPostForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_JOB_POST_FORM_H
