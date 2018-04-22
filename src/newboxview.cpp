#include "newboxview.h"
#include "box.h"
#include <QIntValidator>

NewBoxView::NewBoxView(User* usr, QWidget *parent) : AdminUI(usr, parent)
{
    setWindowTitle("Crea nuova scatola");
    init();
}
void NewBoxView::clearFields(){
    codeLine->clear();
    capacityLine->clear();
}
void NewBoxView::authorizedUI(){
    codeLine = new QLineEdit;
    capacityLine = new QLineEdit;
    capacityLine->setValidator(new QIntValidator(1, Box::MAX_CAPACITY));
    colorCbo = new QComboBox;
    //Red, Blue, Green, Yellow, Orange, Purple
    colorCbo->addItem("Rosso", Box::Red);
    colorCbo->addItem("Blu", Box::Blue);
    colorCbo->addItem("Verde", Box::Green);
    colorCbo->addItem("Giallo", Box::Yellow);
    colorCbo->addItem("Arancione", Box::Orange);
    colorCbo->addItem("Viola", Box::Purple);
    insertButton = new QPushButton("Crea");
    resultLabel = new QLabel("");
    mainLayout->addWidget(new QLabel("Codice:"), 0, 0);
    mainLayout->addWidget(codeLine, 0, 1);
    mainLayout->addWidget(new QLabel("Capacità:"), 1, 0);
    mainLayout->addWidget(capacityLine, 1, 1);
    mainLayout->addWidget(new QLabel("Colore:"), 2, 0);
    mainLayout->addWidget(colorCbo, 2, 1);
    mainLayout->addWidget(insertButton, 3, 0, 1, 2, Qt::AlignHCenter);
    mainLayout->addWidget(resultLabel, 4, 0, 1, 2, Qt::AlignHCenter);
    QObject::connect(insertButton, SIGNAL(clicked(bool)), this, SLOT(addBox()));
}
void NewBoxView::closeEvent(QCloseEvent *event){
    Box::saveAll();
}

void NewBoxView::addBox(){
    QString code = codeLine->text(), capacity = capacityLine->text();
    Box::Color color = Box::Color(colorCbo->currentData().toInt());
    if(code.isEmpty() || capacity.isEmpty())
        resultLabel->setText("<p style='color:red'>Compilare tutti i campi.</p>");
    else{
        Box* box = new Box(color, code, capacity.toInt());
        if(box->create()){
            resultLabel->setText("<p style='color:green'>Scatola inserita correttamente.</p>");
            clearFields();
        }
        else{
           resultLabel->setText("<p style='color:red'>Esiste già una scatola con lo stesso codice.</p>");
        }
    }
}

