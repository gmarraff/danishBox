#ifndef WELCOMEFORM_H
#define WELCOMEFORM_H

#include <QMainWindow>
#include "loginform.h"
#include "signupform.h"
#include "menuview.h"
#include "user.h"

class WelcomeForm : public QMainWindow
{
    Q_OBJECT
private:
    LoginForm *loginForm;
    SignUpForm *signUpForm;
    MenuView *menuView;
public:
    WelcomeForm(QWidget *parent = 0);
    ~WelcomeForm();
    void initLoginForm();
    void initSignUpForm();
    void initMenuView(User* usr);

public slots:
    void switchToSignUp();
    void switchToLogin();
    void switchToMenu(User* usr);
};

#endif // WELCOMEFORM_H
