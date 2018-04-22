#ifndef DANISHBOX_H
#define DANISHBOX_H
#include "box.h"
class DanishBox: public Box{
public:
    DanishBox(Box* box);
	Type type() const override;
	bool pushItem(Item*) override;
    	QString itemHeader() const override;
};
#endif
