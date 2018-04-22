#include "sewingtool.h"
SewingTool::SewingTool(QString cd, QString n, int u, int idx): Item(cd, idx), name(n){
	setUtility(u);
}
SewingTool::~SewingTool(){}
void SewingTool::setUtility(int u){
	if(u < 0) utility = 0;
	else if(u > 100) utility = 100;
	else utility = u;
}
QString SewingTool::infoLine() const{
    QString infoline = Item::infoLine();
    infoline += ", " + name;
    infoline += ", " + QString::number(utility);
	return infoline;
}
SewingTool* SewingTool::fromJson(QJsonObject obj){
    if(obj["code"].isNull() ||
            obj["id"].isNull() ||
            obj["name"].isNull() ||
            obj["utility"].isNull())
        throw JsonManager::ObjectNotValid();
    else
        return new SewingTool(obj["code"].toString(), obj["name"].toString(), obj["utility"].toInt(), obj["id"].toInt());
}
QString SewingTool::iconPath() const{
    return "icons/items/sewingtool.svg";
}
QJsonObject SewingTool::toJson() const{
    QJsonObject obj = Item::toJson();
    obj["name"] = name;
    obj["utility"] = utility;
    return obj;
}
Item::Type SewingTool::getType() const{
    return Item::Sewing;
}
