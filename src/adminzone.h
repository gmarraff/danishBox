#ifndef ADMINZONE_H
#define ADMINZONE_H

#include <QWidget>
#include <QGridLayout>
#include <QVector>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include "user.h"
#include "adminzonecontroller.h"
#include "adminui.h"

class AdminZone : public AdminUI
{
    Q_OBJECT
private:
    static int columnsNumber;
    QPushButton *saveButton;
    QLabel *saveLabel;
    QVector<User*> managedUsers;
    QVector<QComboBox*> cboBoxes;
    QVector<AdminZoneController*> controllers;
    QVector<QPushButton*> removeButtons;
    QVector<QJsonObject> removedUsers;
    QComboBox* roleCboBox(User* usr);
protected:
    void authorizedUI() override;
    void closeEvent(QCloseEvent *event) override;
public:
    explicit AdminZone(User* usr, QWidget *parent = 0);

signals:

public slots:
    void saveUsers();
    void hideRow(int row, QJsonObject usr);
};

#endif // ADMINZONE_H
