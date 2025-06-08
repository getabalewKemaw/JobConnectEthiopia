#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>

class DBManager {
public:
    // Singleton access
    static DBManager& getInstance();
    QSqlDatabase getDatabase();

    // Prevent copying
    DBManager(const DBManager&) = delete;
    DBManager& operator=(const DBManager&) = delete;

private:
    DBManager();           // Private constructor
    ~DBManager();
    QSqlDatabase db;
};

#endif // DBMANAGER_H
