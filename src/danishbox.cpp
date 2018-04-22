#include "danishbox.h"
#include "danish.h"
DanishBox::DanishBox(Box* box): Box(*box){}
Box::Type DanishBox::type() const{
	return Box::Danish;
}
bool DanishBox::pushItem(Item* source){
    if(dynamic_cast<::Danish*>(source)) return Box::pushItem(source);
	return false;
}
QString DanishBox::itemHeader() const{
    return Box::itemHeader() + ", Dimensione, Buono?";
}
