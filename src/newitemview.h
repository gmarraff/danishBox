#ifndef NEWITEMVIEW_H
#define NEWITEMVIEW_H

#include "authui.h"
#include "newquisquiliaview.h"
#include "newsewingview.h"

class NewItemView : public authUI
{
    Q_OBJECT
private:
    newQuisquiliaView* nqv;
    NewSewingView *nsv;
public:
    explicit NewItemView(User* usr,QWidget *parent = 0);
protected:
    bool authorized() const override;
    void authorizedUI() override;
    void closeEvent(QCloseEvent *event) override;
signals:

public slots:
};

#endif // NEWITEMVIEW_H
