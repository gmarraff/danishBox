#include "item.h"
QString Item::path = "storage/items.json";
QJsonArray Item::storage = JsonManager::loadFile(Item::path);
bool Item::saveAll(){
    return JsonManager::saveFile(Item::storage, Item::path);
}

Item::Item(QString cd, int idx): code(cd){
    id = idx;
}
Item::~Item(){}
QString Item::infoLine() const{
    return code;
}
QString Item::iconPath() const{
    return "icons/items/item.png";
}
QString Item::boolStr(bool value) const{
    return (value ? "Si" : "No");
}
Item* Item::fromJson(QJsonObject obj){
    if(obj["code"].isNull() || obj["id"].isNull()) throw JsonManager::ObjectNotValid();
    return new Item(obj["code"].toString(), obj["id"].toInt());
}
QString Item::filename() const{
    return Item::path;
}
QJsonArray* Item::getStorage() const{
    return &Item::storage;
}
QJsonObject Item::toJson() const{
    QJsonObject obj = JsonManager::toJson();
    obj["code"] = code;
    obj["type"] = getType();
    return obj;
}
bool Item::checkUniq() const{
    QJsonArray *items = getStorage();
    for(int it = 0; it < items->size(); ++it)
        if(items->at(it).toObject()["code"].toString().compare(code) == 0)
            return false;
    return true;
}
Item::Type Item::getType() const{
    return Item::Default;
}
