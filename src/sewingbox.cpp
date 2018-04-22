#include "sewingbox.h"
#include "sewingtool.h"
SewingBox::SewingBox(Box *box): Box(*box){}
Box::Type SewingBox::type() const{
	return Box::Type::Sewing;
}
bool SewingBox::pushItem(Item* source){
    if(dynamic_cast<::SewingTool*>(source)) return Box::pushItem(source);
	return false;
}
QString SewingBox::itemHeader() const{
    return Box::itemHeader() + ", Nome, Utilità";
}
