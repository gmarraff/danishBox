#include "box.h"
#ifndef SEWINGBOX_H
#define SEWINGBOX_H
class SewingBox: public Box{
public:
    SewingBox(Box* box);
    Type type() const override;
    bool pushItem(Item*) override;
    QString itemHeader() const override;
};
#endif
