#ifndef JOB_POST_FORM_H
#define JOB_POST_FORM_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class JobPostForm; }
QT_END_NAMESPACE

class JobPostForm : public QDialog
{
    Q_OBJECT

public:
    JobPostForm(QWidget *parent = nullptr);
    ~JobPostForm();

private:
    Ui::JobPostForm *ui;
};

#endif
