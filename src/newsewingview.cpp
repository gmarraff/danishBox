#include "newsewingview.h"
#include "admin.h"
#include "grandma.h"
#include "sewingtool.h"
#include <QIntValidator>

NewSewingView::NewSewingView(User* usr, QWidget *parent) : authUI(usr, parent)
{
    init();
}
bool NewSewingView::authorized()const{
    return (dynamic_cast<Admin*>(loggedUser) || dynamic_cast<Grandma*>(loggedUser));
}
void NewSewingView::notAuthorizedUI(){}
void NewSewingView::authorizedUI(){
    codeLine = new QLineEdit;
    nameLine = new QLineEdit;
    utilityLine = new QLineEdit;
    utilityLine->setValidator(new QIntValidator(0, 100));
    insertButton = new QPushButton("Crea");
    resultLabel = new QLabel;
    mainLayout->addWidget(new QLabel("Codice:"), 0, 0);
    mainLayout->addWidget(codeLine, 0, 1);
    mainLayout->addWidget(new QLabel("Nome:"), 1, 0);
    mainLayout->addWidget(nameLine, 1, 1);
    mainLayout->addWidget(new QLabel("Utilità: "), 2, 0);
    mainLayout->addWidget(utilityLine, 2, 1);
    mainLayout->addWidget(insertButton, 3, 0, 1, 2, Qt::AlignHCenter);
    mainLayout->addWidget(resultLabel, 4, 0, 1, 2, Qt::AlignHCenter);
    QObject::connect(insertButton, SIGNAL(clicked()), this, SLOT(insertSewingTool()));
}
void NewSewingView::insertSewingTool(){
    QString code = codeLine->text(), name = nameLine->text(), utility = utilityLine->text();
    if(code.isEmpty() || name.isEmpty() || utility.isEmpty())
        resultLabel->setText("<p style='color:red'>Compilare tutti i campi.</p>");
    else{
        SewingTool* sewing = new SewingTool(code, name, utility.toInt());
        if(sewing->create()){
            resultLabel->setText("<p style='color:green'>Attrezzo da cucito inserito correttamente.</p>");
            codeLine->clear();
            nameLine->clear();
            utilityLine->clear();
        }
        else{
           resultLabel->setText("<p style='color:red'>Esiste già un oggetto con lo stesso codice.</p>");
        }
    }
}
