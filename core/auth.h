#ifndef AUTH_H
#define AUTH_H

#include <QString>
#include "dbmanager.h"

class Auth {
public:
    Auth();
    bool login(const QString& email, const QString& password, QString& role);

private:
    DBManager* dbManager;
};

#endif // AUTH_H
