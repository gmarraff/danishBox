#include "grandma.h"
#include "sewingtool.h"

Grandma::Grandma()
{

}
Grandma::Grandma(User* usr): User(*usr){}
QString Grandma::iconPath() const{
    return "icons/users/grandma.png";
}
::User::Type Grandma::role() const{
    return ::User::Grandma;
}
QVector<Item*> Grandma::availableItems() const{
    QJsonArray *allItems = (new Item("", -1))->getStorage();
    QVector<Item*> items;
    for(int it = 0; it < allItems->size(); ++it){
        try{
            Item* item = Box::jsonItem(allItems->at(it).toObject());
            if(dynamic_cast<SewingTool*>(item)) items.push_back(item);
        }catch(JsonManager::ObjectNotValid){}
    }
    return items;
}
