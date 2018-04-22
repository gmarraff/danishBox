#include "admin.h"
#include <QJsonObject>
Admin::Admin()
{

}
Admin::Admin(User* usr): User(*usr){}
QString Admin::iconPath() const{
    return "icons/users/admin.png";
}
QVector<User*> Admin::availableUsers() const{
    QJsonArray *allUsers = getStorage();
    QVector<User*> users;
    for(int it = 0; it < allUsers->size(); ++it){
        try{
            User* user = User::fromJson(allUsers->at(it).toObject());
            users.push_back(user);
        }
        catch(JsonManager::ObjectNotValid){}
    }
    return users;
}
QVector<Item*> Admin::availableItems() const{
    QJsonArray *allItems = (new Item("", -1))->getStorage();
    QVector<Item*> items;
    for(int it = 0; it < allItems->size(); ++it){
        try{
            items.push_back(Box::jsonItem(allItems->at(it).toObject()));
        }catch(JsonManager::ObjectNotValid){}
    }
    return items;
}
::User::Type Admin::role() const{
    return ::User::Admin;
}
