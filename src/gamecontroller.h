#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <QObject>
#include "box.h"
#include "user.h"

class GameController : public QObject
{
    Q_OBJECT
friend class BoxGame;
private:
    static User* loggedUser;
    Box* managedBox;
    void manageBox() const;
    void sadReact(Box::Type tp) const;
    static QString sadIconPath();
public:
    explicit GameController(Box* box, QObject *parent = 0);
    static void setUser(User* usr);
    static QString typeHelper(Box::Type tp);
    static Box* open(Box* box);

signals:

public slots:
    void react();
};

#endif // GAMECONTROLLER_H
