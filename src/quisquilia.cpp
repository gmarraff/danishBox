#include "quisquilia.h"
#include <iostream>
Quisquilia::Quisquilia(QString cd, QString n, bool a, int idx): Item(cd, idx), name(n), affective(a){}
Quisquilia::~Quisquilia(){}
QString Quisquilia::infoLine() const{
    QString info = Item::infoLine();
    info += ", " + name;
    info += ", " + boolStr(affective);
	return info;
}
Quisquilia* Quisquilia::fromJson(QJsonObject obj){
    if(obj["code"].isNull() ||
            obj["id"].isNull() ||
            obj["name"].isNull() ||
            obj["affective"].isNull())
        throw JsonManager::ObjectNotValid();
    else
        return new Quisquilia(obj["code"].toString(), obj["name"].toString(), obj["affective"].toBool(), obj["id"].toInt());
}
QString Quisquilia::iconPath() const{
    return "icons/items/quisquilia.png";
}
QJsonObject Quisquilia::toJson()const{
    QJsonObject obj = Item::toJson();
    obj["name"] = name;
    obj["affective"] = affective;
    return obj;
}
Item::Type Quisquilia::getType() const{
    return Item::Quisquilia;
}
