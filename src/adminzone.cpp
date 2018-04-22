#include "adminzone.h"
#include "admin.h"
#include <QLabel>
#include <QJsonObject>
int AdminZone::columnsNumber = 5;
AdminZone::AdminZone(User* usr, QWidget *parent) : AdminUI(usr, parent){
    setWindowTitle("Gestisci Utenti");
    init();
}
void AdminZone::authorizedUI(){
    resize(500, 500);
    managedUsers = loggedUser->availableUsers();
    mainLayout->addWidget(new QLabel("<strong>Nome</strong>"),0, 0);
    mainLayout->addWidget(new QLabel("<strong>Cognome</strong>"),0, 1);
    mainLayout->addWidget(new QLabel("<strong>Username</strong>"),0, 2);
    mainLayout->addWidget(new QLabel("<strong>Modifica ruolo</strong>"),0, 3);
    for(int it = 0; it < managedUsers.size(); ++it){
        User* usr = managedUsers[it];
        QComboBox *cbo = roleCboBox(usr);
        cboBoxes.push_back(cbo);
        mainLayout->addWidget(new QLabel(usr->getName()), it+1, 0);
        mainLayout->addWidget(new QLabel(usr->getSurname()), it+1, 1);
        mainLayout->addWidget(new QLabel(usr->getUsername()), it+1, 2);
        mainLayout->addWidget(cbo, it+1, 3);
        AdminZoneController* ac = new AdminZoneController(usr,it+1);
        controllers.push_back(ac);
        QObject::connect(cbo, SIGNAL(currentIndexChanged(int)), ac, SLOT(changeType(int)));
        QPushButton *btn = new QPushButton("Elimina");
        mainLayout->addWidget(btn,it+1, 4);
        QObject::connect(btn, SIGNAL(clicked()), ac,SLOT(removeUser()));
        QObject::connect(ac, SIGNAL(rowRemoved(int, QJsonObject)), this, SLOT(hideRow(int, QJsonObject)));
    }
    saveButton = new QPushButton("Salva");
    mainLayout->addWidget(saveButton, managedUsers.size() + 1, 0, 1, columnsNumber, Qt::AlignHCenter);
    QObject::connect(saveButton, SIGNAL(clicked()),this, SLOT(saveUsers()));
    saveLabel = new QLabel;
    mainLayout->addWidget(saveLabel, managedUsers.size() + 2, 0, 1, columnsNumber, Qt::AlignHCenter);
}
QComboBox* AdminZone::roleCboBox(User* usr){
    QComboBox* cbo = new QComboBox();
    cbo->addItem("Admin", ::User::Admin);
    cbo->addItem("Ragazzo", ::User::Kiddo);
    cbo->addItem("Nonna", ::User::Grandma);
    cbo->setCurrentIndex(usr->role());
    return cbo;
}
void AdminZone::saveUsers(){
    if(User::saveAll()){
        removedUsers.clear();
        saveLabel->setText("<p style='color:green'>Salvataggio avvenuto con successo.</p>");
    }
    else
        saveLabel->setText("<p style='color:red'>Errore nel salvare gli elementi.</p>");
}
void AdminZone::hideRow(int row, QJsonObject usr){
    removedUsers.push_back(usr);
    for(int col = 0; col < columnsNumber; ++col)
        mainLayout->itemAtPosition(row, col)->widget()->hide();
}
void AdminZone::closeEvent(QCloseEvent *event){
    QVector<QJsonObject>::iterator it = removedUsers.begin();
    for(;it != removedUsers.end(); ++it){
        int memId = it->take("memId").toInt();
        User::put(memId, (*it));
        removedUsers.erase(it);
        --it;
    }
}
