#include "welcomeform.h"
#include <QMessageBox>
WelcomeForm::WelcomeForm(QWidget *parent)
    : QMainWindow(parent)
{
    switchToLogin();
}
void WelcomeForm::switchToSignUp(){
    initSignUpForm();
    setWindowTitle("Registrati");
    setCentralWidget(signUpForm);
    resize(500,150);
}
void WelcomeForm::switchToLogin(){
    initLoginForm();
    setWindowTitle("Login");
    setCentralWidget(loginForm);
    resize(500,150);
}
void WelcomeForm::switchToMenu(User* usr){
    QString str = "Benvenuto, ";
    str.append(usr->getName());
    str.append("!");
    initMenuView(usr);
    setWindowTitle(str);
    setCentralWidget(menuView);
    resize(200, 500);
}

void WelcomeForm::initMenuView(User* usr){
    menuView = new MenuView(usr);
    QObject::connect(menuView, SIGNAL(logOut()), this, SLOT(switchToLogin()));
}

void WelcomeForm::initLoginForm(){
    loginForm = new LoginForm();
    QObject::connect(loginForm, SIGNAL(goToSignUp()), this, SLOT(switchToSignUp()));
    QObject::connect(loginForm, SIGNAL(userLogged(User*)), this, SLOT(switchToMenu(User*)));
}
void WelcomeForm::initSignUpForm(){
    signUpForm = new SignUpForm();
    QObject::connect(signUpForm, SIGNAL(goToLogin()), this, SLOT(switchToLogin()));
    QObject::connect(signUpForm, SIGNAL(userSignedUp(User*)), this, SLOT(switchToMenu(User*)));
}

WelcomeForm::~WelcomeForm()
{

}
