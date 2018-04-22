#ifndef KIDDOBOX_H
#define KIDDOBOX_H
#include "box.h"
class KiddoBox: public Box{
public:
    KiddoBox(Box* box);
	Type type() const override;
	bool pushItem(Item*) override;
    	QString itemHeader() const override;
};
#endif
