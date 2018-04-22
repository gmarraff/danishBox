#include "loginform.h"
#include "user.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QKeyEvent>

LoginForm::LoginForm(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *mainLayout;
    QHBoxLayout *userRow, *pswRow, *buttonRow, *registerRow;
    //Riga username
    userRow = new QHBoxLayout();
    QLabel *userLabel = new QLabel("Username");
    username = new QLineEdit();
    userRow->addWidget(userLabel);
    userRow->addWidget(username);

    //Riga Password
    pswRow = new QHBoxLayout();
    QLabel *pswLabel = new QLabel("Password");
    password = new QLineEdit();
    password->setEchoMode(QLineEdit::Password);
    pswRow->addWidget(pswLabel);
    pswRow->addWidget(password);

    //Riga bottone
    loginBtn = new QPushButton("Entra");
    buttonRow = new QHBoxLayout();
    buttonRow->addWidget(loginBtn);
    QObject::connect(loginBtn, SIGNAL(clicked()), this, SLOT(loginClicked()));

    //Riga esito login
    loginLabel = new QLabel();
    loginLabel->setAlignment(Qt::AlignCenter);
    QHBoxLayout *loginInfo = new QHBoxLayout();
    loginInfo->addWidget(loginLabel);

    //Riga registrazione
    registerLabel = new ClickableLabel();
    registerLabel->setText("Non sei iscritto?");
    registerLabel->setStyleSheet("QLabel { color: blue; }");
    registerLabel->setCursor(Qt::PointingHandCursor);
    registerRow = new QHBoxLayout();
    registerRow->addWidget(registerLabel);
    QObject::connect(registerLabel, SIGNAL(clicked()), this, SLOT(signUpClicked()));

    mainLayout = new QVBoxLayout();
    mainLayout->addLayout(userRow);
    mainLayout->addLayout(pswRow);
    mainLayout->addLayout(buttonRow);
    mainLayout->addLayout(loginInfo);
    mainLayout->addLayout(registerRow);

    this->setLayout(mainLayout);
}

void LoginForm::signUpClicked(){
    emit goToSignUp();
}
void LoginForm::loginClicked(){
    QString usr = username->text();
    QString psw = password->text();
    User *loggedUser = User::login(usr, psw);
    if(!loggedUser){
        loginLabel->setStyleSheet("QLabel{ color: red;}");
        loginLabel->setText("Nessun utente compatibile.");
    }else{
        emit userLogged(loggedUser);
    }
}
void LoginForm::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Return)
        loginClicked();
}

LoginForm::~LoginForm(){

}
