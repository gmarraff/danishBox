#ifndef ADMIN_H
#define ADMIN_H
#include "user.h"

class Admin: public User
{
public:
    Admin();
    Admin(User* usr);
    QString iconPath() const override;
    QVector<User*> availableUsers() const override;
    User::Type role() const override;
    QVector<Item*> availableItems() const override;
};

#endif // ADMIN_H
