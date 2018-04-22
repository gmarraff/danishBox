#ifndef BOXVIEW_H
#define BOXVIEW_H

#include <QWidget>
#include <QGridLayout>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include "box.h"
#include "user.h"
#include "gamecontroller.h"

class BoxView : public QWidget
{
    Q_OBJECT
private:
    QGridLayout *mainLayout;
    Box* box;
    User* loggedUser;
    GameController *gc;
    QListWidget *itemsList, *cauldron;
    QPushButton *eatDanishButton, *cookDanishButton, *pickItemButton, *insertItemButton;
    QLineEdit *danishCode, *danishDimension, *searchBar;

    void danishMenu();
    void standardMenu();
    QString boxCapacityStr() const;
    void boxFullMessage() const;

protected:
    void closeEvent(QCloseEvent *event) override;

public:
    explicit BoxView(Box* bx, User* usr, GameController* ngc, QWidget *parent = 0);
public slots:
    void eatCookie();
    void cookDanish();
    void enablePickButton();
    void enableInsertButton();
    void pickItem();
    void insertItem();
    void loadCauldron(QString searchTerm = "");
};

#endif // BOXVIEW_H
