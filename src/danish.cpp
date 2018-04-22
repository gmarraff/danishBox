#include "danish.h"

Danish::Danish(QString cd, int d, bool g, int idx): Item(cd, idx), dimension(d), good(g){}
QString Danish::goodStr() const{
	return boolStr(good);
}
Danish::~Danish(){}
QString Danish::infoLine() const{
    QString infoline = Item::infoLine();
    infoline += ", " + QString::number(dimension);
    infoline += ", " + goodStr();
	return infoline;
}
Danish* Danish::fromJson(QJsonObject obj){
    if(obj["code"].isNull() ||
            obj["dimension"].isNull() ||
            obj["good"].isNull() ||
            obj["id"].isNull())
        throw JsonManager::ObjectNotValid();
    else
        return new Danish(obj["code"].toString(), obj["dimension"].toInt(), obj["good"].toBool(), obj["id"].toInt());
}
QString Danish::iconPath() const{
    return "icons/items/danish.png";
}
QJsonObject Danish::toJson() const{
    QJsonObject obj = Item::toJson();
    obj["dimension"] = dimension;
    obj["good"] = good;
    return obj;
}
Item::Type Danish::getType() const{
    return Item::Danish;
}
