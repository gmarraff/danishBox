#ifndef NEWQUISQUILIAVIEW_H
#define NEWQUISQUILIAVIEW_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include "authui.h"

class newQuisquiliaView : public authUI
{
    Q_OBJECT
private:
    QLineEdit *codeLine, *nameLine;
    QComboBox *affectiveCbo;
    QPushButton *insertButton;
    QLabel *resultLabel;
protected:
    bool authorized() const override;
    void authorizedUI() override;
    void notAuthorizedUI() override;
public:
    explicit newQuisquiliaView(User* usr, QWidget *parent = 0);

signals:

public slots:
    void insertQuisquilia();
};

#endif // NEWQUISQUILIAVIEW_H
