#include "boxgame.h"
#include "gamecontroller.h"


BoxGame::BoxGame(User* usr, QWidget *parent) : QWidget(parent), loggedUser(usr)
{
    GameController::loggedUser = loggedUser;
    resize(510, 510);
    setWindowTitle("Gioca");
    boxes = Box::getAll();
    mainLayout = new QGridLayout;
    boxesLayout = new QGridLayout;
    scrollableWidget = new QWidget(this);

    for(int it = 0; it < boxes.size(); ++it){
        QPushButton *btn = new QPushButton(boxes.at(it)->getCode());
        btn->setCursor(Qt::PointingHandCursor);
        btn->setFixedSize(150, 150);
        btn->setStyleSheet("QPushButton{background-color:" + boxes.at(it)->cssColor() + "}");
        boxesLayout->addWidget(btn, it/3, it%3);
        GameController *gc = new GameController(boxes.at(it));
        controllers.push_back(gc);
        QObject::connect(btn, SIGNAL(clicked(bool)), gc, SLOT(react()));
    }
    scrollableWidget->setLayout(boxesLayout);
    scrollableArea = new QScrollArea;
    scrollableArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollableArea->setWidget(scrollableWidget);
    mainLayout->addWidget(scrollableArea, 0, 0);
    setLayout(mainLayout);
}
