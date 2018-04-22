#include "authui.h"
#include <QLabel>

authUI::authUI(User* usr, QWidget *parent) : QWidget(parent), loggedUser(usr), mainLayout(new QGridLayout){}
void authUI::init(){
    if(authorized()) authorizedUI();
    else notAuthorizedUI();
    setLayout(mainLayout);
}

bool authUI::authorized() const{
    return false;
}
void authUI::notAuthorizedUI(){
    resize(100,100);
    QLabel *notAuthorizedLabel = new QLabel("Utente non autorizzato.");
    mainLayout->addWidget(notAuthorizedLabel, 0, 0);
}
void authUI::authorizedUI(){}

