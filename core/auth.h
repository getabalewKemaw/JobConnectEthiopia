#ifndef AUTH_H
#define AUTH_H

#include <QString>

class Auth {
public:
    bool login(const QString& email, const QString& hashedPassword, QString& role);
};

#endif // AUTH_H
