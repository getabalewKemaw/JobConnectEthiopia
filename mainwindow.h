#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui/login.h"
#include "ui/signup.h"
#include "ui/dashboard_seeker.h"
#include "ui/dashboard_employer.h"
#include "ui/dashboard_admin.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleLogin();
    void showLoginDialog();
    void showSignUpDialog();

private:
    Ui::MainWindow *ui;
    QDialog *dashboard;
};

#endif // MAINWINDOW_H
