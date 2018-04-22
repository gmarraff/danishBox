#include "newquisquiliaview.h"
#include "admin.h"
#include "kiddo.h"
#include "quisquilia.h"

newQuisquiliaView::newQuisquiliaView(User* usr, QWidget *parent) : authUI(usr, parent)
{
    init();
}
bool newQuisquiliaView::authorized()const{
    return (dynamic_cast<Admin*>(loggedUser) || dynamic_cast<Kiddo*>(loggedUser));
}
void newQuisquiliaView::notAuthorizedUI(){}
void newQuisquiliaView::authorizedUI(){
    codeLine = new QLineEdit;
    nameLine = new QLineEdit;
    affectiveCbo = new QComboBox;
    affectiveCbo->addItem("Si", true);
    affectiveCbo->addItem("No", false);
    insertButton = new QPushButton("Crea");
    resultLabel = new QLabel;
    mainLayout->addWidget(new QLabel("Codice:"), 0, 0);
    mainLayout->addWidget(codeLine, 0, 1);
    mainLayout->addWidget(new QLabel("Nome:"), 1, 0);
    mainLayout->addWidget(nameLine, 1, 1);
    mainLayout->addWidget(new QLabel("Ha valore Affettivo:"), 2, 0);
    mainLayout->addWidget(affectiveCbo, 2, 1);
    mainLayout->addWidget(insertButton, 3, 0, 1, 2, Qt::AlignHCenter);
    mainLayout->addWidget(resultLabel, 4, 0, 1, 2, Qt::AlignHCenter);
    QObject::connect(insertButton, SIGNAL(clicked()), this, SLOT(insertQuisquilia()));
}
void newQuisquiliaView::insertQuisquilia(){
    QString code = codeLine->text(), name = nameLine->text();
    bool affective = affectiveCbo->currentData().toBool();
    if(code.isEmpty() || name.isEmpty())
        resultLabel->setText("<p style='color:red'>Compilare tutti i campi.</p>");
    else{
        Quisquilia* quis = new Quisquilia(code, name, affective);
        if(quis->create()){
            resultLabel->setText("<p style='color:green'>Giocattolo inserito correttamente.</p>");
            codeLine->clear();
            nameLine->clear();
        }
        else{
           resultLabel->setText("<p style='color:red'>Esiste già un oggetto con lo stesso codice.</p>");
        }
    }
}
