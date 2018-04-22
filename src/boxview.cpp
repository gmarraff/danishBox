#include "boxview.h"
#include "danishbox.h"
#include "kiddo.h"
#include "grandma.h"
#include "gamecontroller.h"
#include "quisquilia.h"
#include "sewingtool.h"
#include "danish.h"
#include <QListWidgetItem>
#include <QIntValidator>
#include <QMessageBox>
#include <QLabel>

BoxView::BoxView(Box* bx, User *usr, GameController* ngc, QWidget *parent) : QWidget(parent), box(bx), loggedUser(usr), gc(ngc)
{
    setWindowTitle("Scatola " + GameController::typeHelper(box->type())+ " " + boxCapacityStr());
    mainLayout = new QGridLayout;
    itemsList = new QListWidget;
    mainLayout->addWidget(new QLabel("<strong>" + box->itemHeader() + "</strong>"), 0, 0);
    for(auto it = box->begin(); it != box->end(); ++it){
        QListWidgetItem *lwi = new QListWidgetItem(it.item()->infoLine());
        lwi->setIcon(QIcon(it.item()->iconPath()));
        lwi->setData(Qt::UserRole, it.item()->code);
        itemsList->addItem(lwi);
    }
    mainLayout->addWidget(itemsList, 1, 0);
    if(dynamic_cast<DanishBox*>(box)) danishMenu();
    else standardMenu();
    setLayout(mainLayout);
}
void BoxView::closeEvent(QCloseEvent *event){
    Item::saveAll();
    Box::saveAll();
}

void BoxView::danishMenu(){
    int lastRow = 1;
    if(!box->empty()){
        eatDanishButton = new QPushButton("Mangia");
        eatDanishButton->setEnabled(!box->empty());
        mainLayout->addWidget(eatDanishButton, 2, 0);
        QObject::connect(eatDanishButton, SIGNAL(clicked()), this, SLOT(eatCookie()));
        lastRow = 2;
    }
    if(!dynamic_cast<::Kiddo*>(loggedUser)){
        danishCode = new QLineEdit;
        danishCode->setPlaceholderText("Codice");
        danishDimension = new QLineEdit;
        danishDimension->setPlaceholderText("Dimensione");
        danishDimension->setValidator(new QIntValidator());
        cookDanishButton = new QPushButton("Cucina");
        mainLayout->addWidget(new QLabel("-------------"), lastRow+1, 0);
        mainLayout->addWidget(danishCode, lastRow+2, 0);
        mainLayout->addWidget(danishDimension, lastRow+3, 0);
        mainLayout->addWidget(cookDanishButton, lastRow+4, 0);
        QObject::connect(cookDanishButton, SIGNAL(clicked()), this, SLOT(cookDanish()));
    }
}
QString BoxView::boxCapacityStr() const{
    if(box)
        return QString::number(box->getSize()) + "/" + QString::number(box->getCapacity());
    else
        return "";
}
void BoxView::boxFullMessage() const{
    QMessageBox itemNotAllowed;
    itemNotAllowed.setWindowTitle("Scatola piena");
    itemNotAllowed.setText("Hai riempito la scatola, rimuovi qualche oggetto per aggiungerne altri.");
    itemNotAllowed.exec();
}

void BoxView::enablePickButton(){
    if(pickItemButton) pickItemButton->setEnabled(!box->empty() && itemsList->currentItem());
}
void BoxView::enableInsertButton(){
    if(insertItemButton && cauldron) insertItemButton->setEnabled(!box->full() && cauldron->currentItem());;
}

