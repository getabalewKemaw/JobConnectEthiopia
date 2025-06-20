#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include "core/dbmanager.h"

namespace Ui {
class SignUp;
}

class SignUp : public QDialog
{
    Q_OBJECT

public:
    explicit SignUp(QWidget *parent = nullptr);
    ~SignUp();

signals:
    void userSignedUp(const QString& firstName, const QString& lastName, const QString& role);
    void showLogin(); // Signal to show LoginUI

private slots:
    void on_submitButton_clicked();  // Handles form submission
    void on_roleComboBox_currentIndexChanged(int index);  // Toggles Employer fields
    void on_backButton_clicked();  // Slot for the new Back button

private:
    Ui::SignUp *ui;
    DBManager *dbManager;
    void setupConnections();
    bool validateInputs();
    void clearFields();
    bool ensureDatabaseConnection(); // Added to manage DB connection
};

#endif // SIGNUP_H
