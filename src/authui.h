#ifndef AUTHORIZEDUI_H
#define AUTHORIZEDUI_H

#include <QWidget>
#include <QGridLayout>
#include "user.h"

class authUI : public QWidget
{
    Q_OBJECT
protected:
    User* loggedUser;
    QGridLayout *mainLayout;
    virtual void init();
    virtual bool authorized() const;
    virtual void notAuthorizedUI();
    virtual void authorizedUI();
public:
    explicit authUI(User* usr, QWidget *parent = 0);

signals:

public slots:
};

#endif // AUTHORIZEDUI_H
