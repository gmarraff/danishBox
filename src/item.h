#ifndef ITEM_H
#define ITEM_H
#include "jsonmanager.h"
#include <QJsonObject>
class Item: public JsonManager{
public:
    static QJsonArray storage;
    static QString path;
    static bool saveAll();
    QString code;
    Item(QString="", int = -1);
    virtual ~Item(); 
    virtual QString infoLine() const;
    virtual QString iconPath() const;
    QJsonObject toJson() const override;
    bool checkUniq() const override;
    QString boolStr(bool) const;
    QString filename() const;
    QJsonArray* getStorage() const;
    static Item* fromJson(QJsonObject obj);
    enum Type{Quisquilia, Danish, Sewing, Default};
    virtual Type getType() const;
};
#endif
