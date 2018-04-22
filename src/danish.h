#ifndef DANISH_H
#define DANISH_H
#include "item.h"
class Danish: public Item{
private:
	int dimension;
	bool good;
public:
    Danish(QString = "", int=0, bool=true, int = -1);
    ~Danish();
    QString goodStr() const;
    QString infoLine() const override;
    static Danish* fromJson(QJsonObject obj);
    QString iconPath() const override;
    QJsonObject toJson() const override;
    Type getType() const override;
};
#endif
