#ifndef SEWINGTOOL_H
#define SEWINGTOOL_H
#include "item.h"
class SewingTool: public Item{
public:
    QString name;
    int utility;
    SewingTool(QString="",QString="",int=50, int=-1);
    ~SewingTool();
    void setUtility(int);
    QString infoLine() const override;
    static SewingTool* fromJson(QJsonObject obj);
    QString iconPath() const override;
    QJsonObject toJson() const override;
    Type getType() const override;
};
#endif
