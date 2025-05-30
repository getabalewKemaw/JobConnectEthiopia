#include "auth.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

Auth::Auth() : dbManager(new DBManager())
{
}

bool Auth::login(const QString& email, const QString& password, QString& role)
{
    QSqlDatabase db = dbManager->getDatabase();
    if (!db.isOpen()) {
        qDebug() << "Database is not open:" << db.lastError().text();
        return false;
    }

    QSqlQuery query(db);
    query.prepare("SELECT role FROM Users WHERE email = :email AND password = :password AND is_active = TRUE AND blocked = FALSE");
    query.bindValue(":email", email);
    query.bindValue(":password", password);

    if (!query.exec()) {
        qDebug() << "Login query failed:" << query.lastError().text();
        return false;
    }

    if (!query.next()) {
        qDebug() << "No matching user found or user is blocked.";
        return false;
    }

    role = query.value("role").toString();
    return true;
}
