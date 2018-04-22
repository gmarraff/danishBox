#include "user.h"
#include "kiddo.h"
#include "grandma.h"
#include "admin.h"
#include <QJsonObject>

QString User::path = "storage/users.json";
QJsonArray User::storage = JsonManager::loadFile(User::path);
QString User::encryptValue(QString val, QCryptographicHash::Algorithm alg = QCryptographicHash::Sha256){
    return QCryptographicHash::hash(val.toLocal8Bit(), alg);
}
User::User(){}
User::User(QString usr, QString psw, QString nm, QString srnm, int nid = -1):
    username(usr), password(psw), name(nm), surname(srnm)
{
    id = nid;
    if(User::storage.isEmpty()) User::storage = loadFile(filename());
}
User* User::fromJson(QJsonObject obj){
    if(obj["id"].isNull()
            || obj["name"].isNull()
            || obj["surname"].isNull()
            || obj["username"].isNull() ||
            obj["password"].isNull()){
        throw JsonManager::ObjectNotValid();
    }
    User *usr = new User(obj["username"].toString(), obj["password"].toString(),
                         obj["name"].toString(), obj["surname"].toString(), obj["id"].toInt());
    return typeSwitch(usr, obj["type"].toInt());
}
User* User::typeSwitch(User* usr, int type){
    switch(type){
    case(Kiddo):
        usr =  new ::Kiddo(usr);
        break;
    case(Grandma):
        usr = new ::Grandma(usr);
        break;
    case(Admin):
        usr = new ::Admin(usr);
        break;
    }
    return usr;
}
QString User::filename() const{
    return QString(User::path);
}
QString User::iconPath() const{
    return "icons/users/default.png";
}
QJsonArray* User::getStorage() const{
    return &User::storage;
}
void User::update(int tp){
    int it = getMemoryIndex();
    QJsonObject obj;
    obj["id"] = this->id;
    obj["name"] = this->name;
    obj["surname"] = this->surname;
    obj["password"] = this->password;
    obj["username"] = this->username;
    obj["type"] = (tp < 0 ? this->role() : tp);
    User::storage.replace(it, QJsonValue(obj));
}
QJsonObject User::remove(){
     int memId = getMemoryIndex();
     QJsonObject obj = User::storage.takeAt(memId).toObject();
     obj["memId"] = memId;
     return  obj;
}
void User::put(int memId, QJsonObject obj){
    User::storage.insert(memId,obj);
}

User* User::findByUsername(QString username){
    auto it = User::storage.constBegin();
    QJsonObject currentUser;
    for(;it != User::storage.constEnd();++it){
        currentUser = (*it).toObject();
        QString uname = currentUser["username"].toString();
        bool usernameEqual = (uname.compare(username, Qt::CaseInsensitive) == 0);
        if(usernameEqual) return User::fromJson(currentUser);
    }
    return 0;
}

User* User::login(QString usr, QString psw){
    auto it = User::storage.constBegin();
    QJsonObject currentUser;
    for(;it != User::storage.constEnd();++it){
        currentUser = (*it).toObject();
        QString uname = currentUser["username"].toString();
        QString pword = currentUser["password"].toString();
        QString encryptedPassword = User::encryptValue(psw);
        bool usernameEqual = (uname.compare(usr, Qt::CaseInsensitive) == 0);
        bool passwordEqual = (pword.compare(encryptedPassword) == 0);
        if(usernameEqual && passwordEqual) return User::fromJson(currentUser);
    }
    return 0;
}
User* User::signup(QString usr, QString psw, QString nm, QString srnm, Type regType){
    if(User::findByUsername(usr)) return 0;
    User* newUser = new User(usr, User::encryptValue(psw), nm, srnm);
    newUser->id = newUser->getNewId();
    QJsonObject ioUser;
    ioUser["id"] = newUser->id;
    ioUser["name"] = newUser->name;
    ioUser["surname"] = newUser->surname;
    ioUser["username"] = newUser->username;
    ioUser["password"] = newUser->password;
    ioUser["type"] = regType;
    storage.append(QJsonValue(ioUser));
    if(saveAll()){
        return typeSwitch(newUser, regType);
    }
    return 0;

}
bool User::saveAll(){
    return JsonManager::saveFile(User::storage, User::path);
}
void User::setName(QString nm){
    if(!nm.isEmpty()) name = nm;
}
void User::setSurname(QString srnm){
    if(!srnm.isEmpty()) surname = srnm;
}
void User::setUsername(QString usr){
    if(!usr.isEmpty()) username = usr;
}
void User::setPassword(QString psw){
    if(!psw.isEmpty()) password = User::encryptValue(psw);
}
QString User::getUsername() const{
    return username;
}
QString User::getName() const{
    return name;
}
QString User::getSurname() const{
    return surname;
}
QVector<User*> User::availableUsers() const{
    return QVector<User*>(1, this->clone());
}
QVector<Item*> User::availableItems() const{
    return QVector<Item*>();
}

User* User::clone() const{
    return new User(username, password, name, surname, id);
}
User::Type User::role() const{
    return ::User::Default;
}
