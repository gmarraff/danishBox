#ifndef GRANDMA_H
#define GRANDMA_H
#include "user.h"
class Grandma: public User
{
public:
    Grandma();
    Grandma(User* usr);
    QString iconPath() const override;
    User::Type role() const override;
    QVector<Item*> availableItems() const override;
};

#endif // GRANDMA_H
