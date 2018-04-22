#ifndef SIGNUPFORM_H
#define SIGNUPFORM_H

#include <QWidget>
#include <QLineEdit>
#include <QRadioButton>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QKeyEvent>
#include "clickablelabel.h"
#include "user.h"

class SignUpForm : public QWidget
{
    Q_OBJECT
private:
    QGridLayout *mainLayout;
    QLineEdit *usernameLine, *passwordLine, *passwordConfirmationLine, *nameLine, *surnameLine;
    QRadioButton *nannyRadio, *kiddoRadio;
    QLabel *errorLabel;
    ClickableLabel *backToLogin;
    QPushButton *signUpButton;

    void initializeFields();
    void setUpUI();
    void initializeConnectors();

protected:
    void keyPressEvent(QKeyEvent *event) override;

public:
    explicit SignUpForm(QWidget *parent = 0);

signals:
    void goToLogin();
    void userSignedUp(User* usr);

public slots:
    void signUpClicked();
    void loginClicked();
};

#endif // SIGNUPFORM_H
