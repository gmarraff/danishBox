#ifndef NEWBOXVIEW_H
#define NEWBOXVIEW_H

#include <QWidget>
#include <QGridLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include "adminui.h"
class NewBoxView : public AdminUI
{
    Q_OBJECT
private:
    QLineEdit *codeLine, *capacityLine;
    QComboBox *colorCbo;
    QPushButton *insertButton;
    QLabel *resultLabel;
public:
    explicit NewBoxView(User* usr, QWidget *parent = 0);
    void clearFields();
protected:
    void authorizedUI() override;
    void closeEvent(QCloseEvent *event) override;
signals:

public slots:
    void addBox();
};

#endif // NEWBOXVIEW_H
