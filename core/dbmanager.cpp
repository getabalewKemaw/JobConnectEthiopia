#include "dbmanager.h"
#include <QSqlError>
#include <QDebug>
#include <QSqlQuery>

DBManager::DBManager()
{
    // Use a unique connection name to avoid overwriting the default
    db = QSqlDatabase::addDatabase("QPSQL", "JobappConnection");
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
        QSqlDatabase::removeDatabase("JobappConnection"); // Remove the specific connection
    }
}

DBManager& DBManager::getInstance()
{
    static DBManager instance; // Thread-safe singleton in C++11
    return instance;
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
