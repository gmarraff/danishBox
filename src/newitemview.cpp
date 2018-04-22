#include "newitemview.h"
#include "item.h"
#include <QLabel>

NewItemView::NewItemView(User* usr, QWidget *parent) : authUI(usr, parent)
{
    init();
    setWindowTitle("Crea oggetti");
}
bool NewItemView::authorized() const{
    return loggedUser;
}
void NewItemView::authorizedUI(){
    nqv = new newQuisquiliaView(loggedUser);
    nsv = new NewSewingView(loggedUser);
    mainLayout->addWidget(new QLabel("<strong>Inserisci giocattolo</strong>"), 0, 0);
    mainLayout->addWidget(nqv, 1, 0);
    mainLayout->addWidget(new QLabel("---------------------------"), 2, 0);
    mainLayout->addWidget(new QLabel("<strong>Inserisci attrezzo da cucito</strong>"), 3, 0);
    mainLayout->addWidget(nsv, 4, 0);
}
void NewItemView::closeEvent(QCloseEvent *event){
    Item::saveAll();
}
