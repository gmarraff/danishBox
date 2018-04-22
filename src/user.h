#ifndef USER_H
#define USER_H
#include "jsonmanager.h"
#include "item.h"
#include "box.h"
#include <QCryptographicHash>
#include <QVector>
#include <QObject>

class User : public JsonManager
{
private:
    static QJsonArray storage;
    static QString path;
    static QString encryptValue(QString val, QCryptographicHash::Algorithm alg);
protected:
    QString username, password, name, surname;
public:
    enum Type{Admin, Kiddo, Grandma, Default};
    User();
    User(QString usr, QString psw, QString nm, QString srnm, int id);
    QString filename() const;
    virtual QString iconPath() const;
    virtual Type role() const;
    QJsonArray* getStorage() const;
    void update(int tp = -1);
    QJsonObject remove();
    static void put(int memId, QJsonObject obj);
    static User* findByUsername(QString username);
    static User* login(QString usr, QString psw);
    static User* signup(QString usr, QString psw, QString nm, QString srnm, Type regType);
    static User* fromJson(QJsonObject obj);
    static User* typeSwitch(User* usr, int type);
    static bool saveAll();

    void setUsername(QString);
    void setPassword(QString);
    void setName(QString);
    void setSurname(QString);

    virtual QVector<User*> availableUsers() const;
    virtual QVector<Item*> availableItems() const;
    virtual User* clone() const;

    QString getUsername() const;
    QString getName() const;
    QString getSurname() const;
};

#endif // USER_H
