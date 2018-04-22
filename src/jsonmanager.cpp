#include "jsonmanager.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>
JsonManager::JsonManager(){
    memoryIndex = -1;
}
JsonManager::~JsonManager(){}
QJsonArray JsonManager::loadFile(QString filename){
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly)){
        qWarning("File not opened");
        return QJsonArray();
    }
    QByteArray data = file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    return doc.array();
}
bool JsonManager::saveFile(QJsonArray &arr, QString filename){
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly)){
        qWarning("File not opened");
        return false;
    }
    QJsonDocument data(arr);
    file.write(data.toJson());
    return true;
}
int JsonManager::getNewId() const{
    if(getStorage()->empty()) return 1;
    int maxId = 0;
    QJsonArray *models = getStorage();
    for(int it = 0; it < models->size(); ++it){
        QJsonObject obj = models->at(it).toObject();
        int currentId = obj["id"].toInt();
        if(currentId > maxId) maxId = currentId;
    }
    return (maxId + 1);
}
int JsonManager::getMemoryIndex(bool reload){
    //if(memoryIndex != -1 && !reload) return memoryIndex;
    int it = 0;
    QJsonArray* storage = getStorage();
    for(;it < storage->size();++it){
        if(storage->at(it).toObject()["id"] == this->id){
            memoryIndex = it;
            return it;
        }
    }
    qWarning("Nessun elemento trovato.");
    return -1;
}
void JsonManager::setMemoryIndex(int idx){
    if(idx < 0) idx = -1;
    memoryIndex = idx;
}
QJsonObject JsonManager::toJson() const{
    QJsonObject obj;
    obj["id"] = id;
    return obj;
}

void JsonManager::insert() const{
    QJsonObject obj = toJson();
    obj["id"] = getNewId();
    getStorage()->push_back(obj);
}
QJsonObject JsonManager::remove(){
    int memId = getMemoryIndex();
    QJsonObject obj = getStorage()->takeAt(memId).toObject();
    obj["memId"] = memId;
    return  obj;
}
bool JsonManager::checkUniq() const{
    return true;
}
bool JsonManager::create() const{
    if(checkUniq()) {
        insert();
        return true;
    }
    return false;
}
