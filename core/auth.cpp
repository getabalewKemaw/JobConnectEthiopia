#include "auth.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "core/dbmanager.h"

bool Auth::login(const QString& email, const QString& hashedPassword, QString& role)
{
    QSqlDatabase db = DBManager::getInstance().getDatabase();
    if (!db.isOpen()) {
        qDebug() << "Database not open in Auth::login";
        return false;
    }

    QSqlQuery query(db);
    // Use single-argument prepare with the query string
    if (!query.prepare("SELECT role, password FROM Users WHERE email = :email AND is_active = TRUE AND blocked = FALSE")) {
        qDebug() << "Prepare failed:" << query.lastError().text();
        return false;
    }

    query.bindValue(":email", email);
    if (!query.exec()) {
        qDebug() << "Login query failed:" << query.lastError().text();
        qDebug() << "Query executed:" << query.lastQuery();
        return false;
    }

    if (query.next()) {
        QString storedPassword = query.value("password").toString();
        role = query.value("role").toString();
        return (storedPassword == hashedPassword); // Compare hashed passwords
    }
    return false;
}
