#include "adminui.h"
#include "admin.h"

AdminUI::AdminUI(User* usr, QWidget* parent): authUI(usr, parent)
{
}
bool AdminUI::authorized() const{
    return (dynamic_cast<Admin*>(loggedUser));
}
