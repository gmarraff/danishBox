#ifndef ADMINZONECONTROLLER_H
#define ADMINZONECONTROLLER_H

#include <QObject>
#include "user.h"
#include <QJsonObject>

class AdminZoneController : public QObject
{
    Q_OBJECT
private:
    User* usr;
    int row;
public:
    explicit AdminZoneController(User* usr, int row, QObject *parent = 0);

signals:
    void rowRemoved(int row, QJsonObject obj);
public slots:
    void changeType(int type);
    void removeUser();
};

#endif // ADMINZONECONTROLLER_H
