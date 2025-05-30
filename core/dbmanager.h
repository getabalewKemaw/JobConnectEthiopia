#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QSqlDatabase>

class DBManager {
public:
    DBManager();           // Declaration only, no implementation
    ~DBManager();
    QSqlDatabase getDatabase();

private:
    QSqlDatabase db;
};

#endif // DBMANAGER_H
