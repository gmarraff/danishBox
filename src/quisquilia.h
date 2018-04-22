#ifndef QUISQUILIA_H
#define QUISQUILIA_H
#include "item.h"
class Quisquilia: public Item{
public:
    QString name;
    bool affective;
    Quisquilia(QString="", QString="", bool=false, int = -1);
    ~Quisquilia();
    QString infoLine() const override;
    static Quisquilia* fromJson(QJsonObject obj);
    QString iconPath() const override;
    QJsonObject toJson() const override;
    Type getType() const override;
};
#endif
