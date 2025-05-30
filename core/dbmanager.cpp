#include "dbmanager.h"
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>

DBManager::DBManager()
{
    db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setPort(5432);
    db.setDatabaseName("Jobapp");
    db.setUserName("postgres");
    db.setPassword("1234");

    if (!db.open()) {
        qDebug() << "Failed to open database:" << db.lastError().text();
    } else {
        qDebug() << "Successfully connected to Jobapp PostgreSQL database.";
    }
}

DBManager::~DBManager()
{
    if (db.isOpen()) {
        db.close();
    }
}

QSqlDatabase DBManager::getDatabase()
{
    if (!db.isOpen()) {
        if (!db.open()) {
            qDebug() << "Failed to reopen database:" << db.lastError().text();
        } else {
            qDebug() << "Reopened database connection.";
        }
    }
    return db;
}
