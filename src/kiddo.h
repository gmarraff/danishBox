#ifndef KIDDO_H
#define KIDDO_H
#include "user.h"

class Kiddo: public User
{
public:
    Kiddo();
    Kiddo(User* usr);
    QString iconPath() const override;
    User::Type role() const override;
    QVector<Item*> availableItems() const override;
};

#endif // KIDDO_H
