#include "job_post_form.h"
#include "ui_job_post_form.h"

JobPostForm::JobPostForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::JobPostForm)
{
    ui->setupUi(this);
}

JobPostForm::~JobPostForm()
{
    delete ui;
}
