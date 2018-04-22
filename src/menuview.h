#ifndef MENUVIEW_H
#define MENUVIEW_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QPixmap>
#include <QWindow>
#include "user.h"
#include "adminzone.h"
#include "boxgame.h"
#include "newboxview.h"
#include "newitemview.h"
#include "throwboxesview.h"

class MenuView : public QWidget
{
    Q_OBJECT
private:
    User *loggedUser;
    QGridLayout *mainLayout;
    QPushButton *logOutButton, *openBoxesButton, *adminButton,
                *createBoxesButton, *createItemsButton, *throwBoxesButton;
    QPixmap *usrTypeImage;
    AdminZone *adminZone;
    BoxGame *game;
    NewBoxView *boxView;
    NewItemView *itemView;
    ThrowBoxesView *throwBoxesView;

    void initializeFields();
    void setUpUI();
    void initializeConnectors();
public:
    explicit MenuView(User* usr, QWidget *parent = 0);

signals:
    void logOut();

public slots:
    void logOutClicked();
    void openCreateBoxes();
    void openCreateItems();
    void openThrowBoxes();
    void openAdminZone();
    void openGame();
};

#endif // MENUVIEW_H
