#include "box.h"
#include "quisquilia.h"
#include "danish.h"
#include "sewingtool.h"
#include <QJsonObject>
//static vars
QString Box::path = "storage/boxes.json";
QJsonArray Box::storage = JsonManager::loadFile(Box::path);

//inherited members
QString Box::filename() const{
    return QString(Box::path);
}
QJsonArray* Box::getStorage() const{
    return &Box::storage;
}

// node methods
Box::ItemNode::ItemNode(): item(0), next(0){}
Box::ItemNode::ItemNode(const ItemNode& source): 
	item(source.item), next(deepCopy(source.next)){}
Box::ItemNode::ItemNode(Item* source): item(source), next(0){}
Box::ItemNode& Box::ItemNode::operator=(const ItemNode& source){
	if(*this != source){
		ItemNode* aux = this;
		item = source.item;
		next = deepCopy(source.next);
		delete aux;
	}
	return *this;
}
Item* Box::ItemNode::getItem(){
	return item;
}
Box::ItemNode* Box::ItemNode::getNext(){
	return next;
}
bool Box::ItemNode::operator==(const ItemNode& source) const{
	return item == source.item;
}
bool Box::ItemNode::operator!=(const ItemNode& source) const{
	return item != source.item;
}
//BOX Methods
Box::ItemNode* Box::deepCopy(ItemNode* source){
	if(source && source->item){
		ItemNode* destination = new ItemNode(source->item);
		destination->next = deepCopy(source->next);
		return destination;
	}
	return 0;

}
void Box::deepDestruction(ItemNode* source){
	if(source){
		if(source->getNext()) deepDestruction(source->getNext());
		delete source;
	}
}
const unsigned int Box::MAX_CAPACITY = 75;
const unsigned int Box::MIN_CAPACITY = 1;
Box::Box(Color c, QString cd, unsigned int cpt, unsigned int sz, int idx):
    color(c), code(cd), capacity(cpt), size(sz), opened(false), firstItem(0){
    id = idx;
}
Box::Box(const Box& b): color(b.color), code(b.code), capacity(b.capacity), 
	size(b.size), opened(b.opened), firstItem(b.firstItem) {
    id = b.id;
}
Box& Box::operator=(const Box& source){
	if(this != &source){
		Box* aux = this;
		this->code = source.code;
		this->color = source.color;
		this->capacity = source.capacity;
		this->size = source.size;
		this->firstItem = deepCopy(source.firstItem);
		this->opened = source.opened;
        this->id = source.id;
		delete aux;
	}
	return *this;
}
Box::~Box(){
	deepDestruction(firstItem);
}
QString Box::getCode() const{ return code; }
Box::Color Box::getColor() const{ return color; }
unsigned int Box::getCapacity() const{ return capacity; }
unsigned int Box::getSize() const{ return size; }
void Box::setOpened(bool o) { opened = o; }
bool Box::empty() const { return (size == 0); }
bool Box::full() const { return (size == capacity); }
Item* Box::jsonItem(QJsonObject json){
    Item* item;
    switch (json["type"].toInt()) {
    case Item::Quisquilia:
        item = ::Quisquilia::fromJson(json);
        break;
    case Item::Sewing:
        item = ::SewingTool::fromJson(json);
        break;
    case Item::Danish:
        item = ::Danish::fromJson(json);
        break;
    default:
        item = ::Item::fromJson(json);
    }
    return item;
}

void Box::recoveItems(){
    QJsonObject obj = Box::storage.at(getMemoryIndex()).toObject();
    QJsonArray items = obj["items"].toArray();
    for(int it = 0; it < items.size(); ++it){
        QJsonObject item = items.at(it).toObject();
        if(item["type"].isNull()) continue;
        else{
            try{
                pushItem(Box::jsonItem(item));
            }
            catch(JsonManager::ObjectNotValid){continue;}
        }
    }
}
void Box::updateItems(){
    QJsonArray items;
    for(auto it = begin(); it != end(); ++it)
        items.push_back(it.item()->toJson());
    QJsonObject boxObj = Box::storage.at(getMemoryIndex()).toObject();
    boxObj["items"] = items;
    Box::storage.replace(getMemoryIndex(), boxObj);
}
bool Box::pushItem(Item* el){
    if(type() == Closed) throw BoxClosed();
    if(size == capacity) throw BoxFull();
	size++;
	if(!firstItem){
		firstItem = new ItemNode(el);
		return true;
	}
	ItemNode* last = firstItem;
	while(last && last->next)
		last = last->next;
	last->next = new ItemNode(el);
	return true;
}
Item* Box::popItem(){
    if(type() == Closed) throw BoxClosed();
	if(size == 0) return 0;
	ItemNode* prev = 0;
	ItemNode* last = firstItem;
	while(last && last->next){
		prev = last;
		last = last->next;
	}
	Item* returned = last->item;
	if(prev) prev->next = 0;
	delete last;
	size--;
    if(size == 0) firstItem = 0;
	return returned;
}
Item* Box::popByCode(QString code){
    ItemNode *prev = 0, *last= firstItem;
    bool found = false;
    while(last && !found){
        if(last->item->code.compare(code) == 0)
            found = true;
        else{
            prev = last;
            last = last->next;
        }
    }
    if(last && prev) prev->next = last->next;
    if(last && !prev && last->next) firstItem = last->next;
    else if(last && !prev) firstItem = 0;
    size--;
    Item* founded = last->item;
    delete last;
    return founded;
}

