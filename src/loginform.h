#ifndef LOGINFORM_H
#define LOGINFORM_H
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include "clickablelabel.h"
#include "user.h"

class LoginForm: public QWidget{
    Q_OBJECT
private:
    QLineEdit *username, *password;
    QPushButton *loginBtn;
    ClickableLabel *registerLabel;
    QLabel *loginLabel;
protected:
    void keyPressEvent(QKeyEvent *event) override;
public:
    LoginForm(QWidget *parent=0);
    ~LoginForm();
public slots:
    void signUpClicked();
    void loginClicked();
signals:
    void goToSignUp();
    void userLogged(User* usr);
};

#endif // LOGINFORM_H
