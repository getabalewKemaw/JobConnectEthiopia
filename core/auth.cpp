#include "auth.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QCryptographicHash>
#include <QRegularExpression>

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
    query.prepare("SELECT role, password FROM Users WHERE email = :email AND is_active = TRUE AND blocked = FALSE");
    query.bindValue(":email", email);

    if (!query.exec()) {
        qDebug() << "Login query failed:" << query.lastError().text();
        return false;
    }

    if (!query.next()) {
        qDebug() << "No matching user found or user is blocked.";
        return false;
    }

    QString storedPassword = query.value("password").toString();
    role = query.value("role").toString();

    // Check if stored password is hashed (SHA-256 produces 64-character hex string)
    QRegularExpression hexRegex("^[0-9a-fA-F]{64}$");
    bool isHashed = hexRegex.match(storedPassword).hasMatch();

    if (isHashed) {
        // The password parameter is already hashed by login.cpp, so compare directly
        if (password != storedPassword) {
            qDebug() << "Hashed password does not match.";
            return false;
        }
    } else {
        // The password parameter is hashed, but stored password is plain, so this should fail
        // To support plain passwords, we need to hash the stored password and compare
        QString hashedStoredPassword = QString(QCryptographicHash::hash(storedPassword.toUtf8(), QCryptographicHash::Sha256).toHex());
        if (password != hashedStoredPassword) {
            qDebug() << "Plain password (hashed for comparison) does not match.";
            return false;
        }
    }

    return true;
}