Box::Type Box::type() const{
	if(opened) return Amoeba; //Se la scatola è vuota è possibile inserire qualsiasi elemento
	return Closed;
}
// Iteration Methods
Item* Box::itemAt(int idx){
    if(idx < 0) idx = 0;
    unsigned int index = (unsigned int)idx;
    if(index >= capacity) throw CapacityOverhead();
    if(index >= size) throw SizeOverhead();
	ItemIterator it = begin();
	while(index>0){
		it++;
		index--;
	}
	return it.item();
}
Item* Box::ItemIterator::item(){ return node->getItem(); }
Box::ItemIterator Box::ItemIterator::operator++(int){
	if(node) node = node->getNext();
	return *this;
}
Box::ItemIterator& Box::ItemIterator::operator++(){
	if(node) node = node->getNext();
	return *this;
}
bool Box::ItemIterator::operator==(const ItemIterator& source)const{
	return (node == source.node);
}
bool Box::ItemIterator::operator!=(const ItemIterator& source)const{
	return (node != source.node);
}
Box::ItemIterator Box::begin() const{
	ItemIterator aux;
	aux.node = firstItem;
	return aux;
}
Box::ItemIterator Box::end()const{
	ItemIterator aux;
	aux.node = 0;
	return aux;
}
int Box::countItem()const{
	int counter = 0;
	ItemNode *it = firstItem;
	while(it){
		counter++;
		it = it->next;
	}
	return counter;
}
QVector<Box*> Box::getAll(){
    QVector<Box*> boxes;
    for(int it = 0; it < Box::storage.size(); ++it){
        try{
            Box* box = Box::fromJson(Box::storage.at(it).toObject());
            boxes.push_back(box);
        }catch(JsonManager::ObjectNotValid){}
    }
    return boxes;
}
bool Box::saveAll(){
    return JsonManager::saveFile(Box::storage, Box::path);
}

Box* Box::fromJson(QJsonObject obj){
    if(obj["id"].isNull() ||
            obj["code"].isNull() ||
            obj["color"].isNull() ||
            obj["capacity"].isNull() ||
            obj["size"].isNull() ||
            obj["items"].isNull())
        throw JsonManager::ObjectNotValid();
    return new Box(Box::Color(obj["color"].toInt()),
            obj["code"].toString(),
            (unsigned int)obj["capacity"].toInt(),
            (unsigned int)obj["size"].toInt(),
            obj["id"].toInt()
            );
}
QJsonObject Box::toJson() const{
    QJsonObject obj = JsonManager::toJson();
    obj["code"] = code;
    obj["size"] = (int)size;
    obj["capacity"] = (int)capacity;
    obj["color"] = color;
    QJsonArray items;
    for(auto it = begin(); it != end(); ++it)
        items.push_back(it.item()->toJson());
    obj["items"] = items;
    return obj;
}
bool Box::checkUniq() const{
    QJsonArray *boxes = getStorage();
    for(int it = 0; it < boxes->size(); ++it)
        if(boxes->at(it).toObject()["code"].toString().compare(code) == 0)
            return false;
    return true;
}
QString Box::cssColor() const{
    QString str("white");
    switch(color){
    case(Blue):
        str = "blue";
        break;
    case(Red):
        str = "red";
        break;
    case(Green):
        str = "green";
        break;
    case(Yellow):
        str = "yellow";
        break;
    case(Orange):
        str = "orange";
        break;
    case(Purple):
        str = "purple";
        break;
    }
    return str;
}
QString Box::itemHeader() const{
    return "Codice";
}
QString Box::header(){
    return "Codice, capacità";
}
QString Box::infoLine() const{
    return code + ", " + QString::number(capacity);
}
