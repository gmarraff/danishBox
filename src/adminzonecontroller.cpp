#include "adminzonecontroller.h"

AdminZoneController::AdminZoneController(User* usr, int row, QObject *parent) : QObject(parent), usr(usr), row(row)
{

}
void AdminZoneController::changeType(int type){
    usr->update(type);
}
void AdminZoneController::removeUser(){
    emit rowRemoved(row, usr->remove());
}
