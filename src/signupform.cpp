#include "signupform.h"
#include <QLabel>

SignUpForm::SignUpForm(QWidget *parent) : QWidget(parent)
{
    this->initializeFields();
    this->setUpUI();
    this->initializeConnectors();
    this->setLayout(mainLayout);
}
void SignUpForm::initializeFields(){
    mainLayout = new QGridLayout;
    usernameLine = new QLineEdit;
    nameLine = new QLineEdit;
    surnameLine = new QLineEdit;
    passwordLine = new  QLineEdit;
    passwordConfirmationLine = new QLineEdit;
    nannyRadio = new QRadioButton("Nonna");
    kiddoRadio = new QRadioButton("Ragazzo");
    errorLabel = new QLabel;
    errorLabel->setStyleSheet("QLabel { color: red; }");
    errorLabel->setAlignment(Qt::AlignCenter);
    signUpButton = new QPushButton("Registrati");
    backToLogin = new ClickableLabel;
    backToLogin->setText("Torna alla pagina di login");
    backToLogin->setStyleSheet("QLabel { color: blue; }");
    backToLogin->setCursor(Qt::PointingHandCursor);
}
void SignUpForm::setUpUI(){
    mainLayout->addWidget(new QLabel("Nome"), 0, 0);
    mainLayout->addWidget(nameLine, 0, 1);

    mainLayout->addWidget(new QLabel("Cognome"), 1, 0);
    mainLayout->addWidget(surnameLine, 1, 1);

    mainLayout->addWidget(new QLabel("Username"), 2, 0);
    mainLayout->addWidget(usernameLine, 2,1);

    passwordLine->setEchoMode(QLineEdit::Password);
    mainLayout->addWidget(new QLabel("Password"), 3, 0);
    mainLayout->addWidget(passwordLine, 3,1);

    passwordConfirmationLine->setEchoMode(QLineEdit::Password);
    mainLayout->addWidget(new QLabel("Conferma Password"), 4, 0);
    mainLayout->addWidget(passwordConfirmationLine, 4,1);

    mainLayout->addWidget(new QLabel("Categoria: "), 5, 0, 1, 2, Qt::AlignHCenter);

    mainLayout->addWidget(nannyRadio, 6, 0, 1, 1, Qt::AlignHCenter);
    nannyRadio->setChecked(true);
    mainLayout->addWidget(kiddoRadio, 6, 1, 1, 1, Qt::AlignHCenter);

    mainLayout->addWidget(signUpButton, 7,0, 1, 2, Qt::AlignCenter);

    mainLayout->addWidget(errorLabel, 9, 0, 1, 2, Qt::AlignHCenter);
    mainLayout->addWidget(backToLogin, 10, 0, 1, 2, Qt::AlignRight);
}
void SignUpForm::initializeConnectors(){
  QObject::connect(signUpButton, SIGNAL(clicked()), this, SLOT(signUpClicked()));
  QObject::connect(backToLogin, SIGNAL(clicked()), this, SLOT(loginClicked()));
}
void SignUpForm::signUpClicked(){
    QString errs("");
    if(nameLine->text().isEmpty() ||
            surnameLine->text().isEmpty() ||
            usernameLine->text().isEmpty() ||
            passwordLine->text().isEmpty()
            )
        errs.append("Compilare tutti i campi.\n");
    if(QString::compare(passwordLine->text(), passwordConfirmationLine->text()) != 0)
        errs.append("Le due password non coincidono.");
    if(errs.compare("") != 0) errorLabel->setText(errs);
    else{
        User* usr = User::signup(usernameLine->text(),
                                 passwordLine->text(),
                                 nameLine->text(),
                                 surnameLine->text(),
                                 (kiddoRadio->isChecked() ? User::Kiddo : User::Grandma)
                                 );
        if(usr) emit userSignedUp(usr);
        else errorLabel->setText("Esiste già un utente con lo stesso username.");

    }
}
void SignUpForm::loginClicked(){
    emit goToLogin();
}
void SignUpForm::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Return)
        signUpClicked();
}
