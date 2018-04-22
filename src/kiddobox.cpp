#include "kiddobox.h"
#include "quisquilia.h"
KiddoBox::KiddoBox(Box *box): Box(*box){}
Box::Type KiddoBox::type() const{
	return Box::Type::Quisquilia;
}
bool KiddoBox::pushItem(Item* source){
    if(dynamic_cast<::Quisquilia*>(source)) return Box::pushItem(source);
	return false;
}
QString KiddoBox::itemHeader() const{
    return Box::itemHeader() + ", Nome, Ha valore affettivo?";
}
