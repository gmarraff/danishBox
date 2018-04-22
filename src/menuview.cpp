#include "menuview.h"
#include "admin.h"
#include "grandma.h"
#include <QLabel>

MenuView::MenuView(User* usr, QWidget *parent) : QWidget(parent), loggedUser(usr)
{
    this->initializeFields();
    this->setUpUI();
    this->initializeConnectors();
    this->setLayout(mainLayout);
}
void MenuView::initializeFields(){
    mainLayout = new QGridLayout;
    logOutButton = new QPushButton("Logout");
    openBoxesButton = new QPushButton("Apri scatole");
    createItemsButton = new QPushButton("Crea oggetti");
    usrTypeImage = new QPixmap(loggedUser->iconPath());
}
void MenuView::setUpUI(){
    QLabel *imageLabel = new QLabel;
    imageLabel->setPixmap(usrTypeImage->scaled(QSize(150, 150), Qt::IgnoreAspectRatio, Qt::FastTransformation));
    mainLayout->addWidget(imageLabel, 0, 0, 1, 1, Qt::AlignHCenter);
    mainLayout->addWidget(openBoxesButton, 1, 0, 1, 1, Qt::AlignHCenter);
    mainLayout->addWidget(createItemsButton, 2, 0, 1, 1, Qt::AlignHCenter);
    int logOutRow = 3;
    if(dynamic_cast<Admin*>(loggedUser)){
        createBoxesButton = new QPushButton("Crea scatole");
        mainLayout->addWidget(createBoxesButton, 3, 0, 1, 1, Qt::AlignHCenter);
        QObject::connect(createBoxesButton, SIGNAL(clicked()), this, SLOT(openCreateBoxes()));
        adminButton = new QPushButton("Gestisci Utenti");
        mainLayout->addWidget(adminButton, 4, 0, 1, 1, Qt::AlignHCenter);
        QObject::connect(adminButton, SIGNAL(clicked()), this, SLOT(openAdminZone()));
        logOutRow += 2;
    }
    if(dynamic_cast<Admin*>(loggedUser) || dynamic_cast<Grandma*>(loggedUser)){
        throwBoxesButton = new QPushButton("Butta scatole");
        mainLayout->addWidget(throwBoxesButton, logOutRow, 0, 1, 1, Qt::AlignHCenter);
        QObject::connect(throwBoxesButton, SIGNAL(clicked()), this, SLOT(openThrowBoxes()));
        logOutRow += 1;
    }
    mainLayout->addWidget(logOutButton, logOutRow, 0, 1, 1, Qt::AlignHCenter);
}

void MenuView::initializeConnectors(){
    QObject::connect(logOutButton, SIGNAL(clicked()), this, SLOT(logOutClicked()));
    QObject::connect(openBoxesButton, SIGNAL(clicked()), this, SLOT(openGame()));
    QObject::connect(createItemsButton, SIGNAL(clicked()), this, SLOT(openCreateItems()));
}
void MenuView::openAdminZone(){
    adminZone = new AdminZone(loggedUser);
    adminZone->show();
}
void MenuView::openGame(){
    game = new BoxGame(loggedUser);
    game->show();
}
void MenuView::openCreateBoxes(){
    boxView = new NewBoxView(loggedUser);
    boxView->show();
}
void MenuView::openCreateItems(){
    itemView = new NewItemView(loggedUser);
    itemView->show();
}
void MenuView::openThrowBoxes(){
    throwBoxesView = new ThrowBoxesView(loggedUser);
    throwBoxesView->show();
}

void MenuView::logOutClicked(){
    emit logOut();
}
