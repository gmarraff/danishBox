#ifndef JSONMANAGER_H
#define JSONMANAGER_H

#include <QJsonArray>

class JsonManager
{
private:
    int memoryIndex;
protected:
    int id;
public:
    JsonManager();
    virtual ~JsonManager();
    static QJsonArray loadFile(QString filename);
    static bool saveFile(QJsonArray &arr, QString filename);
    virtual QString filename() const = 0;
    virtual QJsonArray* getStorage() const = 0;
    int getNewId() const;
    int getMemoryIndex(bool reload = false);
    void setMemoryIndex(int idx);
    virtual QJsonObject toJson() const;
    virtual void insert() const;
    virtual QJsonObject remove();
    virtual bool create() const;
    virtual bool checkUniq() const;
    class ObjectNotValid{};
    //static int findBy(bool (*compare)(JsonManager*, QJsonObject), QJsonArray &storage);
};

#endif // JSONMANAGER_H
