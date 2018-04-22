#include "kiddo.h"
#include "quisquilia.h"

Kiddo::Kiddo()
{

}
Kiddo::Kiddo(User *usr): User(*usr){}
QString Kiddo::iconPath() const{
    return "icons/users/kiddo.png";
}
::User::Type Kiddo::role()const{
    return User::Kiddo;
}
QVector<Item*> Kiddo::availableItems() const{
    QJsonArray *allItems = (new Item("", -1))->getStorage();
    QVector<Item*> items;
    for(int it = 0; it < allItems->size(); ++it){
        try{
            Item* item = Box::jsonItem(allItems->at(it).toObject());
            if(dynamic_cast<Quisquilia*>(item)) items.push_back(item);
        }catch(JsonManager::ObjectNotValid){}
    }
    return items;
}