void BoxView::standardMenu(){
    int lastRow = 1;
    if(box->empty()){
        danishMenu();
        lastRow = 6;
    }
    pickItemButton = new QPushButton("Togli oggetto");
    insertItemButton = new QPushButton("Inserisci oggetto");
    cauldron = new QListWidget;
    loadCauldron();
    enablePickButton();
    enableInsertButton();
    searchBar = new QLineEdit;
    searchBar->setPlaceholderText("Termine di ricerca");
    mainLayout->addWidget(pickItemButton, lastRow+1, 0);
    mainLayout->addWidget(searchBar, lastRow+2, 0);
    mainLayout->addWidget(cauldron, lastRow+3, 0);
    mainLayout->addWidget(insertItemButton, lastRow+4, 0);
    QObject::connect(itemsList, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), this, SLOT(enablePickButton()));
    QObject::connect(cauldron, SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)), this, SLOT(enableInsertButton()));
    QObject::connect(pickItemButton, SIGNAL(clicked()), this, SLOT(pickItem()));
    QObject::connect(searchBar, SIGNAL(textChanged(QString)), this, SLOT(loadCauldron(QString)));
    QObject::connect(insertItemButton, SIGNAL(clicked(bool)), this, SLOT(insertItem()));
}
void BoxView::eatCookie(){
    box->popItem();
    box->updateItems();
    itemsList->takeItem(box->getSize());
    setWindowTitle("Scatola " + GameController::typeHelper(box->type())+ " " + boxCapacityStr());
    if(box->empty()){
        gc->react();
        this->close();
    }
}
void BoxView::cookDanish(){
    QString code(danishCode->text()), dimension(danishDimension->text());
    if(code.isEmpty() || dimension.isEmpty()) return;
    Danish* dn = new Danish(code, dimension.toInt() , dynamic_cast<::Grandma*>(loggedUser));
    try{
        box->pushItem(dn);
        box->updateItems();
        itemsList->addItem(new QListWidgetItem(QIcon(dn->iconPath()), dn->infoLine()));
        setWindowTitle("Scatola " + GameController::typeHelper(box->type())+ " " + boxCapacityStr());
    }catch(Box::BoxFull){
        boxFullMessage();
    }

    danishCode->clear();
    danishDimension->clear();
    if(box->getSize() == 1){
        gc->react();
        this->close();
    }
    else
        eatDanishButton->setEnabled(true);
}
void BoxView::pickItem(){
    QListWidgetItem* lwi = itemsList->currentItem();
    if(!lwi) return;
    QString code = lwi->data(Qt::UserRole).toString();
    Item* removed = box->popByCode(code);
    if(removed){
        box->updateItems();
        removed->insert();
        QListWidgetItem *toCauldron = itemsList->takeItem(itemsList->row(lwi));
        toCauldron->setData(Qt::UserRole, QVariant::fromValue((void*)removed));
        cauldron->addItem(toCauldron);
        setWindowTitle("Scatola " + GameController::typeHelper(box->type())+ " " + boxCapacityStr());
        if(box->getSize() == 0){
            gc->react();
            this->close();
        }
    }
}
void BoxView::insertItem(){
    QListWidgetItem* lwi = cauldron->currentItem();
    if(!lwi) return;
    Item* item = (Item*)lwi->data(Qt::UserRole).value<void *>();
    if(item){
        try{
            if(box->pushItem(item)){
                item->remove();
                box->updateItems();
                QListWidgetItem *toBox = cauldron->takeItem(cauldron->row(lwi));
                toBox->setData(Qt::UserRole, item->code);
                itemsList->addItem(toBox);
                setWindowTitle("Scatola " + GameController::typeHelper(box->type())+ " " + boxCapacityStr());
                if(box->getSize() == 1){
                    gc->react();
                    this->close();
                }
            }else{
                QMessageBox itemNotAllowed;
                itemNotAllowed.setWindowTitle("Non autorizzato!");
                itemNotAllowed.setText("Il tipo di oggetto non è valido per questa scatola.");
                itemNotAllowed.exec();
            }
        }catch(Box::BoxFull){
            boxFullMessage();
        }
    }
}
void BoxView::loadCauldron(QString searchTerm){
    if(!cauldron) return;
    cauldron->clear();
    QVector<Item*> items = loggedUser->availableItems();
    for(int it = 0; it < items.size(); ++it){
        Item *item = items.at(it);
        QString name("");
        if(dynamic_cast<Quisquilia*>(item)) name = (static_cast<Quisquilia*>(item))->name;
        if(dynamic_cast<SewingTool*>(item)) name = (static_cast<SewingTool*>(item))->name;
        if(searchTerm.size() < 3 ||
                (searchTerm.size() >= 3 &&
                        (name.contains(searchTerm, Qt::CaseInsensitive) ||
                         item->code.contains(searchTerm, Qt::CaseInsensitive)))){
            QListWidgetItem *lwi = new QListWidgetItem(item->infoLine());
            lwi->setIcon(QIcon(item->iconPath()));
            lwi->setData(Qt::UserRole, QVariant::fromValue((void*)item));
            cauldron->addItem(lwi);
        }
    }
}
