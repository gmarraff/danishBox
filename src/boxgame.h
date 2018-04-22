#ifndef BOXGAME_H
#define BOXGAME_H

#include <QWidget>
#include <QVector>
#include <QPushButton>
#include <QGridLayout>
#include <QScrollArea>
#include "box.h"
#include "gamecontroller.h"
#include "user.h"
class BoxGame : public QWidget
{
    Q_OBJECT
private:
    QGridLayout *mainLayout, *boxesLayout;
    QWidget *scrollableWidget;
    QScrollArea *scrollableArea;
    QVector<Box*> boxes;
    QVector<GameController*> controllers;

    User *loggedUser;

public:
    explicit BoxGame(User* usr, QWidget *parent = 0);

signals:

public slots:
};

#endif // BOXGAME_H
