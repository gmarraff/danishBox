#ifndef ADMINUI_H
#define ADMINUI_H
#include "authui.h"

class AdminUI : public authUI
{
    Q_OBJECT
public:
    AdminUI(User* usr, QWidget *parent);
protected:
    bool authorized() const override;
};

#endif // ADMINUI_H
