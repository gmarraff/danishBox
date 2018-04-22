#include "throwboxesview.h"
#include <QLabel>
#include "admin.h"
#include "grandma.h"
#include "box.h"

ThrowBoxesView::ThrowBoxesView(User* usr, QWidget *parent): authUI(usr, parent)
{
    setWindowTitle("Butta scatole");
    init();
}
bool ThrowBoxesView::authorized() const{
    return (dynamic_cast<Admin*>(loggedUser) || dynamic_cast<Grandma*>(loggedUser));
}
void ThrowBoxesView::authorizedUI(){
    boxesList = new QListWidget;
    QVector<Box*> boxes = Box::getAll();
    auto it = boxes.begin();
    for(;it != boxes.end(); ++it){
        QListWidgetItem *lwi = new QListWidgetItem((*it)->infoLine());
        lwi->setData(Qt::UserRole, QVariant::fromValue((void*)(*it)));
        boxesList->addItem(lwi);
    }
    throwButton = new QPushButton("Butta");
    throwButton->setEnabled(false);
    mainLayout->addWidget(new QLabel("<strong>"+Box::header()+"</strong>"), 0, 0);
    mainLayout->addWidget(boxesList, 1, 0);
    mainLayout->addWidget(throwButton, 2, 0);
    QObject::connect(boxesList, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), this, SLOT(enableThrowButton()));
    QObject::connect(throwButton, SIGNAL(clicked()), this, SLOT(throwBox()));
}
void ThrowBoxesView::closeEvent(QCloseEvent *event){
    Box::saveAll();
}

void ThrowBoxesView::enableThrowButton(){
    if(throwButton) throwButton->setEnabled(boxesList->currentItem());
}
void ThrowBoxesView::throwBox(){
    QListWidgetItem* lwi = boxesList->currentItem();
    if(!lwi) return;
    Box* box = (Box*)lwi->data(Qt::UserRole).value<void *>();
    box->remove();
    delete boxesList->takeItem(boxesList->row(lwi));
}
